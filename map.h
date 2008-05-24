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
} GroundTile; //=>28 Tiles

typedef enum {
	E_DINO, E_SMALLTOWER, E_BIGTOWER, E_HOUSE, E_SAWMILL, E_MINECAMP,
	E_WELL, E_FIELD, E_SHEEP, E_GUARDIANS
} EntityId;
typedef enum {S_IDLE, S_MOVING, S_ATTACKING, S_RELOADING, S_SLEEPING} EntityStatus;

/**
	Terrain de jeu
*/
typedef struct {
	int height;				// Hauteur du terrain
	int width;				// Largeur du terrain
	GroundTile *ground; 	// Tableau à 2 dimensions
} Ground;

/**
	Type d'entité
*/
typedef struct {
	int ID;			// ID unique du type
	int IDmin;		// ID min de la plage
	int IDmax;		// ID max de la plage

	int posMax;		// Position max actuelle dans le tableau des entités

	char* name;		// Nom
	int lifeMax;	// Vie max

	int moveRand;	// Chances-3 qu'il reste sur place [-1 == ne peut pas se déplacer]
	int attack;		// Puissance d'attaque [-1 == ne peut pas attaquer]
	int range;		// Distance d'attaque
	int reloadTime;	// Attente entre 2 attaques

	// SON ?
	SDL_Surface *tile;	// Tile de l'entité
} EntityType;

/**
	Entité
*/
typedef struct {
	int ID;					// ID de l'entité
	EntityId typeID;		// ID unique identifiant le type
	int x, y;				// Position de l'entité
	int life;				// Vie restante
	int reload;				// Temps de rechargement restant
	//EntityStatus lastStatus;// Dernier status
	//EntityStatus status;	// Status actuel de l'entité (déplacement, attaque, ...)
} Entity;

/**
	Carte (terrain + entités)
*/
typedef struct{
	char* name;			// Nom de la carte
	Ground ground;		// Terrain
	Entity *entities; 	// Entités (tableau)
}Map;


// Fonctions
// ------------------------------------------------------------------

Map getMap(int spec);

Map getClearMap(int width, int height, char* name);

void freeMap(Map map);

Map loadMap(char* filename);

int saveMap(Map map, char* filename);

#endif // MAP_H_INCLUDED
