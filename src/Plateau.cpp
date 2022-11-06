#include <iostream>
#include <windows.h>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include "../include/Plateau.hpp"
#include "../include/MiniMax.hpp"
#include "../include/AlphaBeta.hpp"

wchar_t forme1[]=L"▄", forme2[]=L"▀", forme3[]=L"█", forme4[]=L" ", forme5[]=L"▄▀", forme6[]=L"▀▄";
using namespace std;

Plateau::Plateau(){
minimax = new MiniMax;
//MiniMax oyur;
wcout << "Construction Du Plateau" << endl;
}

Plateau::~Plateau(){
wcout << "Destruction Du Pluteau" << endl;
}

void Plateau::initialiser_le_plateau(){
    for(int i=0 ;i<24 ;i++)LePlateau[i]='0';
}


//fonction pour répéter le dessine d'une forme de base{forme1,forme2,forme3,forme4,forme5,forme6}
void Plateau::dessiner(wchar_t *chaine ,int repetition){
    HANDLE  Console;
    Console = GetStdHandle(STD_OUTPUT_HANDLE);
    _setmode(_fileno(stdout), _O_U8TEXT);
    color _color;
    if(chaine==forme1||chaine==forme2||chaine==forme3)_color=darkgray;
    if(chaine==forme4)_color=white;
    if(chaine==forme5||chaine==forme6)_color=gray;
    for(int i=0 ;i<repetition ;i++){
            SetConsoleTextAttribute(Console, _color);
            wcout<<chaine;
    }
}

//fonction pour dessiner un pion
void Plateau::dessiner_pion(int position){
    int compteur =0;
        for(int i=0 ;i<24 ;i++){
            if(position==compteur){
                HANDLE  Console;
                Console = GetStdHandle(STD_OUTPUT_HANDLE);
                _setmode(_fileno(stdout), _O_U8TEXT);
                color _color;
                if(LePlateau[i]=='0')_color=yellow;
                if(LePlateau[i]=='1')_color=green;
                if(LePlateau[i]=='2')_color=blue;
                SetConsoleTextAttribute(Console, _color);
                if(compteur<10)wcout << L" ";
                wcout << compteur;
            }
            compteur++;
        }
 }


 //fonctionn pour dessiner une forme
void Plateau::dessiner_forme(wchar_t *forme1 ,int repetition1,wchar_t *forme2 ,int repetition2){
    dessiner(forme1 ,repetition1);
    dessiner(forme2 ,repetition2);
    dessiner(forme1 ,repetition1);
}


//fonction pour dessiner un morceau
 void Plateau::dessiner_morceau(morceau UnMorceau,int argument){
    switch(UnMorceau){
    case LeMorceau1://█▄▀▄▀▄▀▄▀▄▀▄▀█
        dessiner_forme(forme3 ,1,forme5 ,argument);
        break;
    case LeMorceau2://"▄▄▄▄▄▄▄"
        dessiner(forme1 ,argument);
        break;
    case LeMorceau3://"▀▀▀▀▀▀▀▀"
        dessiner(forme2 ,argument);
        break;
    case LeMorceau4://L"      "
        dessiner(forme4 ,argument);
        break;
    case LeMorceau5://L"█\██ "
        dessiner(forme3,1);
        dessiner_pion(argument);
        dessiner(forme4 ,1);
        break;
    case LeMorceau6://L" ██ "
        dessiner(forme4 ,1);
        dessiner_pion(argument);
        dessiner(forme4 ,1);
        break;
    case LeMorceau7://L" ██\█"
        dessiner(forme4 ,1);
        dessiner_pion(argument);
        dessiner(forme3,1);
        break;
    case LeMorceau8://█▄▄█
        dessiner_forme(forme3 ,1,forme1 ,2);
        break;
    case LeMorceau9://█▀▀█
        dessiner_forme(forme3 ,1,forme2 ,2);
        break;
    }
 }

 //fonction pour dessiner une ligne
void Plateau::dessiner_ligne(morceau morceau1,int argument1,morceau morceau2,int argument2,morceau morceau3,int argument3,morceau morceau4,int argument4,morceau morceau5,int argument5,morceau morceau6,int argument6,morceau morceau7,int argument7,morceau morceau8,int argument8,morceau morceau9,int argument9,morceau morceau10,int argument10,morceau morceau11,int argument11,morceau morceau12,int argument12,morceau morceau13,int argument13){
     dessiner_morceau(morceau1,argument1);
     dessiner_morceau(morceau2,argument2);
     dessiner_morceau(morceau3,argument3);
     dessiner_morceau(morceau4,argument4);
     dessiner_morceau(morceau5,argument5);
     dessiner_morceau(morceau6,argument6);
     dessiner_morceau(morceau7,argument7);
     dessiner_morceau(morceau8,argument8);
     dessiner_morceau(morceau9,argument9);
     dessiner_morceau(morceau10,argument10);
     dessiner_morceau(morceau11,argument11);
     dessiner_morceau(morceau12,argument12);
     dessiner_morceau(morceau13,argument13);
}


