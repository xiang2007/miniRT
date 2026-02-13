#include <stdio.h>
#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <math.h>

// Vector operations
struct Vec3 {
    float x, y, z;
    
    __device__ __host__ Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    
    __device__ __host__ Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    __device__ __host__ Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    __device__ __host__ Vec3 operator-() const { return Vec3(-x, -y, -z); }  // ADDED THIS LINE
    __device__ __host__ Vec3 operator*(float t) const { return Vec3(x * t, y * t, z * t); }
    __device__ __host__ Vec3 operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    __device__ __host__ Vec3 operator/(float t) const { return Vec3(x / t, y / t, z / t); }
    
    __device__ __host__ float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    __device__ __host__ float length() const { return sqrtf(x * x + y * y + z * z); }
    __device__ __host__ Vec3 normalize() const { float len = length(); return len > 0 ? Vec3(x / len, y / len, z / len) : Vec3(0, 0, 0); }
    __device__ __host__ Vec3 reflect(const Vec3& n) const { return *this - n * 2.0f * this->dot(n); }
};

__device__ Vec3 refract(const Vec3& uv, const Vec3& n, float etai_over_etat) {
    float cos_theta = fminf((-uv).dot(n), 1.0f);
    Vec3 r_out_perp = (uv + n * cos_theta) * etai_over_etat;
    Vec3 r_out_parallel = n * (-sqrtf(fabsf(1.0f - r_out_perp.dot(r_out_perp))));
    return r_out_perp + r_out_parallel;
}

__device__ float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf((1.0f - cosine), 5.0f);
}

// Material types
enum MaterialType {
    LAMBERTIAN,
    METAL,
    GLASS,
    EMISSIVE
};

// Material structure
struct Material {
    MaterialType type;
    Vec3 albedo;
    float roughness;  // For metal
    float ref_idx;    // For glass
    Vec3 emission;    // For emissive
};

// Sphere structure
struct Sphere {
    Vec3 center;
    float radius;
    Material material;
};

// Ray structure
struct Ray {
    Vec3 origin;
    Vec3 direction;
    
    __device__ Vec3 at(float t) const { return origin + direction * t; }
};

// Hit record
struct HitRecord {
    Vec3 point;
    Vec3 normal;
    float t;
    bool front_face;
    Material material;
    
    __device__ void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = r.direction.dot(outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal * -1.0f;
    }
};

// Check if ray hits sphere
__device__ bool hit_sphere(const Sphere& sphere, const Ray& ray, float t_min, float t_max, HitRecord& rec)
{
    Vec3 oc = ray.origin - sphere.center;
    float a = ray.direction.dot(ray.direction);
    float half_b = oc.dot(ray.direction);
    float c = oc.dot(oc) - sphere.radius * sphere.radius;
    float discriminant = half_b * half_b - a * c;
    
    if (discriminant < 0)
        return false;
    
    float sqrtd = sqrtf(discriminant);
    float root = (-half_b - sqrtd) / a;
    
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max)
            return false;
    }
    
    rec.t = root;
    rec.point = ray.at(rec.t);
    Vec3 outward_normal = (rec.point - sphere.center) / sphere.radius;
    rec.set_face_normal(ray, outward_normal);
    rec.material = sphere.material;
    
    return true;
}

