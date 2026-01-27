#include<SDL3/SDL.h>
#include "Utils.h"
namespace Rendu 
{ 

   // Textures partagées
   extern SDL_Texture* joueurtexture;
   extern SDL_Texture* enemytexture;
   extern SDL_Texture* fond_texture;
   extern SDL_Texture* tirtexture;
   extern SDL_Texture* explosiontexture;
   extern SDL_Texture* viestexture;
   extern SDL_Texture* MenuPrincipaltexture;

   // Instances globales
   extern Joueur Joueur1;
   extern Enemies Enemy1;
   extern Projectile Tir1;
   extern Projectile Tir2;

    // extern std::vector<Enemies> Enemies::listeEnnemis; // gestion de plusieurs enemies


   void MenuPrincipal(SDL_Renderer* Renderer);

   void playing (SDL_Renderer* Renderer);

   void projectilesjoueur (SDL_Renderer* Renderer , float x , float y);

   void projectilesennemi (SDL_Renderer* Renderer , float x , float y);
   
   void initGameTextures(SDL_Renderer* Renderer);
   
   void cleanupGameTextures();

   void nettoyageSDL (SDL_Window* Window , SDL_Renderer* Renderer);

   void collision(SDL_Renderer* Renderer);

   void enemiesspawn(int vagues);

   void enemisupdatespawn();
}
