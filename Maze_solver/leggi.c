#include "leggi.h"

char** acquisisci(int* r, int* c, char* nome) {
    FILE* f = fopen(nome, "r");
    char** mura;
    int i;
    size_t dim;
    fscanf(f, "%d, %d\n", r, c);
    dim = *c * 2 + 2;
    mura = malloc(sizeof(char*) * (*r * 2 + 1));
    for (i = 0; i < *r * 2 + 1; i++) {
        mura[i] = malloc(sizeof(char) * (*c * 2 + 3));
        getline(&mura[i], &dim, f);
    }
    return mura;
}

int** matrice(int* r, int* c, char* nome) {
    char** mura = acquisisci(r, c, nome);
    int** mat = malloc(sizeof(int*) * (*r));
    int i, j;
    int x = 0, y = 0;
    for (i = 0; i < *r; i++) 
        mat[i] = malloc(sizeof(int) * (*c));
    for (i = 1; i < *r * 2 + 1; i += 2) {
        for (j = 1; j < *c * 2 + 1; j += 2) {
            mat[y][x] = EMPTY;
            if (mura[i - 1][j] == 'O')
                mat[y][x] |= UP;
            if (mura[i + 1][j] == 'O')
                mat[y][x] |= DOWN;
            if (mura[i][j - 1] == 'O')
                mat[y][x] |= LEFT;
            if (mura[i][j + 1] == 'O')
                mat[y][x] |= RIGHT;
            x += 1;
        }
        x = 0;
        y += 1;
    }
    distruggi_mura(mura, *r);
    return mat;
}

int esiste(char* nome) {
    FILE* f = fopen(nome, "r");
    if (f) {
        fclose(f);
        return 0;
    }
    return 1;
}

int controlla_intestazione(char* nome) {
    FILE* f = fopen(nome, "r");
    size_t dim = 6;
    char* string = malloc(sizeof(char) * 6);
    if (getline(&string, &dim, f) != -1) {
        int i = 0;
        if (string[i] && string[i] <= '9' && string[i] > '0') {
            i++;
            while (string[i] && string[i] <= '9' && string[i] >= '0')
                i++;
        }
        else {
            free(string);
            fclose(f);
            return 1;
        }
        if (string[i] && string[i] == ',')
            i++;
        else {
            free(string);
            fclose(f);
            return 1;
        }
        if (string[i] && string[i] == ' ')
            i++;
        else {
            free(string);
            fclose(f);
            return 1;
        }
        if (string[i] && string[i] > '0' && string[i] <= '9') {
            i++;
            while (string[i] && string[i] <= '9' && string[i] >= '0')
                i++;
        }
        else {
            free(string);
            fclose(f);
            return 1;
        }
        if (string[i] && string[i] == '\n') {
            free(string);
            fclose(f);
            return 0;
        }
        else {
            free(string);
            fclose(f);
            return 1;
        }
    }
    free(string);
    fclose(f);
    return 1;
}

int controlla_righe(char* nome) {
    FILE* f = fopen(nome, "r");
    int r, c;
    int i = 0;
    size_t dim;
    char* stringa;
    fscanf(f, "%d, %d\n", &r, &c);
    dim = c * 2 + 2;
    stringa = malloc(sizeof(char) * (c * 2 + 2));
    while (getline(&stringa, &dim, f) != -1)
        i++;
    free(stringa);
    fclose(f);
    return (i == r * 2 + 1)? 0 : 1;
}

int controlla_colonne(char* nome) {
    FILE* f = fopen(nome, "r");
    char* string;
    int r, c;
    size_t dim;
    int i;
    string = malloc(sizeof(char) * c * 2 + 2);
    fscanf(f, "%d, %d\n", &r, &c);
    dim = c * 2 + 2;
    for (i = 0; i < r * 2 + 1; i++) {
        getline(&string, &dim, f);
        if (strlen(string) != c * 2 + 2) {
            free(string);
            fclose(f);
            return 1;
        }
    }
    free(string);
    fclose(f);
    return 0;
}

