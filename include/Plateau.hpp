#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include "MiniMax.hpp"
#include "AlphaBeta.hpp"
#include "SDL.hpp"

#include <iostream>
#include <string>


using namespace std;



enum morceau{LeMorceau1=1,LeMorceau2=2,LeMorceau3=3,LeMorceau4=4,LeMorceau5=5,LeMorceau6=6,LeMorceau7=7,LeMorceau8=8,LeMorceau9=9};
enum color {yellow=6,darkgray=7,gray=8,white=15,blue=31,green=175};


struct etat{
public :
    char SonPlateau[24];
    int cout_etat;
    int position;
    int precdent;
    int Pioncapturer=-1;
};

class MiniMax;
class AlphaBeta;
class SDL;
class Plateau{
friend class MiniMax;
friend class AlphaBeta;
friend class SDL;
private:

    char LePlateau[24]={'0'};
    MiniMax *minimax;
    AlphaBeta *alphabeta;
    int Joueur1=0;
    int Joueur1Lose=0;
    int NombreDesPionsPoser=0;
public:
    int ConsolGraphic;
    int MiniMaxAlphaBeta;
    SDL *sdl;
    Plateau();
    ~Plateau();
    //fonctions pour l'affichage console.
    void initialiser_le_plateau();
    void dessiner(wchar_t *chaine ,int repetition);
    void dessiner_pion(int position);
    void dessiner_forme(wchar_t *forme1 ,int repetition1,wchar_t *forme2 ,int repetition2);
    void dessiner_morceau(morceau UnMorceau,int argument);
    void dessiner_ligne(morceau morceau1=LeMorceau4 ,int argument1=0 ,morceau morceau2=LeMorceau4 ,int argument2=0 ,morceau morceau3=LeMorceau4 ,int argument3=0 ,morceau morceau4=LeMorceau4 ,int argument4=0 ,morceau morceau5=LeMorceau4 ,int argument5=0 ,morceau morceau6=LeMorceau4 ,int argument6=0 ,morceau morceau7=LeMorceau4 ,int argument7=0 ,morceau morceau8=LeMorceau4 ,int argument8=0 ,morceau morceau9=LeMorceau4 ,int argument9=0 ,morceau morceau10=LeMorceau4 ,int argument10=0 ,morceau morceau11=LeMorceau4 ,int argument11=0 ,morceau morceau12=LeMorceau4 ,int argument12=0 ,morceau morceau13=LeMorceau4 ,int argument13=0 );
    void AfficherConsol();

    //fonctions pour l'affichage graphique.
    void AfficherGraphique();

    //fonctions du jeu (GamePlay)
    void OrdreDesJoueurs();
    int CasePleine(char *UnPlateau, int position ,char Pion);
    int CaseVide(char *UnPlateau, int position);
    void AjouterPion(int Position ,char Pion ,int PionCapturer=-1);
    void SuprimerPion(int Position);
    int MouvementPossible(char *UnPlateau, int source ,int destination ,char Pion);// A modifier
    int DeplacerPion(char Pion);
    int ChoixValide(string Choix);
    int Voisinages(int source ,int positionTest);
    int moulin(char *UnPlateau, int Position ,char Pion);
    void CapturerPion(int destination ,char Pion);
    int JouerJoueur(char Pion );
    void PremierePhaseDuJeu();
    void DeuxiemePhaseDuJeu();
    int NombreDesPions(char *UnPlteau, char Pion);
    int ArreterLeJeu(char Pion);
    int PasDeMouvement(char *UnPlateau,char pion);
};
#endif
