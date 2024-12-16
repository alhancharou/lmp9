#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
     int n = mat->r;

    for (int k = 0; k < n; k++) {
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

