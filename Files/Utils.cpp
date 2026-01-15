#include "Utils.h"
#include<ctime>
#include<stdlib.h>
#include<SDL3/SDL.h>
#include<windows.h>


// constructeurs joueur

Joueur::Joueur()
{
    joueurtexture = nullptr;
    explosiontexture = nullptr;
    tirtexture = nullptr;

    posj.x = 400.0f;
    posj.y = 700.0f;

    rectj.w = 50.0f;
    rectj.h = 50.0f;
    rectj.x = posj.x;
    rectj.y = posj.y;

    speed = 10.0f;
    Vies = 3;

    Jactive = true;
}

Joueur::~Joueur()
{
    // destructeur vide : les textures sont gérées dans RenduGlobals
}

// initialisation des fonction du joueur

void Joueur::Initialisation(SDL_Texture* j , SDL_Texture* ex ,SDL_Texture*t , float x , float y )
{
      joueurtexture = j;
      explosiontexture = ex;
      tirtexture = t;

      posj.x = x;
      posj.y = y;

      rectj.x = x;
      rectj.y = y;

      Jactive = true;
}

void Joueur::Evenements(const bool* state)
{
    
    
        if (state[SDL_SCANCODE_A])
        {
            posj.x -= speed;
        }

        if (state[SDL_SCANCODE_D])
        {
            posj.x += speed;
        }

        if (state[SDL_SCANCODE_T])
        {
               Uint64 TempsActuel = SDL_GetTicks(); // Recupere le temps actuel

               if (TempsActuel > dernierTir + delaiTir)
               {
                    Projectile p;

                    p.Pactive = true;

                    
                        p.texture = tirtexture;
                        p.pos.x = posj.x ;
                        p.pos.y = posj.y - 20.0f;
                        p.rect.w = 20.0f;
                        p.rect.h = 30.0f;
                        p.rect.x = p.pos.x ;
                        p.rect.y = p.pos.y ;

                        p.speed = 10.0f; // 10 pixels par frame

                        // gerer plusieurs projectiles
                        projectiles.push_back(p);

                 dernierTir = TempsActuel; // mise a jour du moment du dernier tir
               }    
        }
                
        
    

      // empecher le joueur de sortir de la fenetre
    if (posj.x < 25.0f)
    {
        posj.x = 25.0f ;
    }
    if (posj.x > 775.0f)
    {
        posj.x = 775.0f;
    }
}

void Joueur::exploser(SDL_Renderer* Renderer , SDL_Texture* boom)
{
    Uint64 debut = SDL_GetTicks();
    if (debut > debutexplosion + dureexplosion)
    {
       
        joueurtexture = boom;
        SDL_RenderTexture(Renderer , joueurtexture , nullptr , &rectj );


    }
     Jactive == false;
    joueurtexture = nullptr;
}

void Joueur::Update()
{
    rectj.x = posj.x;
    rectj.y = posj.y;

    for (auto &p : projectiles) // parcourir tous les projectiles du conteneur STD::VECTOR
    {
        if (p.Pactive == true)
        {
            p.pos.y -= p.speed;
            p.rect.y = p.pos.y;
            if (p.pos.y + p.rect.h < 0.0f)
            {
                 p.Pactive = false;
            }
        }
    }
} 

void Joueur::Rendu(SDL_Renderer* Renderer)
{
    if (Jactive == true)
    {
        SDL_RenderTexture(Renderer, joueurtexture, nullptr, &rectj);
    }
    else if (SDL_GetTicks() < debutexplosion + dureexplosion )
    {
        SDL_RenderTexture(Renderer, explosiontexture, nullptr, &rectj);
    }

    // Rendre les projectiles actifs
    for (auto &p : projectiles) // parcourir tous les projectiles du conteneur STD::VECTOR
    {
        if (p.Pactive == true)
        {
            SDL_FRect dest = p.rect;
            SDL_RenderTexture(Renderer, p.texture, nullptr, &dest);
        }
    }
} 





