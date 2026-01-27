#include <SDL3/SDL.h>
#include "Utils.h"


namespace ImGUI 
{
      extern SDL_Texture* joueurtexture;
      

  void InitialiserImgui(SDL_Window* Window , SDL_Renderer* Renderer);

  void menuprincipalIMGUI (bool& run);

  void PlayingImGui(Joueur& player);

  void nettoyageImgui();

}