//fonction pour dessiner le plateau
void Plateau::AfficherConsol(){

        wcout<<"\t";dessiner_ligne(LeMorceau2,84);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau5,0,LeMorceau1,17,LeMorceau6,1,LeMorceau1,17,LeMorceau7,2);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau8,1,LeMorceau3,36,LeMorceau8,1,LeMorceau3,36,LeMorceau8,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau2,30,LeMorceau9,1,LeMorceau2,30,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau5,3,LeMorceau1,12,LeMorceau6,4,LeMorceau1,12,LeMorceau7,5,LeMorceau4,6,LeMorceau1,1);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau8,1,LeMorceau3,26,LeMorceau8,1,LeMorceau3,26,LeMorceau8,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau2,20,LeMorceau9,1,LeMorceau2,20,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau5,6,LeMorceau1,7,LeMorceau6,7,LeMorceau1,7,LeMorceau7,8,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau8,1,LeMorceau3,36,LeMorceau8,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau9,1,LeMorceau2,6,LeMorceau9,1,LeMorceau2,6,LeMorceau9,1,LeMorceau4,36,LeMorceau9,1,LeMorceau2,6,LeMorceau9,1,LeMorceau2,6,LeMorceau9,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau5,9,LeMorceau1,2,LeMorceau6,10,LeMorceau1,2,LeMorceau7,11,LeMorceau4,36,LeMorceau5,12,LeMorceau1,2,LeMorceau6,13,LeMorceau1,2,LeMorceau7,14);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau8,1,LeMorceau3,6,LeMorceau8,1,LeMorceau3,6,LeMorceau8,1,LeMorceau4,36,LeMorceau8,1,LeMorceau3,6,LeMorceau8,1,LeMorceau3,6,LeMorceau8,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau9,1,LeMorceau2,36,LeMorceau9,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau5,15,LeMorceau1,7,LeMorceau6,16,LeMorceau1,7,LeMorceau7,17,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau3,20,LeMorceau8,1,LeMorceau3,20,LeMorceau4,6,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,26,LeMorceau1,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau9,1,LeMorceau2,26,LeMorceau9,1,LeMorceau2,26,LeMorceau9,1,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau5,18,LeMorceau1,12,LeMorceau6,19,LeMorceau1,12,LeMorceau7,20,LeMorceau4,6,LeMorceau1,1);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,6,LeMorceau3,30,LeMorceau8,1,LeMorceau3,30,LeMorceau4,6,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau1,1,LeMorceau4,36,LeMorceau1,1,LeMorceau4,36,LeMorceau1,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau9,1,LeMorceau2,36,LeMorceau9,1,LeMorceau2,36,LeMorceau9,1);wcout<<endl;
        wcout<<"\t";dessiner_ligne(LeMorceau5,21,LeMorceau1,17,LeMorceau6,22,LeMorceau1,17,LeMorceau7,23);wcout<<endl;//pions
        wcout<<"\t";dessiner_ligne(LeMorceau3,84);wcout<<endl;
}

//fonction pour choisir lequel des deux joueurs va commencer.
void Plateau::OrdreDesJoueurs()
{
     int choix;
     srand (time(NULL));
     choix= rand() % 2 + 1;
    if(choix==1){
        wcout << "la machine commence" << endl;
        Joueur1=1;
     }
     else{
        wcout << "vous commencez" << endl;
        Joueur1=0;
     }
}


//fonction pour vérifier si une case est pleine par type de pion donné ( pion1 ou pion2)
int Plateau::CasePleine(char *UnPlateau, int Position ,char Pion)
{
    if(UnPlateau[Position]==Pion)return 0;
    else return -1;
}


//fonction pour vérifier si une case est vide
int Plateau::CaseVide(char *UnPlateau, int Position)
{
    if(UnPlateau[Position]=='0')return 0;
    else return -1;
}


//fonction pour ajouter un pion au plateau
void Plateau::AjouterPion(int Position ,char Pion ,int PionCapturer)
{
    LePlateau[Position]=Pion;
    if(ConsolGraphic==1)AfficherConsol();
    else{
        if(PionCapturer==-2)Mix_PlayChannel(-1, sdl->effect1, 0);
        else Mix_PlayChannel(-1, sdl->effect2, 0);
        sdl->afficher(LePlateau);
    }
    if(PionCapturer!=-1&&PionCapturer!=-2){
        LePlateau[PionCapturer]='0';
        wcout << "moulin ! " << endl;
        wcout << "la machine capture le Pion : " << PionCapturer << endl;
        if(ConsolGraphic==1){
            AfficherConsol();
        }
        else {
            sdl->afficher(LePlateau);
            Mix_PlayChannel(-1, sdl->effect4, 0);
        }
    }
    else CapturerPion(Position,Pion);
}

//fonction pour suprimer un pion du tableau
void Plateau::SuprimerPion(int Position)
{
    LePlateau[Position]='0';
}

//fonction pour vérifier si un mouvement est possible
int Plateau::MouvementPossible(char *UnPlateau, int source ,int destination ,char Pion)
{
        if(NombreDesPions(UnPlateau,Pion)==3){
            if(CasePleine(UnPlateau,source,Pion)==0&&CaseVide(UnPlateau,destination)==0)return 0;
            else return -1;
        }
        else{
            if(CasePleine(UnPlateau,source,Pion)==0&&Voisinages(source,destination)==0&&CaseVide(UnPlateau,destination)==0)return 0;
            else return -1;
        }
}


//fonction pour déplacer un pion
int Plateau::DeplacerPion(char Pion)
{
    bool MauvaisChoix=false;
    int source,destination;
    string src,dest;

         do{
            if(MauvaisChoix)wcout << L"Le mouvement n'est pas possible ressayer avec d'autres valeurs," << endl;
            if(ConsolGraphic==1){
            wcout << " donner une case source : ";
            getline(cin,src);
            wcout << " donner une case destination : ";
            getline(cin,dest);
            source=ChoixValide(src);
            destination=ChoixValide(dest);
            }
            else {
                if(MauvaisChoix)Mix_PlayChannel(-1,sdl->effect7,0);
                source=sdl->input(this,Pion);
                destination=sdl->input(this,'0');
            }
            MauvaisChoix=true;
        }while(MouvementPossible(LePlateau, source ,destination ,Pion)!=0);

    char aide=' ';
    aide=LePlateau[source];
    LePlateau[source]=LePlateau[destination];
    LePlateau[destination]=aide;
    if(ConsolGraphic==1)AfficherConsol();
    else {
        Mix_PlayChannel(-1,sdl->effect5,0);
        sdl->afficher(LePlateau);
    }
    CapturerPion(destination,Pion);
    return destination;
}


