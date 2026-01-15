#include<SDL3/SDL.h>
#include<SDL_image/SDL_image.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "Game.h"
#include "Renderer.h"
#include"UI.h"
#include"Utils.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>

// Définitions des variables globales déclarées extern dans Utils.h

// ce namespace va contenir toutes les fonctions de jeu
namespace Games
{

       

 // lancement du jeu 
 void mainmenu ()
 {
   bool playing = true;
   
    // initialisation video et audio
        SDL_Init (SDL_INIT_VIDEO);

        // cretion de fenetre
        SDL_Window* Window= SDL_CreateWindow ("space invaders" , 800 , 800 , SDL_WINDOW_RESIZABLE);
        
        // creation d'un rendu
        SDL_Renderer* Renderer = SDL_CreateRenderer(Window , nullptr);

        // initialisation de ImGui
        ImGUI::InitialiserImgui(Window , Renderer);

        // charger les images du jeu 
        Rendu::initGameTextures(Renderer);

    // boucle d'evenements
    bool run = true ;
    SDL_Event e;
    Uint64 lastTick = SDL_GetTicks();  // variable qui recupere le temps actuel

     while(run)
     {
        // Traiter tous les événements
        while (SDL_PollEvent(&e))
        {
           // transmettre l'événement à ImGui
           ImGui_ImplSDL3_ProcessEvent(&e);

           if (e.type == SDL_EVENT_QUIT)
           {
              run = false ;
           }
          
           if (e.type == SDL_EVENT_KEY_DOWN)
           {
              switch(e.key.key)
              {
                
                case SDLK_ESCAPE: playing = false ; break;
               
              }
           }

           
        }  
        
        const bool* state = SDL_GetKeyboardState(nullptr);
         
        
        

         

        // Rendu par frame (ne pas bloquer)
        SDL_RenderClear (Renderer);
        
        if (playing == false)
        { 
           Rendu::MenuPrincipal (Renderer);
           ImGUI::menuprincipalIMGUI (Window , Renderer , run, playing);
        }
        else
        { 
           
           Rendu::playing(Renderer);
        }

        SDL_Delay (16); // pour limiter à environ 60 FPS
     }

      ImGUI::nettoyageImgui(Window , Renderer);
      Rendu::cleanupGameTextures();
      Rendu::nettoyageSDL (Window , Renderer);
 }

  /* void collision()
 {
   for (auto& p : Joueur1.projectiles)
   {
      if ( p.Pactive == false)
      {
         continue;
      }

      for (auto& e : Rendu::listeEnnemis)
      {
                if( e.Eactive  == true && SDL_HasRectIntersectionFloat (&p.rect , &e.recte) )
                {
                  p.Pactive = false ; 
                  e.Eactive = false ;
                }

      }
   }
 } */
} // fin du namespace Games