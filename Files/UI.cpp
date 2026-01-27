#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "UI.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include"Game.h"


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

  void menuprincipalIMGUI (bool& run)
  {
    // gestion de la navigation au clavier
     ImGuiIO& io = ImGui::GetIO();
     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // debut de la frame ImGui
   // ImGui_ImplSDL3_NewFrame();
    // ImGui_ImplSDLRenderer3_NewFrame();
    
   // ImGui::NewFrame();
    ImGui::SetNextWindowPos (ImVec2 (300, 350) , ImGuiCond_Always);
    ImGui::SetNextWindowSize (ImVec2 (200, 150));
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
    

    //buttons du menu principal
    ImGui::Begin ("Menu Principal" , nullptr , window_flags);
   
    ImVec2 button_size = ImVec2(-1 , 40);

    if (ImGui::Button ("1 Joueur", button_size))
    {
       // activer l'état de jeu : passer en mode "playing"
       Games::Playing = true;
    }
      if (ImGui::IsWindowAppearing())
      {
        ImGui::SetKeyboardFocusHere();  // initialiser le focus sur le premier button
      }

       ImGui::Dummy (ImVec2 (0, 10)); // espace entre les boutons

    if (ImGui::Button ("Quitter" , button_size))
    { 
      run = false;
    }

    // fin de la frame ImGui
    ImGui::End();
    // ImGui::Render();

    // ImGui_ImplSDLRenderer3_RenderDrawData (ImGui::GetDrawData(), Renderer);

    

  }

  void PlayingImGui(Joueur& player)
  {
   /* ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();

      // score dans le coins haut droit

      ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 210, 10), ImGuiCond_Always);
      ImGui::SetNextWindowPos(ImVec2(200, 40));

      ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;

      ImGui::Begin("ScoreHUD", nullptr, flags);
      ImGui::Text("Score : %d", score);
      ImGui::End();
      ImGui::Render();
      ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);


      // vies dans le coin bas gauche

      ImGui::SetNextWindowPos(ImVec2(10, io.DisplaySize.y - 50), ImGuiCond_Always);
      ImGui::SetNextWindowPos(ImVec2(200, 40));

      ImGui::Begin("LivesHUD", nullptr, flags);
      ImGui::Text("Vies : %d", vies);
      ImGui::End();

      ImGui::Render();

      ImGui_ImplSDLRenderer3_RenderDrawData (ImGui::GetDrawData(), Renderer); */

      ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings |  ImGuiWindowFlags_NoFocusOnAppearing;

    // SCORE (haut droit)

    
    

    ImVec2 scoreSize(400, 60);
    ImVec2 scorePos( io.DisplaySize.x - scoreSize.x - 10, 10);

    ImGui::SetNextWindowPos(scorePos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(scoreSize);

    ImGui::Begin("ScoreHUD", nullptr, flags);
    ImGui::Text("Score : %d", player.score);
    ImGui::End();

    
    // VIES (bas gauche)

     const float iconSize = 32.0f;
     const float spacing  = 3.0f;
     int vies = player.vies;
    ImVec2 livesSize (vies * (iconSize + spacing) + 10, iconSize + 10);
    ImVec2 liveswindowSize(vies* (iconSize + spacing) + 10 , iconSize + 10);
    ImVec2 livesPos( 10,  io.DisplaySize.y - livesSize.y - 10);

    ImGui::SetNextWindowPos(livesPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(liveswindowSize);

    ImGui::Begin("LivesHUD", nullptr, flags);
    
    for (int i = 0 ; i < vies ; ++i)
    {
      ImGui::Image((ImTextureID)Rendu::joueurtexture, ImVec2(iconSize, iconSize));

      if (i < vies - 1)
      {
        ImGui::SameLine(0.0f, spacing);
      }
    }


    ImGui::End();

  }

  // nettoyage de ImGui
   void nettoyageImgui()
   {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
   }
}
