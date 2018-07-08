#include "risolvi.h"

int coda(lista* soluzione, char mossa) {
    if (*soluzione == NULL) {
        *soluzione = malloc(sizeof(struct cella));
        if (*soluzione) {
            (*soluzione) -> mossa = mossa;
            (*soluzione) -> next = NULL;
            return 0;
        }
        return 1;
    }
    return coda (&((*soluzione) -> next), mossa);
}

int solve(int** mat, int i, int j, int last, int r, int c) { /* segna le celle visitate durante il percorso e se sono visitate più di una volta */
    if (i < 0 || j < 0)
        return 0;
    if (i == r - 1 && j == c - 1) {
        mat[i][j] |= VISITED;
        return 1;
    }
    switch (last) {
        case LEFT:
            if (i != 0 && j != 0 && !(mat[i][j] & LEFT)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j - 1, UP, r, c);
            }
            if (mat[i][j] & DOWN && !(mat[i][j] & RIGHT)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j + 1, DOWN, r, c);
            }
            if (mat[i][j] & DOWN && mat[i][j] & RIGHT) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j, DOWN, r, c);
            }
            mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
            return solve(mat, i + 1, j, LEFT, r, c);
            
        case RIGHT:
            if (!(mat[i][j] & RIGHT)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j + 1, DOWN, r, c);
            }
            if (mat[i][j] & UP && !(mat[i][j] & LEFT)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j - 1, UP, r, c);
            }
            if (mat[i][j] & UP && mat[i][j] & LEFT) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j, UP, r, c);
            }
            mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
            return solve(mat, i - 1, j, RIGHT, r, c);
            
        case UP:
            if (!(mat[i][j] & UP)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i - 1, j, RIGHT, r, c);
            }
            if (mat[i][j] & LEFT && !(mat[i][j] & DOWN)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i + 1, j, LEFT, r, c);
            }
            if (mat[i][j] & LEFT && mat[i][j] & DOWN) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j, LEFT, r, c);
            }
            mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
            return solve(mat, i, j - 1, UP, r, c);
            
        case DOWN:
            if (!(mat[i][j] & DOWN)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i + 1, j, LEFT, r, c);
            }
            if (mat[i][j] & RIGHT && !(mat[i][j] & UP)) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i - 1, j, RIGHT, r, c);
            }
            if (mat[i][j] & RIGHT && mat[i][j] & UP) {
                mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
                return solve(mat, i, j, RIGHT, r, c);
            }
            mat[i][j] |= (mat[i][j] & VISITED)? ALREADY_VISITED : VISITED;
            return solve(mat, i, j + 1, DOWN, r, c);
    }
    return 1;
}

void crea_soluzione(lista* soluzione, int** mat, int r, int c, int i, int j, int last) { /* crea il percorso escludendo i vicoli ciechi */
    int flag = 1;
    if (i != r - 1 || j != c - 1) {
        if (i > 0 && !(mat[i][j] & UP) && !(mat[i - 1][j] & PASSATO) && mat[i - 1][j] & VISITED) {
            if (last && !(mat[i - 1][j] & ALREADY_VISITED)) {
                coda(soluzione, 'N');
                last = mat[i - 1][j] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i - 1, j, last);
            }
            else if (!last) {
                coda(soluzione, 'N');
                last = mat[i - 1][j] & ALREADY_VISITED;
                mat[i][j] |= PASSATO;
                flag = 0;
                crea_soluzione(soluzione, mat, r, c, i - 1, j, last);
            }
        }
        if (flag && j < c - 1 && !(mat[i][j] & RIGHT) && !(mat[i][j + 1] & PASSATO) && mat[i][j + 1] & VISITED) {
            if (last && !(mat[i][j + 1] & ALREADY_VISITED)) {
                coda(soluzione, 'E');
                last = mat[i][j + 1] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i, j + 1, last);
            }
            else if (!last) {
                coda(soluzione, 'E');
                last = mat[i][j + 1] & ALREADY_VISITED;
                mat[i][j] |= PASSATO;
                flag = 0;
                crea_soluzione(soluzione, mat, r, c, i, j + 1, last);
            }
        }
        if (flag && i < r - 1 && !(mat[i][j] & DOWN) && !(mat[i + 1][j] & PASSATO) && mat[i + 1][j] & VISITED) {
            if (last && !(mat[i + 1][j] & ALREADY_VISITED)) {
                coda(soluzione, 'S');
                last = mat[i + 1][j] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i + 1, j, last);
            }
            else if (!last) {
                coda(soluzione, 'S');
                last = mat[i + 1][j] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i + 1, j, last);
            }
        }
        if (flag && j > 0 && !(mat[i][j] & LEFT) && !(mat[i][j - 1] & PASSATO) && mat[i][j - 1] & VISITED) {
            if (last && !(mat[i][j - 1] & ALREADY_VISITED)) {
                coda(soluzione, 'W');
                last = mat[i][j - 1] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i, j - 1, last);
            }
            else if (!last) {
                coda(soluzione, 'W');
                last = mat[i][j - 1] & ALREADY_VISITED;
                flag = 0;
                mat[i][j] |= PASSATO;
                crea_soluzione(soluzione, mat, r, c, i, j - 1, last);
            }
        }
    }
}

int percorso(int** mat, lista* soluzione, int r, int c) {
    int esiste;
    coda(soluzione, (mat[0][0] & UP)? 'E' : 'S');
    esiste = ((!(mat[0][0] & UP) && !(mat[r - 1][c - 1] & DOWN)) || (!(mat[0][0] & LEFT) && !(mat[r - 1][c - 1] & RIGHT)))? solve(mat, 0, 0, LEFT, r, c) : 0;
    if (esiste)
        crea_soluzione(soluzione, mat, r, c, 0, 0, mat[0][0] & ALREADY_VISITED);
    coda(soluzione, (mat[0][0] & UP)? 'E' : 'S');
    return esiste;
}

void stampa(lista soluzione, char* nome_soluzione, int r, int c) {
    FILE* f = fopen(nome_soluzione, "w+");
    fprintf(f, "Soluzione:\n\n");
    while (soluzione && soluzione -> next) {
        fprintf(f, "%c -> ", soluzione -> mossa);
        soluzione = soluzione -> next;
    }
    fprintf(f, "%c", soluzione -> mossa);
    fclose(f);
}