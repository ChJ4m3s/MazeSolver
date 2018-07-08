//i comandi "system" potrebbero non funzionare su Windows!!!!!!!! :'D

#include <stdio.h>
#include "genera.h"
#include "distruggi.h"
#include "risolvi.h"
#include "leggi.h"

int main() {
    int menù = 1;
    char sostituisci;
    char scelta;
    lista soluzione = NULL;
    char* nome_aux;
    char* nome;
    char* nome_soluzione;
    size_t dim;
    int esci;
    int** mat = NULL;
    FILE* f = NULL;
    printf("|\\  /|   /\\   ¯¯// ||¯¯\n");
    printf("||\\/||  /__\\   //  ||=\n");
    printf("||  || /    \\ //__ ||__\n");
    printf("    ~ S O L V E R ~ \n");
    while (menù) {
        int r, c, u;
        printf("\nInserisci:\n");
        printf("\t'1' per generare un nuovo labirinto\n");
        printf("\t'2' per risolvere un labirinto già esistente\n");
        printf("\t'0' per uscire dal programma\n");
        printf("menù: ");
        scanf("%d", &menù);
        switch (menù) {
            case 1:
                dim = 10;
                do {
                    printf("Inserisci il numero di righe: ");
                    scanf("%d", &r);
                }
                while (r < 1);
                do {
                    printf("Inserisci il numero di colonne: ");
                    scanf("%d", &c);
                }
                while (c < 1);
                do {
                    printf("Inserisci '0' per posizionare l'entrata a sinistra, '1' per posizionare l'etrata in alto: ");
                    scanf("%d", &u);
                }
                while (u != 1 && u != 0);
                do {
                    getchar();
                    sostituisci = 'Y';
                    nome_aux = malloc(sizeof(char) * 10);
                    printf("Inserisci il nome del labirinto: "); /*nome senza estensione */
                    getline(&nome_aux, &dim, stdin);
                    dim = strlen(nome_aux);
                    nome = malloc(sizeof(char) * (dim + 4));
                    strcpy(nome, nome_aux);
                    strcpy(&nome[dim - 1], ".txt");
                    free(nome_aux);
                    f = fopen(nome, "r");
                    if (f) {
                        printf("file già esistente: vuoi sostituire (Y / N)? "); /* vengono presi anche minuscoli */
                        do {
                            scanf("%c", &sostituisci);
                            if (sostituisci == 'Y' || sostituisci == 'y')
                                getchar();
                        }
                        while (sostituisci != 'N' && sostituisci != 'Y' && sostituisci != 'n' && sostituisci != 'y');
                    }
                    fclose(f);
                    if (sostituisci == 'n' || sostituisci == 'N')
                        free(nome);
                }
                while (sostituisci == 'N' || sostituisci == 'n');
                genera_labirinto(r, c, u, nome);
                printf("\nlabirinto generato con successo!\n");
                do {
                    printf("\nvuoi salvare anche la rappresentazione matriciale (Y / N)? ");
                    scanf("%c", &scelta);
                    if (scelta != 'y' && scelta != 'Y' && scelta != 'n' && scelta != 'N')
                        getchar();
                }
                while (scelta != 'y' && scelta != 'Y' && scelta != 'n' && scelta != 'N');
                if (scelta == 'Y' || scelta == 'y') {
                    mat = matrice(&r, &c, nome);
                    stampa_matrice(mat, r, c, nome);
                    distruggi_mat(mat, r);
                    printf("\nmatrice generata con successo\n");
                }
                free(nome);
                break;
                
            case 2:
                esci = 0;
                printf("Inserisci il nome del labirinto da risolvere: ");  /* nome senza estensione */
                getchar();
                do {
                    nome_aux = malloc(sizeof(char) * 10);
                    dim = 10;
                    getline(&nome_aux, &dim, stdin);
                    dim = strlen(nome_aux);
                    nome = malloc(sizeof(char) * (dim + 4));
                    if (nome_aux[0] == '0') {
                        free(nome_aux);
                        esci = 1;
                    }
                    if (esci != 1) {
                        strcpy(nome, nome_aux);
                        free(nome_aux);
                        strcpy(&nome[dim - 1], ".txt");
                        f = fopen(nome, "r");
                        if (f == NULL) {
                            printf("\n%s inesistente, file di testo presenti:\n", nome);
                            system("ls -nome *.txt");   /* cerca i file .txt presenti nella cartella */
                            printf("\n");
                            printf("Inserisci il nome del labirinto da risolvere oppure '0' per tornare al menù principale: ");
                        }
                    }
                }
                while (f == NULL && esci != 1);
                if (esci != 1) {
                    fclose(f);
                    if (controlla(nome) == 0) {
                        soluzione = NULL;
                        mat = matrice(&r, &c, nome);
                        if (percorso(mat, &soluzione, r, c) == 1) {
                            nome_soluzione = malloc(sizeof(char) * (dim + 14));
                            strcpy(nome_soluzione, nome);
                            strcpy(&nome_soluzione[dim - 1], "_soluzione.txt");
                            printf("\n");
                            stampa(soluzione, nome_soluzione, r, c); /* soluzione stampata su file <nome>_soluzione.txt */
                            distruggi_soluzione(soluzione);
                            printf("soluzione salvata con successo\n");
                        }
                        else {
                            distruggi_soluzione(soluzione);
                            printf("Nessuna soluzione\n");
                        }
                        distruggi_mat(mat, r);
                        free(nome);
                    }

                }
                break;
        }
    }
}
