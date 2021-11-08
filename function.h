#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
typedef struct {
	unsigned char R, G, B;
} rgb;
void dynamically_array(void ***mat, int row, int column, char *first_line);
void **readP2(FILE *file, int *column, int *row,int *intensity, char *first_line);
void **readP3(FILE *file, int *column, int *row, int *intensity, char *first_line);
void **readP5(FILE *file, char *x, int *column, int *row,int *intensity, char *first_line);
void **readP6(FILE *file, char *x, int *column, int *row,int *intensity, char *first_line);
void **load(char *x, int *column, int *row, int *intensity, char *first_line);
void swap(int *x1, int *y1, int *x2, int *y2);
int check(char *a, char *b, char *c, char *d, int column, int row);
int check_rotate_square(int x1, int y1, int x2, int y2, char *angle);
void rotate_matrix(void **matrix, int x1, int y1, int x2, int y2, char *angle, char *first_line);
void rotate_matrix_rgb(void **matrix, int x1, int y1, int x2, int y2, char *angle, char *first_line);
void rotate_square(void **mat, int x1, int y1, int x2,int y2, char *angle, char *first_line);
void free_matrix(void **mat, int row);
void **rotate_all_rgb(void **mat, int x2, int y2, char *angle, int *column, int *row, char *first_line);
void **rotate_all_char(void **mat, int x2, int y2, char *angle, int *column, int *row, char *first_line);
void **rotate_all(void **mat, int x2, int y2,char *angle, char *first_line, int *column, int *row);
int check_rotate_all(int x1, int y1, int x2, int y2,char *angle, int column, int row);
void default_size(int *x1, int *y1, int *x2, int *y2, int *column, int *row);
void **crop_char(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line);
void **crop_rgb(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line);
void **crop_all(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line);
void grayscale(void **mat, int x1, int y1, int x2, int y2, char *first_line);
void min_value(double *value, int intensity);
void sepia(void **mat, int x1, int y1, int x2, int y2, char *first_line, int intensity);
void save_rgb(void **mat, int row, int column, char *file, char *type, int intensity);
void save_char(void **mat, int row, int column, char *file, char *type, int intensity);
void save(void **mat, int h, int w, char *line, char *file, char *type, int power);
void verification_save(void **matrix, int row, int column, char *first_line, char *file_name, char *type, int intensity, int open);
void verification_sepia(void **matrix, int x1, int y1, int x2, int y2, char *first_line, int open, int intensity);
void verification_grayscale(void **mat, int x1, int y1, int x2, int y2, char *first_line, int open);
void verification_crop(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line, int open);


