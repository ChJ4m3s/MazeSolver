#ifndef __Maze_solver__risolvi__
#define __Maze_solver__risolvi__

#include <stdio.h>
#include <stdlib.h>
#include "distruggi.h"

#define EMPTY 0
#define LEFT 1
#define UP 2
#define RIGHT 4
#define DOWN 8
#define VISITED 16
#define ALREADY_VISITED 32
#define PASSATO 64

struct cella {
    char mossa;
    struct cella* next;
};

typedef struct cella* lista;

int percorso(int** mat, lista* soluzione, int r, int c);
void stampa(lista soluzione, char* nome, int r, int c);

#endif