int controlla_uscite(char* nome) {
    int r, c;
    FILE* f = fopen(nome, "r");
    int i;
    size_t dim;
    char* string;
    fscanf(f, "%d, %d\n", &r, &c);
    dim = c * 2 + 2;
    string = malloc(sizeof(char) * (r * 2 + 2));
    getline(&string, &dim, f);
    if (string[1] == ' ') {
        if (string[0] != 'O') {
            free(string);
            fclose(f);
            return 1;
        }
        for (i = 2; i < c * 2 + 1; i++) {
            if (string[i] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
        for (i = 1; i < r * 2; i++) {
            getline(&string, &dim, f);
            if (string[0] != 'O' || string[c * 2] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
        getline(&string, &dim, f);
        for (i = 0; i < c * 2 - 1; i++) {
            if (string[i] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
        if (string[c * 2 - 1] != ' ' || string[c * 2] != 'O') {
            free(string);
            fclose(f);
            return 1;
        }
    }
    else {
        for (i = 0; i < c * 2 + 1; i++) {
            if (string[i] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
        getline(&string, &dim, f);
        if (r == 1) {
            if ((string[0] != ' ' || string[c * 2] != ' ')) {
                free(string);
                fclose(f);
                return 1;
            }
            free(string);
            fclose(f);
            return 0;
        }
        if (string[0] != ' ' || string[c * 2] != 'O') {
            free(string);
            fclose(f);
            return 1;
        }
        for (i = 2; i < r * 2 - 1; i++) {
            getline(&string, &dim, f);
            if (string[0] != 'O' || string[c * 2] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
        getline(&string, &dim, f);
        if (string[0] != 'O' || string[c * 2] != ' ') {
            free(string);
            fclose(f);
            return 1;
        }
        getline(&string, &dim, f);
        for (i = 0; i < c * 2 + 1; i++) {
            if (string[i] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
    }
    free(string);
    fclose(f);
    return 0;
}

int controlla_caratteri(char* nome) {
    FILE* f = fopen(nome, "r");
    int i, j;
    size_t dim;
    int r, c;
    char* string;
    fscanf(f, "%d, %d\n", &r, &c);
    dim = c * 2 + 2;
    string = malloc(sizeof(char) * (c * 2 + 2));
    getline(&string, &dim, f);
    for (i = 1; i < r * 2; i++) {
        getline(&string, &dim, f);
        for (j = 1; j < c * 2; j++) {
            if (i % 2 == 1 && j % 2 == 1 && string[j] != ' ') {
                free(string);
                fclose(f);
                return 1;
            }
            if (i % 2 == 0 && j % 2 == 0 && string[j] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
            if (string[j] != ' ' && string[j] != 'O') {
                free(string);
                fclose(f);
                return 1;
            }
        }
    }
    free(string);
    fclose(f);
    return 0;
}

int controlla(char* nome) {
    int errore = 0;
    errore = esiste(nome);
    if (errore) {
        printf("\nImpossibile trovare il file contenente il labirinto\n");
        return 1;
    }
    errore = controlla_intestazione(nome);
    if (errore) {
        printf("\nErrore intestazione\n");
        return 1;
    }
    errore = controlla_righe(nome);
    if (errore) {
        printf("\nIl numero di righe non corrisponde\n");
        return 1;
    }
    errore = controlla_colonne(nome);
    if (errore) {
        printf("\nIl numero di colonne non corrisponde\n");
        return 1;
    }
    errore = controlla_uscite(nome);
    if (errore) {
        printf("\nLe uscite non sono posizionate nella posizione corretta\n");
        return 1;
    }
    errore = controlla_caratteri(nome);
    if (errore) {
        printf("\nCaratteri non ammessi o mal posizionati\n");
        return 1;
    }
    return 0;
}

void stampa_matrice(int** mat, int r, int c, char* nome) {
    char* file;
    size_t dim = strlen(nome);
    FILE* f;
    int i, j;
    file = malloc(sizeof(char) * (dim + 4));
    strcpy(file, nome);
    strcpy(&file[dim - 4], "_mat.txt");
    f = fopen(file, "w+");
    fprintf(f, "Rappresentazione matriciale:\n\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            fprintf(f, "%d ", mat[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
    free(file);
}