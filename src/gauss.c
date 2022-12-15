#include "gauss.h"

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
		for(int j = i + 1; j < mat->c; j++) {
			double max = abs(mat->data[i][i]);
			double max_r = i;
			for(int r = i + 1; r < mat->r; r++) {
				if(abs(mat->data[r][i]) > max) {
					max = abs(mat->data[r][i]);
					max_r = i;
				}
			}

			for(int s = 0; s < mat->c; s++) {
				double t = mat->data[i][s];
				mat->data[i][s] = mat->data[max_r][s];
				mat->data[max_r][s] = t;
			}

			
			double t = b->data[i][0];
			b->data[i][0] = b->data[max_r][0];
			b->data[max_r][0] = t;

			if(max_r != r) {
				rows_swap(mat, r, max_r);
				rows_swap(b, r, max_r);
			}

			int ret = multiply_and_substact(mat, b, i, j);
			if(ret == 1) {
				return 1;
			}
		}
	}
	return 0;
}