// constructeurs ennemis
Enemies::Enemies()
{
   enemytexture = nullptr;
   explosiontexture = nullptr;
   tirtexture = nullptr;
   

    recte.w = 50.0f;
    recte.h = 50.0f;
    recte.x = pose.x;
    recte.y = pose.y;

    speed = 5.0f;
    Eactive = true;

    

}

Enemies::~Enemies()
{
    // destructeur vide : pas de ressources à libérer ici
}

// initialisation des fonction des ennemis

void Enemies::Initialisation(SDL_Texture* en , SDL_Texture* e , SDL_Texture* t , float x , float y)
{
        enemytexture = en;
        explosiontexture = e;
        tirtexture = t;

        pose.x = x;
        pose.y = y;
    
        recte.x = pose.x;
        recte.y = pose.y;
        speed = 5.0f;
    
        Eactive = true;
}

void Enemies::Evenements()
{
    // emettre un tir si le nombre aleatoire est compris entre 51 et 74
    
    if (Eactive == true)
    {
        Uint64 TempsActuel = SDL_GetTicks();
        if (TempsActuel > dernierTir + delaiTir)
        {
            Projectile p;
            p.Pactive = true;
            p.texture = tirtexture;
            p.pos.x = pose.x;
            p.pos.y = pose.y + recte.h;
            p.rect.w = 20.0f;
            p.rect.h = 30.0f;
            p.rect.x = p.pos.x;
            p.rect.y = p.pos.y;
            p.speed = 5.0f;
            projectiles.push_back(p);

            dernierTir = TempsActuel;
        }
         // delai pour eviter plusieurs tirs en une frame
    }

    // empecher l'ennemi de sortir de la fenetre
    if (pose.x < 25.0f)
    {
        pose.x = 25.0f ;
    }
    if (pose.x > 775.0f)
    {
        pose.x = 775.0f;
    }

    
} 

 /* void Enemies::collision()
{
    for (auto& p : Joueur1.projectiles)
    {
        if (p.Pactive && Enemy.Eactive)
        {
            if  ( SDL_HasRectIntersectionFloat(&p.rect , &Enemy.recte))
            {
                p.Pactive = false ;
                Enemy1.Eactive = false ;
                Enemy1.debutexplosion = SDL_GetTicks( );
            }
        }
    }
}
    */

    void Enemies::exploser(SDL_Renderer* Renderer , SDL_Texture* boom)
{
    Uint64 debut = SDL_GetTicks();
    if (debut > debutexplosion + dureexplosion)
    {
        
        enemytexture = boom;
        SDL_RenderTexture(Renderer , enemytexture , nullptr , &recte );
        
    }
    enemytexture = nullptr;
    Eactive == false;
}

void Enemies::Update()
{
   pose.x += speed;
   
   if (pose.x >= 775.0f)
   {
       pose.x = 775.0f;
       speed = -speed;  // quand il atteint un mur il change de direction
   }

   else if (pose.x <= 25.0f)
   {
    pose.x = 25.0f;
    speed = -speed;
   }

   recte.x = pose.x;
   recte.y = pose.y;

    for (auto &p : projectiles)
    {
        if (p.Pactive == true)
        {
            p.pos.y += p.speed;
            p.rect.y = p.pos.y;
            if (p.pos.y > 800.0f) 
            {
                p.Pactive = false; // desactiver le projectile si il sort de la fenetre
            }
        }
    }

   
} 


void Enemies::Rendu(SDL_Renderer* Renderer)
{
     Uint64 TempsActuel = SDL_GetTicks();

    if (Eactive == true)
    {
        SDL_RenderTexture(Renderer, enemytexture, nullptr, &recte);
    }
    else if (TempsActuel < debutexplosion + dureexplosion)
    {
        SDL_RenderTexture(Renderer , explosiontexture , nullptr , &recte);
    }

    for (auto &p : projectiles)
    {
        if (p.Pactive == true)
        {
            SDL_RenderTexture(Renderer, p.texture, nullptr, &p.rect);
        }
    }
} 
