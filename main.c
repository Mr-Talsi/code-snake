#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"
#include "SP_GESTION_JEU.h"
#include <math.h>
void options(ST_SNAKE *snake, ST_PARAM_JEU *param,int*a,int *b)              /*sous programme pour afficher les options*/
{
    printf("1-couleur serpent =%s\n",NomCouleur(param->couleur_snake));
    printf("2-difficulte = %d\n",param->difficulte);
    printf("3-sortir\n");
    printf("votre choix :");
    scanf("%d",a);
    printf("----------------\n");
    if(*a==2)
    {
        printf("1-facile\n");
        printf("2-moyen\n");
        printf("3-difficile\n");
        printf("votre choix :");
        scanf("%d",b);
        param->difficulte=*b;
    }


    if(*a==1)
    {
        printf("1 - Noir\n2 - bleu\n3 - vert\n4 - cyan\n5 - rouge\n6 - magenta\n7 - maron\n");
        printf("votre choix :");
        scanf("%d",b);
        param->couleur_snake=*b-1;
    }
    else if(*a!=3 && *a!=1 &&*a!=2)  /*afficher une erreur lorsque l'utilisateur donne un choix qui n'existe pas dans le menu*/
    {
        printf("choix non valid\n");
    }
}
void affichage_score(char* nom, int s) /*enregister les scores des utilisateurs*/
{
    FILE *f;
    f = fopen("highscore.txt", "a");
    fprintf(f, "%s - %d\n", nom, s);
    fclose(f);
}
void afficherHighScores()   /*affiche la liste des joueurs et leurs scores*/
{
    FILE *f;
    char c[255];
    f = fopen("highscore.txt", "r");
    if (f == NULL)
    {
        printf("Aucun score n'a ete enregistre.\n");
    }
    else
    {
        while (fgets(c, 255, f) != NULL)
        {
            printf("%s", c);
        }
        fclose(f);
    }
}
void Menu(ST_SNAKE *snake, ST_PARAM_JEU *param,int*a,int*d,int* e) /* afficher les differentes choix du menu*/
{
    printf("1-jouer\n2-options\n3-high_score\n4-quitter\n");
    printf("votre choix :");
    scanf("%d",a);
    printf("----------------\n");
    if(*a==2) /*pour le choix 2 : afficher chaque fois ce choix tant que l'utilisateur n'a pas sorti*/
    {
        do
        {
            options(snake,param,d,e);
        }
        while(*d!=3);
    }
    if(*a==3)
    {
        setColor(YELLOW);
        printf("***HIGH SCORES***\n");/*afficher high scores avec la couleur jaune*/
        printf("Nom   Score\n");
        setColor(WHITE);/*afficher les scores avec la couleur jaune*/
        afficherHighScores();
        printf("----------------\n");
    }
    if(*a==4)
    {
        exit(0); /*sortir du programme lorsque le joueur choisi le choix quitter*/
    }
    else if(*a!=1 &&*a!=2 &&*a!=3 &&*a!=4)
    {
        printf("choix non valid\n");
    }
}
int affichage_snake(ST_SNAKE *snake, ST_PARAM_JEU *param) /*sous programme qui permet l'affichage du serpent*/
{
    snake->taille = 2;
    snake->tete.y = param->H_stade / 2;    /*initialiser la tete du serpent dans le milieu du stade*/
    snake->tete.x = param->L_stade / 2;
    for (int i = 0; i < snake->taille; i++) /*initialiser le coprs du serpent dans le milieu du stade*/
    {
        snake->pos[i].y = param->H_stade / 2;
        snake->pos[i].x = (param->L_stade / 2) + snake->taille - i;

    }
    for (int i = 0; i < snake->taille; i++) /*afficher le serpent dans le milieu du stade*/
    {
        printSnakeHead(snake->tete.x, snake->tete.y, param->couleur_snake);
        printSnakeBody(snake->pos[i].x, snake->pos[i].y, param->couleur_snake);
    }
    return 0;
}