__device__ bool hit_world(Sphere* spheres, int num_spheres, const Ray& ray, float t_min, float t_max, HitRecord& rec)
{
    HitRecord temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    
    for (int i = 0; i < num_spheres; i++) {
        if (hit_sphere(spheres[i], ray, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    
    return hit_anything;
}

__device__ bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered, curandState* rand_state)
{
    if (rec.material.type == LAMBERTIAN) {
        // Diffuse
        float theta = 2.0f * 3.14159265f * curand_uniform(rand_state);
        float phi = acosf(2.0f * curand_uniform(rand_state) - 1.0f);
        Vec3 random_dir(sinf(phi) * cosf(theta), sinf(phi) * sinf(theta), cosf(phi));
        
        Vec3 scatter_direction = rec.normal + random_dir.normalize();
        if (scatter_direction.length() < 0.001f)
            scatter_direction = rec.normal;
        
        scattered.origin = rec.point;
        scattered.direction = scatter_direction.normalize();
        attenuation = rec.material.albedo;
        return true;
    }
    else if (rec.material.type == METAL) {
        // Reflective metal
        Vec3 reflected = r_in.direction.normalize().reflect(rec.normal);
        
        // Add roughness
        float theta = 2.0f * 3.14159265f * curand_uniform(rand_state);
        float phi = acosf(2.0f * curand_uniform(rand_state) - 1.0f);
        Vec3 random_dir(sinf(phi) * cosf(theta), sinf(phi) * sinf(theta), cosf(phi));
        
        scattered.origin = rec.point;
        scattered.direction = (reflected + random_dir * rec.material.roughness).normalize();
        attenuation = rec.material.albedo;
        return scattered.direction.dot(rec.normal) > 0;
    }
    else if (rec.material.type == GLASS) {
        // Glass with reflection and refraction
        attenuation = Vec3(1.0f, 1.0f, 1.0f);
        float refraction_ratio = rec.front_face ? (1.0f / rec.material.ref_idx) : rec.material.ref_idx;
        
        Vec3 unit_direction = r_in.direction.normalize();
        float cos_theta = fminf((-unit_direction).dot(rec.normal), 1.0f);
        float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);
        
        bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
        Vec3 direction;
        
        if (cannot_refract || schlick(cos_theta, refraction_ratio) > curand_uniform(rand_state))
            direction = unit_direction.reflect(rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        
        scattered.origin = rec.point;
        scattered.direction = direction;
        return true;
    }
    
    return false;
}

__device__ Vec3 ray_color(Ray& r, Sphere* spheres, int num_spheres, curandState* rand_state)
{
    Vec3 color(1.0f, 1.0f, 1.0f);
    Vec3 accumulated_emission(0.0f, 0.0f, 0.0f);
    
    for (int bounce = 0; bounce < 50; bounce++) {
        HitRecord rec;
        
        if (hit_world(spheres, num_spheres, r, 0.001f, 1e10f, rec)) {
            // Add emission
            accumulated_emission = accumulated_emission + color * rec.material.emission;
            
            if (rec.material.type == EMISSIVE) {
                return accumulated_emission;
            }
            
            Ray scattered;
            Vec3 attenuation;
            
            if (scatter(r, rec, attenuation, scattered, rand_state)) {
                color = color * attenuation;
                r = scattered;
                
                // Russian roulette termination
                float p = fmaxf(color.x, fmaxf(color.y, color.z));
                if (curand_uniform(rand_state) > p)
                    break;
                color = color / p;
            } else {
                break;
            }
        } else {
            // Sky gradient
            Vec3 unit_direction = r.direction.normalize();
            float t = 0.5f * (unit_direction.y + 1.0f);
            Vec3 sky = Vec3(1.0f, 1.0f, 1.0f) * (1.0f - t) + Vec3(0.5f, 0.7f, 1.0f) * t;
            return accumulated_emission + color * sky * 0.8f;
        }
    }
    
    return accumulated_emission;
}

__global__ void render_init(curandState* rand_state, int width, int height)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (x >= width || y >= height)
        return;
    
    int idx = y * width + x;
    curand_init(1984 + idx, 0, 0, &rand_state[idx]);
}

__global__ void render_kernel(unsigned char* pixels, int width, int height, Sphere* spheres, int num_spheres, Vec3 camera_pos, int samples_per_pixel, curandState* rand_state)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (x >= width || y >= height)
        return;
    
    int idx = y * width + x;
    curandState local_rand_state = rand_state[idx];
    
    Vec3 color(0.0f, 0.0f, 0.0f);
    
    // Anti-aliasing with multiple samples
    for (int s = 0; s < samples_per_pixel; s++) {
        float aspect_ratio = (float)width / (float)height;
        float u = (2.0f * (x + curand_uniform(&local_rand_state)) / width - 1.0f) * aspect_ratio;
        float v = 1.0f - 2.0f * (y + curand_uniform(&local_rand_state)) / height;
        
        Ray ray;
        ray.origin = camera_pos;
        ray.direction = Vec3(u, v, -1.0f).normalize();
        
        color = color + ray_color(ray, spheres, num_spheres, &local_rand_state);
    }
    
    color = color / (float)samples_per_pixel;
    
    // Gamma correction
    color.x = sqrtf(color.x);
    color.y = sqrtf(color.y);
    color.z = sqrtf(color.z);
    
    // Write pixel
    int pixel_idx = (y * width + x) * 3;
    pixels[pixel_idx + 0] = (unsigned char)(fminf(255.0f, fmaxf(0.0f, color.x * 255.0f)));
    pixels[pixel_idx + 1] = (unsigned char)(fminf(255.0f, fmaxf(0.0f, color.y * 255.0f)));
    pixels[pixel_idx + 2] = (unsigned char)(fminf(255.0f, fmaxf(0.0f, color.z * 255.0f)));
    
    rand_state[idx] = local_rand_state;
}

void write_ppm(const char* filename, unsigned char* pixels, int width, int height)
{
    FILE* f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    fwrite(pixels, 1, width * height * 3, f);
    fclose(f);
    printf("Image saved to %s\n", filename);
}

