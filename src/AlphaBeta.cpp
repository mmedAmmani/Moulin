#include <iostream>
#include "../include/AlphaBeta.hpp"
#include "../include/Plateau.hpp"
#include<time.h>

using namespace std;

AlphaBeta::AlphaBeta(){

}

AlphaBeta::~AlphaBeta(){

}



//fonction du jeu de la machine
etat AlphaBeta::JoueurAlphaBeta(Plateau *UnPlateau, int Position){
    int profondeur=4;
    int NombreDesPionsPoser;
    etat EtatDepart;
    EtatDepart.cout_etat=0;
    NombreDesPionsPoser=UnPlateau->NombreDesPionsPoser;
    for(int i=0; i<24 ;i++)EtatDepart.SonPlateau[i]=UnPlateau->LePlateau[i];
    EtatDepart.SonPlateau[Position]='2';
    EtatDepart.position=Position;
    int alpha=-1000000,beta=1000000;
    NombreDesNoeuds=0;
    clock_t temps_debut, temps_fin;
    temps_debut=clock();
    etat EtatResultat= alphabeta(UnPlateau, EtatDepart, profondeur, NombreDesPionsPoser, true ,alpha ,beta);
    temps_fin=clock();
    wcout << "le Nombre des noeuds explores est : " << NombreDesNoeuds << endl;
    wcout << "Le temps de la recherche est : " << (double)(temps_fin - temps_debut) / (CLOCKS_PER_SEC) << " s"<< endl << endl;
    return EtatResultat;
}


