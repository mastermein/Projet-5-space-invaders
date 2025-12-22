#include<SDL3/SDL.h>
#include "Game.h"
#include<iostream>

SDL_Init(SDL_INIT_VIDEO);

SDL_Window* window = SDL_CreateWindow( "Space invaders " , 800 , 600 , SDL_WINDOW_RESIZABLE);





SDL_DestroyWindow(window);
SDL_Quit();
