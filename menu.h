/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	menu.h : Header

	Date : 20/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#ifndef DEF_MENU
#define DEF_MENU

// Possibilités du menu
enum {A_NEW_GAME, A_LOAD_GAME, A_OPTIONS, A_QUIT};

char menu(SDL_Surface *ecran);
char boucleMenu(SDL_Surface *ecran,
                SDL_Surface *fondMenu,
                SDL_Surface *nouvPart,
                SDL_Surface *chargPart,
                SDL_Surface *options,
                SDL_Surface *curseur,
                SDL_Rect p_fondMenu,
                SDL_Rect p_nouvPart,
                SDL_Rect p_chargPart,
                SDL_Rect p_options);
char chargMenu(int largeur,
                SDL_Surface **fondMenu,
                SDL_Surface **nouvPart,
                SDL_Surface **chargPart,
                SDL_Surface **options,
                SDL_Surface **curseur,
                SDL_Rect *p_fondMenu,
                SDL_Rect *p_nouvPart,
                SDL_Rect *p_chargPart,
                SDL_Rect *p_options);

#endif