//fonction AlphaBeta
etat AlphaBeta::alphabeta(Plateau *UnPlateau,etat UnEtat, int profondeur, int NombreDesPionsPoser ,bool TourMax ,int alpha ,int beta){
    if(profondeur<=0){
            //cout << "profndeur =0 " << endl;
            return h(UnPlateau,UnEtat);
    }
    if(NombreDesPionsPoser>18){
        if(UnPlateau->PasDeMouvement(UnEtat.SonPlateau,'1')==-1||UnPlateau->NombreDesPions(UnEtat.SonPlateau,'1')==2){
            UnEtat.cout_etat=-1000;
            return UnEtat;
        }
        if(UnPlateau->PasDeMouvement(UnEtat.SonPlateau,'2')==-1||UnPlateau->NombreDesPions(UnEtat.SonPlateau,'2')==2){
            UnEtat.cout_etat=1000;
            return UnEtat;
        }
    }
    if(TourMax){
        profondeur--;
        NombreDesPionsPoser++;
        etat EtatMax;
        copier(UnEtat,&EtatMax);
        EtatMax.cout_etat=-1000000;
        if(NombreDesPionsPoser<=18){
            for(int i=0; i<24 ;i++){
                if(UnPlateau->CaseVide(UnEtat.SonPlateau,i)==0){
                    NombreDesNoeuds++;
                    etat Etatcourant,EtatAide;
                    copier(UnEtat,&Etatcourant);
                    Etatcourant.SonPlateau[i]='1';
                    Etatcourant.position=i;
                    if(UnPlateau->moulin(Etatcourant.SonPlateau,i,'1')==3){
                        for(int j=0; j<24; j++){
                            if(UnEtat.SonPlateau[j]=='2'&&UnPlateau->moulin(UnEtat.SonPlateau,j,'2')!=3){
                                NombreDesNoeuds++;
                                Etatcourant.SonPlateau[j]='0';
                                EtatAide=alphabeta(UnPlateau,Etatcourant,profondeur-1,NombreDesPionsPoser-1,!TourMax,alpha,beta);
                                EtatAide.Pioncapturer=j;
                                EtatAide.position=i;
                            }
                        }
                    }
                    else {
                        EtatAide = alphabeta(UnPlateau,Etatcourant,profondeur,NombreDesPionsPoser,!TourMax,alpha,beta);
                        EtatAide.position=i;
                        EtatAide.Pioncapturer=-1;
                    }
                    if(EtatMax.cout_etat<EtatAide.cout_etat){
                        EtatMax.cout_etat=EtatAide.cout_etat;
                        EtatMax.position=i;
                        EtatMax.Pioncapturer=EtatAide.Pioncapturer;
                    }
                    if(alpha<EtatAide.cout_etat)alpha=EtatAide.cout_etat;
                    if(alpha>=beta)i=25;
                }
            }
            return EtatMax;
        }
        else{
            for(int k=0; k<24 ;k++){
                for(int i=0; i<24; i++){
                    if(UnPlateau->MouvementPossible(UnEtat.SonPlateau,k,i,'1')==0){
                        NombreDesNoeuds++;
                        etat Etatcourant,EtatAide;
                        copier(UnEtat,&Etatcourant);
                        Etatcourant.SonPlateau[k]='0';
                        Etatcourant.SonPlateau[i]='1';
                        Etatcourant.position=i;
                        Etatcourant.precdent=k;
                        if(UnPlateau->moulin(Etatcourant.SonPlateau,i,'1')==3){
                            for(int j=0; j<24; j++){
                                if(UnEtat.SonPlateau[j]=='2'&&UnPlateau->moulin(UnEtat.SonPlateau,j,'2')!=3){
                                    NombreDesNoeuds++;
                                    Etatcourant.SonPlateau[j]='0';
                                    EtatAide=alphabeta(UnPlateau,Etatcourant,profondeur-1,NombreDesPionsPoser-1,!TourMax,alpha,beta);
                                    EtatAide.Pioncapturer=j;
                                    EtatAide.position=i;
                                }
                            }
                        }
                        else {
                            EtatAide = alphabeta(UnPlateau,Etatcourant,profondeur,NombreDesPionsPoser,!TourMax,alpha,beta);
                            EtatAide.position=i;
                            EtatAide.Pioncapturer=-1;
                        }
                        if(EtatMax.cout_etat<EtatAide.cout_etat){
                            EtatMax.cout_etat=EtatAide.cout_etat;
                            EtatMax.position=i;
                            EtatMax.precdent=k;
                            EtatMax.Pioncapturer=EtatAide.Pioncapturer;
                        }
                        if(alpha<EtatAide.cout_etat)alpha=EtatAide.cout_etat;
                        if(alpha>=beta)i=25;
                    }
                }

            }
            return EtatMax;
        }
    }
    else{
        profondeur--;
        NombreDesPionsPoser++;
        etat EtatMin;
        copier(UnEtat,&EtatMin);
        EtatMin.cout_etat=1000000;
        if(NombreDesPionsPoser<=18){
            for(int i=0; i<24 ;i++){
                if(UnPlateau->CaseVide(UnEtat.SonPlateau,i)==0){
                    NombreDesNoeuds++;
                    etat Etatcourant,EtatAide;
                    copier(UnEtat,&Etatcourant);
                    Etatcourant.SonPlateau[i]='2';
                    Etatcourant.position=i;
                    if(UnPlateau->moulin(Etatcourant.SonPlateau,i,'2')==3){
                        for(int j=0; j<24; j++){
                            if(UnEtat.SonPlateau[j]=='1'&&UnPlateau->moulin(UnEtat.SonPlateau,j,'1')!=3){
                                NombreDesNoeuds++;
                                Etatcourant.SonPlateau[j]='0';
                                EtatAide=alphabeta(UnPlateau,Etatcourant,profondeur-1,NombreDesPionsPoser-1,!TourMax,alpha,beta);
                                EtatAide.position=i;
                                EtatAide.Pioncapturer=j;
                            }
                        }
                    }
                    else {
                        EtatAide = alphabeta(UnPlateau,Etatcourant,profondeur,NombreDesPionsPoser,!TourMax,alpha,beta);
                        EtatAide.position=i;
                        EtatAide.Pioncapturer=-1;
                    }
                    if(EtatMin.cout_etat>EtatAide.cout_etat){
                        EtatMin.cout_etat=EtatAide.cout_etat;
                        EtatMin.position=i;
                        EtatMin.Pioncapturer=EtatAide.Pioncapturer;
                    }
                    if(beta>EtatAide.cout_etat)beta=EtatAide.cout_etat;
                    if(beta<=alpha)i=25;
                }
            }
            return EtatMin;
        }
        else{
            for(int k=0; k<24; k++){
                for(int i=0; i<24 ;i++){
                    if(UnPlateau->MouvementPossible(UnEtat.SonPlateau,k,i,'2')==0){
                        NombreDesNoeuds++;
                        etat Etatcourant,EtatAide;
                        copier(UnEtat,&Etatcourant);
                        Etatcourant.SonPlateau[k]='0';
                        Etatcourant.SonPlateau[i]='2';
                        Etatcourant.position=i;
                        Etatcourant.precdent=k;
                        if(UnPlateau->moulin(Etatcourant.SonPlateau,i,'2')==3){
                            for(int j=0; j<24; j++){
                                if(UnEtat.SonPlateau[j]=='1'&&UnPlateau->moulin(UnEtat.SonPlateau,j,'1')!=3){
                                    NombreDesNoeuds++;
                                    Etatcourant.SonPlateau[j]='0';
                                    EtatAide=alphabeta(UnPlateau,Etatcourant,profondeur-1,NombreDesPionsPoser-1,!TourMax,alpha,beta);
                                    EtatAide.position=i;
                                    EtatAide.Pioncapturer=j;
                                }
                            }
                        }
                        else {
                            EtatAide = alphabeta(UnPlateau,Etatcourant,profondeur-1,NombreDesPionsPoser,!TourMax,alpha,beta);
                            EtatAide.position=i;
                            EtatAide.Pioncapturer=-1;
                        }
                        if(EtatMin.cout_etat>EtatAide.cout_etat){
                            EtatMin.cout_etat=EtatAide.cout_etat;
                            EtatMin.position=i;
                            EtatMin.precdent=k;
                            EtatMin.Pioncapturer=EtatAide.Pioncapturer;
                        }
                        if(beta>EtatAide.cout_etat)beta=EtatAide.cout_etat;
                        if(beta<=alpha)i=25;
                    }
                }
            }

            return EtatMin;
        }
    }
        //(||NombreDesPionsPoser>=9&&){}
}

//fonction d'evaluation h
etat AlphaBeta::h(Plateau *UnPlateau, etat UnEtat){
        int maxPions=0,minPions=0;
        for(int i=0; i<24; i++){
            if(UnEtat.SonPlateau[i]=='1')maxPions++;
            if(UnEtat.SonPlateau[i]=='2')minPions++;
            if(UnPlateau->moulin(UnEtat.SonPlateau,i,'1')==2)maxPions+=15;
            if(UnPlateau->moulin(UnEtat.SonPlateau,i,'2')==2)minPions+=30;
            if(UnPlateau->moulin(UnEtat.SonPlateau,i,'1')==3)maxPions=maxPions+50;
            if(UnPlateau->moulin(UnEtat.SonPlateau,i,'2')==3)minPions=minPions+100;
        }
        UnEtat.cout_etat=maxPions-minPions;
    return UnEtat;
}

//fonction pour copier les données d'un etat (etat source) dans un autre etat (etat copie)
void AlphaBeta::copier(etat source, etat *copie){
    copie->cout_etat=source.cout_etat;
    copie->position=source.position;
    for(int i=0; i<24 ;i++){
        copie->SonPlateau[i]=source.SonPlateau[i];
    }
}

