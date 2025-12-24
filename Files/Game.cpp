#include<SDL3/SDL.h>
#include<SDL_image/SDL_image.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "Game.h"
#include "Renderer.h"
#include<iostream>

// ce namespace va contenir toutes les fonctions de jeu
namespace Games
{
 // lancement du jeu 
void mainmenu ()
{
   // initialisation video et audio
    SDL_Init (SDL_INIT_VIDEO);

    // cretion de fenetre
    SDL_Window* Window= SDL_CreateWindow ("space invaders" , 800 , 600 , SDL_WINDOW_RESIZABLE);
    
    // creation d'un rendu
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window , nullptr);

    // intialisation de Dear ImGui

        // creation du contexte ImGui
        
        ImGui::CreateContext();
      

     // 2. Initialiser les plateformes (le lien entre la fenêtre et le rendu)
         ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer);
         ImGui_ImplSDLRenderer3_Init(Renderer);
   
     // selection d'un style
        ImGui::StyleColorsDark();


    // boucle d'evenements
    bool run = true ;
    SDL_Event e;

     while(run)
     {
        while (SDL_PollEvent(&e))
        {
           if (e.type== SDL_EVENT_QUIT)
           {
              run = false ;
           }
        }

         Rendu::MenuPrincipal (Renderer);
     }
    
   
}
}