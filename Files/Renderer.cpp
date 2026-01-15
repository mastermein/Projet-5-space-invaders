#include<Renderer.h>
#include"SDL_Image/SDL_image.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include "Game.h"
#include "UI.h"
#include "Utils.h"
   

std::vector<Enemies> Enemies::listeEnnemis;



// ce namespace va contenir toutes les fonctions de rendu
namespace Rendu 
{

    SDL_Texture* fond_texture = nullptr;
    SDL_Texture* joueurtexture = nullptr;
    SDL_Texture* enemytexture = nullptr;
    SDL_Texture* tirtexture = nullptr;
    SDL_Texture* explosiontexture = nullptr;

    
    Joueur Joueur1;
    Enemies Enemy1;
    Projectile Tir1;
   Projectile Tir2;

    
    // Stockage des textures (chargées une fois au démarrage)
    
    

    


    // valeurs par défaut : initialisées dans initGameTextures()
    


    void initGameTextures(SDL_Renderer* Renderer)
    {
        joueurtexture = IMG_LoadTexture(Renderer, "Images/player1.jpeg");
        enemytexture = IMG_LoadTexture(Renderer, "Images/player2.jpeg");
        fond_texture = IMG_LoadTexture(Renderer, "Images/fond.jpeg");
        tirtexture = IMG_LoadTexture(Renderer, "Images/tir.jpeg");
        explosiontexture = IMG_LoadTexture(Renderer, "Images/boom.jpeg");

        // initialiser joueur
        Joueur1.Initialisation(joueurtexture, explosiontexture, tirtexture, 400.0f, 700.0f);

        
         
         for (int i = 0 ; i < 5 ; i++)
         {
            Enemies e;

            e.Initialisation(enemytexture , explosiontexture , tirtexture , 100.0f + (i * 150.0f) , 100.0f);
            Enemies::listeEnnemis.push_back(e);
         }
    }

    void cleanupGameTextures()
    {
        if (Joueur1.joueurtexture) SDL_DestroyTexture(Joueur1.joueurtexture);
      for (auto& e : Enemies::listeEnnemis)
      {
        if (e.enemytexture) SDL_DestroyTexture(e.enemytexture);
      }
        if (fond_texture) SDL_DestroyTexture(fond_texture);
        if (Tir1.texture) SDL_DestroyTexture(Tir1.texture);
        if (Tir2.texture) SDL_DestroyTexture(Tir2.texture);
    }

    void MenuPrincipal(SDL_Renderer* Renderer)
    {
        
     SDL_Texture* MenuPprincipal = IMG_LoadTexture (Renderer , "Images/menuprincipal.jpeg" );

    // remise des parametres de jeu a zero

      
       Joueur1.Initialisation(joueurtexture, explosiontexture, tirtexture, 400.0f, 700.0f);

       Enemies::listeEnnemis.clear();
    
         
        for (int i=0 ; i<5 ; i++)
        {
            Enemies e;
            e.Initialisation(enemytexture , explosiontexture , tirtexture , 100.0f + (i * 150.0f) , 100.0f);
            Enemies::listeEnnemis.push_back(e);
        }
    
    

                              

    // nettoyage de l'ecran et affichage de l'image (présentation effectuée après le rendu ImGui)
    SDL_RenderClear (Renderer);
    SDL_RenderTexture (Renderer , MenuPprincipal , nullptr , nullptr );

    SDL_DestroyTexture (MenuPprincipal);
    }


    void playing (SDL_Renderer* Renderer)
    {

     const bool* state = SDL_GetKeyboardState(nullptr);
    
      Joueur1.Evenements(state);

         
      // verification des collisions 
        

        // position du joueur (utilise la variable globale)

         Joueur1.Update();
         Enemy1.Evenements();
         Enemy1.Update();
        // Games.collision();

        // Rendu des textures (déjà chargées)
        SDL_RenderTexture(Renderer, fond_texture, nullptr, nullptr);
        Joueur1.Rendu(Renderer);
        Enemy1.Rendu(Renderer);

        for(auto& e : Enemies::listeEnnemis)
        {
            e.Evenements();
            e.Update();
            e.Rendu(Renderer);
        }

        Rendu::collision(Renderer);

        

        
        // Mettre à jour et rendre le tir du joueur s'il est actif
        if (Tir1.Pactive == true)
        {
            Tir1.pos.y -= Tir1.speed; // mouvement par frame (speed positif)
            Tir1.rect.y = Tir1.pos.y;
            if (Tir1.rect.y + Tir1.rect.h < 0.0f)
            {
                Tir1.Pactive = false;
            }
            else
            {
                SDL_RenderTexture(Renderer, Tir1.texture, nullptr, &Tir1.rect);
            }
        }

        // Mettre à jour et rendre le tir de l'ennemi s'il est actif
        

        // présenter le rendu
        SDL_RenderPresent(Renderer);
    }



    void nettoyageSDL (SDL_Window* Window , SDL_Renderer* Renderer)
    {
        SDL_DestroyRenderer (Renderer);
        SDL_DestroyWindow (Window);
        SDL_Quit();
    }

    void collision(SDL_Renderer* Renderer)
        {  
            // collision entre enemies et tir de joueur

            for(auto& p : Rendu::Joueur1.projectiles)
            {
                if (p.Pactive == false)
                {
                    continue ;
                }
                else 
                {
                    for (auto& e : Enemies::listeEnnemis)
                    {
                        if (e.Eactive == false)
                        {
                            continue;
                        }
                        else
                        {
                            if (SDL_HasRectIntersectionFloat(&p.rect , &e.recte))
                            {
                                e.Eactive = false;
                                p.Pactive = false;
                                e.exploser(Renderer , explosiontexture);
                            }
                        }
                    }
                }
            }

            // collision entre joueur et tirs enemies

            for (auto& p : Enemies::listeEnnemis)
            {
                for (auto& en : p.projectiles)
                {
                   if (en.Pactive == false)
                     {
                         continue;
                     }
                    else
                     {
                         if (Rendu::Joueur1.Jactive == false || en.Pactive == false)
                          {
                             continue;
                          }
                         else 
                          {
                             if (SDL_HasRectIntersectionFloat(&en.rect , &Rendu::Joueur1.rectj))
                              {
                            en.Pactive == false;
                            Rendu::Joueur1.Jactive == false;
                            Rendu::Joueur1.exploser(Renderer , explosiontexture);
                              }
                          }
                     }
                }
            }
        }       
}