#ifndef __Maze_solver__distruggi__
#define __Maze_solver__distruggi__

#include <stdlib.h>
#include "risolvi.h"

typedef struct cella* list;

void distruggi_mura(char** mura, int r);
void distruggi_mat(int** mat, int r);
void distruggi_soluzione(list soluzione);

#endif
