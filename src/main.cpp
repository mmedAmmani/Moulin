#include <iostream>
#include <windows.h>
#include <codecvt>
#include <io.h>
#include <fcntl.h>


#include "../include/Plateau.hpp"
#include "../include/MiniMax.hpp"
#include "../include/AlphaBeta.hpp"
#include "../include/SDL.hpp"


enum choix{consol,graphic,minimax,alphabeta};


using namespace std;


int main(int argc, char **argv){
    _setmode(_fileno(stdout), _O_U16TEXT);

    Plateau Monplateau;
    Monplateau.initialiser_le_plateau();
    bool PremiereFois=true;
    string input;
    do{
        if(!PremiereFois)wcout << "Choix n'est pas valide ):" << endl;
        wcout << "Choisir le mode du jeu : " << endl;
        wcout << "1. pour le consol " << endl;
        wcout << "2. pour le graphic " << endl;
        wcout << "Donner votre choix : ";
        wcout.flush();
        getline(cin,input);
        PremiereFois=false;
    }while(input!="1"&&input!="2");
    if(input=="1"){
        Monplateau.ConsolGraphic=1;
        PremiereFois=true;
        system("cls");
        do{
            if(!PremiereFois)wcout << "Choix n'est pas valide ):" << endl;
            wcout << "Choisir le mode du jeu : " << endl;
            wcout << "1. pour minimax " << endl;
            wcout << "2. pour alphabeta " << endl;
            wcout << "Donner votre choix : ";
            getline(cin,input);
            PremiereFois=false;
        }while(input!="1"&&input!="2");
        if(input=="1")Monplateau.MiniMaxAlphaBeta=1;
        else Monplateau.MiniMaxAlphaBeta=2;
        system("cls");
        Monplateau.OrdreDesJoueurs();
        Monplateau.PremierePhaseDuJeu();
        Monplateau.DeuxiemePhaseDuJeu();
    }
    else {
        Monplateau.OrdreDesJoueurs();
        Monplateau.ConsolGraphic=2;
        Monplateau.sdl=new SDL;
        Monplateau.sdl->Menu(&Monplateau);
    }

    //Monplateau.AfficherConsol();
    //wcout << "This is the value of the test : "<< Monplateau.Voisinages(2,5) << endl;
    /*wcout << "Nombres des des 0 : " << Monplateau.NombreDesPions('0') << endl;
    wcout << "Nombres des des 1 : " << Monplateau.NombreDesPions('1') << endl;
    wcout << "Nombres des des 2 : " << Monplateau.NombreDesPions('2') << endl;*/
    /*wcout << "Nombres des des 0 : " << Monplateau.NombreDesPions('0') << endl;
    wcout << "Nombres des des 1 : " << Monplateau.NombreDesPions('1') << endl;
    wcout << "Nombres des des 2 : " << Monplateau.NombreDesPions('2') << endl;*/
    return 0;
}
