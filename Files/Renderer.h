#include<SDL3/SDL.h>
namespace Rendu 
{ 
   struct vector
   {
     float x;
     float y;
   };
   extern vector positionjoueur;

   void MenuPrincipal(SDL_Renderer* Renderer);

   void playing (SDL_Renderer* Renderer);

   void projectilesjoueur (SDL_Renderer* Renderer , float x , float y);

   void projectilesennemi (SDL_Renderer* Renderer , float x , float y);
   
   void initGameTextures(SDL_Renderer* Renderer);
   
   void cleanupGameTextures();

   void nettoyageSDL (SDL_Window* Window , SDL_Renderer* Renderer);
}
