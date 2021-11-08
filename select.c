#include "function.h"
void swap(int *x1, int *y1, int *x2, int *y2)
{
	int aux = 0;
	if (*x1 > *x2) {
		aux = *x1;
		*x1 = *x2;
		*x2 = aux;
	}
	if (*y1 > *y2) {
		aux = *y1;
		*y1 = *y2;
		*y2 = aux;
	}
}

int check(char *a, char *b, char *c, char *d, int column, int row)
{
	int done = 1;
	int x1 = atoi(a);
	int y1 = atoi(b);
	int x2 = atoi(c);
	int y2 = atoi(d);
	swap(&x1, &y1, &x2, &y2);
	if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		done = 0;
	} else if (x1 < 0) {
		printf("Invalid set of coordinates\n");
		done = 0;
	} else if (y1 < 0) {
		printf("Invalid set of coordinates\n");
		done = 0;
	} else if (x2 > column) {
		printf("Invalid set of coordinates\n");
		done = 0;
	} else if (y2 > row) {
		printf("Invalid set of coordinates\n");
		done = 0;
	}
	return done;
	return 0;
}