//fonction pour vérifier si un choix est valide
int Plateau::ChoixValide(string Choix){
    //for(int i=20 ;i<23 ;i++)if(i==((Choix[0]-48)*20+Choix[1]-48))return i;
        for(int i=10 ;i<24 ;i++)if(i==((Choix[0]-48)*10+Choix[1]-48)&&(Choix[0]-48)<3)return i;
        for(int i=0 ;i<10 ;i++)if(i==Choix[0]-48)return i;
    return -1;
}


//fonction qui donne la mains au joueur pour joueur
int Plateau::JouerJoueur(char Pion){
    bool MauvaisChoix=false;
        int Position;
        string Choix;
        do{
            do{
                if(MauvaisChoix)wcout << " Le choix n'est pas valide, donner une autre position : ";
                else wcout << " donner une position : ";
                getline(cin,Choix);
                MauvaisChoix=true;
                Position=ChoixValide(Choix);
            }while(Position==-1);
        }while(CaseVide(LePlateau,Position)==-1);
        return Position;
}


//fonction qui simule la première phase du jeu
void Plateau::PremierePhaseDuJeu()
{
    if(ConsolGraphic==1)AfficherConsol();
    else sdl->afficher(LePlateau);
    etat EtatMachine;
    if(Joueur1==1){
        int PositionDuJoueur=0;
        for(int i=0; i<9 ;i++){
            if(ConsolGraphic==1){
                if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this,PositionDuJoueur);
                else EtatMachine=alphabeta->JoueurAlphaBeta(this,PositionDuJoueur);
                wcout << "la machine choisit : " << EtatMachine.position << endl;
                AjouterPion(EtatMachine.position,'1',EtatMachine.Pioncapturer);
                NombreDesPionsPoser++;
                PositionDuJoueur=JouerJoueur('2');
                AjouterPion(PositionDuJoueur,'2',-2);
                NombreDesPionsPoser++;
            }
            else{
                if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this,PositionDuJoueur);
                else EtatMachine=alphabeta->JoueurAlphaBeta(this,PositionDuJoueur);
                wcout << "la machine choisit : " << EtatMachine.position << endl;
                AjouterPion(EtatMachine.position,'1',EtatMachine.Pioncapturer);
                NombreDesPionsPoser++;
                int PositionDuJoueur=sdl->input(this,'0');
                AjouterPion(PositionDuJoueur,'2',-2);
                NombreDesPionsPoser++;
            }
        }
    }
    else for(int i=0; i<9 ;i++){
            if(ConsolGraphic==1){
                int PositionDuJoueur=JouerJoueur('2');
                AjouterPion(PositionDuJoueur,'2',-2);
                NombreDesPionsPoser++;
                if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this,PositionDuJoueur);
                else EtatMachine=alphabeta->JoueurAlphaBeta(this,PositionDuJoueur);
                wcout << "la machine choisit : " << EtatMachine.position << endl;
                AjouterPion(EtatMachine.position,'1',EtatMachine.Pioncapturer);
                NombreDesPionsPoser++;
            }
            else {
                int PositionDuJoueur=sdl->input(this,'0');
                AjouterPion(PositionDuJoueur,'2',-2);
                NombreDesPionsPoser++;
                if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this,PositionDuJoueur);
                else EtatMachine=alphabeta->JoueurAlphaBeta(this,PositionDuJoueur);
                wcout << "la machine choisit : " << EtatMachine.position << endl;
                AjouterPion(EtatMachine.position,'1',EtatMachine.Pioncapturer);
                NombreDesPionsPoser++;
            }
            //minimax&alpha_beta
        }
}


//fonction pour vérifier si un pion est dans les voisinages d'un case
int Plateau::Voisinages(int source,int PositionTest)
{
    switch(source){
        case 0 : if(PositionTest==1||PositionTest==9)return 0;break;
        case 1 : if(PositionTest==0||PositionTest==2||PositionTest==4)return 0;break;
        case 2 : if(PositionTest==1||PositionTest==14)return 0;break;
        case 3 : if(PositionTest==4||PositionTest==10)return 0;break;
        case 4 : if(PositionTest==1||PositionTest==3||PositionTest==5||PositionTest==7)return 0;break;
        case 5 : if(PositionTest==4||PositionTest==13)return 0;break;
        case 6 : if(PositionTest==7||PositionTest==11)return 0;break;
        case 7 : if(PositionTest==4||PositionTest==6||PositionTest==8)return 0;break;
        case 8 : if(PositionTest==7||PositionTest==12)return 0;break;
        case 9 : if(PositionTest==0||PositionTest==10||PositionTest==21)return 0;break;
        case 10 : if(PositionTest==3||PositionTest==9||PositionTest==11||PositionTest==18)return 0;break;
        case 11 : if(PositionTest==6||PositionTest==10||PositionTest==15)return 0;break;
        case 12 : if(PositionTest==8||PositionTest==13||PositionTest==17)return 0;break;
        case 13 : if(PositionTest==5||PositionTest==12||PositionTest==14||PositionTest==20)return 0;break;
        case 14 : if(PositionTest==2||PositionTest==13||PositionTest==23)return 0;break;
        case 15 : if(PositionTest==11||PositionTest==16)return 0;break;
        case 16 : if(PositionTest==15||PositionTest==17||PositionTest==19)return 0;break;
        case 17 : if(PositionTest==12||PositionTest==16)return 0;break;
        case 18 : if(PositionTest==10||PositionTest==19)return 0;break;
        case 19 : if(PositionTest==16||PositionTest==18||PositionTest==20||PositionTest==22)return 0;break;
        case 20 : if(PositionTest==13||PositionTest==19)return 0;break;
        case 21 : if(PositionTest==9||PositionTest==22)return 0;break;
        case 22 : if(PositionTest==19||PositionTest==21||PositionTest==23)return 0;break;
        case 23 : if(PositionTest==14||PositionTest==22)return 0;break;

    }
    return -1;
}


