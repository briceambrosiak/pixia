/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	nouvellePartie.c : Affichage du menu de nouvelle partie

	Date : 21/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <FMOD/fmod.h>

#include "constants.h"
#include "nouvellePartie.h"
#include "map.h"

void nouvellePartie(SDL_Surface *ecran)
{
    //----DECLARATIONS-------------------------------------------
    char ok, select;


    // Affichage menu nouvelle partie
	select = loopNewGame(ecran);

    // Lancement de partie (choix de map)
    switch(select)
    {
        case B_EASY:
			startTestMap(ecran);
            break;

        case B_NORMAL:
            break;

        case B_HARD:
            break;

		// Retour écran précédent
        case B_BACK:
            break;

        default:
            fprintf(stderr, "Erreur choix de difficulte [nouvellePartie.c]");
            exit(EXIT_FAILURE);
            break;
    }
}



/**
	Boucle menu nouvelle partie
*/
char loopNewGame(SDL_Surface *ecran)
{
    // Déclarations SDL
    SDL_Surface *fondNouvellePart, *facile, *moyen, *dur, *curseur;
    SDL_Rect p_fondNouvellePart, p_facile, p_moyen, p_dur, p_curseur;
    SDL_Event event;
    // Déclarations Sons
    FSOUND_SAMPLE *clic;
    // Déclarations autres
    char select, ok, son=0, continuer=1, echap=0;
    int iRes = 0, horSpace = 0, vertSpace = 0;
	int posButtons[2][3][4];

    enum {RES_800, RES_1024}; // Résolutions disponibles

	// Indice du tableau en fonction de la résolution
    switch (ecran->w) {
    	case 800: 	iRes = RES_800;	 break;
    	case 1024: 	iRes = RES_1024; break;
    	case 1280: 	iRes = RES_1024;
					horSpace = 128;
					vertSpace = 16; break; // Idem que 1024, avec bords noirs
    	default:
			fprintf(stderr, "Erreur @ nouvellePartie.c");
			exit(EXIT_FAILURE);
    }

    // Initialisations coordonnées
	posButtons[RES_800][B_EASY][0] = 357;
	posButtons[RES_800][B_EASY][1] = 461;
	posButtons[RES_800][B_EASY][2] = 278;
	posButtons[RES_800][B_EASY][3] = 311;
	posButtons[RES_800][B_NORMAL][0] = 349;
	posButtons[RES_800][B_NORMAL][1] = 475;
	posButtons[RES_800][B_NORMAL][2] = 332;
	posButtons[RES_800][B_NORMAL][3] = 370;
	posButtons[RES_800][B_HARD][0] = 373;
	posButtons[RES_800][B_HARD][1] = 447;
	posButtons[RES_800][B_HARD][2] = 379;
	posButtons[RES_800][B_HARD][3] = 406;
    posButtons[RES_1024][B_EASY][0] = 454;
	posButtons[RES_1024][B_EASY][1] = 596;
	posButtons[RES_1024][B_EASY][2] = 358;
	posButtons[RES_1024][B_EASY][3] = 399;
	posButtons[RES_1024][B_NORMAL][0] = 448;
	posButtons[RES_1024][B_NORMAL][1] = 606;
	posButtons[RES_1024][B_NORMAL][2] = 425;
	posButtons[RES_1024][B_NORMAL][3] = 471;
	posButtons[RES_1024][B_HARD][0] = 475;
	posButtons[RES_1024][B_HARD][1] = 573;
	posButtons[RES_1024][B_HARD][2] = 486;
	posButtons[RES_1024][B_HARD][3] = 521;


    //-----------------------------------------------------------
    //Chargement accueil nouvelle partie
    ok = chargImg(ecran->w, &fondNouvellePart, &facile, &moyen, &dur,
                    &p_fondNouvellePart, &p_facile, &p_moyen, &p_dur);
    if(ok !=1){
        fprintf(stderr, "Erreur (chargImg) [boucleNouvP]");
        exit(EXIT_FAILURE);
    }

    curseur = IMG_Load(FILE_CURSOR_ARROW);
    p_curseur.x = 0;
    p_curseur.y = 0;

    clic = FSOUND_Sample_Load(FSOUND_FREE, FILE_SOUND_CLIC, 0, 0, 0);

    //Affichage accueil nouvelle partie
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    SDL_BlitSurface(fondNouvellePart, NULL, ecran, &p_fondNouvellePart);
    SDL_BlitSurface(curseur, NULL, ecran, &p_curseur);
    SDL_Flip(ecran);


    //Boucle de choix
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type){
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
                if(event.button.button==SDL_BUTTON_LEFT && select!=4)
                    continuer = 0;
                    FSOUND_PlaySound(FSOUND_FREE, clic);
                break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));
        SDL_BlitSurface(fondNouvellePart, NULL, ecran, &p_fondNouvellePart);
        select = B_BACK;

        //Test bouton actif------------
        if(p_curseur.x > (posButtons[iRes][B_EASY][0] + horSpace)
        && p_curseur.x < (posButtons[iRes][B_EASY][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][B_EASY][2] + vertSpace)
            && p_curseur.y < (posButtons[iRes][B_EASY][3] + vertSpace))
		{
                SDL_BlitSurface(facile, NULL, ecran, &p_facile);
				select = B_EASY;
				if (son!=1){
					FSOUND_PlaySound(FSOUND_FREE, clic);
					son = 1;
				}
		}

        if(p_curseur.x > (posButtons[iRes][B_NORMAL][0] + horSpace)
		&& p_curseur.x < (posButtons[iRes][B_NORMAL][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][B_NORMAL][2] + vertSpace)
            && p_curseur.y < (posButtons[iRes][B_NORMAL][3] + vertSpace))
		{
			SDL_BlitSurface(moyen, NULL, ecran, &p_moyen);
			select = B_NORMAL;
			if (son!=2){
				FSOUND_PlaySound(FSOUND_FREE, clic);
				son = 2;
			}
		}

        if(p_curseur.x > (posButtons[iRes][B_HARD][0] + horSpace)
        && p_curseur.x < (posButtons[iRes][B_HARD][1] + horSpace))
            if(p_curseur.y > (posButtons[iRes][B_HARD][2] + vertSpace)
            && p_curseur.y < (posButtons[iRes][B_HARD][3] + vertSpace))
		{
                SDL_BlitSurface(dur, NULL, ecran, &p_dur);
				select = B_HARD;
				if (son!=3) {
					FSOUND_PlaySound(FSOUND_FREE, clic);
					son = 3;
				}
		}

        SDL_BlitSurface(curseur, NULL, ecran, &p_curseur);
        SDL_Flip(ecran);
    }

    if(echap == 1) select = B_BACK;


    // Libération de mémoire
    FSOUND_Sample_Free(clic);
    SDL_FreeSurface(fondNouvellePart);
    SDL_FreeSurface(facile);
    SDL_FreeSurface(moyen);
    SDL_FreeSurface(dur);
    SDL_FreeSurface(curseur);

    return select;
}

