#include "function.h"
void **readP2(FILE *file, int *column, int *row,int *intensity, char *first_line)
{
	char *line = (char *)malloc(sizeof(char) * 10000);
	int ok = 1;
	void **mat;
	*row = 0;
	*column = 0;
	int h = 0, w = 0;
	*intensity = 0;
	int val = 0;
	while (fgets(line, 10000, file)) {
		if (strlen(line) >= 1)
			if (line[0] != '#') {
				const char s[4] = "  \n\t";
				char *number;
				number = strtok(line, s);
				while (number) {
					if (*column == 0) {
						*column = atoi(number);
					}
					else if (*row == 0) {
						*row = atoi(number);
					} else {
						if (*intensity == 0) {
							*intensity = atoi(number);
						} else {
							if (ok)
								dynamically_array(&mat, *row,*column, first_line);
							ok = 0;
							if (w < *column) {
								val = atoi(number);
								((unsigned char **)mat)[h][w] = val;
								w++;
							} else if(h < *row - 1) {
								h++;
								w = 1;
								val = atoi(number);
								((unsigned char **)mat)[h][0] = val;
							}
						}
					}
					number = strtok(0, s);
				}
			}
	}
	free(line);
	return mat;
}

void **readP3(FILE *file, int *column, int *row, int *intensity, char *first_line)
{
	char *line = (char *)malloc(sizeof(char) * 10000);
	void **matrix_rgb;
	int ok = 1, val = 0;
	*row = 0;
	*column = 0;
	*intensity = 0;
	int h = 0, w = 0;
	while (fgets(line, 10000, file)) {
		if (strlen(line) >= 1)
			if (line[0] != '#') {
				const char s[4] = "  \n\t";
				char *number;
				number = strtok(line, s);
				while (number) {
					if (*column == 0) {
						*column = atoi(number);
					} else if (*row == 0) {
						*row = atoi(number);
					} else {
						if (*intensity == 0) {
							*intensity = atoi(number);
						} else {
							if (ok)
								dynamically_array(&matrix_rgb, *row,
												  *column, first_line);
							ok = 0;
							if (w < *column) {
								val = atoi(number);
								((rgb **)matrix_rgb)[h][w].R = val;
								number = strtok(0, s);
								if (number == 0) {
									fgets(line, 10000, file);
									number = strtok(line, s);
								}
								val = atoi(number);
								((rgb **)matrix_rgb)[h][w].G = val;
								number = strtok(0, s);
								if (number == 0) {
									fgets(line, 10000, file);
									number = strtok(line, s);
								}
								val = atoi(number);
								((rgb **)matrix_rgb)[h][w].B = val;
								w++;
							} else if (h < *row - 1) {
								h++;
								w = 1;
								val = atoi(number);
								((rgb **)matrix_rgb)[h][0].R = val;
								number = strtok(0, s);
								if (number == 0) {
									fgets(line, 10000, file);
									number = strtok(line, s);
								}
								val = atoi(number);
								((rgb **)matrix_rgb)[h][0].G = val;
								number = strtok(0, s);
								if (number == 0) {
									fgets(line, 10000, file);
									number = strtok(line, s);
								}
								val = atoi(number);
								((rgb **)matrix_rgb)[h][0].B = val;
							}
						}
					}
					number = strtok(0, s);
				}
			}
	}

	free(line);
	return matrix_rgb;
}

void **readP5(FILE *file, char *x, int *column, int *row,
			  int *intensity, char *first_line)
{
	char *line = (char *)malloc(sizeof(char) * 10000);
	void **matrix;
	*row = 0;
	int byte_counter = 0;
	*column = 0;
	int h = 0, w = 0;
	*intensity = 0;
	while ((fgets(line, 10000, file) != NULL) && *intensity == 0) {
		byte_counter += strlen(line);
		if (strlen(line) >= 1 && line[0] != '#') {
			const char s[4] = "  \n\t";
			char *number;
			number = strtok(line, s);
			while (number && *intensity == 0) {
				if (*column == 0) {
					*column = atoi(number);
				} else if (*row == 0) {
					*row = atoi(number);
				} else if (*intensity == 0) {
					*intensity = atoi(number);
				}
				number = strtok(0, s);
			}
		}
	}
	fclose(file);
	FILE *in = fopen(x, "rb");
	fseek(in, byte_counter, SEEK_SET);
	unsigned char cp;
	dynamically_array(&matrix, *row, *column, first_line);
	for (h = 0; h < *row; h++)
		for (w = 0; w < *column; w++) {
			fread(&cp, 1, 1, in);
			memcpy((*(matrix + h) + w), &cp, 1);
		}
	fclose(in);
	free(line);
	return matrix;
}

void **readP6(FILE *file, char *x, int *column, int *row,
			  int *intensity, char *first_line)
{
	char *line = (char *)malloc(sizeof(char) * 10000);
	void **matrix;
	*row = 0;
	int byte_counter = 0;
	*column = 0;
	int h = 0, w = 0;
	*intensity = 0;
	while ((fgets(line, 100000, file) != NULL) && *intensity == 0) {
		byte_counter += strlen(line);
		if (strlen(line) >= 1)
			if (line[0] != '#') {
				const char s[4] = "  \n\t";
				char *number;
				number = strtok(line, s);
				while (number && *intensity == 0) {
					if (*column == 0) {
						*column = atoi(number);
					} else if (*row == 0) {
						*row = atoi(number);
					} else if (*intensity == 0)
						*intensity = atoi(number);
					number = strtok(0, s);
				}
			}
	}
	fclose(file);
	FILE *in = fopen(x, "rb");
	fseek(in, byte_counter, SEEK_SET);
	unsigned char cp;
	dynamically_array(&matrix, *row, *column, first_line);
	for (h = 0; h < *row; h++)
		for (w = 0; w < *column; w++) {
			fread(&cp, 1, 1, in);
			((rgb **)matrix)[h][w].R = cp;
			fread(&cp, 1, 1, in);
			((rgb **)matrix)[h][w].G = cp;
			fread(&cp, 1, 1, in);
			((rgb **)matrix)[h][w].B = cp;
		}
	fclose(in);
	free(line);
	return matrix;
}

void **load(char *x, int *column, int *row, int *intensity, char *first_line)
{
	void **matrix;
	FILE *file = fopen(x, "r");
	if (strcmp(first_line, "P2") == 0) {
		matrix = (void **)readP2(file, column, row, intensity, first_line);
		fclose(file);
	}
	if (strcmp(first_line, "P3") == 0) {
		matrix = (void **)readP3(file, column, row, intensity, first_line);
		fclose(file);
	}
	if (strcmp(first_line, "P5") == 0) {
		matrix = (void **)readP5(file, x, column, row, intensity, first_line);
	}
	if (strcmp(first_line, "P6") == 0) {
		matrix = (void **)readP6(file, x, column, row, intensity, first_line);
	}
	return matrix;
}