//fonction qui simule la deuxième phase du jeu
void Plateau::DeuxiemePhaseDuJeu()
{
    bool stop=false;
    etat EtatMachine;
    while(stop==false){
        if(Joueur1==1){
            if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this);
            else EtatMachine=alphabeta->JoueurAlphaBeta(this);
            wcout << "la machine passe de la case " << EtatMachine.precdent << " a la case " << EtatMachine.position << endl;
            LePlateau[EtatMachine.position]='1';
            LePlateau[EtatMachine.precdent]='0';
            if(EtatMachine.Pioncapturer!=-1){
                wcout << "moulin !" << endl << "la machine capture le Pion : " << EtatMachine.Pioncapturer << endl;
                LePlateau[EtatMachine.Pioncapturer]='0';
                if(ConsolGraphic==2)Mix_PlayChannel(-1,sdl->effect4,0);
            }
            if(ConsolGraphic==1)AfficherConsol();
            else {
                Mix_PlayChannel(-1,sdl->effect6,0);
                sdl->afficher(LePlateau);
            }
            if(ArreterLeJeu('2')==-1){
                stop=true;
                Joueur1Lose=0;
            }

            else {
                DeplacerPion('2');
                if(ConsolGraphic==1)AfficherConsol();
                else {
                    Mix_PlayChannel(-1,sdl->effect5,0);
                    sdl->afficher(LePlateau);
                }
                if(ArreterLeJeu('1')==-1){
                    stop=true;
                    Joueur1Lose=1;
                }
            }
        }
        else{
            int position=DeplacerPion('2');
            if(ConsolGraphic==1)AfficherConsol();
            else {
                Mix_PlayChannel(-1,sdl->effect5,0);
                sdl->afficher(LePlateau);
            }
            if(ArreterLeJeu('1')==-1){
                stop=true;
                Joueur1Lose=1;
            }
            else{
                if(MiniMaxAlphaBeta==1)EtatMachine=minimax->JoueurMiniMax(this,position);
                else EtatMachine=alphabeta->JoueurAlphaBeta(this,position);
                wcout << "la machine passe de la case " << EtatMachine.precdent << " a la case " << EtatMachine.position << endl;
                LePlateau[EtatMachine.position]='1';
                LePlateau[EtatMachine.precdent]='0';
                if(EtatMachine.Pioncapturer!=-1){
                    wcout << " moulin !" << endl << "la machine capture le Pion : " << EtatMachine.Pioncapturer << endl;
                    LePlateau[EtatMachine.Pioncapturer]='0';
                    if(ConsolGraphic==2)Mix_PlayChannel(-1,sdl->effect4,0);
                }
                if(ConsolGraphic==1)AfficherConsol();
                else {
                    Mix_PlayChannel(-1,sdl->effect6,0);
                    sdl->afficher(LePlateau);
                }
                if(ArreterLeJeu('2')==-1){
                    stop=true;
                    Joueur1Lose=0;
                }
            }
        }
    }
}


//fonction pour calculer le nombre des Pions d'un joueur
int Plateau::NombreDesPions(char *UnPlateau,char Pion)
{
    int compteur=0;
    for(int i=0 ;i<24 ;i++){
        if(UnPlateau[i]==Pion)compteur++;
    }
    return compteur++;
}


