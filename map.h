/**

	Pixia - Projet C ESIAL 1A
	--------------------------

	map.c : Fichier de la carte

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

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL/SDL.h>


// Types
// ------------------------------------------------------------------


// Elements constituant le terrain
typedef enum {
//Decors :
WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
MOUNTAIN1, MOUNTAIN2, MOUNTAIN3, MOUNTAIN4, MINE, RUINS,
//Entites :
DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS
} GroundTile; //=>25 Tiles

/**
	Terrain de jeu
*/
typedef struct {
	int height;				// Hauteur du terrain
	int width;				// Largeur du terrain
	GroundTile *ground; 	// Tableau à 2 dimensions
} Ground;

/**
	Entité
*/
typedef struct {
	int x;				// Position x de l'entité
	int y;				// Position y de l'entité
	int lifeMax;		// Vie max
	int life;			// Vie restante
	SDL_Surface *tile; 	// Image de l'entité
} Entity;


/**
	Carte (terrain + entités)
*/
typedef struct {
	char* name;			// Nom de la carte
	Ground ground;		// Terrain
	Entity *entities; 	// Entités (tableau)
} Map;


// Fonctions
// ------------------------------------------------------------------

Map getMap(int spec);

Map getClearMap(int width, int height, char* name);

void freeMap(Map map);

Map loadMap(char* filename);

int saveMap(Map map, char* filename);

#endif // MAP_H_INCLUDED
