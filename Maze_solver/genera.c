#include "genera.h"
#include "distruggi.h"

int** genera_mat(r, c) {
    int** mat = malloc(sizeof(int*) * r);
    int i, j;
    for (i = 0; i < r; i++) {
        mat[i] = malloc(sizeof(int) * c);
        for (j = 0; j < c; j++) { /* matrice inizializzata con tutte le celle murate */
            mat[i][j] = EMPTY;
            mat[i][j] |= UP;
            mat[i][j] |= DOWN;
            mat[i][j] |= LEFT;
            mat[i][j] |= RIGHT;
        }
    }
    return mat;
}

void scava(int** mat, int r, int c, int i, int j) {
    int ran = rand() % 4;
    int h;
    mat[i][j] |= VISITED;
    for (h = 0; h < 4; h++) {
        switch (ran) {
            case 0:
                if (i > 0 && !(mat[i - 1][j] & VISITED)) {
                    mat[i][j] &= ~UP;
                    mat[i - 1][j] &= ~DOWN;
                    scava(mat, r, c, i - 1, j);
                }
                break;
                
            case 1:
                if (i < r - 1 && !(mat[i + 1][j] & VISITED)) {
                    mat[i][j] &= ~DOWN;
                    mat[i + 1][j] &= ~UP;
                    scava(mat, r, c, i + 1, j);
                }
                break;
                
            case 2:
                if (j > 0 && !(mat[i][j - 1] & VISITED)) {
                    mat[i][j] &= ~LEFT;
                    mat[i][j - 1] &= ~RIGHT;
                    scava(mat, r, c, i, j - 1);
                }
                break;
                
            case 3:
                if (j < c - 1 && !(mat[i][j + 1] & VISITED)) {
                    mat[i][j] &= ~RIGHT;
                    mat[i][j + 1] &= ~LEFT;
                    scava(mat, r, c, i, j + 1);
                }
                break;
        }
        if (ran != 3)
            ran++;
        else
            ran = 0;
    }
}

char** costuisci_mura(int r, int c) { /* rappresentazione con matrice di carateri, con tutte le celle murate */
    char** mura = malloc(sizeof(char*) * (r * 2 + 1));
    int i, j;
    for (i = 0; i < r * 2 + 1; i++) {
        mura[i] = malloc(sizeof(char) * (c * 2 + 1));
        if (i % 2 == 0) {
            for (j = 0; j < c * 2 + 1; j++)
                mura[i][j] = 'O';
        }
        else {
            for (j = 0; j < c * 2 + 1; j++) {
                if (j % 2 == 0)
                    mura[i][j] = 'O';
                else
                    mura[i][j] = ' ';
            }
        }
    }
    return mura;
}

void scava_mura(int** mat, char** mura, int r, int c, int u) {
    int i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++) {
            if (!(mat[i][j] & UP))
                mura[i * 2][j * 2 + 1] = ' ';
            if (!(mat[i][j] & DOWN))
                mura[i * 2 + 2][j * 2 + 1] = ' ';
            if (!(mat[i][j] & LEFT))
                mura[i * 2 + 1][j * 2] = ' ';
            if (!(mat[i][j] & RIGHT))
                mura[i * 2 + 1][j * 2 + 2] = ' ';
        }
}

void genera_labirinto(int r, int c, int u, char* nome) { /* genera e stampa su file */
    int** mat = genera_mat(r, c);
    char** mura = costuisci_mura(r, c);
    int i, j;
    FILE* f = fopen(nome, "w+");
    srand(time(NULL));
    scava(mat, r, c, 0, 0);
    scava_mura(mat, mura, r, c, u);
    distruggi_mat(mat, r);
    if (u == 0) {
        mura[1][0] = ' ';
        mura[r * 2 - 1][c * 2] = ' ';
    }
    else {
        mura[0][1] = ' ';
        mura[r * 2][c * 2 - 1] = ' ';
    }
    fprintf(f, "%d, %d\n", r, c);
    for (i = 0; i < r * 2 + 1; i++) {
        for (j = 0; j < c * 2 + 1; j++)
            fprintf(f, "%c", mura[i][j]);
        fprintf(f, "\n");
    }
    distruggi_mura(mura, r);
    fclose(f);
}