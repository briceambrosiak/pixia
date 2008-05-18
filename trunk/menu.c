/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	menu.c : Affichage du menu principal

	Date : 20/03/08
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

//Includes SDL et FSOUND
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <FMOD/fmod.h>

//Includes des fichiers de jeu
#include "constants.h"
#include "menu.h"

enum {RES_800, RES_1024}; 				// Résolutions disponibles
enum {NEW_GAME, LOAD_GAME, OPTIONS};    // index des différentes options du menu

typedef struct S_boucleMenu S_boucleMenu;

/**
	Fonction menu principal
*/
char menu(SDL_Surface *ecran)
{
    //--------DECLARATIONS-----------------------------------
    SDL_TimerID timer;  //Un timer pour la boucle du menu
    S_boucleMenu s_p;   //Structure spéciale envoyée au timer (un timer nécessite un unique paramètre)
    SDL_Event event;    //Pile des évènements
    char ok;            //Valeur de test : booleen

    //-------------------------------------------------------
    // Chargement des images du menu et leurs positions
    s_p.ecran = ecran;

    ok = chargMenu(&s_p);
    if(ok != 1){
        fprintf(stderr, "Erreur de chargement d'images menu (chargMenu) [menu.c]");
        exit(EXIT_FAILURE);
    }

    //--------------------------------------------------------
    // Indice du tableau en fonction de la résolution
    s_p.horSpace = 0;
    s_p.vertSpace = 0;

    switch (ecran->w) {
    	case 800:
            s_p.iRes = RES_800;
            break;
    	case 1024:
            s_p.iRes = RES_1024;
            break;
    	case 1280:  // Idem que 1024, avec bords noirs
            s_p.iRes = RES_1024;
            s_p.horSpace = 128;
            s_p.vertSpace = 16;
            break;
    	default:
			fprintf(stderr, "Erreur @ menu.c");
			exit(EXIT_FAILURE);
    }

	// Initialisation coordonnées
	s_p.posButtons[RES_800][NEW_GAME][0] = 267;
	s_p.posButtons[RES_800][NEW_GAME][1] = 542;
	s_p.posButtons[RES_800][NEW_GAME][2] = 214;
	s_p.posButtons[RES_800][NEW_GAME][3] = 253;
	s_p.posButtons[RES_800][LOAD_GAME][0] = 276;
	s_p.posButtons[RES_800][LOAD_GAME][1] = 524;
	s_p.posButtons[RES_800][LOAD_GAME][2] = 264;
	s_p.posButtons[RES_800][LOAD_GAME][3] = 305;
	s_p.posButtons[RES_800][OPTIONS][0] = 335;
	s_p.posButtons[RES_800][OPTIONS][1] = 472;
	s_p.posButtons[RES_800][OPTIONS][2] = 319;
	s_p.posButtons[RES_800][OPTIONS][3] = 356;
    s_p.posButtons[RES_1024][NEW_GAME][0] = 337;
	s_p.posButtons[RES_1024][NEW_GAME][1] = 692;
	s_p.posButtons[RES_1024][NEW_GAME][2] = 271;
	s_p.posButtons[RES_1024][NEW_GAME][3] = 325;
	s_p.posButtons[RES_1024][LOAD_GAME][0] = 350;
	s_p.posButtons[RES_1024][LOAD_GAME][1] = 674;
	s_p.posButtons[RES_1024][LOAD_GAME][2] = 340;
    s_p.posButtons[RES_1024][LOAD_GAME][3] = 389;
	s_p.posButtons[RES_1024][OPTIONS][0] = 430;
	s_p.posButtons[RES_1024][OPTIONS][1] = 603;
	s_p.posButtons[RES_1024][OPTIONS][2] = 409;
	s_p.posButtons[RES_1024][OPTIONS][3] = 455;

    s_p.select = A_QUIT;

    //Chargement du son
    s_p.clic = FSOUND_Sample_Load(FSOUND_FREE, FILE_SOUND_CLIC, 0, 0, 0);

    //----------------------------------------------------------------
    //Premier affichage:
    /// TODO : centrer le curseur ?
    s_p.p_curseur.x = 0;
    s_p.p_curseur.y = 0;

    SDL_BlitSurface(s_p.fondMenu, NULL, s_p.ecran, &s_p.p_fondMenu);    //Mise en place du fond
    SDL_Flip(s_p.ecran);                                                //Actualisation de l'écran

	// Boucle menu
	timer = SDL_AddTimer(45, boucleMenu, &s_p);

	s_p.echap = 0;

    while(s_p.continuer){   //Boucle de menu (tant qu'aucun choix n'est fait)

        while(SDL_PollEvent(&event)){       //Boucle d'évènement (tant qu'un évènement au moins est dans la pile)
            switch(event.type)
            {
                case SDL_QUIT:
                    s_p.continuer=0;
                    break;

                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            s_p.continuer=0;
                            s_p.echap = 1;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    s_p.p_curseur.x = event.motion.x;
                    s_p.p_curseur.y = event.motion.y;
                    break;

                case SDL_MOUSEBUTTONUP:
                    if(event.button.button==SDL_BUTTON_LEFT && s_p.select!=A_QUIT)
                        s_p.continuer = 0;
                        FSOUND_PlaySound(FSOUND_FREE, s_p.clic);
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(15);
    }

    SDL_RemoveTimer(timer);

    if(s_p.echap == 1)
        s_p.select = A_QUIT;

    // Suppression espace mémoire de menu
    SDL_FreeSurface(s_p.fondMenu);
    SDL_FreeSurface(s_p.nouvPart);
    SDL_FreeSurface(s_p.chargPart);
    SDL_FreeSurface(s_p.options);
    SDL_FreeSurface(s_p.curseur);

    FSOUND_Sample_Free(s_p.clic);

    return s_p.select;
}


/**
	Affichage du menu + interactions
*/
Uint32 boucleMenu(Uint32 intervalle, void *param)
{
    S_boucleMenu *p = param;

    //-----------------------------------------------------------------
    //Boucle Menu

    // Affichage du fond
    SDL_FillRect(p->ecran, NULL, SDL_MapRGB((p->ecran)->format, 0,0,0));
    SDL_BlitSurface(p->fondMenu, NULL, p->ecran, &p->p_fondMenu);

    p->select = A_QUIT;

    // Test bouton actif
    if(p->p_curseur.x > (p->posButtons[p->iRes][NEW_GAME][0] + p->horSpace)
    && p->p_curseur.x < (p->posButtons[p->iRes][NEW_GAME][1] + p->horSpace)){
        if(p->p_curseur.y > (p->posButtons[p->iRes][NEW_GAME][2] + p->vertSpace)
        && p->p_curseur.y < (p->posButtons[p->iRes][NEW_GAME][3] + p->vertSpace))
        {
            SDL_BlitSurface(p->nouvPart, NULL, p->ecran, &p->p_nouvPart);
                p->select = A_NEW_GAME;
                if(p->son!=1){
                    FSOUND_PlaySound(FSOUND_FREE, p->clic);
                    p->son = 1;
                }
        }
    }
    if(p->p_curseur.x > (p->posButtons[p->iRes][LOAD_GAME][0] + p->horSpace)
    && p->p_curseur.x < (p->posButtons[p->iRes][LOAD_GAME][1] + p->horSpace)){
        if(p->p_curseur.y > (p->posButtons[p->iRes][LOAD_GAME][2] + p->vertSpace)
        && p->p_curseur.y < (p->posButtons[p->iRes][LOAD_GAME][3] + p->vertSpace))
        {
            SDL_BlitSurface(p->chargPart, NULL, p->ecran, &p->p_chargPart);
                p->select = A_LOAD_GAME;
                if(p->son!=2){
                    FSOUND_PlaySound(FSOUND_FREE, p->clic);
                    p->son = 2;
                }
        }
    }
    if(p->p_curseur.x > (p->posButtons[p->iRes][OPTIONS][0] + p->horSpace)
    && p->p_curseur.x < (p->posButtons[p->iRes][OPTIONS][1] + p->horSpace)){
        if(p->p_curseur.y > (p->posButtons[p->iRes][OPTIONS][2] + p->vertSpace)
        && p->p_curseur.y < (p->posButtons[p->iRes][OPTIONS][3] + p->vertSpace))
        {
            SDL_BlitSurface(p->options, NULL, p->ecran, &p->p_options);
                p->select = A_OPTIONS;
                if(p->son!=3){
                    FSOUND_PlaySound(FSOUND_FREE, p->clic);
                    p->son = 3;
                }
        }
    }

    SDL_BlitSurface(p->curseur, NULL, p->ecran, &p->p_curseur);
    SDL_Flip(p->ecran);

    return intervalle;
}


/**
	Chargement textures & coordonnées menu
*/
char chargMenu(S_boucleMenu *s_p){
    //--DECLARATION------------------------------------------------------
    int hauteur;

    //---------------------------------------------------------------------
    s_p->curseur = IMG_Load(FILE_CURSOR_ARROW);

    //Suivant résolution :
    int largeur = s_p->ecran->w;

    switch(largeur){
        case 1280:
            hauteur = 800;
            s_p->fondMenu = IMG_Load(FILE_BG_MENU);
            s_p->p_fondMenu.x = (largeur-1024)/2;
            s_p->p_fondMenu.y = (hauteur-768)/2;
            s_p->nouvPart = IMG_Load(FILE_IMG_NEWGAME);
            s_p->p_nouvPart.x = 268 + (largeur-1024)/2;
            s_p->p_nouvPart.y = 257 + (hauteur-768)/2;
            s_p->chargPart = IMG_Load(FILE_IMG_LOADGAME);
            s_p->p_chargPart.x = 277 + (largeur-1024)/2;
            s_p->p_chargPart.y = 321 + (hauteur-768)/2;
            s_p->options = IMG_Load(FILE_IMG_OPTIONS);
            s_p->p_options.x = 383 + (largeur-1024)/2;
            s_p->p_options.y = 388 + (hauteur-768)/2;
            break;
        case 1024:
            s_p->fondMenu = IMG_Load(FILE_BG_MENU);
            s_p->p_fondMenu.x = 0;
            s_p->p_fondMenu.y = 0;
            s_p->nouvPart = IMG_Load(FILE_IMG_NEWGAME);
            s_p->p_nouvPart.x = 268;
            s_p->p_nouvPart.y = 257;
            s_p->chargPart = IMG_Load(FILE_IMG_LOADGAME);
            s_p->p_chargPart.x = 277;
            s_p->p_chargPart.y = 321;
            s_p->options = IMG_Load(FILE_IMG_OPTIONS);
            s_p->p_options.x = 383;
            s_p->p_options.y = 388;
            break;
        case 800:
            s_p->fondMenu = IMG_Load(FILE_BG_MENU_P);
            s_p->p_fondMenu.x = 0;
            s_p->p_fondMenu.y = 0;
            s_p->nouvPart = IMG_Load(FILE_IMG_NEWGAME_P);
            s_p->p_nouvPart.x = 209;
            s_p->p_nouvPart.y = 201;
            s_p->chargPart = IMG_Load(FILE_IMG_LOADGAME_P);
            s_p->p_chargPart.x = 217;
            s_p->p_chargPart.y = 251;
            s_p->options = IMG_Load(FILE_IMG_OPTIONS_P);
            s_p->p_options.x = 299;
            s_p->p_options.y = 303;
            break;
        default:
            fprintf(stderr, "Erreur chargement images de Menu (chargMenu) [chargMenu.c]");
            exit(EXIT_FAILURE);
    }

    return 1;
}







