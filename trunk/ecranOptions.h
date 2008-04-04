/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	ecranOptions.h : Header

	Date : 20/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#ifndef DEF_ECRANOPTIONS
#define DEF_ECRANOPTIONS

void ecranOptions(SDL_Surface *ecran);
char chargImOp(int largeur,
                SDL_Surface **fondOptions,
                SDL_Surface **valide,
                SDL_Rect *p_fondOptions,
                SDL_Rect *p_resolution,
                SDL_Rect *p_couleur,
                SDL_Rect *p_volume,
                SDL_Rect *p_actif);
char boucleOp(SDL_Surface *ecran,
				SDL_Surface *fondOptions,
				SDL_Surface *valide,
				SDL_Rect p_fondOptions,
				SDL_Rect *p_resolution,
				SDL_Rect *p_couleur,
				SDL_Rect *p_volume,
				SDL_Rect *p_actif);

#endif