int main()
{
    const int width = 15360;
    const int height = 8460;
    const int samples_per_pixel = 10000;
    const int num_spheres = 9;
    
    unsigned char* h_pixels = (unsigned char*)malloc(width * height * 3);
    
    // Create awesome scene with glass spheres
    Sphere h_spheres[9];
    
    // Ground (large diffuse sphere)
    h_spheres[0].center = Vec3(0.0f, -1000.0f, -5.0f);
    h_spheres[0].radius = 1000.0f;
    h_spheres[0].material.type = LAMBERTIAN;
    h_spheres[0].material.albedo = Vec3(0.5f, 0.5f, 0.5f);
    h_spheres[0].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Large glass sphere (center)
    h_spheres[1].center = Vec3(0.0f, 1.0f, -5.0f);
    h_spheres[1].radius = 1.0f;
    h_spheres[1].material.type = GLASS;
    h_spheres[1].material.ref_idx = 1.5f;
    h_spheres[1].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Metal sphere (left)
    h_spheres[2].center = Vec3(-2.5f, 1.0f, -5.0f);
    h_spheres[2].radius = 1.0f;
    h_spheres[2].material.type = METAL;
    h_spheres[2].material.albedo = Vec3(0.8f, 0.6f, 0.2f);
    h_spheres[2].material.roughness = 0.0f;
    h_spheres[2].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Glass sphere (right)
    h_spheres[3].center = Vec3(2.5f, 1.0f, -5.0f);
    h_spheres[3].radius = 1.0f;
    h_spheres[3].material.type = GLASS;
    h_spheres[3].material.ref_idx = 1.5f;
    h_spheres[3].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Small diffuse red
    h_spheres[4].center = Vec3(-1.0f, 0.3f, -3.0f);
    h_spheres[4].radius = 0.3f;
    h_spheres[4].material.type = LAMBERTIAN;
    h_spheres[4].material.albedo = Vec3(1.0f, 0.2f, 0.2f);
    h_spheres[4].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Small blue glass
    h_spheres[5].center = Vec3(1.0f, 0.3f, -3.0f);
    h_spheres[5].radius = 0.3f;
    h_spheres[5].material.type = GLASS;
    h_spheres[5].material.ref_idx = 1.8f;
    h_spheres[5].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Light source (emissive)
    h_spheres[6].center = Vec3(0.0f, 5.0f, -3.0f);
    h_spheres[6].radius = 1.5f;
    h_spheres[6].material.type = EMISSIVE;
    h_spheres[6].material.emission = Vec3(4.0f, 4.0f, 4.0f);
    
    // Polished metal
    h_spheres[7].center = Vec3(0.0f, 0.5f, -2.5f);
    h_spheres[7].radius = 0.5f;
    h_spheres[7].material.type = METAL;
    h_spheres[7].material.albedo = Vec3(0.9f, 0.9f, 0.9f);
    h_spheres[7].material.roughness = 0.05f;
    h_spheres[7].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    // Diamond-like (high refractive index)
    h_spheres[8].center = Vec3(-1.5f, 0.4f, -4.0f);
    h_spheres[8].radius = 0.4f;
    h_spheres[8].material.type = GLASS;
    h_spheres[8].material.ref_idx = 2.4f;
    h_spheres[8].material.emission = Vec3(0.0f, 0.0f, 0.0f);
    
    Vec3 camera_pos(0.0f, 1.5f, 1.0f);
    
    // Allocate device memory
    unsigned char* d_pixels;
    Sphere* d_spheres;
    curandState* d_rand_state;
    
    cudaMalloc(&d_pixels, width * height * 3);
    cudaMalloc(&d_spheres, num_spheres * sizeof(Sphere));
    cudaMalloc(&d_rand_state, width * height * sizeof(curandState));
    
    cudaMemcpy(d_spheres, h_spheres, num_spheres * sizeof(Sphere), cudaMemcpyHostToDevice);
    
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((width + 15) / 16, (height + 15) / 16);
    
    printf("Rendering %dx%d image with %d samples per pixel...\n", width, height, samples_per_pixel);
    printf("Glass spheres with reflections and refractions!\n");
    
    // Initialize random states
    render_init<<<numBlocks, threadsPerBlock>>>(d_rand_state, width, height);
    cudaDeviceSynchronize();
    
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);
    
    render_kernel<<<numBlocks, threadsPerBlock>>>(d_pixels, width, height, d_spheres, num_spheres, camera_pos, samples_per_pixel, d_rand_state);
    
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(err));
        return 1;
    }
    
    cudaMemcpy(h_pixels, d_pixels, width * height * 3, cudaMemcpyDeviceToHost);
    
    printf("Render time: %.2f ms (%.2f seconds)\n", milliseconds, milliseconds / 1000.0f);
    
    write_ppm("output.ppm", h_pixels, width, height);
    
    cudaFree(d_pixels);
    cudaFree(d_spheres);
    cudaFree(d_rand_state);
    free(h_pixels);
    
    return 0;
}