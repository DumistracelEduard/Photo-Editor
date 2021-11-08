#include "function.h"
void save_rgb(void **mat, int row, int column, char *file, char *type, int intensity)
{
	int i, j;
	unsigned char print_mat;
	FILE *file_save = fopen(file, "wb");
	if (strcmp(type, "ascii") == 0 && type) {
		fprintf(file_save, "P3\n");
		fprintf(file_save, "%d %d\n", column, row);
		fprintf(file_save, "%d\n", intensity);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				print_mat = ((rgb **)mat)[i][j].R;
				fprintf(file_save, "%hhu ", print_mat);
				print_mat = ((rgb **)mat)[i][j].G;
				fprintf(file_save, "%hhu ", print_mat);
				print_mat = ((rgb **)mat)[i][j].B;
				fprintf(file_save, "%hhu ", print_mat);
			}
			fprintf(file_save, "\n");
		}
	} else {
		fprintf(file_save, "P6\n");
		fprintf(file_save, "%d %d\n", column, row);
		fprintf(file_save, "%d\n", intensity);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				print_mat = ((rgb **)mat)[i][j].R;
				fwrite(&print_mat, sizeof(print_mat), 1, file_save);
				print_mat = ((rgb **)mat)[i][j].G;
				fwrite(&print_mat, sizeof(print_mat), 1, file_save);
				print_mat = ((rgb **)mat)[i][j].B;
				fwrite(&print_mat, sizeof(print_mat), 1, file_save);
			}
		}
	}
	printf("Saved %s\n", file);
	fclose(file_save);
}

void save_char(void **mat, int row, int column, char *file, char *type, int intensity)
{
	int i, j;
	unsigned char print_mat;
	FILE *file_save = fopen(file, "wb");
	if (strcmp(type, "ascii") == 0 && strlen(type) != 1) {
		fprintf(file_save, "P2\n");
		fprintf(file_save, "%d %d\n", column, row);
		fprintf(file_save, "%d\n", intensity);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				print_mat = ((unsigned char **)mat)[i][j];
				fprintf(file_save, "%u ", print_mat);
			}
			fprintf(file_save, "\n");
		}
	} else {
		fprintf(file_save, "P5\n");
		fprintf(file_save, "%d %d\n", column, row);
		fprintf(file_save, "%d\n", intensity);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				print_mat = ((unsigned char **)mat)[i][j];
				fwrite(&print_mat, sizeof(print_mat), 1, file_save);
			}
		}
	}
	printf("Saved %s\n", file);
	fclose(file_save);
}
