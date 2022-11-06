#include <iostream>
#include <string>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL.hpp"
#include "../include/Plateau.hpp"

using namespace std;
SDL_Window *window;
SDL_Surface *ecran;
unsigned int lastTime = 0, currentTime;

SDL::SDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2,30)!=0){
        SDL_ExitWithErrors();
    }
    Mix_AllocateChannels(8);
    music =Mix_LoadMUS("src/sons/music.mp3");
    effect1 = Mix_LoadWAV("src/sons/click.wav");
    effect2 = Mix_LoadWAV("src/sons/machine_click.wav");
    effect3 = Mix_LoadWAV("src/sons/moulin.wav");
    effect4 = Mix_LoadWAV("src/sons/machine_moulin.wav");
    effect5 = Mix_LoadWAV("src/sons/mouve.wav");
    effect6 = Mix_LoadWAV("src/sons/machine_mouve.wav");
    effect7 = Mix_LoadWAV("src/sons/choix_invalide.wav");
    effect8 = Mix_LoadWAV("src/sons/button.wav");
    effect9 = Mix_LoadWAV("src/sons/you_win.wav");
    effect10 = Mix_LoadWAV("src/sons/you_lose.wav");
    //icon=IMG_Load("../src/images/icon.ico");
    //if(icon==NULL)exit(EXIT_FAILURE);
    //SDL_SetWindowIcon(window,icon);
}
SDL::~SDL(){
    //SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
void SDL::SDL_ExitWithErrors()
{
    SDL_Log("%s\n", SDL_GetError());
    exit(EXIT_FAILURE);
}

void SDL::DesignerForme(SDL_Surface *srcsurface, SDL_Surface *destsurface, SDL_Rect *srcrect, SDL_Rect *destrect){
    SDL_BlitSurface(srcsurface,srcrect, destsurface,destrect);
}


void SDL::afficher(char *UnPlteau){
    SDL_Surface *srcsurface;
    SDL_Rect destrect;
    destrect.h=45,destrect.w=45;

    srcsurface=IMG_Load("src/images/bord.png");
    if(srcsurface==NULL)SDL_ExitWithErrors();
    DesignerForme(srcsurface,ecran, NULL, NULL);
    SDL_FreeSurface(srcsurface);
    SDL_UpdateWindowSurface(window);



    for(int i=0; i<24; i++){
        switch(i){
            case 0: destrect.x=27;destrect.y=41;break;
            case 1: destrect.x=256;destrect.y=41;break;
            case 2: destrect.x=483;destrect.y=41;break;
            case 3: destrect.x=97;destrect.y=112;break;
            case 4: destrect.x=256;destrect.y=112;break;
            case 5: destrect.x=411;destrect.y=112;break;
            case 6: destrect.x=167;destrect.y=180;break;
            case 7: destrect.x=256;destrect.y=180;break;
            case 8: destrect.x=343;destrect.y=180;break;
            case 9: destrect.x=27;destrect.y=269;break;
            case 10: destrect.x=97;destrect.y=269;break;
            case 11: destrect.x=167;destrect.y=269;break;
            case 12: destrect.x=343;destrect.y=269;break;
            case 13: destrect.x=411;destrect.y=269;break;
            case 14: destrect.x=483;destrect.y=269;break;
            case 15: destrect.x=167;destrect.y=358;break;
            case 16: destrect.x=256;destrect.y=358;break;
            case 17: destrect.x=343;destrect.y=358;break;
            case 18: destrect.x=97;destrect.y=426;break;
            case 19: destrect.x=256;destrect.y=426;break;
            case 20: destrect.x=411;destrect.y=426;break;
            case 21: destrect.x=27;destrect.y=497;break;
            case 22: destrect.x=256;destrect.y=497;break;
            case 23: destrect.x=483;destrect.y=497;break;
        }
        if(UnPlteau[i]=='1'){
            srcsurface=IMG_Load("src/images/pion1.png");
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_FreeSurface(srcsurface);
        }

        if(UnPlteau[i]=='2'){
            srcsurface=IMG_Load("src/images/pion2.png");
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_FreeSurface(srcsurface);
        }
    }
    SDL_UpdateWindowSurface(window);

}


int SDL::input(Plateau *UnPlateau,char Pion){
    int choix=-1;
    SDL_Event event;
    bool MouvaisChoix=false;
    while(choix==-1||UnPlateau->LePlateau[choix]!=Pion){
        SDL_UpdateWindowSurface(window);
        if(MouvaisChoix){
            Mix_PlayChannel(-1,effect7,0);
            MouvaisChoix=false;
        }
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x>=27&&event.button.y>=41&&event.button.x<=27+45&&event.button.y<=41+45)choix=0;
                    if(event.button.x>=256&&event.button.y>=41&&event.button.x<=256+45&&event.button.y<=41+45)choix=1;
                    if(event.button.x>=483&&event.button.y>=41&&event.button.x<=483+45&&event.button.y<=41+45)choix=2;
                    if(event.button.x>=97&&event.button.y>=112&&event.button.x<=97+45&&event.button.y<=112+45)choix=3;
                    if(event.button.x>=256&&event.button.y>=112&&event.button.x<=256+45&&event.button.y<=112+45)choix=4;
                    if(event.button.x>=411&&event.button.y>=112&&event.button.x<=411+45&&event.button.y<=112+45)choix=5;
                    if(event.button.x>=167&&event.button.y>=180&&event.button.x<=167+45&&event.button.y<=180+45)choix=6;
                    if(event.button.x>=256&&event.button.y>=180&&event.button.x<=256+45&&event.button.y<=180+45)choix=7;
                    if(event.button.x>=343&&event.button.y>=180&&event.button.x<=343+45&&event.button.y<=180+45)choix=8;
                    if(event.button.x>=27&&event.button.y>=269&&event.button.x<=27+45&&event.button.y<=269+45)choix=9;
                    if(event.button.x>=97&&event.button.y>=269&&event.button.x<=97+45&&event.button.y<=269+45)choix=10;
                    if(event.button.x>=167&&event.button.y>=269&&event.button.x<=167+45&&event.button.y<=269+45)choix=11;
                    if(event.button.x>=343&&event.button.y>=269&&event.button.x<=343+45&&event.button.y<=269+45)choix=12;
                    if(event.button.x>=411&&event.button.y>=269&&event.button.x<=411+45&&event.button.y<=269+45)choix=13;
                    if(event.button.x>=483&&event.button.y>=269&&event.button.x<=483+45&&event.button.y<=269+45)choix=14;
                    if(event.button.x>=167&&event.button.y>=358&&event.button.x<=167+45&&event.button.y<=358+45)choix=15;
                    if(event.button.x>=256&&event.button.y>=358&&event.button.x<=256+45&&event.button.y<=358+45)choix=16;
                    if(event.button.x>=343&&event.button.y>=358&&event.button.x<=343+45&&event.button.y<=358+45)choix=17;
                    if(event.button.x>=97&&event.button.y>=426&&event.button.x<=97+45&&event.button.y<=426+45)choix=18;
                    if(event.button.x>=256&&event.button.y>=426&&event.button.x<=256+45&&event.button.y<=426+45)choix=19;
                    if(event.button.x>=411&&event.button.y>=426&&event.button.x<=411+45&&event.button.y<=426+45)choix=20;
                    if(event.button.x>=27&&event.button.y>=497&&event.button.x<=27+45&&event.button.y<=497+45)choix=21;
                    if(event.button.x>=256&&event.button.y>=497&&event.button.x<=256+45&&event.button.y<=497+45)choix=22;
                    if(event.button.x>=483&&event.button.y>=497&&event.button.x<=483+45&&event.button.y<=497+45)choix=23;
                    if(choix==-1)Mix_PlayChannel(-1,effect7,0);
                    MouvaisChoix=true;
                    break;
                    case SDL_QUIT: SDL_DestroyWindow(window);
                        Mix_CloseAudio();
                        exit(0);
                        break;
            }
        }
        currentTime = SDL_GetTicks();
        FPS(&lastTime,&currentTime);
    }
    return choix;
}

