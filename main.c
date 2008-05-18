/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	main.c : Fichier principal

	Date : 18/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak

	Copyright 2008 Gaétan SCHMITT

This file is part of Pixia.

    Pixia is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Pixia is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pixia; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//Includes classiques
#include <stdlib.h>
#include <stdio.h>

//Includes SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

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
    int o_largeur, o_hauteur, o_couleur, o_volume; // Options de jeu (lues d'un fichier)
    FSOUND_STREAM *m_menu, *m_enjeu; // Sons, musiques
    int vol;    //Volume calculé
    char ok;    //Valeur booleen pour les tests de réussite

    //------------------------------------------------------------
    // Chargement des options contenues dans le fichier d'option
    ok = optionsLoad(&o_largeur, &o_hauteur, &o_couleur, &o_volume);
    if(ok != 1){
        fprintf(stderr, "Erreur de lecture des options [main.c]");
        exit(EXIT_FAILURE);
    }

	// Volume audio
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

    //Musique de menu
    m_menu = FSOUND_Stream_Open(FILE_MUSIC_MENU, FSOUND_LOOP_NORMAL, 0, 0);       //Chargement du fichier
    FSOUND_Stream_SetLoopCount(m_menu, -1);                                       //Mise en mode REPEAT
    //Musique en jeu
    m_enjeu = FSOUND_Stream_Open(FILE_MUSIC_INGAME, FSOUND_LOOP_NORMAL, 0, 0);    //Chargement du fichier
    FSOUND_Stream_SetLoopCount(m_enjeu, -1);                                      //Mise en mode REPEAT

    //-------------------------------------------------------------
    //Lancement de la musique du menu
    FSOUND_Stream_Play(FSOUND_FREE, m_menu);
    FSOUND_SetVolume(FSOUND_ALL,vol);

    //-------------------------------------------------------------
    //Initialisation fenêtre
    SDL_WM_SetIcon(SDL_LoadBMP(FILE_ICON), NULL);               //Icone de fenêtre

    ecran = SDL_SetVideoMode(o_largeur,o_hauteur,o_couleur,     //Création de l'"écran support"
            SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);

    SDL_WM_SetCaption(GAME_NAME, NULL);                         //Nom de la fenêtre
    SDL_ShowCursor(SDL_DISABLE);                                //Désactivation du curseur de base

    //-------------------------------------------------------------
    //Initialisation de la TTF (affichage de texte)
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //--------------------------------------------------------------
    // Lancement menu principal
    while(ok != A_QUIT)
    {
        ok = menu(ecran);

        switch(ok)
        {
        	// Nouvelle partie
            case A_NEW_GAME:
                //Changement de musique
                FSOUND_Stream_Stop(m_menu);
                FSOUND_Stream_Play(FSOUND_FREE, m_enjeu);

                nouvellePartie(ecran);

                //Changement de musique
                FSOUND_Stream_Stop(m_enjeu);
                FSOUND_Stream_Play(FSOUND_FREE, m_menu);
                break;

			// Charger partie
            case A_LOAD_GAME:
                fprintf(stdout, "je load");
                SDL_FillRect(ecran, NULL, SDL_MapRGB((ecran)->format, 0,0,0));
                SDL_Flip(ecran);
                SDL_Delay(3000);
                /// TODO : Load Game non fait
                break;

			// Options
            case A_OPTIONS:
                ecranOptions(ecran);
                break;

			// Quitter
            case A_QUIT:
            fprintf(stdout, "je quitte");
                break;

			// Erreur
            default:
                fprintf(stderr,"Choix de menu erroné (menu()->ok) [main.c]");
                exit(EXIT_FAILURE);
                break;
        }
    }


    // Suppression de mémoire et stop module
    FSOUND_Stream_Stop(m_menu);         //Arrêt de la musique

    FSOUND_Stream_Close(m_menu);        //Suppression de l'espace mémoire
    FSOUND_Stream_Close(m_enjeu);      //Suppression de l'espace mémoire

    TTF_Quit();

    SDL_Quit();         //Cloture de la SDL
    FSOUND_Close();     //Cloture de FSOUND

    return EXIT_SUCCESS;
}

