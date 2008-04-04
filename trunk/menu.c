/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	menu.c : Affichage du menu principal

	Date : 20/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <FMOD/fmod.h>

#include "constants.h"
#include "menu.h"

/**
	Fonction menu principal
*/
char menu(SDL_Surface *ecran)
{
    //--------DECLARATIONS-----------------------------------
    SDL_Surface *fondMenu, *nouvPart, *chargPart, *options, *curseur;
    SDL_Rect p_fondMenu, p_nouvPart, p_chargPart, p_options;
    char choix, ok;
    int largeur = ecran->w;

    //-------------------------------------------------------

    // Chargement des images du menu et leur position
    ok = chargMenu(largeur, &fondMenu, &nouvPart, &chargPart, &options, &curseur,
                    &p_fondMenu, &p_nouvPart, &p_chargPart, &p_options);
    if(ok != 1){
        fprintf(stderr, "Erreur de chargement d'images menu (chargMenu) [menu.c]");
        exit(EXIT_FAILURE);
    }


	// Boucle menu
    choix = boucleMenu(ecran, fondMenu, nouvPart, chargPart, options, curseur,
						p_fondMenu, p_nouvPart, p_chargPart, p_options);

    /// TODO : <<<<< UN TIMER A LA PLACE ???? >>>>>


    // Suppression espace mémoire de menu
    SDL_FreeSurface(fondMenu);
    SDL_FreeSurface(nouvPart);
    SDL_FreeSurface(chargPart);
    SDL_FreeSurface(options);
    SDL_FreeSurface(curseur);

    return choix;
}


/**
	Affichage du menu + interactions
*/
char boucleMenu(SDL_Surface *ecran,
                SDL_Surface *fondMenu,
                SDL_Surface *nouvPart,
                SDL_Surface *chargPart,
                SDL_Surface *options,
                SDL_Surface *curseur,
                SDL_Rect p_fondMenu,
                SDL_Rect p_nouvPart,
                SDL_Rect p_chargPart,
                SDL_Rect p_options)
{
    //---DECLARATIONS-------------------------------------------------
    enum {RES_800, RES_1024}; 				// Résolutions disponibles
	enum {NEW_GAME, LOAD_GAME, OPTIONS};

    SDL_Rect p_curseur;
    SDL_Event event;
	FSOUND_SAMPLE *clic;
    int posButtons[2][3][4];
    int iRes = 0, horSpace = 0, vertSpace = 0;
    char continuer=1, select=A_QUIT, echap=0, son=0;

	// Indice du tableau en fonction de la résolution
    switch (ecran->w) {
    	case 800: 	iRes = RES_800;	 break;
    	case 1024: 	iRes = RES_1024; break;
    	case 1280: 	iRes = RES_1024;
					horSpace = 128;
					vertSpace = 16; break; // Idem que 1024, avec bords noirs
    	default:
			fprintf(stderr, "Erreur @ menu.c");
			exit(EXIT_FAILURE);
    }

	// Initialisations coordonnées
	posButtons[RES_800][NEW_GAME][0] = 267;
	posButtons[RES_800][NEW_GAME][1] = 542;
	posButtons[RES_800][NEW_GAME][2] = 214;
	posButtons[RES_800][NEW_GAME][3] = 253;
	posButtons[RES_800][LOAD_GAME][0] = 276;
	posButtons[RES_800][LOAD_GAME][1] = 524;
	posButtons[RES_800][LOAD_GAME][2] = 264;
	posButtons[RES_800][LOAD_GAME][3] = 305;
	posButtons[RES_800][OPTIONS][0] = 335;
	posButtons[RES_800][OPTIONS][1] = 472;
	posButtons[RES_800][OPTIONS][2] = 319;
	posButtons[RES_800][OPTIONS][3] = 356;
    posButtons[RES_1024][NEW_GAME][0] = 337;
	posButtons[RES_1024][NEW_GAME][1] = 692;
	posButtons[RES_1024][NEW_GAME][2] = 271;
	posButtons[RES_1024][NEW_GAME][3] = 325;
	posButtons[RES_1024][LOAD_GAME][0] = 350;
	posButtons[RES_1024][LOAD_GAME][1] = 674;
	posButtons[RES_1024][LOAD_GAME][2] = 340;
	posButtons[RES_1024][LOAD_GAME][3] = 389;
	posButtons[RES_1024][OPTIONS][0] = 430;
	posButtons[RES_1024][OPTIONS][1] = 603;
	posButtons[RES_1024][OPTIONS][2] = 409;
	posButtons[RES_1024][OPTIONS][3] = 455;


    clic = FSOUND_Sample_Load(FSOUND_FREE, FILE_SOUND_CLIC, 0, 0, 0);

    //----------------------------------------------------------------
    //Premier affichage:
    /// TODO : centrer le curseur ?
    p_curseur.x = 0;
    p_curseur.y = 0;

    SDL_BlitSurface(fondMenu, NULL, ecran, &p_fondMenu);
    SDL_Flip(ecran);

    //-----------------------------------------------------------------
    //Boucle Menu

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer=0;
                        echap=1;
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                p_curseur.x = event.motion.x;
                p_curseur.y = event.motion.y;
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT && select!=A_QUIT)
                    continuer = 0;
                    FSOUND_PlaySound(FSOUND_FREE, clic);
                break;
        }

		// Affichage du fond
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));
        SDL_BlitSurface(fondMenu, NULL, ecran, &p_fondMenu);
        select = A_QUIT;

        // Test bouton actif
        if(p_curseur.x > (posButtons[iRes][NEW_GAME][0] + horSpace)
		&& p_curseur.x < (posButtons[iRes][NEW_GAME][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][NEW_GAME][2] + vertSpace)
			&& p_curseur.y < (posButtons[iRes][NEW_GAME][3] + vertSpace))
			{
                SDL_BlitSurface(nouvPart, NULL, ecran, &p_nouvPart);
                    select = A_NEW_GAME;
                    if(son!=1){
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        son = 1;
                    }
            }
        if(p_curseur.x > (posButtons[iRes][LOAD_GAME][0] + horSpace)
        && p_curseur.x < (posButtons[iRes][LOAD_GAME][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][LOAD_GAME][2] + vertSpace)
            && p_curseur.y < (posButtons[iRes][LOAD_GAME][3] + vertSpace))
            {
                SDL_BlitSurface(chargPart, NULL, ecran, &p_chargPart);
                    select = A_LOAD_GAME;
                    if(son!=2){
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        son = 2;
                    }
            }
        if(p_curseur.x > (posButtons[iRes][OPTIONS][0] + horSpace)
        && p_curseur.x < (posButtons[iRes][OPTIONS][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][OPTIONS][2] + vertSpace)
            && p_curseur.y < (posButtons[iRes][OPTIONS][3] + vertSpace))
            {
                SDL_BlitSurface(options, NULL, ecran, &p_options);
                    select = A_OPTIONS;
                    if(son!=3){
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        son = 3;
                    }
            }

        SDL_BlitSurface(curseur, NULL, ecran, &p_curseur);
        SDL_Flip(ecran);
    }

    if(echap) select = A_QUIT;

    FSOUND_Sample_Free(clic);
    return select;
}