void SDL::moulin(char *UnPlateau, int position){

}


void SDL::Menu(Plateau *UnPlateau){

    window = SDL_CreateWindow("Jeu Du Moulin",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        // la fennetre ne peut pas etre creér
        printf("Could not create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);

    SDL_Surface *srcsurface,*icon;

    icon=IMG_Load("src/images/icon2.png");
    if(icon==NULL)exit(EXIT_FAILURE);
    SDL_SetWindowIcon(window,icon);
    SDL_FreeSurface(icon);

    SDL_Rect destrect;

    ecran=SDL_GetWindowSurface(window);




    SDL_Event event,event1,event2;
    bool fermer=false;
    while(!fermer){

            srcsurface=IMG_Load("src/images/accueil.png");
            if(srcsurface==NULL)SDL_ExitWithErrors();
            DesignerForme(srcsurface,ecran, NULL, NULL);
            SDL_FreeSurface(srcsurface);

            lastTime=SDL_GetTicks();
            srcsurface=IMG_Load("src/images/titre.png");
            destrect.x=200;destrect.y=50;destrect.h=80;destrect.w=400;
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_FreeSurface(srcsurface);


            srcsurface=IMG_Load("src/images/play1.png");
            destrect.x=292;destrect.y=200;destrect.h=85;destrect.w=215;
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_FreeSurface(srcsurface);


            srcsurface=IMG_Load("src/images/options1.png");
            destrect.x=292;destrect.y=320;destrect.h=85;destrect.w=215;
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_FreeSurface(srcsurface);


            srcsurface=IMG_Load("src/images/quit1.png");
            destrect.x=292;destrect.y=440;destrect.h=85;destrect.w=215;
            DesignerForme(srcsurface,ecran, NULL, &destrect);
            SDL_UpdateWindowSurface(window);
            SDL_FreeSurface(srcsurface);



            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_MOUSEBUTTONDOWN:
                        switch(event.button.button){
                            case SDL_BUTTON_LEFT:
                                if( event.button.x>294 && event.button.x<505 && event.button.y>202 && event.button.y<282){
                                    //SDL_WaitEvent( &event );
                                    //while()
                                    //event.button.x=0;
                                    Mix_PlayChannel(-1, effect8, 0);
                                    srcsurface=IMG_Load("src/images/play2.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=200;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_UpdateWindowSurface(window);
                                    SDL_FreeSurface(srcsurface);
                                    SDL_Delay(200);
                                    //SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
                                    //SDL_Delay(150);
                                    //SDL_PumpEvents();
                                     srcsurface=IMG_Load("src/images/accueil.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    DesignerForme(srcsurface,ecran, NULL, NULL);
                                    SDL_FreeSurface(srcsurface);

                                    srcsurface=IMG_Load("src/images/titre.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=200;destrect.y=50;destrect.h=80;destrect.w=400;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_FreeSurface(srcsurface);


                                    srcsurface=IMG_Load("src/images/minimax1.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=200;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_FreeSurface(srcsurface);

                                    srcsurface=IMG_Load("src/images/alphabeta1.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=320;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_FreeSurface(srcsurface);

                                    srcsurface=IMG_Load("src/images/back1.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=440;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_UpdateWindowSurface(window);
                                    SDL_FreeSurface(srcsurface);
                                    //SDL_Delay(1000);
                                    bool fermer1=false;
                                    while(!fermer1){
                                        while(SDL_PollEvent(&event1)){
                                            switch(event1.type){
                                                case SDL_MOUSEBUTTONDOWN:
                                                    switch(event1.button.button){
                                                        case SDL_BUTTON_LEFT:
                                                            if(event1.button.x>294 && event1.button.x<505 && event1.button.y>202 && event1.button.y<282){
                                                                Mix_PlayChannel(-1, effect8, 0);
                                                                UnPlateau->MiniMaxAlphaBeta=1;
                                                                srcsurface=IMG_Load("src/images/minimax2.png");
                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=292;destrect.y=200;destrect.h=85;destrect.w=215;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                                SDL_Delay(200);
                                                                //char T[24]={'1','2','2','0','0','1','1','2','2','0','0','1','1','2','2','0','0','1','1','2','2','0','0','1'};
                                                                //afficher(T);
                                                                //SDL_Delay(1000);
                                                                UnPlateau->PremierePhaseDuJeu();
                                                                UnPlateau->DeuxiemePhaseDuJeu();

                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_Delay(500);

                                                                if(UnPlateau->Joueur1Lose==1){
                                                                    Mix_PlayChannel(-1,effect9,0);
                                                                    srcsurface=IMG_Load("src/images/you_win.png");
                                                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                    DesignerForme(srcsurface,ecran, NULL, NULL);
                                                                    SDL_UpdateWindowSurface(window);
                                                                    SDL_FreeSurface(srcsurface);
                                                                    SDL_Delay(2000);
                                                                }
                                                                else{
                                                                     Mix_PlayChannel(-1,effect10,0);
                                                                    srcsurface=IMG_Load("src/images/you_lose.png");
                                                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                    DesignerForme(srcsurface,ecran, NULL, NULL);
                                                                    SDL_UpdateWindowSurface(window);
                                                                    SDL_FreeSurface(srcsurface);
                                                                    SDL_Delay(2000);
                                                                }
                                                                fermer1=true;
                                                                for(int i=0; i<24; i++)UnPlateau->LePlateau[i]='0';
                                                                UnPlateau->NombreDesPionsPoser=0;
                                                                UnPlateau->Joueur1Lose=0;
                                                                break;
                                                            }
                                                            if(event1.button.x>294 && event1.button.x<505 && event1.button.y>322 && event1.button.y<404){
                                                                Mix_PlayChannel(-1, effect8, 0);
                                                                UnPlateau->MiniMaxAlphaBeta=2;
                                                                srcsurface=IMG_Load("src/images/alphabeta2.png");
                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=292;destrect.y=320;destrect.h=85;destrect.w=215;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                                SDL_Delay(200);
                                                                //char T[24]={'1','2','2','0','0','1','1','2','2','0','0','1','1','2','2','0','0','1','1','2','2','0','0','1'};
                                                                //afficher(T);
                                                                //SDL_Delay(1000);
                                                                UnPlateau->PremierePhaseDuJeu();
                                                                UnPlateau->DeuxiemePhaseDuJeu();

                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_Delay(500);
                                                                if(UnPlateau->Joueur1Lose==1){
                                                                    Mix_PlayChannel(-1,effect9,0);
                                                                    srcsurface=IMG_Load("src/images/you_win.png");
                                                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                    DesignerForme(srcsurface,ecran, NULL, NULL);
                                                                    SDL_UpdateWindowSurface(window);
                                                                    SDL_FreeSurface(srcsurface);
                                                                    SDL_Delay(2000);
                                                                }
                                                                else{
                                                                     Mix_PlayChannel(-1,effect10,0);
                                                                    srcsurface=IMG_Load("src/images/you_lose.png");
                                                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                    DesignerForme(srcsurface,ecran, NULL, NULL);
                                                                    SDL_UpdateWindowSurface(window);
                                                                    SDL_FreeSurface(srcsurface);
                                                                    SDL_Delay(2000);
                                                                }
                                                                fermer1=true;
                                                                for(int i=0; i<24; i++)UnPlateau->LePlateau[i]='0';
                                                                UnPlateau->NombreDesPionsPoser=0;
                                                                UnPlateau->Joueur1Lose=0;
                                                                break;
                                                            }
                                                            if(event1.button.x>294 && event1.button.x<505 && event1.button.y>442 && event1.button.y<524){
                                                                Mix_PlayChannel(-1, effect8, 0);
                                                                srcsurface=IMG_Load("src/images/back2.png");
                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=292;destrect.y=440;destrect.h=85;destrect.w=215;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                                SDL_Delay(200);
                                                                fermer1=true;
                                                            }
                                                            break;
                                                        //default: break;
                                                    }
                                                    break;
                                                case SDL_QUIT:
                                                    fermer1=true;
                                                    fermer=true;
                                                    break;
                                                //default: break;
                                            }
                                        }
                                        currentTime = SDL_GetTicks();
                                        FPS(&lastTime,&currentTime);
                                    }

                                }
                                if(event.button.x>294 && event.button.x<505 && event.button.y>322 && event.button.y<404){
                                    Mix_PlayChannel(-1, effect8, 0);
                                    srcsurface=IMG_Load("src/images/options2.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=320;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_UpdateWindowSurface(window);
                                    SDL_FreeSurface(srcsurface);

                                    bool fermer2=false;
                                    while(!fermer2){
                                        srcsurface=IMG_Load("src/images/options3.png");
                                        if(srcsurface==NULL)SDL_ExitWithErrors();
                                        DesignerForme(srcsurface,ecran, NULL, NULL);
                                        SDL_FreeSurface(srcsurface);

                                        if(musicON==1)srcsurface=IMG_Load("src/images/sound.png");
                                        else srcsurface=IMG_Load("src/images/muet.png");
                                        if(srcsurface==NULL)SDL_ExitWithErrors();
                                        destrect.x=490;destrect.y=140;destrect.h=47;destrect.w=50;
                                        DesignerForme(srcsurface,ecran, NULL, &destrect);
                                        SDL_FreeSurface(srcsurface);

                                        if(effectON==1)srcsurface=IMG_Load("src/images/sound.png");
                                        else srcsurface=IMG_Load("src/images/muet.png");
                                        if(srcsurface==NULL)SDL_ExitWithErrors();
                                        destrect.x=490;destrect.y=335;destrect.h=47;destrect.w=50;
                                        DesignerForme(srcsurface,ecran, NULL, &destrect);
                                        SDL_FreeSurface(srcsurface);

                                        srcsurface=IMG_Load("src/images/back1.png");
                                        if(srcsurface==NULL)SDL_ExitWithErrors();
                                        destrect.x=292;destrect.y=460;destrect.h=85;destrect.w=215;
                                        DesignerForme(srcsurface,ecran, NULL, &destrect);
                                        SDL_UpdateWindowSurface(window);
                                        SDL_FreeSurface(srcsurface);

                                        while(SDL_PollEvent(&event2)){
                                            switch(event2.type){
                                                case SDL_MOUSEBUTTONDOWN:
                                                    switch(event2.button.button){
                                                        case SDL_BUTTON_LEFT:
                                                            if(event2.button.x>490&& event2.button.x<540 && event2.button.y>140 && event2.button.y<190){
                                                                Mix_PlayChannel(-1, effect8, 0);
                                                                if(musicON==1){
                                                                    srcsurface=IMG_Load("src/images/muet.png");
                                                                    musicON=0;
                                                                    Mix_VolumeMusic(0);
                                                                }
                                                                else{
                                                                    srcsurface=IMG_Load("src/images/sound.png");
                                                                    musicON=1;
                                                                    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
                                                                }

                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=490;destrect.y=140;destrect.h=47;destrect.w=50;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                            }
                                                            if(event2.button.x>490&& event2.button.x<540 && event2.button.y>335 && event2.button.y<385){
                                                                Mix_PlayChannel(-1, effect8, 0);
                                                                if(effectON==1){
                                                                    srcsurface=IMG_Load("src/images/muet.png");
                                                                    effectON=0;
                                                                    effect1->volume=0;effect2->volume=0;effect3->volume=0;
                                                                    effect4->volume=0;effect5->volume=0;effect6->volume=0;
                                                                    effect7->volume=0;effect8->volume=0;effect9->volume=0;effect10->volume=0;
                                                                }
                                                                else{
                                                                    srcsurface=IMG_Load("src/images/sound.png");
                                                                    effectON=1;
                                                                    effect1->volume=128;effect2->volume=128;effect3->volume=128;
                                                                    effect4->volume=128;effect5->volume=128;effect6->volume=128;
                                                                    effect7->volume=128;effect8->volume=128;effect9->volume=128;effect10->volume=128;
                                                                }

                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=490;destrect.y=140;destrect.h=47;destrect.w=50;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                            }
                                                            if(event2.button.x>292&& event2.button.x<505 && event2.button.y>462 && event2.button.y<544){
                                                                Mix_PlayChannel(-1,effect8,0);
                                                                srcsurface=IMG_Load("src/images/back2.png");
                                                                if(srcsurface==NULL)SDL_ExitWithErrors();
                                                                destrect.x=292;destrect.y=460;destrect.h=85;destrect.w=215;
                                                                DesignerForme(srcsurface,ecran, NULL, &destrect);
                                                                SDL_UpdateWindowSurface(window);
                                                                SDL_FreeSurface(srcsurface);
                                                                SDL_Delay(200);
                                                                fermer2=true;
                                                            }
                                                            break;
                                                    }
                                                    break;
                                             case SDL_QUIT:
                                                fermer2=true;
                                                fermer=true;
                                                break;
                                            }
                                        }
                                        currentTime = SDL_GetTicks();
                                        FPS(&lastTime,&currentTime);
                                    }
                                }
                                if(event.button.x>294 && event.button.x<505 && event.button.y>442 && event.button.y<524){
                                    Mix_PlayChannel(-1, effect8, 0);
                                    srcsurface=IMG_Load("src/images/quit2.png");
                                    if(srcsurface==NULL)SDL_ExitWithErrors();
                                    destrect.x=292;destrect.y=440;destrect.h=85;destrect.w=215;
                                    DesignerForme(srcsurface,ecran, NULL, &destrect);
                                    SDL_UpdateWindowSurface(window);
                                    SDL_FreeSurface(srcsurface);
                                    SDL_Delay(200);
                                    fermer=true;
                                }
                                break;
                            //default: break;
                        }
                        break;
                    case SDL_QUIT:
                        fermer=true;
                        break;
                        //default: break;
                    }
                }

            currentTime = SDL_GetTicks();
            FPS(&lastTime,&currentTime);
    }
    SDL_DestroyWindow(window);
}

void SDL::FPS(unsigned int *lastTime,unsigned int *currentTime){
    if (*currentTime > *lastTime + 50) {
        *lastTime = *currentTime;
    }
    else {
        SDL_Delay(*lastTime + 50-*currentTime);
        *lastTime = *currentTime;
    }
}
