#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>

#define TIMECST 500000
#define CSTH 1000
#define CSTW 1000

typedef enum bool_st
{
     false = 0,
     true = 1
}bool;

typedef struct cadre_st
{
     int ** Table;
     unsigned int hauteur;
     unsigned int largeur;
}cadre;

int compter_cases_vie(cadre T, int i, int j);

cadre * passage(cadre * T);

void afficher_cadre(cadre Cadre);

void passage_itere(SDL_Renderer * renderer, cadre * Cadre, int tempo, unsigned int nb_iterations, int Folklore);

cadre * allouer_cadre(unsigned int hauteur, unsigned int largeur);

cadre * copier_cadre(cadre Cadre);

void liberer_cadre(cadre * Cadre);

void pause();

void print_rect(SDL_Renderer * renderer, unsigned int h, unsigned int w, unsigned int x, unsigned int y, int c1, int c2, int c3, int c4);

void render_cadre(SDL_Renderer * renderer, cadre Cadre, int Folklore);

void rafraichir(SDL_Renderer * renderer)
{
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
     SDL_RenderClear(renderer);
}

int min(int a, int b){ return (a < b)*a + (a >= b)*b;}

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

int reste_div(int a, int b)
{
     int reste = a;
     while (reste >= b || reste < 0)
     {
          if (reste < 0)
               reste += b;
          else
               reste -= b;
     }
     return reste;
}
int compter_cases_vie(cadre T, int ligne, int colonne)
{
     int cell;
     int out = 0;
     for (int i = -1; i < 2; i++)
     {
          for (int j = -1; j < 2; j++)
          {
               cell = T.Table[reste_div((ligne + i), T.hauteur)][reste_div((colonne + j), T.largeur)];
               if (cell == 1 && (i != 0 || j != 0))
                    out+=1;
          }
     }
     return out;
}

cadre * passage(cadre * T)
{
     unsigned int cmp;
     cadre * Out = allouer_cadre(T->hauteur, T->largeur);
     for (unsigned int i = 0; i < T->hauteur; i++)
     {
          for (unsigned int j = 0; j < T->largeur; j++)
          {
               cmp = compter_cases_vie(*T, i, j);
               //printf("%d", cmp);
               if (T->Table[i][j] == 1)
                    if ((cmp == 2) || (cmp == 3))
                         Out->Table[i][j] = 1;
                    else
                         Out->Table[i][j] = 0;
               else
               {
                    if (cmp == 3)
                         Out->Table[i][j] = 1;
                    else
                         Out->Table[i][j] = 0;
               }
          }
          //printf("\n");
     }
     liberer_cadre(T);
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

void passage_itere(SDL_Renderer * renderer, cadre * Cadre, int tempo, unsigned int nb_iterations, int Folklore)
{
     clock_t beg, end;
     int ret;

     for (unsigned int i = 0; i < nb_iterations; i++)
     {
          SDL_Event QUIT;
          if (QUIT.type != SDL_KEYUP)
          {
               ret = SDL_PollEvent(&QUIT);
               beg = clock();
               end = clock();
               if (QUIT.type == SDL_MOUSEBUTTONDOWN)
                    pause(renderer);
               while (end - beg < TIMECST / tempo)
                    end = clock();
               Cadre = passage(Cadre);
               rafraichir(renderer);

               render_cadre(renderer, *Cadre, Folklore);
               SDL_RenderPresent(renderer);

          }
          else
               break;
     }
     liberer_cadre(Cadre);
}

void pause(SDL_Renderer * pRenderer)
{
    int continuer = 1;
    SDL_Event event;
     SDL_Surface* pSprite = SDL_LoadBMP("button_black_pause.bmp");
     if ( pSprite )
     {
       SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite
       if ( pTexture )
       {
           SDL_Rect dest = {0,0, pSprite->w, pSprite->h};
           SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite grâce au SDL_Renderer

           SDL_RenderPresent(pRenderer); // Affichage

       }
       else
       {
           fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
       }

       SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
     }
     else
     {
       fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
     }
     while (continuer)
     {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:

                continuer = 0;
                break;
            case SDL_QUIT:
                if ( event.key.keysym.sym == SDLK_ESCAPE )
                    exit(314);
        }
     }
}

void print_rect(SDL_Renderer * renderer, unsigned int h, unsigned int w, unsigned int x, unsigned int y, int c1, int c2, int c3, int c4)
{
     // Creat a rect at pos ( x, y ) that's w pixels wide and h pixels high.
     SDL_Rect r;
     r.x = x;
     r.y = y;
     r.w = w;
     r.h = h;

     // Set render color ( rect will be rendered in this color )
     SDL_SetRenderDrawColor(renderer, c1, c2, c3, c4);

     // Render rect
     SDL_RenderFillRect( renderer, &r );
}

