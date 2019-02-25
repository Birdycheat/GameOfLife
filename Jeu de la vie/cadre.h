typedef struct cadre_st
{
     int ** Table;
     unsigned int hauteur;
     unsigned int largeur;
}cadre;

cadre * copier_cadre(cadre);

void liberer_cadre(cadre *);

cadre * planeur(cadre *);

cadre * canon(cadre *);

cadre * puffer(cadre *);

cadre * machine_rotative(cadre *);

cadre * aleatoire(cadre *);

cadre * allouer_cadre(unsigned int, unsigned int);

void afficher_cadre(cadre);
