#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tableau_hachage.h"

int main()
{
    char texte[1000];
    TableauHashage *tableauHashage = creerTableauHashage(1000);
    
    printf("Saisir le texte (mots séparés par des espaces) :\n> ");
    fgets(texte, sizeof(texte), stdin);

    char *mots = strtok(texte, " ");
    while (mots != NULL)
    {
        for (size_t i = 0; i < strlen(mots); i++)
        {
            mots[i] = tolower(mots[i]);
        }

        if (mots[strlen(mots) - 1] == '\n')
        {
            mots[strlen(mots) - 1] = '\0';
        }

        insererOuModifier(tableauHashage, mots);
        mots = strtok(NULL, " ");
    }

    // A - Afficher les mots du texte avec leurs fréquences.
    printf("Fréquences des mots :\n");
    afficherFrequences(tableauHashage);

    // B - Afficher le mot du texte le moins fréquent (c-à-d celui avec la plus petite fréquence).
    char *minMot = chercherFrequenceMinimum(tableauHashage);
    printf("Le mot ayant la fréquence minimale : %s\n", minMot);

    // C - Afficher la fréquence d’un mot dans le texte. Ce mot sera saisi au clavier.
    char motrecherche[50];
    printf("Entrez un mot pour trouver sa fréquence :\n> ");
    scanf("%s", motrecherche);

    int frequence = chercherFrequenceMot(tableauHashage, motrecherche);
    printf("Fréquence de %s : %d.\n", motrecherche, frequence);

    nettoyage(tableauHashage);
    return EXIT_SUCCESS;
}
