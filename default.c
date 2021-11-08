#include "function.h"
void dynamically_array(void ***mat, int row, int column, char *first_line)
{
	int h;
	if ((strcmp(first_line, "P3") == 0) || (strcmp(first_line, "P6") == 0)) {
		*mat = (void **)malloc(row * sizeof(rgb *));
		for (h = 0; h < row; h++)
			*((*mat) + h) = malloc(column * sizeof(rgb));
	} else {
		*mat = (void **)malloc(row * sizeof(unsigned char *));
		for (h = 0; h < row; h++)
			*((*mat) + h) = malloc(column * sizeof(unsigned char));
	}
}

void default_size(int *x1, int *y1, int *x2, int *y2, int *column, int *row)
{
	*x1 = 0;
	*y1 = 0;
	*x2 = *column;
	*y2 = *row;
}

void save(void **mat, int h, int w, char *line, char *file, char *type, int power)
{
	if ((strcmp(line, "P3") == 0) || (strcmp(line, "P6") == 0))
		save_rgb(mat, h, w, file, type, power);
	else
		save_char(mat, h, w, file, type, power);
}

void verification_save(void **matrix, int row, int column, char *first_line, char *file_name, char *type, int intensity, int open)
{
	if (open != 0)
		save(matrix, row, column, first_line, file_name, type, intensity);
	else
		printf("No image loaded\n");
}

void verification_sepia(void **matrix, int x1, int y1, int x2, int y2, char *first_line, int open, int intensity)
{
	if (open != 0)
		sepia(matrix, x1, y1, x2, y2, first_line, intensity);
	else
		printf("No image loaded\n");
}

void verification_grayscale(void **mat, int x1, int y1, int x2, int y2, char *first_line, int open)
{
	if (open != 0)
		grayscale(mat, x1, y1, x2, y2, first_line);
	else
		printf("No image loaded\n");
}

void verification_crop(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line, int open)
{
	if (open != 0)
		matrix = crop_all(matrix, x1, y1, x2, y2, column, row, first_line);
	else
		printf("No image loaded\n");
}