/**
	Chargement textures & coordonnées menu
*/
char chargMenu(int largeur,
                SDL_Surface **fondMenu,
                SDL_Surface **nouvPart,
                SDL_Surface **chargPart,
                SDL_Surface **options,
                SDL_Surface **curseur,
                SDL_Rect *p_fondMenu,
                SDL_Rect *p_nouvPart,
                SDL_Rect *p_chargPart,
                SDL_Rect *p_options){
    //--DECLARATION------------------------------------------------------
    int hauteur;
    //---------------------------------------------------------------------
    *curseur = IMG_Load(FILE_CURSOR_ARROW);
    //Suivant résolution :
    switch(largeur){
        case 1280:
            hauteur = 800;
            *fondMenu = IMG_Load(FILE_BG_MENU);
            p_fondMenu->x = (largeur-1024)/2;
            p_fondMenu->y = (hauteur-768)/2;
            *nouvPart = IMG_Load(FILE_IMG_NEWGAME);
            p_nouvPart->x = 268 + (largeur-1024)/2;
            p_nouvPart->y = 257 + (hauteur-768)/2;
            *chargPart = IMG_Load(FILE_IMG_LOADGAME);
            p_chargPart->x = 277 + (largeur-1024)/2;
            p_chargPart->y = 321 + (hauteur-768)/2;
            *options = IMG_Load(FILE_IMG_OPTIONS);
            p_options->x = 383 + (largeur-1024)/2;
            p_options->y = 388 + (hauteur-768)/2;
            break;
        case 1024:
            *fondMenu = IMG_Load(FILE_BG_MENU);
            p_fondMenu->x = 0;
            p_fondMenu->y = 0;
            *nouvPart = IMG_Load(FILE_IMG_NEWGAME);
            p_nouvPart->x = 268;
            p_nouvPart->y = 257;
            *chargPart = IMG_Load(FILE_IMG_LOADGAME);
            p_chargPart->x = 277;
            p_chargPart->y = 321;
            *options = IMG_Load(FILE_IMG_OPTIONS);
            p_options->x = 383;
            p_options->y = 388;
            break;
        case 800:
            *fondMenu = IMG_Load(FILE_BG_MENU_P);
            p_fondMenu->x = 0;
            p_fondMenu->y = 0;
            *nouvPart = IMG_Load(FILE_IMG_NEWGAME_P);
            p_nouvPart->x = 209;
            p_nouvPart->y = 201;
            *chargPart = IMG_Load(FILE_IMG_LOADGAME_P);
            p_chargPart->x = 217;
            p_chargPart->y = 251;
            *options = IMG_Load(FILE_IMG_OPTIONS_P);
            p_options->x = 299;
            p_options->y = 303;
            break;
        default:
            fprintf(stderr, "Erreur chargement images de Menu (chargMenu) [chargMenu.c]");
            exit(EXIT_FAILURE);
    }
    return 1;
}







