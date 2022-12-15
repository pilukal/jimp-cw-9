#include "gauss.h"

#include <stdlib.h>

static void rows_swap(Matrix *mat, int r_a, int r_b) {
	for(int i = 0; i < mat->c; i++) {
		double tmp = mat->data[r_a][i];
		mat->data[r_a][i] = mat->data[r_b][i];
		mat->data[r_b][i] = tmp;
	}
}

static void row_select(Matrix *mat, Matrix *b, int r) {
	double max = abs(mat->data[r][r]);
	double max_r = r;
	for(int i = r + 1; i < mat->r; i++) {
		if(abs(mat->data[i][r]) > max) {
			max = abs(mat->data[i][r]);
			max_r = i;
		}
	}

	if(max_r != r) {
		rows_swap(mat, r, max_r);
		rows_swap(b, r, max_r);
	}
}

/*
 * Mnoży przez skalar i odejmuje wiersze macierzy.
 * Zwraca 0 - zakończenie sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
static int multiply_and_substact(Matrix *mat, Matrix *b, int r_1, int r_2) {
	if(mat->data[r_1][r_1] == 0) {
		return 1;
	}
	double s = mat->data[r_2][r_1] / mat->data[r_1][r_1];
	for(int i = r_1; i < mat->c; i++) {
		mat->data[r_2][i] = mat->data[r_2][i] - mat->data[r_1][i] * s;
	}
	b->data[r_2][0] = b->data[r_2][0] - b->data[r_1][0] * s;
	return 0;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    for(int i = 0; i < mat->c; i++) {
		row_select(mat, b, i);
		for(int j = i + 1; j < mat->c; j++) {
			int ret = multiply_and_substact(mat, b, i, j);
			if(ret == 1) {
				return 1;
			}
		}
	}

	return 0;
}
