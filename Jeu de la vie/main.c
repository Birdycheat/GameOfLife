#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "cadre.h"
#include "arith.h"
#include "main.h"
#include "const.h"


void rafraichir(SDL_Renderer * renderer)
{
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
     SDL_RenderClear(renderer);
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
               {
                    out+=1;
               }
          }
     }
     return out;
}

void mod_clic(SDL_Event * Event, cadre * Cadre, SDL_Renderer * pRenderer, bool Folklore)
{
     unsigned int CONSTH = CSTH / Cadre->hauteur;
     unsigned int CONSTW = CSTW / Cadre->largeur;
     int x;
     int y;

     int continuer = 1;
     while (continuer)
     {
          SDL_WaitEvent(Event);
          switch (Event->type)
          {
               case SDL_MOUSEBUTTONDOWN:
                    x = (int) Event->motion.x / CONSTW;
                    y = (int) Event->motion.y / CONSTH;
                    if (Cadre->Table[y][x] == 1)
                    {
                         Cadre->Table[y][x] = 0;
                    }
                    else
                    {
                         Cadre->Table[y][x] = 1;
                    }
                    rafraichir(pRenderer);
                    render_cadre(pRenderer, *Cadre, Folklore);
                    SDL_RenderPresent(pRenderer);
                    break;
               case SDL_KEYDOWN:
                    continuer = 0;
                    break;
          }
     }
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
               if (T->Table[i][j] == 1)
               {
                    if ((cmp == 2) || (cmp == 3))
                    {
                         Out->Table[i][j] = 1;
                    }
                    else
                    {
                         Out->Table[i][j] = 0;
                    }
               }
               else
               {
                    if (cmp == 3)
                    {
                         Out->Table[i][j] = 1;
                    }
                    else
                    {
                         Out->Table[i][j] = 0;
                    }
               }
          }
     }
     liberer_cadre(T);
     return Out;
}

void passage_itere(SDL_Renderer * renderer, cadre * Cadre, int tempo, unsigned int nb_iterations, bool Folklore)
{
     clock_t beg, end;
     int ret;

     for (unsigned int i = 0; i < nb_iterations; i++)
     {
          SDL_Event QUIT;
          if (QUIT.type != SDL_KEYUP || QUIT.key.keysym.sym != SDLK_ESCAPE)
          {
               ret = SDL_PollEvent(&QUIT);
               beg = clock();
               end = clock();
               if (QUIT.type == SDL_KEYDOWN && QUIT.key.keysym.sym == SDLK_p)
               {
                    pause(renderer, Cadre, Folklore);
               }
               while (end - beg < TIMECST / tempo)
               {
                    end = clock();
               }
               Cadre = passage(Cadre);
               rafraichir(renderer);

               render_cadre(renderer, *Cadre, Folklore);
               SDL_RenderPresent(renderer);

          }
          else
          {
               break;
          }
     }
     liberer_cadre(Cadre);
}

void pause(SDL_Renderer * pRenderer, cadre * Cadre, bool Folklore)
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
               case SDL_KEYDOWN:
                    continuer = 0;
                    break;

               case SDL_QUIT:
                    if ( event.key.keysym.sym == SDLK_ESCAPE )
                    {
                         exit(314);
                    }
               case SDL_MOUSEBUTTONDOWN:
                    mod_clic(&event, Cadre, pRenderer, Folklore);
                    continuer = 0;
                    break;
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

     // Set render color
     SDL_SetRenderDrawColor(renderer, c1, c2, c3, c4);

     // Render rect
     SDL_RenderFillRect( renderer, &r );
}

void render_cadre(SDL_Renderer * renderer, cadre Cadre, bool Folklore)
{
     int c1, c2, c3, c4;

     unsigned int CONSTH = CSTH / Cadre.hauteur;
     unsigned int CONSTW = CSTW / Cadre.largeur;

     if (Folklore == 1)
     {
          int t = clock();
          c1 = (int)fabs(cos((double)(t/CSTC1))*CSTLUM1);
          c2 = (int)fabs(sin((double)(t/CSTC2))*CSTLUM2);
          c3 = (int)fabs(sin((double)(t/CSTC3))*CSTLUM3);
          c4 = (int)fabs(cos((double)(t/CSTC4))*CSTLUM4);
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
     printf("\nQuelle graine de départ voulez-vous ?\n\t1) Planeur\n\t2) Canon (50 x 50 min.)\n\t3) Aléatoire\n\t4) Machine instable (500 x 500 min.)\n\t5) Puffer (50 x 50 min.)\n\t6) Mode libre\n");
     fgets(ch, 10, stdin);
     int choice = atoi(ch);
     switch (choice)
     {
          case 1:
          // Planeur
               planeur(Cadre);
               break;
          case 2:
          // Canon
               canon(Cadre);
               break;
          case 3:
          // random gen
               aleatoire(Cadre);
               break;
          case 4:
          // Rotative machine
               machine_rotative(Cadre);
               break;
          case 5:
          // Puffer
               puffer(Cadre);
               break;
          case 6:
               break;
          default:
               exit(-11);
     }
     printf("Entrez une vitesse entre 1 et 99\n" );
     fgets(ch, 5, stdin);
     int vitesse = atoi(ch) % 100;

     if (vitesse == 0)
     {
          vitesse += 1;
     }
     printf("Voulez-vous de la couleur ?(Y/n) (Attention épileptiques...)\n");
     fgets(ch, 3, stdin);
     bool Folklore;
     if (ch[0] == 'Y')
     {
          Folklore = true;
     }
     else
     {
          Folklore = false;
     }
     printf("Et enfin donner le nombre de générations voulues (-1 pour un pseudo-infini)\n" );
     fgets(ch, 25, stdin);
     int generations = atoi(ch);
     free(ch);


     if (SDL_Init(SDL_INIT_VIDEO) == -1)
     {
          fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Error log
          exit(EXIT_FAILURE); // Quit prog
     }
     SDL_Window* pWindow;
     pWindow = SDL_CreateWindow("Jeu de la vie",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CSTH, CSTW, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     SDL_Renderer *renderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
     render_cadre(renderer, *Cadre, Folklore);
     SDL_RenderPresent(renderer);

     passage_itere(renderer, Cadre, vitesse, generations, Folklore);


     SDL_Event event;
     while (event.type != SDL_MOUSEBUTTONDOWN)
     {
          SDL_WaitEvent(&event);
     }
     if(pWindow)
     {
          SDL_DestroyRenderer(renderer);
          SDL_DestroyWindow(pWindow); // Destruction of the window
     }
     else
     {
         fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
     }

     SDL_Quit();
}
