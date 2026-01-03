#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "UI.h"
#include "Renderer.h"
#include <SDL3/SDL.h>


namespace ImGUI 
{
  void InitialiserImgui(SDL_Window* Window , SDL_Renderer* Renderer)
  {
    // creation du contexte ImGui
    ImGui::CreateContext();
    
    ImGui_ImplSDL3_InitForSDLRenderer (Window , Renderer);
    ImGui_ImplSDLRenderer3_Init (Renderer);

    // selection du theme
    ImGui::StyleColorsDark();


  }

  void menuprincipalIMGUI (SDL_Window* Window , SDL_Renderer* Renderer , bool& run, bool& playing)
  {
    // debut de la frame ImGui
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos (ImVec2 (250, 300) , ImGuiCond_Always);
    ImGui::SetNextWindowSize (ImVec2 (100, 100));
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
    

    //buttons du menu principal
    ImGui::Begin ("Menu Principal" , nullptr , window_flags);
    if (ImGui::Button ("1 Joueur"))
    {
       // activer l'état de jeu : passer en mode "playing"
       playing = true;
    }
    
       ImGui::Dummy (ImVec2 (0, 10)); // espace entre les boutons

    if (ImGui::Button ("Quitter"))
    { 
      run = false;
    }

    // fin de la frame ImGui
    ImGui::End();
    ImGui::Render();

    ImGui_ImplSDLRenderer3_RenderDrawData (ImGui::GetDrawData(), Renderer);

    // présenter le rendu combiné (background + ImGui)
    SDL_RenderPresent(Renderer);

  }

  // nettoyage de ImGui
   void nettoyageImgui(SDL_Window* Window , SDL_Renderer* Renderer)
   {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
   }
}
