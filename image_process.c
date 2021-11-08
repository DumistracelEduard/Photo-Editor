#include "function.h"
void **crop_char(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line)
{
	printf("Image cropped\n");
	void **mat;
	int i, j;
	int row_crop = *y2 - *y1;
	int column_crop = *x2 - *x1;
	dynamically_array(&mat, row_crop, column_crop, first_line);
	for (i = *y1; i < *y2; i++)
		for (j = *x1; j < *x2; j++) {
			((unsigned char **)mat)[i - *y1][j - *x1] = ((unsigned char **)matrix)[i][j];
		}
	free_matrix(matrix, *row);
	*column = column_crop;
	*row = row_crop;
	*x1 = 0;
	*y1 = 0;
	*x2 = *column;
	*y2 = *row;
	return mat;
}
void **crop_rgb(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line)
{
	printf("Image cropped\n");
	void **mat;
	int i, j;
	int row_crop = *y2 - *y1;
	int column_crop = *x2 - *x1;
	dynamically_array(&mat, row_crop, column_crop, first_line);
	for (i = *y1; i < *y2; i++)
		for (j = *x1; j < *x2; j++) {
			((rgb **)mat)[i - *y1][j - *x1].R = ((rgb **)matrix)[i][j].R;
			((rgb **)mat)[i - *y1][j - *x1].G = ((rgb **)matrix)[i][j].G;
			((rgb **)mat)[i - *y1][j - *x1].B = ((rgb **)matrix)[i][j].B;
		}
	free_matrix(matrix, *row);
	*column = column_crop;
	*row = row_crop;
	*x1 = 0;
	*y1 = 0;
	*x2 = *column;
	*y2 = *row;
	return mat;
}
void **crop_all(void **matrix, int *x1, int *y1, int *x2, int *y2, int *column, int *row, char *first_line)
{
	if ((strcmp(first_line, "P3") == 0) || (strcmp(first_line, "P6") == 0))
		matrix = crop_rgb(matrix, x1, y1, x2, y2, column, row, first_line);
	else
		matrix = crop_char(matrix, x1, y1, x2, y2, column, row, first_line);

	return matrix;
}

void grayscale(void **mat, int x1, int y1, int x2, int y2, char *first_line)
{//aplic grayscale
	int i, j;
	double value1, value2, value3, value;
	if ((strcmp(first_line, "P3") != 0) && (strcmp(first_line, "P6") != 0))
		printf("Grayscale filter not available\n");
	else {
		printf("Grayscale filter applied\n");
		for (i = y1; i < y2; i++)
			for (j = x1; j < x2; j++) {
				value1 = (double)((rgb **)mat)[i][j].R;
				value2 = (double)((rgb **)mat)[i][j].G;
				value3 = (double)((rgb **)mat)[i][j].B;
				value = (value1 + value2 + value3) / 3;
				((rgb **)mat)[i][j].R = round(value);
				((rgb **)mat)[i][j].G = round(value);
				((rgb **)mat)[i][j].B = round(value);
			}
	}
}
void min_value(double *value, int intensity)
{
	if (*value > intensity)
		*value = intensity;
}
void sepia(void **mat, int x1, int y1, int x2, int y2, char *first_line, int intensity)
{//aplic sepia
	int i, j;
	double value1, value2, value3, newRed, newGreen, newBlue;
	if ((strcmp(first_line, "P3") != 0) && (strcmp(first_line, "P6") != 0))
		printf("Sepia filter not available\n");
	else {
		printf("Sepia filter applied\n");
		for (i = y1; i < y2; i++)
			for (j = x1; j < x2; j++) {
				value1 = (double)((rgb **)mat)[i][j].R;
				value2 = (double)((rgb **)mat)[i][j].G;
				value3 = (double)((rgb **)mat)[i][j].B;
				newRed = 0.393 * value1 + 0.769 * value2 + 0.189 * value3;
				min_value(&newRed, intensity);
				newGreen = 0.349 * value1 + 0.686 * value2 + 0.168 * value3;
				min_value(&newGreen, intensity);
				newBlue = 0.272 * value1 + 0.534 * value2 + 0.131 * value3;
				min_value(&newBlue, intensity);
				((rgb **)mat)[i][j].R = round(newRed);
				((rgb **)mat)[i][j].G = round(newGreen);
				((rgb **)mat)[i][j].B = round(newBlue);
			}
	}
}