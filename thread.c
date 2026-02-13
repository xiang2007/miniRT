#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_arg
{
	int	i;
	pthread_mutex_t	lock;
}	t_arg;

void	*loop(void *arg)
{
	t_arg	*ag = arg;
	int i = ag->i;
	pthread_mutex_lock(&ag->lock);
	printf("Thread %d start\n", i);
	int j = 0;
	while (j < 50000000)
		j++;
	usleep(i * 1000);
	printf("Thread %d finished\n", i);
	pthread_mutex_unlock(&ag->lock);
	free(ag);
	return (NULL);
}

int	main()
{
	pthread_t	*thread;
	pthread_mutex_t	mutex;

	thread = malloc(sizeof(pthread_t) * 1000);
	pthread_mutex_init(&mutex, NULL);
	if (!thread)
		return 1;
	for (int i = 0; i < 1000; i++) {
		t_arg *ag = malloc(sizeof(t_arg));
		if (!ag)
			return (1);
		ag->i = i;
		ag->lock = mutex;
		if (pthread_create(&thread[i], NULL, loop, ag) != 0)
			for (int j = i; j < i; j--)
				pthread_join(thread[j], NULL);
	}
	for (int i = 0; i < 1000; i++)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}