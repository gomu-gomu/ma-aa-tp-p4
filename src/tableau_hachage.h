#ifndef A_TABLEAU_HACHAGE
#define A_TABLEAU_HACHAGE

typedef struct
{
  char *mot;
  int frequence;
} CleValeur;

typedef struct Noeud
{
  CleValeur donnee;
  struct Noeud *suivant;
} Noeud;

typedef struct
{
  int taille;
  Noeud **tableau;
} TableauHashage;

int hacher(char *cle, int taille);

CleValeur *creeCleValeur(char *cle);

Noeud *creerNoeud(CleValeur *donnee);

TableauHashage *creerTableauHashage(int taille);

void insererOuModifier(TableauHashage *tableauHashage, char *mot);

void afficherFrequences(TableauHashage *tableauHashage);

char *chercherFrequenceMinimum(TableauHashage *tableauHashage);

int chercherFrequenceMot(TableauHashage *tableauHashage, char *mot);

void nettoyage(TableauHashage *tableauHashage);

#endif