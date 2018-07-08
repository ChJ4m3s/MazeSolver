#ifndef __Maze_solver__leggi__
#define __Maze_solver__leggi__

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "distruggi.h"

#define EMPTY 0
#define LEFT 1
#define UP 2
#define RIGHT 4
#define DOWN 8

int** matrice(int* r, int* c, char* nome);
int controlla(char* nome);
void stampa_matrice(int** mat, int r, int c, char* nome);

#endif