#include "function.h"
int check_rotate_square(int x1, int y1, int x2, int y2, char *angle)
{
	int distance_height, distance_width;
	int angle_number = atoi(angle);
	if (angle_number < 0)
		angle_number = -atoi(angle);
	distance_height = y2 - y1;
	distance_width = x2 - x1;
	if (angle_number % 90 == 0) {
		if (angle_number / 90 == 1 || angle_number / 90 == 2) {
			if (distance_width == distance_height)
				return 1;
			else
				printf("The selection must be square\n");
		} else if (angle_number / 90 == 3 || angle_number / 90 == 4) {
			if (distance_width == distance_height)
				return 1;
			else
				printf("The selection must be square\n");
		} else if (angle_number / 90 == 0) {
			if (distance_width == distance_height)
				return 1;
			else
				printf("The selection must be square\n");
		}
	} else
		printf("Unsupported rotation angle\n");
	return 0;
}

void rotate_matrix(void **matrix, int x1, int y1, int x2, int y2, char *angle, char *first_line)
{
	void **mat;
	int h, w, ok = 0, number_rotate;
	unsigned char aux;
	int n = (x2 - x1);
	dynamically_array(&mat, n, n, first_line);
	for (h = y1; h < y2; h++)
		for (w = x1; w < x2; w++)
			((unsigned char **)mat)[h - y1][w - x1] = ((unsigned char **)matrix)[h][w];
	if (atoi(angle) < 0)
		number_rotate = -atoi(angle) / 90;
	else
		number_rotate = atoi(angle) / 90;
	while (ok != number_rotate) {
		for (h = 0; h < n + 1 / 2 && atoi(angle) > 0; h++)
			for (w = h; w < n - h - 1; w++) {
				aux = ((unsigned char **)mat)[h][w];
				((unsigned char **)mat)[h][w] = ((unsigned char **)mat)[n - 1 - w][h];
				((unsigned char **)mat)[n - 1 - w][h] = ((unsigned char **)mat)[n - 1 - h][n - 1 - w];
				((unsigned char **)mat)[n - 1 - h][n - 1 - w] = ((unsigned char **)mat)[w][n - 1 - h];
				((unsigned char **)mat)[w][n - 1 - h] = aux;
			}
		for (h = 0; h < n / 2 && atoi(angle) < 0; h++)
			for (w = h; w < n - h - 1; w++) {
				aux = ((unsigned char **)mat)[h][w];
				((unsigned char **)mat)[h][w] = ((unsigned char **)mat)[w][n - h - 1];
				((unsigned char **)mat)[w][n - h - 1] = ((unsigned char **)mat)[n - h - 1][n - w - 1];
				((unsigned char **)mat)[n - h - 1][n - w - 1] = ((unsigned char **)mat)[n - w - 1][h];
				((unsigned char **)mat)[n - w - 1][h] = aux;
			}
		ok++;
	}
	for (h = y1; h < y2; h++)
		for (w = x1; w < x2; w++)
			((unsigned char **)matrix)[h][w] = ((unsigned char **)mat)[h - y1][w - x1];//revin la matricea initiala
	if (ok == number_rotate)
		printf("Rotated %s\n", angle);
}

void rotate_matrix_rgb(void **matrix, int x1, int y1, int x2, int y2, char *angle, char *first_line)
{
	void **mat;
	int h, w, ok = 0, number_rotate;
	rgb aux;
	int n = (x2 - x1);
	dynamically_array(&mat, n, n, first_line);
	for (h = y1; h < y2; h++)
		for (w = x1; w < x2; w++)
			((rgb **)mat)[h - y1][w - x1] = ((rgb **)matrix)[h][w];

	if (atoi(angle) < 0)
		number_rotate = -atoi(angle) / 90;
	else
		number_rotate = atoi(angle) / 90;
	while (ok != number_rotate) {
		for (h = 0; h < n / 2 && atoi(angle) > 0; h++)
			for (w = h; w < n - h - 1; w++) {
				aux = ((rgb **)mat)[h][w];
				((rgb **)mat)[h][w] = ((rgb **)mat)[n - 1 - w][h];
				((rgb **)mat)[n - 1 - w][h] = ((rgb **)mat)[n - 1 - h][n - 1 - w];
				((rgb **)mat)[n - 1 - h][n - 1 - w] = ((rgb **)mat)[w][n - 1 - h];
				((rgb **)mat)[w][n - 1 - h] = aux;
			}
		for (h = 0; h < n / 2 && atoi(angle) < 0; h++)
			for (w = h; w < n - h - 1; w++) {
				aux = ((rgb **)mat)[h][w];
				((rgb **)mat)[h][w] = ((rgb **)mat)[w][n - h - 1];
				((rgb **)mat)[w][n - h - 1] = ((rgb **)mat)[n - h - 1][n - w - 1];
				((rgb **)mat)[n - h - 1][n - w - 1] = ((rgb **)mat)[n - w - 1][h];
				((rgb **)mat)[n - w - 1][h] = aux;
			}
		ok++;
	}
	for (h = y1; h < y2; h++)
		for (w = x1; w < x2; w++)
			((rgb **)matrix)[h][w] = ((rgb **)mat)[h - y1][w - x1];//copiez elem in cea veche
	printf("Rotated %s\n", angle);
}

