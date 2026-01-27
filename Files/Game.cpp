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
      bool Playing = false;
      

 // lancement du jeu 
 void mainmenu ()
 {

   
    // initialisation video et audio
        SDL_Init (SDL_INIT_VIDEO);

        // cretion de fenetre
        SDL_Window* Window= SDL_CreateWindow ("space invaders" , 800 , 800, 0  );
        
        // creation d'un rendu
        SDL_Renderer* Renderer = SDL_CreateRenderer(Window , nullptr);

        // initialisation de ImGui
        ImGUI::InitialiserImgui(Window , Renderer);

        // charger les images du jeu 
        Rendu::initGameTextures(Renderer);

    // boucle d'evenements
    bool run = true ;
    SDL_Event e;
   // Uint64 lastTick = SDL_GetTicks();  // variable qui recupere le temps actuel

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
                
                case SDLK_ESCAPE: Playing = false ; break;
               
              }
           }

           
        }  
        
      //  const bool* state = SDL_GetKeyboardState(nullptr);
         
        
        

         

        // Rendu par frame (ne pas bloquer)
        SDL_SetRenderDrawColor(Renderer, 0 , 0 , 0 , 255);
        SDL_RenderClear (Renderer);
        
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        
        if (Playing == false)
        { 
           Rendu::MenuPrincipal (Renderer);
           ImGUI::menuprincipalIMGUI (run);
           
           
        }
        else
        { 
           Rendu::playing(Renderer);
           ImGUI::PlayingImGui( Rendu::Joueur1);

         

           
        }

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);

        

        SDL_RenderPresent(Renderer);
        SDL_Delay (16); // pour limiter à environ 60 FPS
     }

      ImGUI::nettoyageImgui();
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