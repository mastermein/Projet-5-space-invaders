#include<Renderer.h>
#include"SDL_Image/SDL_image.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include "Game.h"
#include "UI.h"
#include "Utils.h"


// ce namespace va contenir toutes les fonctions de rendu
namespace Rendu 
{


    vector positionjoueur = {400.0f, 700.0f};
    
    // Stockage des textures (chargées une fois au démarrage)
     SDL_Texture* Player1_texture = nullptr;
     SDL_Texture* Player2_texture = nullptr;
     SDL_Texture* fond_texture = nullptr;
     SDL_Texture* tirjoueur = nullptr;

    

    

    // objets du jeu (déclarations)
    joueur joueur1;
    enemies enemy1;
    projectile tir1; //joueur 
    projectile tir2; // ennemi

    // valeurs par défaut : initialisées dans initGameTextures()
    


    void initGameTextures(SDL_Renderer* Renderer)
    {
        joueur1.texture = IMG_LoadTexture(Renderer, "Images/player1.jpeg");
        enemy1.texture = IMG_LoadTexture(Renderer, "Images/player2.jpeg");
        fond_texture = IMG_LoadTexture(Renderer, "Images/fond.jpeg");
        tir1.texture = IMG_LoadTexture(Renderer, "Images/tir.jpeg");
        tir2.texture = IMG_LoadTexture(Renderer, "Images/tir.jpeg");

        // initialiser joueur
        joueur1.rect.w = 50.0f;
        joueur1.rect.h = 50.0f;
        joueur1.pos.x = positionjoueur.x;
        joueur1.pos.y = positionjoueur.y;
        joueur1.rect.x = joueur1.pos.x;
        joueur1.rect.y = joueur1.pos.y;
        joueur1.speed = 30.0f;
        joueur1.active = true;

        // initialiser ennemi

         // generateur de nombres aléatoires
     std::srand(std::time(0));
        enemy1.rect.w = 50.0f;
        enemy1.rect.h = 50.0f;
        enemy1.pos.x = (rand( ) % 2== 0 ? 0.0f : 8.0f) * 50.0f;
        enemy1.pos.y = (static_cast<float>(rand() ) / RAND_MAX * 5.0f) * 50.0f;
        enemy1.rect.x = enemy1.pos.x;
        enemy1.rect.y = enemy1.pos.y;
        enemy1.speed = 5.0f;
        enemy1.active = true;

        // initialiser tir du joueur 
        tir1.rect.w = 20.0f;
        tir1.rect.h = 30.0f;
        tir1.rect.x = positionjoueur.x;
        tir1.rect.y = positionjoueur.y;
        tir1.pos.x = positionjoueur.x;
        tir1.pos.y = positionjoueur.y;
        tir1.speed = 10.0f;
        tir1.active = false;

        // initialiser tir de l'ennemi
        tir2.rect.w = 20.0f;
        tir2.rect.h = 30.0f;
        tir2.rect.x = enemy1.pos.x;
        tir2.rect.y = enemy1.pos.y;
        tir2.pos.x = enemy1.pos.x;
        tir2.pos.y = enemy1.pos.y;
        tir2.speed = 7.0f;
        tir2.active = false;

    }

    void cleanupGameTextures()
    {
        if (joueur1.texture) SDL_DestroyTexture(joueur1.texture);
        if (enemy1.texture) SDL_DestroyTexture(enemy1.texture);
        if (fond_texture) SDL_DestroyTexture(fond_texture);
        if (tir1.texture) SDL_DestroyTexture(tir1.texture);
        if (tir2.texture) SDL_DestroyTexture(tir2.texture);
    }

    void MenuPrincipal(SDL_Renderer* Renderer)
    {
        
     SDL_Texture* MenuPprincipal = IMG_LoadTexture (Renderer , "Images/menuprincipal.jpeg" );


    // nettoyage de l'ecran et affichage de l'image (présentation effectuée après le rendu ImGui)
    SDL_RenderClear (Renderer);
    SDL_RenderTexture (Renderer , MenuPprincipal , nullptr , nullptr );

    SDL_DestroyTexture (MenuPprincipal);
    }


    void playing (SDL_Renderer* Renderer)
    {
        // position du joueur (utilise la variable globale)

        // empecher le joueur de sortir de la fenetre
        if (positionjoueur.x < 0.0f)
           {
               positionjoueur.x = 0.0f;
           }
           if (positionjoueur.x > 800.0f)
           {
               positionjoueur.x = 800.0f;
           }

        // Rendu des textures (déjà chargées)
        SDL_RenderTexture(Renderer, fond_texture, nullptr, nullptr);

        // synchroniser la position du joueur et son rectangle
        joueur1.pos.x = positionjoueur.x;
        joueur1.pos.y = positionjoueur.y;
        joueur1.rect.x = joueur1.pos.x;
        joueur1.rect.y = joueur1.pos.y;

        SDL_RenderTexture(Renderer, joueur1.texture, nullptr, &joueur1.rect);
        SDL_RenderTexture(Renderer, enemy1.texture, nullptr, &enemy1.rect);

        // Mettre à jour et rendre le tir du joueur s'il est actif
        if (tir1.active == true)
        {
            tir1.pos.y -= tir1.speed; // mouvement par frame (speed positif)
            tir1.rect.y = tir1.pos.y;
            if (tir1.rect.y + tir1.rect.h < 0.0f)
            {
                tir1.active = false;
            }
            else
            {
                SDL_RenderTexture(Renderer, tir1.texture, nullptr, &tir1.rect);
            }
        }

        // Mettre à jour et rendre le tir de l'ennemi s'il est actif
        if (tir2.active == true)
        {
            tir2.pos.y += tir2.speed; // mouvement par frame (speed positif)
            tir2.rect.y = tir2.pos.y;
            if (tir2.rect.y > 800.0f)
            {
                tir2.active = false;
            }
            else
            {
                SDL_RenderTexture(Renderer, tir2.texture, nullptr, &tir2.rect);
            }
        }

        // présenter le rendu
        SDL_RenderPresent(Renderer);
    }

    void projectilesjoueur (SDL_Renderer* Renderer , float x , float y)
    {
        // fonction non-bloquante : initialise le tir, le déplacement se fera dans playing()
        tir1.active = true;
        tir1.rect.x = x;
        tir1.rect.y = y;
        tir1.pos.x = x;
        tir1.pos.y = y;

    
    }

    void projectilesennemi (SDL_Renderer* Renderer , float x , float y)
    {
        // fonction non-bloquante : initialise le tir, le déplacement se fera dans playing()
        tir2.active = true;
        tir2.rect.x = x;
        tir2.rect.y = y;
        tir2.pos.x = x;
        tir2.pos.y = y;

    
    }


    void nettoyageSDL (SDL_Window* Window , SDL_Renderer* Renderer)
    {
        SDL_DestroyRenderer (Renderer);
        SDL_DestroyWindow (Window);
        SDL_Quit();
    }
}