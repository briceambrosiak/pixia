/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	main.c : Fichier principal

	Date : 18/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

//Includes classiques
#include <stdlib.h>
#include <stdio.h>

//Includes SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//Includes son
#include <FMOD/fmod.h>

//Includes de fichier du jeu
#include "options.h"
#include "menu.h"
#include "ecranOptions.h"
#include "nouvellePartie.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    //--------------DECLARATIONS---------------------------------

    SDL_Surface *ecran;
    int o_largeur, o_hauteur, o_couleur, o_volume; // Options
    FSOUND_STREAM *musique, *enjeu; // Sons, musiques
    int vol;
    char ok;

    //------------------------------------------------------------

    // Chargement des options
    ok = optionsLoad(&o_largeur, &o_hauteur, &o_couleur, &o_volume);
    if(ok != 1){
        fprintf(stderr, "Erreur de lecture des options [main.c]");
        exit(EXIT_FAILURE);
    }

	// Volume
	/// TODO : changement de volume ne marche pas
	if (o_volume >= 0 && o_volume <= 100)
		vol = (int) (o_volume/100) * 255;
	else {
		fprintf(stderr, "Valeur de volume inconnu [main.c]");
		exit(EXIT_FAILURE);
	}


    //-------------------------------------------------------------
    //Initialisation video
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    //-------------------------------------------------------------
    //Initialisation musique
    FSOUND_Init(44100, 32, 0);
    musique = FSOUND_Stream_Open(FILE_MUSIC_MENU, FSOUND_LOOP_NORMAL, 0, 0);
    enjeu = FSOUND_Stream_Open(FILE_MUSIC_INGAME, FSOUND_LOOP_NORMAL, 0, 0);
    FSOUND_Stream_SetLoopCount(musique, -1);
    FSOUND_Stream_Play(FSOUND_FREE, musique);
    FSOUND_SetVolume(FSOUND_ALL,vol);

    //-------------------------------------------------------------
    //Initialisation fenêtre
    SDL_WM_SetIcon(SDL_LoadBMP(FILE_ICON), NULL);
    ecran = SDL_SetVideoMode(o_largeur,o_hauteur,o_couleur,
            SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(GAME_NAME, NULL);
    SDL_ShowCursor(SDL_DISABLE);

    //--------------------------------------------------------------
    // Lancement menu principal
    while(ok != A_QUIT)
    {
        ok = menu(ecran);

        switch(ok)
        {
        	// Nouvelle partie
            case A_NEW_GAME:
                FSOUND_Stream_Stop(musique);
                FSOUND_Stream_Play(FSOUND_FREE, enjeu);

                nouvellePartie(ecran);

                FSOUND_Stream_Stop(enjeu);
                FSOUND_Stream_Play(FSOUND_FREE, musique);
                break;

			// Charger partie
            case A_LOAD_GAME:
                break;

			// Options
            case A_OPTIONS:
                ecranOptions(ecran);
                break;

			// Quitter
            case A_QUIT:
                break;

			// Erreur
            default:
                fprintf(stderr,"Choix de menu erroné (menu()->ok) [main.c]");
                exit(EXIT_FAILURE);
                break;
        }
    }


    // Suppression de mémoire et stop module
    FSOUND_Stream_Stop(musique);

    SDL_Quit();
    FSOUND_Close();

    return EXIT_SUCCESS;
}

