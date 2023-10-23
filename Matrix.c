/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

double *input_matrix(int *rows, int *columns, char *name);
int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2, int m2_rows, int m2_columns, double *m3);
void output_matrix(double *matrix, int rows, int columns);
/*---------------------------------------------------------------------------*/
int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}
/*---------------------------------------------------------------------------*/
double *input_matrix(int *rows, int *columns, char *name) {

    printf("Number of rows   : ");
    scanf("%d", rows);
    printf("Number of columns: ");
    scanf("%d", columns);
    printf("\n");

    if (*rows <= 0 || *columns <= 0) {
        printf("Invalid dimensions\n");
	return NULL;
    }

    double *matrix = malloc(*rows * *columns * sizeof(double));
    if (matrix == NULL) {
	printf("Error allocating memory for %s\n", name);
	return NULL;
    }

    double value = 1;
    for (int i = 0; i < *rows; i++) {
	for (int j = 0; j < *columns; j++) {
	    matrix[i * (*columns) + j] = value++;
	}
    }
    return matrix;
} 
/*---------------------------------------------------------------------------*/
int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2, int m2_rows, int m2_columns, double *m3) {

    if (m1_columns != m2_rows) {
	return 0;
    }

    for (int i = 0; i < m1_rows; i++) {
	for (int j = 0; j < m2_columns; j++) {
	    m3[i * m2_columns + j] = 0;
	    for (int s = 0; s < m1_columns; s++) {
		m3[i * m2_columns + j] += m1[i * m1_columns + s] * m2[s * m2_columns + j];
	    }
	}
    }
    return 1; 
}
/*---------------------------------------------------------------------------*/
void output_matrix(double *matrix, int rows, int columns) {

    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < columns; j++) {
	    printf("%lf ", matrix[i * columns + j]);
	}
	printf("\n");
    }
}
/*---------------------------------------------------------------------------*/
