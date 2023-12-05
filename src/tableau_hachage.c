#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tableau_hachage.h"

int hacher(char *cle, int taille)
{
  int valeur_hashage = 0;

  while (*cle != '\0')
  {
    valeur_hashage += *cle;
    cle++;
  }

  return valeur_hashage % taille;
}

CleValeur *creeCleValeur(char *cle)
{
  CleValeur *couple = (CleValeur *)malloc(sizeof(CleValeur));
  couple->mot = strdup(cle);
  couple->frequence = 1;

  return couple;
}

Noeud *creerNoeud(CleValeur *donnee)
{
  Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
  noeud->donnee = *donnee;

  noeud->suivant = NULL;
  return noeud;
}

TableauHashage *creerTableauHashage(int taille)
{
  TableauHashage *tableauHashage = (TableauHashage *)malloc(sizeof(TableauHashage));
  tableauHashage->taille = taille;
  tableauHashage->tableau = (Noeud **)malloc(sizeof(Noeud *) * taille);

  for (int i = 0; i < taille; i++)
  {
    tableauHashage->tableau[i] = NULL;
  }

  return tableauHashage;
}

void insererOuModifier(TableauHashage *tableauHashage, char *mot)
{
  int indice = hacher(mot, tableauHashage->taille);
  Noeud *noeud = tableauHashage->tableau[indice];

  while (noeud != NULL)
  {
    if (strcmp(noeud->donnee.mot, mot) == 0)
    {
      noeud->donnee.frequence++;
      return;
    }

    noeud = noeud->suivant;
  }

  CleValeur *couple = creeCleValeur(mot);
  Noeud *noeudCree = creerNoeud(couple);

  noeudCree->suivant = tableauHashage->tableau[indice];
  tableauHashage->tableau[indice] = noeudCree;
}

void afficherFrequences(TableauHashage *tableauHashage)
{
  for (int i = 0; i < tableauHashage->taille; i++)
  {
    Noeud *noeud = tableauHashage->tableau[i];

    while (noeud != NULL)
    {
      printf("%s: %d\n", noeud->donnee.mot, noeud->donnee.frequence);
      noeud = noeud->suivant;
    }
  }
}

char *chercherFrequenceMinimum(TableauHashage *tableauHashage)
{
  char *minMot = NULL;
  int minFrequence = -1;

  for (int i = 0; i < tableauHashage->taille; i++)
  {
    Noeud *noeud = tableauHashage->tableau[i];

    while (noeud != NULL)
    {
      if (minFrequence == -1 || noeud->donnee.frequence < minFrequence)
      {
        minFrequence = noeud->donnee.frequence;
        minMot = noeud->donnee.mot;
      }

      noeud = noeud->suivant;
    }
  }

  return minMot;
}

int chercherFrequenceMot(TableauHashage *tableauHashage, char *mot)
{
  int indice = hacher(mot, tableauHashage->taille);
  Noeud *noeud = tableauHashage->tableau[indice];

  while (noeud != NULL)
  {
    if (strcmp(noeud->donnee.mot, mot) == 0)
    {
      return noeud->donnee.frequence;
    }

    noeud = noeud->suivant;
  }

  return 0;
}

void nettoyage(TableauHashage *tableauHashage)
{
  for (int i = 0; i < tableauHashage->taille; i++)
  {
    Noeud *noeud = tableauHashage->tableau[i];

    while (noeud != NULL)
    {
      Noeud *suivant = noeud->suivant;

      free(noeud->donnee.mot);
      free(noeud);

      noeud = suivant;
    }
  }

  free(tableauHashage->tableau);
  free(tableauHashage);
}