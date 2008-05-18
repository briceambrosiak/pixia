/**
    Projet Jeu Pixia pour ESIAL CSH
    -------------------------------

    Editeur de carte

    Cr�� le 17 mai 2008

    Par Ga�tan SCHMITT et Brice AMBROSIAK

    Copyright 2008 Ga�tan SCHMITT

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

#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

#include <SDL/SDL.h>

// Elements constituant le terrain
typedef enum {WATER, GRASS, FOREST, MOUNTAIN, FIELD, HOUSE, SMALLTOWER, BIGTOWER, SAWMILL} GroundTile;

/**
	Terrain de jeu
*/
typedef struct {
	int height;				// Hauteur du terrain
	int width;				// Largeur du terrain
	GroundTile *ground; 	// Tableau � 2 dimensions
} Ground;

/**
	Entit�
*/
typedef struct {
	int x;				// Position x de l'entit�
	int y;				// Position y de l'entit�
	int lifeMax;		// Vie max
	int life;			// Vie restante
	SDL_Surface *tile; 	// Image de l'entit�
} Entity;


/**
	Carte (terrain + entit�s)
*/
typedef struct {
	char* name;			// Nom de la carte
	Ground ground;		// Terrain
	Entity *entities; 	// Entit�s (tableau)
} Map;

#endif // BIBLIO_H_INCLUDED
