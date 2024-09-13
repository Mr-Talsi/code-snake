#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"

/*===================================================================================
/ Nom S�mantique : FONCTION SP_Gestion_Clavier

/ S�mantique : G�re la d�tection des �v�nements clavier sur les touches de direction

/ Param�tres :
/ direction (OUT) - entier : Contient la direction sollicit�e par l'utilisateur
/ DROITE = 0 , GAUCHE = 1 , BAS = 2 , HAUT = 3, ENTREE = 4 et -1 SINON
/ Pr�-condition : AUCUNE
/ Post conditions : la direction vaut -1,0,1,2,3 4
/ ====================================================================================
/ Test : le chiffre renvoy� correspond � la direction appuy�e
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
