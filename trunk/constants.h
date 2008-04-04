/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	constants.h : Définition des constantes

	Date : 28/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constantes diverses
#define GAME_NAME			"Pixia"

// Constantes fichiers
#define FILE_OPTIONS		"options.txt"
#define FILE_ICON			"images/palmier.bmp"
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
#define COLOR_BLACK(ecran) 	SDL_MapRGB(ecran->format, 0, 0, 0)

// Constantes tiles
#define TILE_WIDTH 			30
#define TILE_HEIGHT 		30
#define TILE_SPACE 			6
#define TILE_BLANK_SPACE 	15

// Fonctions


#endif
