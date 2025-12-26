#include<Renderer.h>
#include"SDL_Image/SDL_image.h"
#include<iostream>
#include "Game.h"
#include "UI.h"


// ce namespace va contenir toutes les fonctions de rendu
namespace Rendu 
{


    void MenuPrincipal(SDL_Renderer* Renderer)
    {
        
    // charger l'image de menu principal 
    SDL_Texture* MenuPprincipal = IMG_LoadTexture (Renderer , "Images/menuprincipal.jpeg" );


    // nettoyage de l'ecran et affichage de l'image (présentation effectuée après le rendu ImGui)
    SDL_RenderClear (Renderer);
    SDL_RenderTexture (Renderer , MenuPprincipal , nullptr , nullptr );

    //SDL_DestroyTexture (MenuPprincipal);
    }

    void nettoyageSDL (SDL_Window* Window , SDL_Renderer* Renderer)
    {
        SDL_DestroyRenderer (Renderer);
        SDL_DestroyWindow (Window);
        SDL_Quit();
    }
}
