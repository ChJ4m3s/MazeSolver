#ifndef __Maze_solver__genera__
#define __Maze_solver__genera__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0
#define LEFT 1
#define UP 2
#define RIGHT 4
#define DOWN 8
#define VISITED 16

void genera_labirinto(int r, int c, int u, char* nome);

#endif