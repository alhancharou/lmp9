#include "backsubst.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	int n = mat->r;

    // Sprawdzenie rozmiarów macierzy
    if (x->r != n || b->r != n || x->c != 1 || b->c != 1) {
        fprintf(stderr, "Błąd! Nieprawidłowe rozmiary macierzy w funkcji backsubst.\n");
        return 2;
    }

    for (int i = n - 1; i >= 0; i--) {
        if (fabs(mat->data[i][i]) < 1e-12) {
            fprintf(stderr, "Błąd! Element diagonalny macierzy jest zerem podczas wstecznego podstawiania (wiersz %d).\n", i);
            return 1; // Dzielenie przez 0
        }

        x->data[i][0] = b->data[i][0];
        for (int j = i + 1; j < n; j++) {
            x->data[i][0] -= mat->data[i][j] * x->data[j][0];
        }
        x->data[i][0] /= mat->data[i][i];
    }

    return 0; // Sukces
}


