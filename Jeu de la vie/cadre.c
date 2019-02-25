#include <stdlib.h>
#include <stdio.h>
#include "cadre.h"
#include "arith.h"

cadre * copier_cadre(cadre Cadre)
{
     cadre * Out = malloc(sizeof(cadre));
     Out->hauteur = Cadre.hauteur;
     Out->largeur = Cadre.largeur;
     Out->Table = malloc(sizeof(int*)*Cadre.hauteur);
     for (unsigned int i = 0; i < Cadre.hauteur; i++)
     {
          Out->Table[i] = malloc(sizeof(int)*Cadre.largeur);
     }
     for (unsigned int i = 0; i < Out->hauteur; i++)
     {
          for (unsigned int j = 0; j < Out->largeur; j++)
          {
               Out->Table[i][j] = Cadre.Table[i][j];
          }
     }
     return Out;
}

void liberer_cadre(cadre * Cadre)
{
     for(int i = 0; i < Cadre->hauteur; i++)
     {
          free(Cadre->Table[i]);
     }
     free(Cadre->Table);
     free(Cadre);
}

cadre * allouer_cadre(unsigned int hauteur, unsigned int largeur)
{
     cadre * Out = malloc(sizeof(cadre));

     Out->hauteur = hauteur;
     Out->largeur = largeur;


     Out->Table = malloc(sizeof(int*)*hauteur);

     for (unsigned int i = 0; i < hauteur; i++)
     {
          Out->Table[i] = malloc(sizeof(int)*largeur);
     }
     for (unsigned int i = 0; i < hauteur; i++)
     {
          for (unsigned int j = 0; j < largeur; j++)
          {
               Out->Table[i][j]= 0;
          }
     }
     return Out;
}

void afficher_cadre(cadre T)
{
     for (unsigned int i = 0; i < T.hauteur; i++)
     {
          for (unsigned int j = 0; j < T.largeur; j++)
          {
               if (T.Table[i][j] == false)
               {
                    printf(" ");
               }
               else
                    printf("o");
          }
          printf("\n");
     }
}

cadre * planeur(cadre * Cadre)
{
     Cadre->Table[0+min(Cadre->hauteur, Cadre->largeur)/2][1] = 1;
     Cadre->Table[1+min(Cadre->hauteur, Cadre->largeur)/2][1] = 1;
     Cadre->Table[1+min(Cadre->hauteur, Cadre->largeur)/2][2] = 1;
     Cadre->Table[2+min(Cadre->hauteur, Cadre->largeur)/2][2] = 1;
     Cadre->Table[2+min(Cadre->hauteur, Cadre->largeur)/2][0] = 1;

     return Cadre;
}

cadre * canon(cadre * Cadre)
{
     Cadre->Table[6][2] = 1;
     Cadre->Table[6][3] = 1;
     Cadre->Table[7][2] = 1;
     Cadre->Table[7][3] = 1;
     Cadre->Table[7][12] = 1;
     Cadre->Table[6][12] = 1;
     Cadre->Table[5][13] = 1;
     Cadre->Table[4][14] = 1;
     Cadre->Table[4][15] = 1;
     Cadre->Table[5][17] = 1;
     Cadre->Table[6][18] = 1;
     Cadre->Table[8][12] = 1;
     Cadre->Table[9][13] = 1;
     Cadre->Table[10][14] = 1;
     Cadre->Table[10][15] = 1;
     Cadre->Table[9][17] = 1;
     Cadre->Table[8][18] = 1;
     Cadre->Table[7][18] = 1;
     Cadre->Table[7][16] = 1;
     Cadre->Table[7][19] = 1;
     Cadre->Table[5][22] = 1;
     Cadre->Table[6][22] = 1;
     Cadre->Table[4][22] = 1;
     Cadre->Table[6][23] = 1;
     Cadre->Table[5][23] = 1;
     Cadre->Table[4][23] = 1;
     Cadre->Table[3][24] = 1;
     Cadre->Table[3][26] = 1;
     Cadre->Table[2][26] = 1;
     Cadre->Table[7][24] = 1;
     Cadre->Table[7][26] = 1;
     Cadre->Table[8][26] = 1;
     Cadre->Table[5][36] = 1;
     Cadre->Table[5][37] = 1;
     Cadre->Table[4][36] = 1;
     Cadre->Table[4][37] = 1;

     return Cadre;
}

cadre * aleatoire(cadre * Cadre)
{
     for (unsigned int i = 0; i < Cadre->hauteur; i++)
     {
          for (unsigned int j = 0; j < Cadre->largeur; j++)
          {
               Cadre->Table[i][j] = rand() % 2;
          }
     }
     return Cadre;
}

cadre * machine_rotative(cadre * Cadre)
{
     Cadre->Table[110+11][110+10] = 1;
     Cadre->Table[110+10][110+11] = 1;
     Cadre->Table[110+11][110+12] = 1;
     Cadre->Table[110+13][110+10] = 1;
     Cadre->Table[110+13][110+13] = 1;
     Cadre->Table[110+14][110+13] = 1;
     Cadre->Table[110+15][110+13] = 1;
     Cadre->Table[110+14][110+12] = 1;

     return Cadre;
}

cadre * puffer(cadre * Cadre)
{
     Cadre->Table[21][20] = 1;
     Cadre->Table[20][21] = 1;
     Cadre->Table[20][22] = 1;
     Cadre->Table[20][23] = 1;
     Cadre->Table[20][24] = 1;
     Cadre->Table[21][24] = 1;
     Cadre->Table[23][23] = 1;
     Cadre->Table[22][24] = 1;
     Cadre->Table[23][20] = 1;
     Cadre->Table[26][21] = 1;
     Cadre->Table[27][22] = 1;
     Cadre->Table[28][22] = 1;
     Cadre->Table[29][22] = 1;
     Cadre->Table[29][21] = 1;
     Cadre->Table[30][20] = 1;


     Cadre->Table[21+14][20] = 1;
     Cadre->Table[20+14][21] = 1;
     Cadre->Table[20+14][22] = 1;
     Cadre->Table[20+14][23] = 1;
     Cadre->Table[20+14][24] = 1;
     Cadre->Table[21+14][24] = 1;
     Cadre->Table[22+14][24] = 1;
     Cadre->Table[23+14][23] = 1;
     Cadre->Table[23+14][20] = 1;

     return Cadre;
}