//fonction qui vérifier pour un Pion s'il fait partir d'un moulin ou non
int Plateau::moulin(char *UnPlateau,int position ,char Pion)
{
    int moulin=0;
    switch(position){
        case 0 : if((UnPlateau[9]==Pion&&UnPlateau[21]==Pion)||(UnPlateau[1]==Pion&&UnPlateau[2]==Pion)) moulin=2;break;
        case 1 : if((UnPlateau[7]==Pion&&UnPlateau[4]==Pion)||(UnPlateau[0]==Pion&&UnPlateau[2]==Pion)) moulin=2;break;
        case 2 : if((UnPlateau[14]==Pion&&UnPlateau[23]==Pion)||(UnPlateau[0]==Pion&&UnPlateau[1]==Pion)) moulin=2;break;
        case 3 : if((UnPlateau[10]==Pion&&UnPlateau[18]==Pion)||(UnPlateau[4]==Pion&&UnPlateau[5]==Pion)) moulin=2;break;
        case 4 : if((UnPlateau[1]==Pion&&UnPlateau[7]==Pion)||(UnPlateau[3]==Pion&&UnPlateau[5]==Pion)) moulin=2;break;
        case 5 : if((UnPlateau[13]==Pion&&UnPlateau[20]==Pion)||(UnPlateau[3]==Pion&&UnPlateau[4]==Pion)) moulin=2;break;
        case 6 : if((UnPlateau[11]==Pion&&UnPlateau[15]==Pion)||(UnPlateau[7]==Pion&&UnPlateau[8]==Pion)) moulin=2;break;
        case 7 : if((UnPlateau[1]==Pion&&UnPlateau[4]==Pion)||(UnPlateau[6]==Pion&&UnPlateau[8]==Pion)) moulin=2;break;
        case 8 : if((UnPlateau[12]==Pion&&UnPlateau[17]==Pion)||(UnPlateau[6]==Pion&&UnPlateau[7]==Pion)) moulin=2;break;
        case 9 : if((UnPlateau[0]==Pion&&UnPlateau[21]==Pion)||(UnPlateau[10]==Pion&&UnPlateau[11]==Pion)) moulin=2;break;
        case 10 : if((UnPlateau[3]==Pion&&UnPlateau[18]==Pion)||(UnPlateau[9]==Pion&&UnPlateau[11]==Pion)) moulin=2;break;
        case 11 : if((UnPlateau[6]==Pion&&UnPlateau[15]==Pion)||(UnPlateau[9]==Pion&&UnPlateau[10]==Pion)) moulin=2;break;
        case 12 : if((UnPlateau[8]==Pion&&UnPlateau[17]==Pion)||(UnPlateau[13]==Pion&&UnPlateau[14]==Pion)) moulin=2;break;
        case 13 : if((UnPlateau[5]==Pion&&UnPlateau[20]==Pion)||(UnPlateau[12]==Pion&&UnPlateau[14]==Pion)) moulin=2;break;
        case 14 : if((UnPlateau[2]==Pion&&UnPlateau[23]==Pion)||(UnPlateau[12]==Pion&&UnPlateau[13]==Pion)) moulin=2;break;
        case 15 : if((UnPlateau[6]==Pion&&UnPlateau[11]==Pion)||(UnPlateau[16]==Pion&&UnPlateau[17]==Pion)) moulin=2;break;
        case 16 : if((UnPlateau[19]==Pion&&UnPlateau[22]==Pion)||(UnPlateau[15]==Pion&&UnPlateau[17]==Pion)) moulin=2;break;
        case 17 : if((UnPlateau[8]==Pion&&UnPlateau[12]==Pion)||(UnPlateau[15]==Pion&&UnPlateau[16]==Pion)) moulin=2;break;
        case 18 : if((UnPlateau[3]==Pion&&UnPlateau[10]==Pion)||(UnPlateau[19]==Pion&&UnPlateau[20]==Pion)) moulin=2;break;
        case 19 : if((UnPlateau[16]==Pion&&UnPlateau[22]==Pion)||(UnPlateau[18]==Pion&&UnPlateau[20]==Pion)) moulin=2;break;
        case 20 : if((UnPlateau[5]==Pion&&UnPlateau[13]==Pion)||(UnPlateau[18]==Pion&&UnPlateau[19]==Pion)) moulin=2;break;
        case 21 : if((UnPlateau[0]==Pion&&UnPlateau[9]==Pion)||(UnPlateau[22]==Pion&&UnPlateau[23]==Pion)) moulin=2;break;
        case 22 : if((UnPlateau[16]==Pion&&UnPlateau[19]==Pion)||(UnPlateau[21]==Pion&&UnPlateau[23]==Pion)) moulin=2;break;
        case 23 : if((UnPlateau[2]==Pion&&UnPlateau[14]==Pion)||(UnPlateau[21]==Pion&&UnPlateau[22]==Pion)) moulin=2;break;
    }
    if(moulin==2){
        if(UnPlateau[position]==Pion)moulin=3;
        else moulin=-1;
    }
    if(moulin==0){
        switch(position){
            case 0 :
                if((UnPlateau[9]=='0'&&UnPlateau[21]==Pion)||(UnPlateau[1]=='0'&&UnPlateau[2]==Pion)) moulin=1;
                if((UnPlateau[9]==Pion&&UnPlateau[21]=='0')||(UnPlateau[1]==Pion&&UnPlateau[2]=='0')) moulin=1;
                break;
            case 1 :
                if((UnPlateau[7]=='0'&&UnPlateau[4]==Pion)||(UnPlateau[0]=='0'&&UnPlateau[2]==Pion)) moulin=1;
                if((UnPlateau[7]==Pion&&UnPlateau[4]=='0')||(UnPlateau[0]==Pion&&UnPlateau[2]=='0')) moulin=1;
                break;
            case 2 :
                if((UnPlateau[14]=='0'&&UnPlateau[23]==Pion)||(UnPlateau[0]=='0'&&UnPlateau[1]==Pion)) moulin=1;
                if((UnPlateau[14]==Pion&&UnPlateau[23]=='0')||(UnPlateau[0]==Pion&&UnPlateau[1]=='0')) moulin=1;
                break;
            case 3 :
                if((UnPlateau[10]=='0'&&UnPlateau[18]==Pion)||(UnPlateau[4]=='0'&&UnPlateau[5]==Pion)) moulin=1;
                if((UnPlateau[10]==Pion&&UnPlateau[18]=='0')||(UnPlateau[4]==Pion&&UnPlateau[5]=='0')) moulin=1;
                break;
            case 4 :
                if((UnPlateau[1]=='0'&&UnPlateau[7]==Pion)||(UnPlateau[3]=='0'&&UnPlateau[5]==Pion)) moulin=1;
                if((UnPlateau[1]==Pion&&UnPlateau[7]=='0')||(UnPlateau[3]==Pion&&UnPlateau[5]=='0')) moulin=1;
                break;
            case 5 :
                if((UnPlateau[13]=='0'&&UnPlateau[20]==Pion)||(UnPlateau[3]=='0'&&UnPlateau[4]==Pion)) moulin=1;
                if((UnPlateau[13]==Pion&&UnPlateau[20]=='0')||(UnPlateau[3]==Pion&&UnPlateau[4]=='0')) moulin=1;
                break;
            case 6 :
                if((UnPlateau[11]=='0'&&UnPlateau[15]==Pion)||(UnPlateau[7]=='0'&&UnPlateau[8]==Pion)) moulin=1;
                if((UnPlateau[11]==Pion&&UnPlateau[15]=='0')||(UnPlateau[7]==Pion&&UnPlateau[8]=='0')) moulin=1;
                break;
            case 7 :
                if((UnPlateau[1]=='0'&&UnPlateau[4]==Pion)||(UnPlateau[6]=='0'&&UnPlateau[8]==Pion)) moulin=1;
                if((UnPlateau[1]==Pion&&UnPlateau[4]=='0')||(UnPlateau[6]==Pion&&UnPlateau[8]=='0')) moulin=1;
                break;
            case 8 :
                if((UnPlateau[12]=='0'&&UnPlateau[17]==Pion)||(UnPlateau[6]=='0'&&UnPlateau[7]==Pion)) moulin=1;
                if((UnPlateau[12]==Pion&&UnPlateau[17]=='0')||(UnPlateau[6]==Pion&&UnPlateau[7]=='0')) moulin=1;
                break;
            case 9 :
                if((UnPlateau[0]=='0'&&UnPlateau[21]==Pion)||(UnPlateau[10]=='0'&&UnPlateau[11]==Pion)) moulin=1;
                if((UnPlateau[0]==Pion&&UnPlateau[21]=='0')||(UnPlateau[10]==Pion&&UnPlateau[11]=='0')) moulin=1;
                break;
            case 10 :
                if((UnPlateau[3]=='0'&&UnPlateau[18]==Pion)||(UnPlateau[9]=='0'&&UnPlateau[11]==Pion)) moulin=1;
                if((UnPlateau[3]==Pion&&UnPlateau[18]=='0')||(UnPlateau[9]==Pion&&UnPlateau[11]=='0')) moulin=1;
                break;
            case 11 :
                if((UnPlateau[6]=='0'&&UnPlateau[15]==Pion)||(UnPlateau[9]=='0'&&UnPlateau[10]==Pion)) moulin=1;
                if((UnPlateau[6]==Pion&&UnPlateau[15]=='0')||(UnPlateau[9]==Pion&&UnPlateau[10]=='0')) moulin=1;
                break;
            case 12 :
                if((UnPlateau[8]=='0'&&UnPlateau[17]==Pion)||(UnPlateau[13]=='0'&&UnPlateau[14]==Pion)) moulin=1;
                if((UnPlateau[8]==Pion&&UnPlateau[17]=='0')||(UnPlateau[13]==Pion&&UnPlateau[14]=='0')) moulin=1;
                break;
            case 13 :
                if((UnPlateau[5]=='0'&&UnPlateau[20]==Pion)||(UnPlateau[12]=='0'&&UnPlateau[14]==Pion)) moulin=1;
                if((UnPlateau[5]==Pion&&UnPlateau[20]=='0')||(UnPlateau[12]==Pion&&UnPlateau[14]=='0')) moulin=1;
                break;
            case 14 :
                if((UnPlateau[2]=='0'&&UnPlateau[23]==Pion)||(UnPlateau[12]=='0'&&UnPlateau[13]==Pion)) moulin=1;
                if((UnPlateau[2]==Pion&&UnPlateau[23]=='0')||(UnPlateau[12]==Pion&&UnPlateau[13]=='0')) moulin=1;
                break;
            case 15 :
                if((UnPlateau[6]=='0'&&UnPlateau[11]==Pion)||(UnPlateau[16]=='0'&&UnPlateau[17]==Pion)) moulin=1;
                if((UnPlateau[6]==Pion&&UnPlateau[11]=='0')||(UnPlateau[16]==Pion&&UnPlateau[17]=='0')) moulin=1;
                break;
            case 16 :
                if((UnPlateau[19]=='0'&&UnPlateau[22]==Pion)||(UnPlateau[15]=='0'&&UnPlateau[17]==Pion)) moulin=1;
                if((UnPlateau[19]==Pion&&UnPlateau[22]=='0')||(UnPlateau[15]==Pion&&UnPlateau[17]=='0')) moulin=1;
                break;
            case 17 :
                if((UnPlateau[8]=='0'&&UnPlateau[12]==Pion)||(UnPlateau[15]=='0'&&UnPlateau[16]==Pion)) moulin=1;
                if((UnPlateau[8]==Pion&&UnPlateau[12]=='0')||(UnPlateau[15]==Pion&&UnPlateau[16]=='0')) moulin=1;
                break;
            case 18 :
                if((UnPlateau[3]=='0'&&UnPlateau[10]==Pion)||(UnPlateau[19]=='0'&&UnPlateau[20]==Pion)) moulin=1;
                if((UnPlateau[3]==Pion&&UnPlateau[10]=='0')||(UnPlateau[19]==Pion&&UnPlateau[20]=='0')) moulin=1;
                break;
            case 19 :
                if((UnPlateau[16]=='0'&&UnPlateau[22]==Pion)||(UnPlateau[18]=='0'&&UnPlateau[20]==Pion)) moulin=1;
                if((UnPlateau[16]==Pion&&UnPlateau[22]=='0')||(UnPlateau[18]==Pion&&UnPlateau[20]=='0')) moulin=1;
                break;
            case 20 :
                if((UnPlateau[5]=='0'&&UnPlateau[13]==Pion)||(UnPlateau[18]=='0'&&UnPlateau[19]==Pion)) moulin=1;
                if((UnPlateau[5]==Pion&&UnPlateau[13]=='0')||(UnPlateau[18]==Pion&&UnPlateau[19]=='0')) moulin=1;
                break;
            case 21 :
                if((UnPlateau[0]=='0'&&UnPlateau[9]==Pion)||(UnPlateau[22]=='0'&&UnPlateau[23]==Pion)) moulin=1;
                if((UnPlateau[0]==Pion&&UnPlateau[9]=='0')||(UnPlateau[22]==Pion&&UnPlateau[23]=='0')) moulin=1;
                break;
            case 22 :
                if((UnPlateau[16]=='0'&&UnPlateau[19]==Pion)||(UnPlateau[21]=='0'&&UnPlateau[23]==Pion)) moulin=1;
                if((UnPlateau[16]==Pion&&UnPlateau[19]=='0')||(UnPlateau[21]==Pion&&UnPlateau[23]=='0')) moulin=1;
                break;
            case 23 :
                if((UnPlateau[2]=='0'&&UnPlateau[14]==Pion)||(UnPlateau[21]=='0'&&UnPlateau[22]==Pion)) moulin=1;
                if((UnPlateau[2]==Pion&&UnPlateau[14]=='0')||(UnPlateau[21]==Pion&&UnPlateau[22]=='0')) moulin=1;
                break;
        }
        if(moulin==1){
            if(UnPlateau[position]==Pion)moulin=2;
        }
        else moulin=-1;
    }
    return moulin;
}


