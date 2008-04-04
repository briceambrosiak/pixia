/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	map.h : Header. D�finition des types pour la carte

	Date : 26/03/08
	Author : Ga�tan Schmitt, Brice Ambrosiak
*/

#include <SDL/SDL.h>

#ifndef MAP_H
#define MAP_H

// Elements constituant le terrain
typedef enum {WATER, GRASS, FOREST, MOUNTAIN} GroundTile;

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

// ----------------------------------------------------------------------------

void startTestMap(SDL_Surface*);
Map getTestMap();
void freeMap(Map map);
Map loadMap(char*);
int saveMap(char*, Map);

#endif
