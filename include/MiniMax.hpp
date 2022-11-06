#ifndef MINIMAX_HPP
#define MINIMAX_HPP
#include <iostream>
#include "Plateau.hpp"


struct etat;


class Plateau;
class SDL;
class MiniMax{
friend class SDL;
private :
    int data1=0;
    int NombreDesNoeuds=0;
    Plateau *UnPlateau;
public :
    MiniMax();
    ~MiniMax();
    etat h(Plateau *UnPlateau, etat UnEtat);
    etat minimax(Plateau *UnPlateau, etat UnEtat, int profondeur, int NombreDesPionsPoser, bool TourMax);
    etat JoueurMiniMax(Plateau *UnPlateau, int Position=0);
    bool comparer(etat *a, etat *b);
    void copier(etat source, etat *copie);
};
#endif
