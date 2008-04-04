/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	nouvellePartie.h : Header

	Date : 21/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#ifndef DEF_NOUVELLEPARTIE
#define DEF_NOUVELLEPARTIE

// Actions possibles
enum {B_EASY, B_NORMAL, B_HARD, B_BACK};

void nouvellePartie(SDL_Surface *ecran);
char loopNewGame(SDL_Surface *ecran);
char chargImg(int largeur,
                SDL_Surface **fond,
                SDL_Surface **facile,
                SDL_Surface **moyen,
                SDL_Surface **dur,
                SDL_Rect *p_fond,
                SDL_Rect *p_facile,
                SDL_Rect *p_moyen,
                SDL_Rect *p_dur);

#endif

