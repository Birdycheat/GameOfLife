
int compter_cases_vie(cadre, int, int);

cadre * passage(cadre *);

void afficher_cadre(cadre);

void passage_itere(SDL_Renderer *, cadre *, int, unsigned int, bool);

cadre * allouer_cadre(unsigned int, unsigned int);

void pause(SDL_Renderer *, cadre *, bool);

void print_rect(SDL_Renderer *, unsigned int, unsigned int, unsigned int, unsigned int, int, int, int, int);

void render_cadre(SDL_Renderer *, cadre, bool);

void mod_clic(SDL_Event *, cadre *, SDL_Renderer *, bool);
