#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"

/*===================================================================================
/ Nom Sémantique : FONCTION SP_Gestion_Clavier

/ Sémantique : Gère la détection des évènements clavier sur les touches de direction

/ Paramètres :
/ direction (OUT) - entier : Contient la direction sollicitée par l'utilisateur
/ DROITE = 0 , GAUCHE = 1 , BAS = 2 , HAUT = 3, ENTREE = 4 et -1 SINON
/ Pré-condition : AUCUNE
/ Post conditions : la direction vaut -1,0,1,2,3 4
/ ====================================================================================
/ Test : le chiffre renvoyé correspond à la direction appuyée
/ ====================================================================================*/
int SP_Gestion_Clavier(){
    char direction ;
    int dir;

    if ( kbhit()) {

    direction = getkey() ;

    switch (direction){

        case KEY_UP : dir = HAUT ; break;
        case KEY_DOWN : dir = BAS ; break;
        case KEY_LEFT : dir = GAUCHE ; break;
        case KEY_RIGHT: dir= DROITE ; break;
        case KEY_ENTER: dir= ENTREE ; break;
        }
    }
    else {dir=-1;}
    return dir;
}

// A COMPLETER...
