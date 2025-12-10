//a mettre dans le main
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Cette partie définie les statistique de la fenêtre, le maximum de chaque classe liée a l'animal
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 500
#define MAX_STAT 100
#define STAT_DECAY_RATE 0.5f //ici c'est le temps de diminution des statistiques pour les animaux

