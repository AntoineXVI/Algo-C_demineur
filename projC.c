#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define size 10
#define RowMax 10
#define RowMin 3

void printNumero(int row);
int scanCoordonee(int max, int min, char* message);
void isVisual(int matrice[size][size], int matriceVisual[size][size], int choixI1, int choixJ1, int rowMax, bool tour1);
void isZero(int matrice[size][size],int matriceVisual[size][size], int matriceVisual2[size][size], int choixI1, int choixJ1, int rowMax, bool tour1);
void isBomb(int matrice[size][size], int bomb[size][size], int rowMax);
bool isWin(int matriceVisual[size][size], int rowMax, int nbBomb);
void red();
void green();
void yellow();
void purple();
void reset();



int main()
{
    int rejouer = 1;
    while (rejouer == 1)
    {
        // On commence par initialiser le générateur de nombre aléatoires.
        srand(time(NULL));

        // On initialise les variables pour la taille de la matrice.
        int row = RowMin;

        printf("Bienvenue. Tu dois vider la grille en ne laissant que les bombes. Les cases inconnus a vider sont representes par des 9.\nAides toi des indices pourconnaitre la position des bombes.\nBonne chance!\n");

        printf("Entrez le nombre de lignes (min 3 et max 10)\n");

        while (((scanf_s("%d", &row)) != 1) || (row > RowMax) || (row < RowMin))
        {
            printf("erreur de scan. reessayez.\n");
            printf(" Entrez le nombre de lignes (min %d et max %d)\n", RowMin, RowMax);
        }
        int col = row;      //grille caree donc ligne = collonne.

        // On initialise la matrice pour stocker les bombes.
        int bomb[size][size];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                bomb[i][j] = 0;
            }
        }

        // On initialise la matrice de jeu.
        int matrice[size][size];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrice[i][j] = 0;
            }
        }

        // On initialise la matriceVisual.
        int matriceVisual[size][size];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < row; j++)
            {
                matriceVisual[i][j] = 9;
            }
        }

        int matriceVisual2[size][size];     //matrice bonus pour valider les cases avec 0.

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < row; j++)
            {
                matriceVisual2[i][j] = 0;
            }
        }

        bool tour1 = true;
        while (isWin(matriceVisual, row, (row - 1)))
        {
            printf("choisisez les coordonees de la ");
            if (tour1 == true)
            {
                printf("premiere ");
            }
            printf("case a detruire.\n");

            if (tour1 == true)
            {
                printNumero(row);
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        green();
                        printf("%3d", matrice[i][j]);                   //affiche la grille de jeu.
                        reset();
                    }
                    printf("\n");
                }
            }

            int choixI = scanCoordonee(row, 0, "ligne");
            int choixJ = scanCoordonee(col, 0, "colonne");
            while (matriceVisual[choixI][choixJ] != 9)
            {
                printf("erreur, choissisez une case du tableau non utilisé \n");
                choixI = scanCoordonee(row, 0, "ligne");
                choixJ = scanCoordonee(col, 0, "colonne");
            }

            if (bomb[choixI][choixJ] == 1)
            {
                printf("bombe touche. Game over.\n");
                break;
            }

            if (tour1 != true)
            {
                printf("Bombe non touche. Bravo,continue!\n");
            }
            else
            {
                printf("Premiere case jouee,continue!\n");

            }
            printf("je continue!\n");
            matrice[choixI][choixJ] = 1;
            int choixI1 = choixI;
            int choixJ1 = choixJ;

            if (tour1 == true)
            {
                for (int i = 0; i < row - 1; i++)
                {
                    int coordI = rand() % row;      // Tirer deux coordonees aléatoire entre 0 et la longueur max du tableau seulement au tour 1.
                    int coordJ = rand() % row;
                    while (matrice[coordI][coordJ] == 1)
                    {
                        coordI = rand() % row;    //Si la bombe est placé sur la 1ere case du joueur,rechoissir des novelles coordonees.
                        coordJ = rand() % row;
                        printf("je cherche a placer une bombe\n");
                    }

                    bomb[coordI][coordJ] = 1;       //placer les bombes dans la grille.
                }
            }

            printf("grille bomb\n");
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    red();
                    printf("%3d", bomb[i][j]);          //affiche la grille de bombe avec la bombe pour les tests.
                    reset();
                }
                printf("\n");
            }
            printf("\n");

            isBomb(matrice, bomb, row);             //calcule les bombes proche de chaques cases.

            printf("grille jeu apres isBomb\n");
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    printf("%3d", matrice[i][j]);          //grille jeu apres le calcul pour les tests.
                }
                printf("\n");
            }
            printf("\n");

            isVisual(matrice, matriceVisual, choixI1, choixJ1, row, tour1); //rend visibles les cases grace la grille de jeu et au dernier tour.
            isZero(matrice,matriceVisual, matriceVisual2, choixI1, choixJ1, row, tour1); //affiche les cases autour des 0.

            printNumero(row);

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (matriceVisual[i][j] == 9)
                    {
                        purple();
                    }
                    printf("%3d", matriceVisual[i][j]);                   //affiche la grille de jeu.
                    reset();
                }
                printf("\n");
            }
            tour1 = false;

        }
        printf("Fin de partie.Veux tu rejouer ? ( 0 / 1)\n");
        while ((scanf_s("%d", &rejouer) != 1) || ((rejouer != 1) && (rejouer != 0)))
        {
            printf("erreur de scan, reessayer.\n");
            printf("Fin de partie.Veux tu rejouer ? ( 0 / 1)\n");
        }
        printf("\n");
    }
    printf("tu as choisi d'arreter . Bonne journee!\n");
    return EXIT_SUCCESS;
}

