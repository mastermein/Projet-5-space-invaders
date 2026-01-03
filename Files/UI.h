#include <SDL3/SDL.h>

namespace ImGUI 
{
  void InitialiserImgui(SDL_Window* Window , SDL_Renderer* Renderer);

  void menuprincipalIMGUI (SDL_Window* Window , SDL_Renderer* Renderer, bool& run, bool& playing);

  void nettoyageImgui(SDL_Window* Window , SDL_Renderer* Renderer);

}
