/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	constants.h : Définition des constantes

	Date : 28/03/08
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

#ifndef CONSTANTS_H

    #define CONSTANTS_H

    // Constantes diverses
    #define GAME_NAME			"Pixia"
    #define EDITOR_NAME			"Editeur"

    #define ERROR_MSG_DURATION	3
    #define REFRESH_TIME_LIMIT	15
    #define REFRESH_DELAY_TIME	1
    #define MOVE_OFFSET		    40

    // Constantes fichiers
	#ifdef IN_EDITOR_MODE
		#define FILE_OPTIONS	"../options.txt"
	#else
		#define FILE_OPTIONS	"options.txt"
	#endif
    #define FILE_ICON			"images/palmier.bmp"
    #define FILE_EDITOR_ICON	"../images/palmier2.bmp"
    #define FILE_CURSOR_ARROW	"images/curseur2.png"

    #define FILE_MUSIC_MENU		"music/piano_rain.mp3"
    #define FILE_MUSIC_INGAME	"music/arc_en_ciel.mp3"

    #define FILE_SOUND_CLIC		"sound/clic.wav"

    #define FILE_TILE_GRASS		"images/tiles/tile_grass.png"
    #define FILE_TILE_WATER		"images/tiles/tile_water.png"
    #define FILE_TILE_FOREST	"images/tiles/tile_forest.png"

    #define FILE_BG_OPTIONS		"images/backgrounds/fond_options.jpg"
    #define FILE_BG_OPTIONS_P	"images/backgrounds/fond_optionsP.jpg"
    #define FILE_BG_MENU		"images/backgrounds/fond_menu.jpg"
    #define FILE_BG_MENU_P		"images/backgrounds/fond_menuP.jpg"
    #define FILE_BG_NEWGAME		"images/backgrounds/ecranPartie.jpg"
    #define FILE_BG_NEWGAME_P	"images/backgrounds/ecranPartieP.jpg"

    #define FILE_IMG_VALID		"images/valide.png"
    #define FILE_IMG_ACTIVE		"images/actif.png"
    #define FILE_IMG_NEWGAME	"images/nouv_partie.jpg"
    #define FILE_IMG_NEWGAME_P	"images/nouv_partieP.jpg"
    #define FILE_IMG_LOADGAME	"images/charg_partie.jpg"
    #define FILE_IMG_LOADGAME_P	"images/charg_partieP.jpg"
    #define FILE_IMG_OPTIONS	"images/options.jpg"
    #define FILE_IMG_OPTIONS_P	"images/optionsP.jpg"
    #define FILE_IMG_EASY		"images/facile.jpg"
    #define FILE_IMG_EASY_P		"images/facileP.jpg"
    #define FILE_IMG_NORMAL		"images/moyen.jpg"
    #define FILE_IMG_NORMAL_P	"images/moyenP.jpg"
    #define FILE_IMG_HARD		"images/dur.jpg"
    #define FILE_IMG_HARD_P		"images/durP.jpg"



    // Constantes couleurs
    #define COLOR_BLACK(E) 		SDL_MapRGB(E->format, 0, 0, 0)
    #define COLOR_BLEUTE(E) 	SDL_MapRGB(E->format, 190, 190, 250)

    // Constantes tiles
    #define TILE_WIDTH 			38
    #define TILE_HEIGHT 		14
    #define TILE_SPACE 			10
    #define TILE_BLANK_SPACE 	15


    // Fonctions
	#define WRITETXT(E, M, P, C, PO)\
    ({\
		SDL_Surface *texte;\
		SDL_Color black;\
		black.r=black.g=black.b=0;\
		texte = TTF_RenderText_Shaded(P, M, C, black);\
		SDL_BlitSurface(texte, NULL, E, &PO);\
		SDL_FreeSurface(texte);\
    })

#endif
