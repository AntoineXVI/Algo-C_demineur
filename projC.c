#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define size 10
#define RowMax 10
#define RowMin 3

void initMatrice(int matrice[size][size], int valeurDepart, int rowMax);
void printMatrice(int matriceAAfficher[size][size], int matriceCondition[size][size], char* couleur, int rowMax, int condition);
void printNumero(int row);
int scanCoordonee(int max, int min, char* message);
void isVisual(int matrice[size][size], int matriceVisual[size][size], int choixI1, int choixJ1, int rowMax);
void isZero(int matrice[size][size], int matriceVisual[size][size], int matriceVisual2[size][size], int choixI1, int choixJ1, int rowMax);
void isBomb(int matrice[size][size], int bomb[size][size], int rowMax);
bool isWin(int matriceVisual[size][size], int rowMax, int nbBomb, int* score);
void red();
void green();
void yellow();
void purple();
void reset();



int main()
{
    int rejouer = 1;
    int score = 0;
    int loose = 0;
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
        int col = row;      //grille caree donc ligne = colonne.

        // On initialise la matrice pour stocker les bombes.
        int bomb[size][size];
        initMatrice(bomb, 0, row);

        // On initialise la matrice de jeu.
        int matrice[size][size];
        initMatrice(matrice, 0, row);

        // On initialise la matriceVisual.
        int matriceVisual[size][size];
        initMatrice(matriceVisual, 9, row);

        // On initialise la matriceVisual2.
        int matriceVisual2[size][size];     //matrice bonus pour valider les cases avec 0.
        initMatrice(matriceVisual2, 0, row);

        int nbBomb = row - 1;        // nombre de bomb en fonction de la taille
        if (row > 5)            //si la grille est tres grande , doubler le nombre de bombes.
        {
            nbBomb = nbBomb * 2;
        }

        bool tour1 = true;
        while (isWin(matriceVisual, row, nbBomb, &score))
        {
            printf("choisisez les coordonees de la ");
            if (tour1 == true)
            {
                printf("premiere ");
            }
            printf("case a detruire.\n");

            if (tour1 == true)
            {
                printMatrice(matrice, matriceVisual, "green", row, -1);
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
                loose += 1;
                printf("voici la grille complete avec les bombes\n"); //affiche la grille de bombe avec la bombe pour les tests.
                printMatrice(matrice, matrice, "green", row, 9);
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
                for (int i = 0; i < nbBomb; i++)
                {
                    int coordI = rand() % row;      // Tirer deux coordonees aléatoire entre 0 et la longueur max du tableau seulement au tour 1.
                    int coordJ = rand() % row;
                    while (matrice[coordI][coordJ] == 1)
                    {
                        coordI = rand() % row;    //Si la bombe est placé sur la 1ere case du joueur,rechoissir des novelles coordonees.
                        coordJ = rand() % row;
                    }
                    bomb[coordI][coordJ] = 1;       //placer les bombes dans la grille.
                }
            }
            isBomb(matrice, bomb, row);             //calcule les bombes proche de chaques cases.

            isVisual(matrice, matriceVisual, choixI1, choixJ1, row); //rend visibles les cases grace la grille de jeu à chaque tour.
            isZero(matrice, matriceVisual, matriceVisual2, choixI1, choixJ1, row); //affiche les cases autour des 0.

            printMatrice(matriceVisual, matriceVisual, "0", row, 9);

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
    printf("tu as choisi d'arreter. Bonne journee!\n");
    printf("ton score est de %d victoire(s) et de %d defaite(s).\n", score, loose);
    printf("Bonne journee!\n");
    return EXIT_SUCCESS;
}


void initMatrice(int matrice[size][size], int valeurDepart, int rowMax) //fonction pour init un ematrice avec une valeur defini
{
    for (int i = 0; i < rowMax; i++)
    {
        for (int j = 0; j < rowMax; j++)
        {
            matrice[i][j] = valeurDepart;
        }
    }
}

void printMatrice(int matriceAAfficher[size][size], int matriceCondition[size][size], char* couleur, int rowMax, int condition) //fonction pour print une matrice avec une couleur defini
{       // avec la matrice a afficher et sa taille, la couleur s'il y en a sinon "0", la condition pour la couleur sinon -1.
    printNumero(rowMax);
    for (int i = 0; i < rowMax; i++)
    {
        yellow();
        printf("|%d|", i);
        reset();
        for (int j = 0; j < rowMax; j++)
        {
            if ((condition != -1) && (matriceCondition[i][j] == condition)) // si la case a une valeur defini
            {
                purple(); //change la grille en violet
            }
            else if (couleur != "0")
            {
                if (couleur == "green")
                {
                    green();  //change la grille en vert
                }
                if (couleur == "red")
                {
                    red(); //change la grille en rouge
                }
            }
            printf("%3d", matriceAAfficher[i][j]);        //affiche la grille.
            reset();
        }
        printf("\n");
    }
}
void printNumero(int row)
{
    printf("    ");
    for (int i = 0; i < row; i++)
    {
        yellow();
        printf("|%d|", i);
        reset();
    }
    printf("\n\n");
}

int scanCoordonee(int max, int min, char* message) //fonction permettant de demander le choix de row/col et return l'int de la row/col avec comme
{                                                  //parametre le message pour demander ligne ou col, et le min et max possible.
    int coord;
    printf("choississez un numero de %s entre %d et %d\n", message, min, (max - 1));

    while (((scanf_s(" %d", &coord)) != 1) || (coord > (max - 1) || coord < (min - 1)))
    {
        printf("erreur de scan. Reessayez.\n");
        printf("choississez un numero de %s entre %d et %d\n", message, min, (max - 1));
    }
    return coord;
}


void isVisual(int matrice[size][size], int matriceVisual[size][size], int choixI1, int choixJ1, int rowMax)//fonction permettant d'afficher
{   //les cases visible pour le joueur avec comme parametre la grille visuel et jeu,du X et Y de la case, et la longeur du tableau.
    if (choixI1 < 0 || choixJ1 < 0)
    {
        printf("erreur: coordonees negatives\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        rowMax = rowMax - 1;

        matriceVisual[choixI1][choixJ1] = matrice[choixI1][choixJ1];
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

void isZero(int matrice[size][size], int matriceVisual[size][size], int matriceVisual2[size][size], int choixI1, int choixJ1, int rowMax)
{                // permet de découvrir une plus grande zone s'il y a des 0.
    int isSame = 0;
    while (true)
    {
        for (int i = 0; i < rowMax; i++)
        {
            for (int j = 0; j < rowMax; j++)
            {
                if (matriceVisual[i][j] != 9)  //si la case est visible
                {
                    if (i > 0)
                    {
                        if ((matrice[i - 1][j] == 0) && (matriceVisual2[i - 1][j] == 0)) //si la case d'au dessus vaut 0 et qu'elle n'est pas deja validé
                        {
                            matriceVisual[i - 1][j] = matrice[i - 1][j];        //afficher sur la grille.
                            matriceVisual2[i - 1][j] = 1;                   // et on valide la case dans une autre matrice.
                            isSame += 1;            // le nombre de case qui changent.
                        }
                        if (j != rowMax)
                        {
                            if ((matrice[i][j + 1] == 0) && (matriceVisual2[i][j + 1] == 0))
                            {
                                matriceVisual[i][j + 1] = matrice[i][j + 1];        //afficher sur la grille.
                                matriceVisual2[i][j + 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                            if ((matrice[i - 1][j + 1] == 0) && (matriceVisual2[i - 1][j + 1] == 0))
                            {
                                matriceVisual[i - 1][j + 1] = matrice[i - 1][j + 1];        //afficher sur la grille.
                                matriceVisual2[i - 1][j + 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                        }
                        if (j > 0)
                        {
                            if ((matrice[i][j - 1] == 0) && (matriceVisual2[i][j - 1] == 0))
                            {
                                matriceVisual[i][j - 1] = matrice[i][j - 1];        //afficher sur la grille.
                                matriceVisual2[i][j - 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                            if ((matrice[i - 1][j - 1] == 0) && (matriceVisual2[i - 1][j - 1] == 0))
                            {
                                matriceVisual[i - 1][j - 1] = matrice[i - 1][j - 1];        //afficher sur la grille.
                                matriceVisual2[i - 1][j - 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                        }
                    }
                    if (i != rowMax)
                    {
                        if ((matrice[i + 1][j] == 0) && (matriceVisual2[i + 1][j] == 0))
                        {
                            matriceVisual[i + 1][j] = matrice[i + 1][j];        //afficher sur la grille.
                            matriceVisual2[i + 1][j] = 1;                   // et on valide la case dans une autre matrice.
                            isSame += 1;            // le nombre de case qui changent.
                        }
                        if (j > 0)
                        {
                            if ((matrice[i][j - 1] == 0) && (matriceVisual2[i][j - 1] == 0))
                            {
                                matriceVisual[i][j - 1] = matrice[i][j - 1];        //afficher sur la grille.
                                matriceVisual2[i][j - 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                            if ((matrice[i + 1][j - 1] == 0) && (matriceVisual2[i + 1][j - 1] == 0))
                            {
                                matriceVisual[i + 1][j - 1] = matrice[i + 1][j - 1];        //afficher sur la grille.
                                matriceVisual2[i + 1][j - 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                        }
                        if (j < rowMax)
                        {
                            if ((matrice[i][j + 1] == 0) && (matriceVisual2[i][j + 1] == 0))
                            {
                                matriceVisual[i][j + 1] = matrice[i][j + 1];        //afficher sur la grille.
                                matriceVisual2[i][j + 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                            if ((matrice[i + 1][j + 1] == 0) && (matriceVisual2[i + 1][j + 1] == 0))
                            {
                                matriceVisual[i + 1][j + 1] = matrice[i + 1][j + 1];        //afficher sur la grille.
                                matriceVisual2[i + 1][j + 1] = 1;                   // et on valide la case dans une autre matrice.
                                isSame += 1;            // le nombre de case qui changent.
                            }
                        }
                    }
                }
                if ((matriceVisual[i][j] == 0) && (matriceVisual2[i][j] != 2)) //si la case est un 0 et qu'elle n'est pas deja valide
                {
                    isVisual(matrice, matriceVisual, i, j, rowMax);  //on decouvre les cases autour
                    matriceVisual2[i][j] = 2;                   // et on valide la case dans une autre matrice.
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

bool isWin(int matriceVisual[size][size], int rowMax, int nbBomb, int* score) //fonction permettant de calculer la win 
{
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
        printf("bravo, tu as gagne! \n");
        *score += 1;
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

void yellow() {
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