//fonction qui vérifie si un joueur viens de construire un moulin, et si oui elle donne la mains pour capturer un pions de l'adversair
void Plateau::CapturerPion(int destination, char Pion)
{
    if(moulin(LePlateau,destination,Pion)==3){
        string Position;
        int Choix=-3;
        char Pion2=Pion%2+49;
        for(int i=0 ;i<24 ;i++){
            if(LePlateau[i]==Pion2)
            if(moulin(LePlateau,i,Pion2)!=3){
                Choix=-2;
                i=24;
            }
        }
        if(Choix==-2){
            do{
                do{
                    if(Choix!=-2)wcout << "Le choix n'est pas valide" << endl;
                    wcout << "Donner la position du pion que vous voulez capturer : ";
                    if(ConsolGraphic==1){
                        getline(cin,Position);
                        Choix=ChoixValide(Position);
                    }
                    else Choix=sdl->input(this,Pion2);
                }while(Choix==-1);
            }while(LePlateau[Choix]!=Pion2||moulin(LePlateau,Choix,Pion2)==3);
            SuprimerPion(Choix);
            if(ConsolGraphic==1)AfficherConsol();
            else {
                sdl->afficher(LePlateau);
                Mix_PlayChannel(-1, sdl->effect3, 0);
            }
            wcout << "le Pion est bien capturer :)" << endl;
        }
        else {
            wcout << "oups! l'adversaire n'a que des moulin, vous pouver pas capturer un pion :(" << endl;
            //AfficherConsol();
        }
    }
}

