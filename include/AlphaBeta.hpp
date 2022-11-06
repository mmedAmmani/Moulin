#ifndef ALPHABETA_HPP
#define ALPHABETA_HPP
#include <iostream>
#include "Plateau.hpp"


struct etat;


class Plateau;
class SDL;
class Plateau;
class AlphaBeta{
friend class SDL;
friend class Plateau;
private :
    int data1=0;
    int NombreDesNoeuds=0;
    Plateau *UnPlateau;
public :
    AlphaBeta();
    ~AlphaBeta();
    etat h(Plateau *UnPlateau, etat UnEtat);
    etat alphabeta(Plateau *UnPlateau, etat UnEtat, int profondeur, int NombreDesPionsPoser, bool TourMax, int alpha, int beta);
    etat JoueurAlphaBeta(Plateau *UnPlateau, int Position=0);
    bool comparer(etat *a, etat *b);
    void copier(etat source, etat *copie);
};
#endif
