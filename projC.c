#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printNumero();
void tabActuel(char tab[], int bomb[], int idBomb);



int main()
{
    // On commence par initialiser le générateur de nombre pseudo-aléatoires.
    srand(time(NULL));
    while (true)
    {
        while (true) {
            int bomb[20];                           //initialise le tab des bombes
            int idBomb = 0;

            // Tirer une valeur aléatoire entre 0 et 100.
            int bombe = rand() % 101;
            bomb[idBomb] = bombe;                //stocke les cases des bombes dans un tableau
            idBomb += 1;



            char tab[100];
            for (int i = 0; i < 100; i++)
            {
                tab[i] = "|X|";
            }

            printNumero();

            for (int i = 0; i < 100; i++)
            {
                printf("%c", tab[i]);

                if (((i + 1) % 10) == 0)
                {
                    printf("\n");

                }
            }
            printf("choisisez la case a detruire\n");
            int choix;
            if ((scanf_s("%d", &choix)) != 1)
            {
                printf("erreur de scan\n");
                return EXIT_FAILURE;
            }
            while (choix >= 100)
            {
                printf("erreur, choissisez une case du tableau non utilisé\n");
                if ((scanf_s("%d", &choix)) != 1)
                {
                    printf("erreur de scan\n");
                    return EXIT_FAILURE;
                }
            }
            for (int k = idBomb; k >= 0; k--)
            {
                if (bomb[k] == choix)
                {
                    printf("bombe touche. Game over. la valeur de la bombe est %d\n", bomb[k]);
                    return 0;
                }
            }

            printf("bombe non touche. Bravo,continue!\n");
            tab[choix] = "| |";

            tabActuel(tab, bomb, idBomb);

        }
        printf("Game Over. Belle partie.voulez vous recommencer ?\n");
        int sortie;
        if ((scanf_s("%d", &sortie)) != 1)
        {
            printf("erreur de scan\n");
            return EXIT_FAILURE;
        }
        if (sortie == 0)
        {
            break;
        }
    }
    printf("Fin de partie.\n");
    return EXIT_SUCCESS;
}

void printNumero()
{
    for (int i = 1; i <= 10; i++)
    {
        printf("|%d|", i);
    }
    printf("\n");
}

void tabActuel(char tab[], int bomb[], int idBomb)  //actualise le tab en calculant les numero indices des cases en fonction du tab ancien, de la liste de bomb et l'id de la derniere bombe du tab de bomb
{
    for (int i = 0; i <= 100; i++)
    {
        if (tab[i] == "| |")         //si la case est vide...
        {
            int countBomb = 0;
            for(int k = idBomb; k >= 0; k--)                    //...claculer le nombre de bombes proches
            {
                if (tab[i - 11] == bomb[k])
                {
                    countBomb += 1;
                }

                if (tab[i - 10] == bomb[k])
                {
                    countBomb += 1;
                }

                if (tab[i - 9] == bomb[k])
                {
                    countBomb += 1;
                }

                if (tab[i - 1] == bomb[k])
                {
                    countBomb += 1;
                }

                if (tab[i + 1] == bomb[k])
                {
                    countBomb += 1;
                }

                if (tab[i + 9] == bomb[k])
                {
                    countBomb += 1;
                }
                
                if (tab[i + 10] == bomb[k])
                {
                    countBomb += 1;
                }
                
                if (tab[i + 11] == bomb[k])
                {
                    countBomb += 1;
                }
            }
            tab[i] = "|(char)countBomb|";
            printf("%c", tab[i]);
        }
        printf("%c", tab[i]);
        if (((i + 1) % 10) == 0)
        {
            printf("\n");

        }
    }
}