//fonction qui vérifier si l'un des joueur à deux pions ou n'a pas la posssiblité de déplacer aucun pion
int Plateau::ArreterLeJeu(char Pion)
{
    if(NombreDesPions(LePlateau,'1')>2&&NombreDesPions(LePlateau,'2')>2){
        if(NombreDesPions(LePlateau,Pion)>3){
            return PasDeMouvement(LePlateau,Pion);
        }
        else return 0;
    }
    else return -1;
}
int Plateau::PasDeMouvement(char *UnPlateau, char Pion){
    for(int i=0 ;i<24 ;i++){
        if(UnPlateau[i]==Pion){
            switch(i){
                case 0 : if(UnPlateau[1]=='0'||UnPlateau[9]=='0')return 0;break;
                case 1 : if(UnPlateau[0]=='0'||UnPlateau[2]=='0'||UnPlateau[4]=='0')return 0;break;
                case 2 : if(UnPlateau[1]=='0'||UnPlateau[14]=='0')return 0;break;
                case 3 : if(UnPlateau[4]=='0'||UnPlateau[10]=='0')return 0;break;
                case 4 : if(UnPlateau[1]=='0'||UnPlateau[3]=='0'||UnPlateau[5]=='0'||UnPlateau[7]=='0')return 0;break;
                case 5 : if(UnPlateau[4]=='0'||UnPlateau[13]=='0')return 0;break;
                case 6 : if(UnPlateau[7]=='0'||UnPlateau[11]=='0')return 0;break;
                case 7 : if(UnPlateau[4]=='0'||UnPlateau[6]=='0'||UnPlateau[8]=='0')return 0;break;
                case 8 : if(UnPlateau[7]=='0'||UnPlateau[12]=='0')return 0;break;
                case 9 : if(UnPlateau[0]=='0'||UnPlateau[10]=='0'||UnPlateau[21]=='0')return 0;break;
                case 10 : if(UnPlateau[3]=='0'||UnPlateau[9]=='0'||UnPlateau[11]=='0'||UnPlateau[18]=='0')return 0;break;
                case 11 : if(UnPlateau[6]=='0'||UnPlateau[10]=='0'||UnPlateau[15]=='0')return 0;break;
                case 12 : if(UnPlateau[8]=='0'||UnPlateau[13]=='0'||UnPlateau[17]=='0')return 0;break;
                case 13 : if(UnPlateau[5]=='0'||UnPlateau[12]=='0'||UnPlateau[14]=='0'||UnPlateau[20]=='0')return 0;break;
                case 14 : if(UnPlateau[2]=='0'||UnPlateau[13]=='0'||UnPlateau[23]=='0')return 0;break;
                case 15 : if(UnPlateau[11]=='0'||UnPlateau[16]=='0')return 0;break;
                case 16 : if(UnPlateau[15]=='0'||UnPlateau[17]=='0'||UnPlateau[19]=='0')return 0;break;
                case 17 : if(UnPlateau[12]=='0'||UnPlateau[16]=='0')return 0;break;
                case 18 : if(UnPlateau[10]=='0'||UnPlateau[19]=='0')return 0;break;
                case 19 : if(UnPlateau[16]=='0'||UnPlateau[18]=='0'||UnPlateau[20]=='0'||UnPlateau[22]=='0')return 0;break;
                case 20 : if(UnPlateau[13]=='0'||UnPlateau[19]=='0')return 0;break;
                case 21 : if(UnPlateau[9]=='0'||UnPlateau[22]=='0')return 0;break;
                case 22 : if(UnPlateau[19]=='0'||UnPlateau[21]=='0'||UnPlateau[23]=='0')return 0;break;
                case 23 : if(UnPlateau[14]=='0'||UnPlateau[22]=='0')return 0;break;
            }
        }
    }
    return -1;
}
/*
        wcout << L"\t";wcout << L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" <<endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_pion_joueur1);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L" █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█ ";SetConsoleTextAttribute(hConsole, color_du_pion_joueur2);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L" █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█ ";SetConsoleTextAttribute(hConsole, color_du_pion_joueur1);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▄";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▄";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▄";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                    █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                    █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                        █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                          █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                        █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                          █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_du_pion_joueur1);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_du_pion_joueur1);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                        █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                          █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                        █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                          █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█      ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀      █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                    █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                  █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█                                    █";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█";SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀";SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"█";SetConsoleTextAttribute(hConsole, color_du_pion_joueur2);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_du_pion_joueur1);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_du_plateau);wcout<<L"▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀";SetConsoleTextAttribute(hConsole, color_du_pion_joueur2);wcout<<pion1;SetConsoleTextAttribute(hConsole, color_de_la_frantiere);wcout<<L"█" << endl;
        wcout << L"\t";wcout << L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" <<endl;
        SetConsoleTextAttribute(hConsole, 15);
        _setmode(_fileno(stdout), _O_TEXT);
        cout << "bla bla " <<endl;
        cout << "bla bla " <<endl;cout << "bla bla " <<endl;cout << "bla bla " <<endl;cout << "bla bla " <<endl;



    /   wcout << L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" <<endl;  1          1█ 3▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
        wcout << L"█▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█" << endl;  3       2█ 4▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
        wcout << L"█▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█" << endl; 3(4)+2+3+2+3  3 1█▄▀█  2█▀▄█
        wcout << L"█▄▀█                                  █▄▀█                                    █▄▀█" << endl;  3+5+3+5+3   4 █▀▀█  █▄▄█
        wcout << L"█▄▀█                                  █▄▀█                                    █▄▀█" << endl;     //      5 "     "
        wcout << L"█▄▀█      ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄      █▄▀█" << endl; 3+5+1+3+1+5+3
        wcout << L"█▄▀█      █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█      █▄▀█" << endl; 3+5+3+5+3
        wcout << L"█▄▀█      █▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█      █▄▀█" << endl; 3+5+3+2+3+2+3+5+3
        wcout << L"█▄▀█      █▄▀█                        █▄▀█                          █▄▀█      █▄▀█" << endl; 3+5+3+5+3+5+3+5+3
        wcout << L"█▄▀█      █▄▀█                        █▄▀█                          █▄▀█      █▄▀█" << endl; //
        wcout << L"█▄▀█      █▄▀█      ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄      █▄▀█      █▄▀█" << endl; 3+5+3+5+1+3+1+5+3+5+3
        wcout << L"█▄▀█      █▄▀█      █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█      █▄▀█      █▄▀█" << endl; 3+5+3+5+3+5+3+5+3
        wcout << L"█▄▀█      █▄▀█      █▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█      █▄▀█      █▄▀█" << endl; 3+5+3+5+3+2+3+5+3+5+3
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl; 3+5+3+5+3+5+3+5+3+5+3
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl; //
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl; //
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl; //
        wcout << L"█▄▀█▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄█▄▀█                                  █▄▀█▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄█▄▀█" << endl; 3+1+3+1+3+5+3+1+3+1+3
        wcout << L"█▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█                                  █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█" << endl; 3+5+3
        wcout << L"█▄▀█▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀█▄▀█                                  █▄▀█▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀█▄▀█" << endl;  symérique (on remplace 1 par 2 et 2 par 1)
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀█                                  █▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█      ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀      █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█                        █▄▀█                          █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█                        █▄▀█                          █▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      █▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█      █▄▀█" << endl;
        wcout << L"█▄▀█      ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀      █▄▀█" << endl;
        wcout << L"█▄▀█                                  █▄▀█                                    █▄▀█" << endl;
        wcout << L"█▄▀█                                  █▄▀█                                    █▄▀█" << endl;
        wcout << L"█▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▀█" << endl;
        wcout << L"█▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█" << endl;
        wcout << L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" <<endl;

        */

