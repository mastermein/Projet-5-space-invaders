#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>
#include <vector>

// structure d'un projectile
struct projectile
{
    SDL_Texture* texture;
    SDL_FRect rect;
    SDL_FPoint pos;
    float speed;
    bool active;
};

// structure d'un joueur
struct joueur
{
    SDL_Texture* texture;
    SDL_FRect rect;
    SDL_FPoint pos;
    float speed;   
    int Vies;
    bool active;
};

// structure d'un ennemi
struct enemies 
{
    SDL_Texture* texture;
    SDL_FPoint pos;
    SDL_FRect rect;
    float speed;
    bool active;
};


    extern joueur joueur1;
    extern enemies enemy1;
    extern projectile tir1;
    extern projectile tir2;


#endif 