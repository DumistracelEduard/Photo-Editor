#include "function.h"
int main(void)
{
	int x1, x2, y1, y2, column = 0, row = 0, intensity = 0;
	int ok = 1, set_size, file_open = 0, open = 0, invalid_line;
	void **matrix;
	char str[100], vect[100][100], first_line[3];
	while (ok != 0) {
		invalid_line = 0;
		for (int i = 0; i < 100; i++)
			vect[i][0] = 0;
		fgets(str, 100, stdin);
		int i = 0, nr = 1;
		const char s[4] = "  \n";
		char *token;
		token = strtok(str, s);
		while (token != 0) {
			strcpy(vect[i], token);
			token = strtok(0, s);
			i++;
			nr++;
		}
		if (strcmp(vect[0], "LOAD") == 0) {
			invalid_line = 1;
			file_open++;
			if (open != 0)
				free_matrix(matrix, row);
			FILE *file = fopen(vect[1], "r");
			if (file == NULL) {
				printf("Failed to load %s\n", vect[1]);
				open = 0;
			} else {
				open = 1;
				printf("Loaded %s\n", vect[1]);
				fgets(first_line, 3, file);
				fclose(file);
				set_size = 1;
				matrix = load(vect[1], &column, &row, &intensity, first_line);
			}
		}
		if (set_size == 1) {
			default_size(&x1, &y1, &x2, &y2, &column, &row);
			set_size = 0;
		}
		if ((strcmp(vect[0], "SELECT") == 0) && (strcmp(vect[1], "ALL") )) {
			invalid_line = 1;
			if (open != 0) {
				if (check(vect[1], vect[2], vect[3], vect[4], column, row)) {
					x1 = atoi(vect[1]);
					y1 = atoi(vect[2]);
					x2 = atoi(vect[3]);
					y2 = atoi(vect[4]);
					swap(&x1, &y1, &x2, &y2);
					printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
					set_size = 0;
				}
			} else 
				printf("No image loaded\n");
		}
		if (strcmp(vect[0], "SELECT") == 0 && strcmp(vect[1], "ALL") == 0) {
			invalid_line = 1;
			if (open != 0) {
				printf("Selected ALL\n");
				default_size(&x1, &y1, &x2, &y2, &column, &row);
			} else
				printf("No image loaded\n");
		}
		if (strcmp(vect[0], "ROTATE") == 0 ) {
			invalid_line = 1;
			if (open != 0) {
				if (check_rotate_all(x1, y1, x2, y2, vect[1], column, row) == 1) {
					matrix = rotate_all(matrix, x2, y2, vect[1], first_line, &column, &row);
					x2 = column;
					y2 = row;
				} else if (check_rotate_square(x1, y1, x2, y2, vect[1]) == 1) {
					rotate_square(matrix, x1, y1, x2, y2, vect[1], first_line);
				}
			} else
				printf("No image loaded\n");
		}
		if (strcmp(vect[0], "CROP") == 0) {
			invalid_line = 1;
			if (open != 0) {
				matrix = crop_all(matrix, &x1, &y1, &x2, &y2, &column, &row, first_line);
			} else {
				printf("No image loaded\n");
			}
		}
		if (strcmp(vect[0], "GRAYSCALE") == 0 ){
			invalid_line = 1;
			verification_grayscale(matrix, x1, y1, x2, y2, first_line, open);
		}
		if (strcmp(vect[0], "SEPIA") == 0 ){
			invalid_line = 1;
			verification_sepia(matrix, x1, y1, x2, y2, first_line, open, intensity);
		}
		if (strcmp(vect[0], "SAVE") == 0  ){
			verification_save(matrix, row, column, first_line, vect[1], vect[2], intensity, open);
			invalid_line = 1;
		}
		if (strcmp(vect[0], "EXIT") == 0  ) {
			invalid_line = 1;
			if (open == 0)
				printf("No image loaded\n");
			else
				free_matrix(matrix, row);
			return 0;
		}
		if (invalid_line == 0)
			printf("Invalid command\n");
	}
	return 0;
}
