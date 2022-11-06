#ifndef SDL_HPP
#define SDL_HPP




#include <iostream>
#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Plateau.hpp"

class Plateau;
class SDL{
friend class Plateau;
public :
    SDL();
    ~SDL();
    void SDL_ExitWithErrors();
    void DesignerForme(SDL_Surface *srcsurface, SDL_Surface *destsurface, SDL_Rect *srcrect, SDL_Rect *destrect);
    void afficher(char *UnPlateau);
    void moulin(char *UnPlateau, int position);
    void Menu(Plateau *UnPlateau);
    int input(Plateau *UnPlateau,char Pion);
    void FPS(unsigned int *lastTime,unsigned int *currentTime);
    Mix_Chunk *effect1=NULL,*effect2=NULL,*effect3=NULL,*effect4=NULL,*effect5=NULL,*effect6=NULL,*effect7=NULL,*effect8=NULL,*effect9=NULL,*effect10=NULL;
    Mix_Music *music=NULL;
private :
    int musicON=1,effectON=1;
    //SDL_Window *window;
    //SDL_Surface *ecran,*icon;
};


#endif // SDL_HPP