/**
	Chargement des images du menu nouvelle partie
*/
char chargImg(int largeur,
                SDL_Surface **fond,
                SDL_Surface **facile,
                SDL_Surface **moyen,
                SDL_Surface **dur,
                SDL_Rect *p_fond,
                SDL_Rect *p_facile,
                SDL_Rect *p_moyen,
                SDL_Rect *p_dur){
    //----------------------------------------------------------
    switch(largeur){
        case 1280:
            *fond = IMG_Load(FILE_BG_NEWGAME);
            p_fond->x = 128;
            p_fond->y = 16;
            *facile = IMG_Load(FILE_IMG_EASY);
            p_facile->x = 450+128;
            p_facile->y = 349+16;
            *moyen = IMG_Load(FILE_IMG_NORMAL);
            p_moyen->x = 437+128;
            p_moyen->y = 415+16;
            *dur = IMG_Load(FILE_IMG_HARD);
            p_dur->x = 464+128;
            p_dur->y = 477+16;
            break;
        case 1024:
            *fond = IMG_Load(FILE_BG_NEWGAME);
            p_fond->x = 0;
            p_fond->y = 0;
            *facile = IMG_Load(FILE_IMG_EASY);
            p_facile->x = 450;
            p_facile->y = 349;
            *moyen = IMG_Load(FILE_IMG_NORMAL);
            p_moyen->x = 437;
            p_moyen->y = 415;
            *dur = IMG_Load(FILE_IMG_HARD);
            p_dur->x = 464;
            p_dur->y = 477;
            break;
        case 800:
            *fond = IMG_Load(FILE_BG_NEWGAME_P);
            p_fond->x = 0;
            p_fond->y = 0;
            *facile = IMG_Load(FILE_IMG_EASY_P);
            p_facile->x = 352;
            p_facile->y = 273;
            *moyen = IMG_Load(FILE_IMG_NORMAL_P);
            p_moyen->x = 341;
            p_moyen->y = 324;
            *dur = IMG_Load(FILE_IMG_HARD_P);
            p_dur->x = 363;
            p_dur->y = 373;
            break;
        default:
            fprintf(stderr, "Erreur chargement image (chargImg) [boucleNouvP.c]");
            exit(EXIT_FAILURE);
            break;
    }

    return 1;
}