void rotate_square(void **mat, int x1, int y1, int x2,
				   int y2, char *angle, char *first_line)
{
	if ((strcmp(first_line, "P3") == 0) || (strcmp(first_line, "P6") == 0))
		rotate_matrix_rgb(mat, x1, y1, x2, y2, angle, first_line);
	else
		rotate_matrix(mat, x1, y1, x2, y2, angle, first_line);
}

void free_matrix(void **mat, int row)
{
	for (int i = 0; i < row; i++) {
		free(mat[i]);
	}
	free(mat);
}

void **rotate_all_rgb(void **mat, int x2, int y2, char *angle, int *column, int *row, char *first_line)
{
	void **matrix;
	int aux;
	if (atoi(angle) == 90 || atoi(angle) == -270) {
		aux = *row;
		*row = *column;
		*column = aux;
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < x2; i++)
			for (int j = 0; j < y2; j++)
				((rgb **)matrix)[i][j] = ((rgb **)mat)[y2 - j - 1][i];
	}
	if (atoi(angle) == 180 || atoi(angle) == -180) {
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < y2; i++)
			for (int j = 0; j < x2; j++)
				((rgb **)matrix)[i][j] = ((rgb **)mat)[y2 - 1 - i][x2 - j - 1];
	}
	if (atoi(angle) == 270 || atoi(angle) == -90) {
		aux = *row;
		*row = *column;
		*column = aux;
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < x2; i++)
			for (int j = 0; j < y2; j++)
				((rgb **)matrix)[i][j] = ((rgb **)mat)[j][x2 - i - 1];
	}
	if (atoi(angle) == 360 || atoi(angle) == -360 || atoi(angle) == 0) {
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < y2; i++)
			for (int j = 0; j < x2; j++)
				((rgb **)matrix)[i][j] = ((rgb **)mat)[i][j];
	}
	return matrix;
}

void **rotate_all_char(void **mat, int x2, int y2, char *angle, int *column, int *row, char *first_line)
{
	void **matrix;
	int aux;
	if (atoi(angle) == 90 || atoi(angle) == -270) {
		aux = *row;
		*row = *column;
		*column = aux;
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < x2; i++)
			for (int j = 0; j < y2; j++)
				((unsigned char **)matrix)[i][j] = ((unsigned char **)mat)[y2 - j - 1][i];
	}
	if (atoi(angle) == 180 || atoi(angle) == -180) {
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < y2; i++)
			for (int j = 0; j < x2; j++)
				((unsigned char **)matrix)[i][j] = ((unsigned char **)mat)[y2 - 1 - i][x2 - j - 1];
	}
	if (atoi(angle) == 270 || atoi(angle) == -90) {
		aux = *row;
		*row = *column;
		*column = aux;
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < x2; i++)
			for (int j = 0; j < y2; j++)
				((unsigned char **)matrix)[i][j] = ((unsigned char **)mat)[j][x2 - i - 1];
	}
	if (atoi(angle) == 360 || atoi(angle) == -360 || atoi(angle) == 0) {
		dynamically_array(&matrix, *row, *column, first_line);
		for (int i = 0; i < y2; i++)
			for (int j = 0; j < x2; j++)
				((unsigned char **)matrix)[i][j] = ((unsigned char **)mat)[i][j];
	}
	return matrix;
}

void **rotate_all(void **mat, int x2, int y2,
				  char *angle, char *first_line, int *column, int *row)
{
	printf("Rotated %s\n", angle);
	if ((strcmp(first_line, "P3") == 0) || (strcmp(first_line, "P6") == 0))
		mat = rotate_all_rgb(mat, x2, y2, angle, column, row, first_line);
	else
		mat = rotate_all_char(mat, x2, y2, angle, column, row, first_line);

	return mat;
}

int check_rotate_all(int x1, int y1, int x2, int y2,
					 char *angle, int column, int row)
{
	int angle_number = atoi(angle);
	if (angle_number < 0)
		angle_number = -atoi(angle);
	if (x1 == 0 && x2 == column && y1 == 0 && y2 == row) {
		if (angle_number % 90 == 0) {
			if (angle_number / 90 == 1 || angle_number / 90 == 2)
				return 1;
			else if (angle_number / 90 == 3 || angle_number / 90 == 4)
				return 1;
			else if (angle_number / 90 == 0)
				return 1;
			else
				printf("Unsupported rotation angle\n");
		}
	}
	return 0;
}