void stade(ST_PARAM_JEU *param) /*afficher le stade pour une longeur et une largeur définie avec la couleur bleu */
{
    for (int i = 1; i < param->L_stade + 2; i++)
    {
        for (int j = 1; j < param->H_stade + 2; j++)
        {
            if (i == 1 || i == param->L_stade + 1)
            {
                printStadeElement(i, j, BLUE);
            }
            else if (j == 1 || j == param->H_stade + 1)
            {
                printStadeElement(i, j, BLUE);
            }
            else
            {
                printStadeElement(i, j, param->couleur_stade);
            }
        }
    }
}
void stade2(ST_PARAM_JEU *param){
    for (int i = 1; i < param->L_stade -5; i++){ printStadeElement(i,(param->H_stade)/2, BLUE);}
}
void deplacement(ST_SNAKE *snake, ST_PARAM_JEU *param)/*sous programme qui permet le déploacement du sepent selon le choix de l'utilisateur*/
{
    switch (snake->direction)
    {
    case DROITE:
        for (int i = 0; i < snake->taille - 1; i++)/*pour passer à droite le serpent doit avancer selon l'axe des  x et augmenter la position de la tete de meme*/
        {
            snake->pos[i].x = snake->pos[i + 1].x;
            snake->pos[i].y = snake->pos[i + 1].y;

        }
        snake->pos[snake->taille - 1].x = snake->tete.x;
        snake->pos[snake->taille - 1].y = snake->tete.y;
        snake->tete.x += 1;
        break;
    case GAUCHE:
        for (int i = 0; i < snake->taille - 1; i++)/*pour passer à gauche le serpent doit décaler selon l'axe des  x et  la position de la tete de meme*/
        {
            snake->pos[i].x = snake->pos[i + 1].x;
            snake->pos[i].y = snake->pos[i + 1].y;

        }
        snake->pos[snake->taille - 1].x = snake->tete.x;
        snake->pos[snake->taille - 1].y = snake->tete.y;
        snake->tete.x -= 1;
        break;
    case HAUT:/*pour passer en haut le serpent doit reculer selon l'axe des  y*/
        for (int i = 0; i < snake->taille - 1; i++)
        {
            snake->pos[i].x = snake->pos[i + 1].x;
            snake->pos[i].y = snake->pos[i + 1].y;

        }
        snake->pos[snake->taille - 1].x = snake->tete.x;
        snake->pos[snake->taille - 1].y= snake->tete.y;
        snake->tete.y-=1;
        break;
    case BAS:/*pour passer en bas le serpent doit avancer selon l'axe des  y */
        for (int i = 0; i < snake->taille - 1; i++)
        {
            snake->pos[i].x = snake->pos[i + 1].x;
            snake->pos[i].y = snake->pos[i + 1].y;

        }
        snake->pos[snake->taille - 1].x = snake->tete.x;
        snake->pos[snake->taille - 1].y= snake->tete.y;
        snake->tete.y+=1;
        break;

    }
    printStadeElement(snake->old_tail.x, snake->old_tail.y, param->couleur_stade);/*permet d'éliminer la queue du serpent*/
    for (int i = 0; i < snake->taille ; i++)
    {
        printSnakeBody(snake->pos[i].x, snake->pos[i].y, param->couleur_snake);

    }
    printSnakeHead(snake->tete.x, snake->tete.y, param->couleur_snake);
}

