# Matrix functions that I currently have

# Matrix

```c
	t_matrix	*create_matrix(int row, int col)
	void		free_matrix(t_matrix *m)
	int			compare_matrix(t_matrix *m1, t_matrix *m2)
	void		print_mat(t_matrix *m);
```

# Matrix calculation

```c
	t_matrix	*transpose_matrix(t_matrix *m1)
	int			determinant(t_matrix *m)
	int			minor_matrix(t_matrix *m, int row, int col)
	t_matrix	*mult_matrix_w_tuple(t_matrix *m1, t_tuple *t)
	t_matrix	*mult_matrix(t_matrix *m1, t_matrix *m2);
	void		identity_matrix(t_matrix **m)
	t_matrix	*inverse_matrix(t_matrix *m)
	int			cofactor(t_matrix *m1, int row, int col)
	t_matrix	*dynamic_mult_matrix(t_matrix *m1, t_matrix *m2)
	t_matrix	*sub_matrix(t_matrix *m, int row, int col)
```

# Matrix conversion
```c
		
```