void render_cadre(SDL_Renderer * renderer, cadre Cadre, int Folklore)
{
     int c1, c2, c3, c4;
     if (Folklore == 1)
     {
          int t = clock();
          c1 = (int)fabs(cos((double)(t/2211))*100);
          c2 = (int)fabs(sin((double)(t/999))*100);
          c3 = (int)fabs(sin((double)(t/777))*100);
          c4 = (int)fabs(cos((double)(t/1110))*100);
     }
     else
     {
          c1 = 255;
          c2 = 255;
          c3 = 255;
          c4 = 255;
     }
     for (unsigned int i = 0; i < Cadre.hauteur; i++)
     {
          for (unsigned int j = 0; j < Cadre.largeur; j++)
          {
               if (Cadre.Table[i][j] == 1)
               {
                    unsigned int CONSTH = CSTH / Cadre.hauteur;
                    unsigned int CONSTW = CSTW / Cadre.largeur;
                    print_rect(renderer, CONSTH, CONSTW, CONSTW*j, CONSTH*i, c1, c2, c3, c4);
               }
          }
     }
}


int main()
{


     srand(time(NULL));
     clock_t beg,end;
     char * ch = malloc(sizeof(char));
     printf("De quelle taille voulez-vous votre grille de Jeu ?\nHauteur :");
     fgets(ch, 20, stdin);
     int Hauteur = atoi(ch);
     printf("Largeur :");
     fgets(ch, 20, stdin);
     int Largeur = atoi(ch);

     cadre * Cadre = allouer_cadre(Hauteur, Largeur);
     printf("\nQuelle graine de départ voulez-vous ?\n\t1) Planeur\n\t2) Canon (50 x 50 min.)\n\t3) Aléatoire\n\t4) Machine instable (500 x 500 min.)\n\t5) Puffer (50 x 50 min.)\n");
     fgets(ch, 10, stdin);
     int choice = atoi(ch);
     switch (choice)
     {
          case 1:
          //planeur

               Cadre->Table[0+min(Hauteur, Largeur)/2][1] = 1;
               Cadre->Table[1+min(Hauteur, Largeur)/2][1] = 1;
               Cadre->Table[1+min(Hauteur, Largeur)/2][2] = 1;
               Cadre->Table[2+min(Hauteur, Largeur)/2][2] = 1;
               Cadre->Table[2+min(Hauteur, Largeur)/2][0] = 1;
               break;
          case 2:
               // Canon

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
               break;

          case 3:
               for (unsigned int i = 0; i < Cadre->hauteur; i++)
               {
                    for (unsigned int j = 0; j < Cadre->largeur; j++)
                    {
                         Cadre->Table[i][j] = rand() % 2;
                    }
               }
               break;
          case 4:
          // rotative machine

               Cadre->Table[110+11][110+10] = 1;
               Cadre->Table[110+10][110+11] = 1;
               Cadre->Table[110+11][110+12] = 1;
               Cadre->Table[110+13][110+10] = 1;
               Cadre->Table[110+13][110+13] = 1;
               Cadre->Table[110+14][110+13] = 1;
               Cadre->Table[110+15][110+13] = 1;
               Cadre->Table[110+14][110+12] = 1;
               break;
          case 5:
          // Puffer

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
               break;
          default:
               exit(-11);
     }
     printf("Entrez une vitesse entre 1 et 99\n" );
     fgets(ch, 5, stdin);
     int vitesse = atoi(ch) % 100;
     if (vitesse == 0)
          vitesse += 1;
     printf("Voulez-vous de la couleur ?(Y/n) (Attention épileptiques...)\n");
     fgets(ch, 3, stdin);
     int Folklore;
     if (ch[0] == 'Y')
     {
          Folklore = 1;
     }
     else
     {
          Folklore = 0;
     }
     printf("Et enfin donner le nombre de générations voulues (-1 pour un pseudo-infini)\n" );
     fgets(ch, 25, stdin);
     int generations = atoi(ch);
     free(ch);






     //system("clear");
     //afficher_cadre(*Cadre);


     if (SDL_Init(SDL_INIT_VIDEO) == -1)
     {
          fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
          exit(EXIT_FAILURE); // On quitte le programme
     }
     SDL_Window* pWindow;
     pWindow = SDL_CreateWindow("Jeu de la vie",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CSTH, CSTW, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     SDL_Renderer *renderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
     render_cadre(renderer, *Cadre, Folklore);
     SDL_RenderPresent(renderer);

     passage_itere(renderer, Cadre, vitesse, generations, Folklore);

     SDL_Event event;
     while (event.type != SDL_MOUSEBUTTONDOWN)
          SDL_WaitEvent(&event);
     if(pWindow)
     {
          /* Suite du programme */
          SDL_DestroyRenderer(renderer);
          SDL_DestroyWindow(pWindow); // Destruction de la fenêtre
     }
     else
     {
         fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
     }

     SDL_Quit();
}