void printNumero(int row)
{
    printf(" ");
    for (int i = 0; i < row; i++)
    {
        yellow();
        printf("|%d|", i);
        reset();
    }
    printf("\n\n");
}

int scanCoordonee(int max, int min, char* message ) //fonction permettant de demander le choix de row/col et return l'int de la row/col avec comme
{                                                  //parametre le message pour demander ligne ou col, et le min et max possible.
    int coord;
    printf("choississez un numero de %s entre %d et %d\n", message,min,(max -1));

    while (((scanf_s(" %d", &coord)) != 1) || (coord > (max - 1) || coord < (min - 1)))
    {
        printf("erreur de scan. Reessayez.\n");
        printf("choississez un numero de %s entre %d et %d\n", message, min, (max - 1));
    }
    return coord;
}

void isVisual(int matrice[size][size], int matriceVisual[size][size], int choixI1, int choixJ1, int rowMax, bool tour1)//fonction permettant d'afficher
{   //les cases visible pour le joueur avec comme parametre la grille visuel et jeu,du X et Y de la case, la longeur du tableau et un bool pour tour1.
    if (choixI1 < 0 || choixJ1 < 0)
    {
        printf("erreur: coordonees negatives\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        rowMax = rowMax - 1;

        matriceVisual[choixI1][choixJ1] = matrice[choixI1][choixJ1];
        if (tour1 == true)
        {
            if (choixI1 > 0)
            {
                matriceVisual[choixI1 - 1][choixJ1] = matrice[choixI1 - 1][choixJ1];
                if (choixJ1 != rowMax)
                {
                    matriceVisual[choixI1][choixJ1 + 1] = matrice[choixI1][choixJ1 + 1];
                    matriceVisual[choixI1 - 1][choixJ1 + 1] = matrice[choixI1 - 1][choixJ1 + 1];
                }
                if (choixJ1 > 0)
                {
                    matriceVisual[choixI1][choixJ1 - 1] = matrice[choixI1][choixJ1 - 1];
                    matriceVisual[choixI1 - 1][choixJ1 - 1] = matrice[choixI1 - 1][choixJ1 - 1];
                }
            }
            if (choixI1 != rowMax)
            {
                matriceVisual[choixI1 + 1][choixJ1] = matrice[choixI1 + 1][choixJ1];
                if (choixJ1 > 0)
                {
                    matriceVisual[choixI1][choixJ1 - 1] = matrice[choixI1][choixJ1 - 1];
                    matriceVisual[choixI1 + 1][choixJ1 - 1] = matrice[choixI1 + 1][choixJ1 - 1];
                }
                if (choixJ1 < rowMax)
                {
                    matriceVisual[choixI1][choixJ1 + 1] = matrice[choixI1][choixJ1 + 1];
                    matriceVisual[choixI1 + 1][choixJ1 + 1] = matrice[choixI1 + 1][choixJ1 + 1];
                }
            }
        }
    }
}
    
void isZero(int matrice[size][size],int matriceVisual[size][size], int matriceVisual2[size][size], int choixI1, int choixJ1, int rowMax, bool tour1)
{                // permet de découvrir une plus grande zone s'il y a des 0.
    int isSame = 0;
    while (true)
    {
        for (int i = 0; i < rowMax; i++)
        {
            for (int j = 0; j < rowMax; j++)
            {
                if (matriceVisual[i][j] == 0 && matriceVisual2[i][j] == 0) //si la case est un 0 et qu'elle n'est pas deja valide
                {
                    isVisual(matrice, matriceVisual, i, j, rowMax, tour1);  //on decouvre les cases autour
                    matriceVisual2[i][j] = 1;                   // et on valide la case dans une autre matrice.
                    isSame += 1;            // le nombre de case qui changent.
                }
            }
        }
        if (isSame == 0)                     //si aucune case n'a changé, fin de boucle.
        {
            break;
        }
        isSame = 0;
    }
}

void isBomb(int matrice[size][size], int bomb[size][size], int rowMax) //fonction permettant d'afficher le nombre de bombes proches des cases avec comme
{                                                                      //parametre la grille de bombe et la grille de jeu, et la longeur du tableau.
    int countBomb = 0;
    for (int row = 0; row < rowMax; row++)      
    {
        for (int col = 0; col < rowMax; col++)
        {
            if (row > 0) 
            {
                if (bomb[row - 1][col] == 1)  
                {
                    countBomb += 1;
                }
                if (col != rowMax)  
                {
                    if (bomb[row - 1][col + 1] == 1) 
                    {
                        countBomb += 1;
                    }
                }
                if (col > 0) 
                {
                    if (bomb[row - 1][col - 1] == 1) 
                    {
                        countBomb += 1;
                    }
                }
            }
            if (col != rowMax) 
            {
                if (bomb[row][col + 1] == 1) 
                {
                    countBomb += 1; 
                }
            }
            if (col > 0) 
            {
                if (bomb[row][col - 1] == 1) 
                {
                    countBomb += 1;
                }
            }
            if (row != rowMax) 
            {
                if (bomb[row + 1][col] == 1) 
                {
                    countBomb += 1;
                }
                if (col > 0) 
                {
                    if (bomb[row + 1][col - 1] == 1) 
                    {
                        countBomb += 1;
                    }
                }
                if (col != rowMax) 
                {
                    if (bomb[row + 1][col + 1] == 1)
                    {
                        countBomb += 1;
                    }
                }
            }
            if (bomb[row][col] != 1) //si la case n'est pas une bomb 
            {
                matrice[row][col] = countBomb;  //alors la case vaut l'indice.
            }
            else
            {
                matrice[row][col] = 9;      //sinon elle vaut 9 car "non devouverte".
            }
            countBomb = 0;
        }
    }
}

bool isWin(int matriceVisual[size][size], int rowMax, int nbBomb) //fonction permettant de calculer la win avec comme
{                                                               //parametres le tableau et sa taille, et le nombre de bombes.
    int countCaseVide = 0;
    for (int i = 0; i < rowMax; i++)
    {
        for (int j = 0; j < rowMax; j++)
        {
            if (matriceVisual[i][j] == 9)
            {
                countCaseVide += 1;
            }
        }
    }
    if (countCaseVide <= nbBomb)
    {
        return false;
    }
    else
    {
        return true;
    }
}



void red()
{
    printf("\033[1;31m");
}

void yellow(){
  printf("\033[1;33m");
}

void green() {
    printf("\033[1;32m");
}

void purple() {
    printf("\033[0;35m");
}


void reset() {
    printf("\033[0;37m");
}
//