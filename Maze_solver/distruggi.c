#include "distruggi.h"

void distruggi_mat(int** mat, int r) {
    int i;
    for (i = 0; i < r; i++)
        free(mat[i]);
    free(mat);
}

void distruggi_mura(char** mura, int r) {
    int i;
    for (i = 0; i < r * 2 + 1; i++)
        free(mura[i]);
    free(mura);
}

void distruggi_soluzione(list soluzione) {
    if (soluzione != NULL) {
        distruggi_soluzione(soluzione -> next);
        free(soluzione);
    }
}