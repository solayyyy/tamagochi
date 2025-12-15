#ifndef INIT_SDL_HPP
#define INIT_SDL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

void Barre_Etat(SDL_Renderer* renderer, int x, int y, int w, int h, float percent, SDL_Color color);

bool Init_SDL(SDL_Window** win, SDL_Renderer** ren);

void cleanup(SDL_Window* win, SDL_Renderer* ren);

#endif