void afficher_pomme(ST_PARAM_JEU *param,ST_SNAKE *snake,int*x,int*y,int* b)/*afficher la pomme dans le stade*/
{
    *x=rand()%(param->L_stade-1) + 2;
    *y=rand()%(param->H_stade-1) + 2;
    for(int i=0 ; i<snake->taille; i++)
    {   /*choix des conditions dans la boucle while pour que la pomme ne se confondre pas avec le serpent ou avec le stade*/
        while(*x==1 || *x==param->H_stade+1 || *y==1 || *y==param->L_stade+1 || ((*x==snake->pos[i].x && *y==snake->pos[i].y)||(*x==snake->tete.x && *y==snake->tete.y)))
        {
            *x=rand()%(param->L_stade-1) + 2;
            *y=rand()%(param->H_stade-1) + 2;
        }
    }
    printPomme(*x,*y,YELLOW);
    *b+=3;/*tant que le joueur n'a pas perdu son score augmente*/
}
void afficher_pomme2(ST_PARAM_JEU *param,ST_SNAKE *snake,int*x,int*y,int* b)/*afficher la pomme dans le stade*/
{
    *x=rand()%(param->L_stade-1) + 2;
    *y=rand()%(param->H_stade-1) + 2;
    for(int i=0 ; i<snake->taille; i++)
    {   /*choix des conditions dans la boucle while pour que la pomme ne se confondre pas avec le serpent ou avec le stade*/
        while(*x==1 || *x==param->H_stade+1 || *y==1 || *y==param->L_stade+1 || ((*x==snake->pos[i].x && *y==snake->pos[i].y)||(*x==snake->tete.x && *y==snake->tete.y)))
        {
            *x=rand()%(param->L_stade-1) + 2;
            *y=rand()%(param->H_stade-1) + 2;
        }
    }
    for(int i=0 ; i<param->L_stade-5; i++){
            while(*y==(param->H_stade)/2 && *x==i){
            *x=rand()%(param->L_stade-1) + 2;
            *y=rand()%(param->H_stade-1) + 2;
    }
    }
    printPomme(*x,*y,YELLOW);
    *b+=3;/*tant que le joueur n'a pas perdu son score augmente*/
}
void pomme_empoisonnee(ST_PARAM_JEU *param,ST_SNAKE *snake,int*x,int*y)/*afficher la pomme dans le stade*/
{
    *x=rand()%(param->L_stade-1) + 2;
    *y=rand()%(param->H_stade-1) + 2;
    for(int i=0 ; i<snake->taille; i++)
    {   /*choix des conditions dans la boucle while pour que la pomme ne se confondre pas avec le serpent ou avec le stade*/
        while(*x==1 || *x==param->H_stade+1 || *y==1 || *y==param->L_stade+1 || ((*x==snake->pos[i].x && *y==snake->pos[i].y)||(*x==snake->tete.x && *y==snake->tete.y)))
        {
            *x=rand()%(param->L_stade-1) + 2;
            *y=rand()%(param->H_stade-1) + 2;
        }
    }
    printPomme(*x,*y,GREEN);

}
void echec(int*a,ST_PARAM_JEU *param,ST_SNAKE *snake)          //probléme lorsque taille egale a la hauteur +1 pour h=30 car pos est de longeur 30//
{/*lorsque le serpent touche le stade il mort*/
    if (snake->tete.x==1 || snake->tete.x==param->L_stade+1)
    {
        gotoxy(1,param->H_stade+8);
        setColor(YELLOW);
        printf("PERDU!!!");
        *a=1;
    }
    else if (snake->tete.y==1 || snake->tete.y==param->H_stade+1)
    {
        gotoxy(1,param->H_stade+8);
        setColor(YELLOW);
        printf("PERDU!!!");
        *a=1;
    }
    for (int i = 0; i < snake->taille; i++)/*lorsque la tete du serpent touche son corps il mort*/
    {
        if(snake->tete.x==snake->pos[i].x && snake->tete.y==snake->pos[i].y)
        {
            gotoxy(1,param->H_stade+8);
            setColor(YELLOW);
            printf("PERDU!!!");
            *a=1;
        }
    }
}
void echec2(int*a,ST_PARAM_JEU *param,ST_SNAKE *snake)
{for (int i = 1; i <param->L_stade-5 ; i++){if (snake->tete.y==(param->H_stade)/2 && snake->tete.x==i)
{gotoxy(1,param->H_stade+8);
        setColor(YELLOW);
        printf("PERDU!!!");
        *a=1;}}}


