/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	map.c : Gestion des cartes (chargement, sauvegarde, ...)

	Date : 26/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "map.h"

#include "constants.h"

/**
	Démarre un affichage de la map test
*/
void startTestMap(SDL_Surface *screen)
{
	SDL_Surface *tileGrass,
				*tileWater,
				*tileForest,
				*tileToBlit,
				*cursor = NULL;
	SDL_Rect p_tile, p_cursor;
	SDL_Event event;
	Map map;
	int continuer = 1, i = 0,  j= 0;

	srand(time(NULL));

	map = getTestMap(20, 40);

	tileGrass = IMG_Load(FILE_TILE_GRASS);
	tileWater = IMG_Load(FILE_TILE_WATER);
	tileForest = IMG_Load(FILE_TILE_FOREST);
	cursor = IMG_Load(FILE_CURSOR_ARROW);
	p_cursor.x = 0;
    p_cursor.y = 0;

    SDL_EnableKeyRepeat(300, 100);

	while (continuer)
	{
		SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

			case SDL_MOUSEMOTION:
                p_cursor.x = event.motion.x;
                p_cursor.y = event.motion.y;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

					case SDLK_SPACE:
						freeMap(map);
						map = getTestMap(20, 40);
						break;
                }
                break;
        }


		//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
		SDL_FillRect(screen, NULL, COLOR_BLACK(screen));

		p_tile.x = 0;
		p_tile.y = 0;

		// Mise à jour des tiles
		for (i=0 ; i<map.ground.height ; i++)
		{
			for (j=0 ; j<map.ground.width ; j++)
			{
				// Calcul position tile
				p_tile.x = j * TILE_WIDTH - TILE_SPACE*j + (map.ground.height-i)*TILE_SPACE;
				p_tile.y = i * TILE_HEIGHT;

				switch (map.ground.ground[i*map.ground.height + j])
				{
					case GRASS:
						tileToBlit = tileGrass;
						break;

					case WATER:
						tileToBlit = tileWater;
						break;

					case FOREST:
						tileToBlit = tileForest;
						break;
				}

				SDL_BlitSurface(tileToBlit, NULL, screen, &p_tile);
			}
		}

		SDL_BlitSurface(cursor, NULL, screen, &p_cursor);

		SDL_Flip(screen);
	}

	SDL_FreeSurface(tileGrass);
	SDL_FreeSurface(tileWater);
	SDL_FreeSurface(tileForest);
	SDL_FreeSurface(tileToBlit);
	SDL_FreeSurface(cursor);
	freeMap(map);
}

/**
	Charge une map test (herbe uniquement)
*/
Map getTestMap(int height, int width)
{
	int i, r;
	Map map;
	Ground ground;

	ground.height = height;
	ground.width = width;
	ground.ground = malloc(ground.height * ground.width * sizeof(GroundTile));

	for (i=0 ; i<ground.height*ground.width ; i++)
	{
		r = rand() % 100;

		if (r >= 0 && r < 70)
			ground.ground[i] = GRASS;
		else if (r >= 70 && r < 90)
			ground.ground[i] = WATER;
		else
			ground.ground[i] = FOREST;
	}

	map.name = "test";
	map.entities = NULL;
	map.ground = ground;

	return map;
}

/**
	Libère la mémoire utilisée par une map
*/
void freeMap(Map map)
{
	free(map.ground.ground);
}

/**
	Charge un terrain de jeu à partir d'un nom de fichier
*/
Map loadMap(char* filename)
{
	FILE* file;
	Map map;

	file = fopen(filename, "r");

	// Si impossible d'ouvrir le fichier
	if (file == NULL) return map;

	// Chargement terrain
	/// TODO : chargement terrain

	fclose(file);

	return map;
}
