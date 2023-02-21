#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printNumero();



int main()
{
    // On commence par initialiser le générateur de nombre pseudo-aléatoires.
    //srand(time(NULL));

    while (true) {
        /*
        // Tirer une valeur aléatoire entre 0 et 100.
        int searchedValue = rand() % 101;
        */
        char* tab[100];
        for (int i = 0; i < 100; i++)
        {
            tab[i] = "X";
        }

        printNumero();

        for (int i = 0; i < 100; i++)
        {
            printf("%s", tab[i]);

            if (((i + 1) % 10) == 0)
            {
                printf("\n");

            }
        }

        int sortie = 0;
        if (sortie == 0) break;

    }

    printf("GG");

    return EXIT_SUCCESS;
}

void printNumero()
{
    for (int i = 1; i <= 10; i++)
    {
        printf("%d", i);
    }
    printf("\n");
}