void rallonger_snake(ST_PARAM_JEU *param,ST_SNAKE *snake)/*sous programme permet de rallonger le serpent lorqu'il mange une pomme*/
{
    snake->pos[snake->taille].x = snake->pos[snake->taille-1].x ;
    snake->pos[snake->taille].y = snake->pos[snake->taille-1].y;
    for(int i=1; i<snake->taille; i++)
    {
        snake->pos[snake->taille-i].x = snake->pos[snake->taille-i-1].x;
        snake->pos[snake->taille-i].y = snake->pos[snake->taille-i-1].y;

    }
    snake->pos[0].x = snake->old_tail.x ;
    snake->pos[0].y = snake->old_tail.y;

}

int main()
{
    setColor(YELLOW);
    printf("************************************************\n");
    printf("BIENVENU DANS NOTRE JEU DU SNAKE\n");
    printf("************************************************\n");
    setColor(WHITE);

    char c[20];
    printf("donnez votre nom :");
    scanf("%s",c);
    setColor(YELLOW);
    printf("***bienvenue %s tu vas t'eclater!!!!!***\n",c);
    setColor(WHITE);
    ST_SNAKE snake;
    ST_PARAM_JEU param;
    int d;
    int e;
    int f;
    int a = 0;
    int x;
    int y;
    int n;
    int m;
    param.H_stade = 30;
    param.L_stade = 60;
    param.couleur_stade = RED;
    param.couleur_snake = BLUE;
    param.difficulte=2;
    do
    {
        Menu(&snake,&param,&d,&e,&f);
    }
    while(d!=1);
    system("cls");   //pour effacer l'écran
    int b=-3;
    if(d!=3)
    {
        stade(&param);
        affichage_snake(&snake, &param);
        snake.direction=GAUCHE;
        afficher_pomme(&param,&snake,&x,&y,&b);
    }
    while (a != 1 && d==1 && d!=4 && b<=20)
    {
        if (kbhit())
        {
            snake.direction = SP_Gestion_Clavier();
        }
        if(snake.tete.x==x && snake.tete.y==y)
           {printStadeElement(n,m, param.couleur_stade);
           n=0;
        m=0;
            afficher_pomme(&param,&snake,&x,&y,&b);
            rallonger_snake(&param,&snake);
            snake.taille++;
        }
        if((b+1)%5==0){
        pomme_empoisonnee(&param,&snake,&n,&m);
        b=b+1;}

        if(snake.tete.x==n && snake.tete.y==m){a=1;
            gotoxy(1,param.H_stade+8);
            setColor(YELLOW);
            printf("PERDU!!!");
            exit(0);}


        snake.old_tail.x=snake.pos[0].x;
        snake.old_tail.y=snake.pos[0].y;
        deplacement(&snake, &param);
        gotoxy(1,param.H_stade+3);
        setColor(YELLOW);
        printf("SCORE = %d\n",b);
        printf("La taille de ton serpent =%d\n",snake.taille);
        echec(&a,&param,&snake);
        msleep(200/param.difficulte);}
        stade(&param);
        stade2(&param);
        afficher_pomme2(&param,&snake,&x,&y,&b);
          while (a!=1 && b>20)
    {
        if (kbhit())
        {
            snake.direction = SP_Gestion_Clavier();
        }
        if(snake.tete.x==x && snake.tete.y==y)
           {printStadeElement(n,m, param.couleur_stade);
           n=0;
        m=0;
            afficher_pomme(&param,&snake,&x,&y,&b);
            rallonger_snake(&param,&snake);
            snake.taille++;
        }
        if((b+1)%5==0){
        pomme_empoisonnee(&param,&snake,&n,&m);
        b=b+1;}

        if(snake.tete.x==n && snake.tete.y==m){a=1;
            gotoxy(1,param.H_stade+8);
            setColor(YELLOW);
            printf("PERDU!!!");
            exit(0);}
        snake.old_tail.x=snake.pos[0].x;
        snake.old_tail.y=snake.pos[0].y;
        deplacement(&snake, &param);
        gotoxy(1,param.H_stade+3);
        setColor(YELLOW);
        printf("SCORE = %d\n",b);
        printf("La taille de ton serpent =%d\n",snake.taille);
        echec(&a,&param,&snake);
        echec2(&a,&param,&snake);
        msleep(200/param.difficulte);}
        affichage_score(c,b-3);


    return 0;
}
