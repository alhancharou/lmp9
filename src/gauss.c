#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
	int n = mat->r;

    for (int k = 0; k < n; k++) {
        // Wybór elementu głównego (maksymalna wartość w kolumnie k)
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > fabs(mat->data[max_row][k])) {
                max_row = i;
            }
        }

        // Zamiana wierszy, jeśli potrzebna
        if (max_row != k) {
            double* temp_row = mat->data[k];
            mat->data[k] = mat->data[max_row];
            mat->data[max_row] = temp_row;

            double temp_b = b->data[k][0];
            b->data[k][0] = b->data[max_row][0];
            b->data[max_row][0] = temp_b;
        }

        // Sprawdzenie, czy element diagonalny nie jest zerem
        if (fabs(mat->data[k][k]) < 1e-12) {
            fprintf(stderr, "Błąd! Element diagonalny macierzy jest zerem (kolumna %d).\n", k);
            return 1; // Macierz osobliwa
        }

        // Eliminacja zmiennych
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];
            for (int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // Sukces

}

