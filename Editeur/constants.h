/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	constants.h : Définition des constantes

	Date : 17/05/08
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
    #define GAME_NAME			"Editeur"

    // Constantes fichiers
    #define FILE_OPTIONS		"../options.txt"
    #define FILE_ICON			"../images/palmier2.bmp"

    // Constantes couleurs
    #define COLOR_BLACK(E) 	SDL_MapRGB(E->format, 0, 0, 0)
    #define COLOR_BLEUTE(E) SDL_MapRGB(E->format, 190, 190, 250)

    // Constantes tiles
    #define TILE_WIDTH 			38
    #define TILE_HEIGHT 		14
    #define TILE_SPACE 			10
    #define TILE_BLANK_SPACE 	15

    // Fonctions
    #define WRITETXT(E, M, P, C, PO)\
    ({\
    SDL_Surface *texte;\
    SDL_Color black = {0, 0, 0};\
    texte = TTF_RenderText_Shaded(P, M, C, black);\
    SDL_BlitSurface(texte, NULL, E, &PO);\
    SDL_FreeSurface(texte);\
    })


#endif // CONSTANTS_H_INCLUDED
