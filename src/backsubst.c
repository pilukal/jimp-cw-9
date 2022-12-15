#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	for (int i = x->r - 1; i >= 0; i--) {
		double s = 0;
		for(int j = x->r - 1; j > i; j--) {
			s += mat->data[i][j] * x->data[j][0];
		}
		x->data[i][0] = (b->data[i][0] - s) / mat->data[i][i];
	}

	return 0;
}


