#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>
#include <vector>

// structure d'un projectile
struct Projectile
{
    SDL_Texture* texture;
    SDL_FRect rect;
    SDL_FPoint pos;
    float speed;
    bool Pactive;
};

// classe d'un joueur
class Joueur
{
 public:
    Joueur();
    ~Joueur();

    void Initialisation(SDL_Texture* j , SDL_Texture* ex ,SDL_Texture* t , float x , float y );
    void Evenements(const bool* state);
    void exploser(SDL_Renderer* Renderer , SDL_Texture* boom );

    void Update();
    void Rendu(SDL_Renderer* Renderer);

    // gestion des projectiles du joueur (plusieurs projectiles simultanement)
    std::vector<Projectile> projectiles;


    SDL_Texture* joueurtexture;  // image du joueur
    SDL_Texture* explosiontexture; // image d'explosion
    SDL_Texture* tirtexture;  // image de projectile

    SDL_FRect rectj;
    SDL_FPoint posj;

    float speed;   
    int vies;
    bool Jactive;
    bool findepartie;
    static int score;

    Uint64 dernierTir = 0;
    Uint64 delaiTir = 500 ; // vitesse de tir du joueur

    Uint64 debutexplosion = 0;
    Uint64 dureexplosion = 500;
    
};

// structure d'un ennemi
class Enemies 
{  
   public:
      Enemies();
      ~Enemies();
      
    void Initialisation(SDL_Texture* enemytexture, SDL_Texture* explosiontexture, SDL_Texture* tirtexture, float x, float y);
    void Evenements(); 
    void Update();
    void exploser(SDL_Renderer* Renderer , SDL_Texture* boom );
    void Rendu(SDL_Renderer* Renderer);

    // projectiles de l'ennemi (gestion de plusieurs projectiles simultanement)
    std::vector<Projectile> projectiles;

    SDL_Texture* enemytexture;
    SDL_Texture* explosiontexture;
    SDL_Texture* tirtexture;

    SDL_FRect recte;
    SDL_FPoint pose;
    
    //mouvements
    float speedx;
    float speedy;
    bool Eactive;
    bool spawn = false;
    int vagues;

    Uint64 dernierTir = 0;
    Uint64 delaiTir = 2000 ; // L'ennemi tire toutes les secondes
  
    Uint64 debutexplosion = 0;
    Uint64 dureexplosion = 500;
    
    static std::vector<Enemies> listeEnnemis;
};

void collision();


#endif 