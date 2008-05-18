/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	map.c : Gestion des cartes (chargement, sauvegarde, ...)

	Date : 26/03/08
	Author : Ga�tan Schmitt, Brice Ambrosiak
*/

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "map.h"

#include "constants.h"

/**
	D�marre un affichage de la map test
*/
void startTestMap(SDL_Surface *screen)
{
	SDL_Surface *tileGrass,
				*tileWater,
				*tileForest,
				*tileCursor,
				*tileWireframe,
				*tileToBlit,
				*cursor = NULL;
    SDL_Surface *textSurface;
	SDL_Rect p_tile, p_cursor, p_font, p_tileCursor;
	SDL_Event event;
	SDL_Color fontColor = {128,128,128};
	Map map;
	TTF_Font *font;
	int continuer = 1, i = 0,  j= 0;
	int curX = 0, curY = 0;
	char textBuffer[256];

	srand(time(NULL));

    TTF_Init();
    font = TTF_OpenFont("verdana.ttf", 10);
    //font = TTF_OpenFont("courier.ttf", 10);
	map = getTestMap(20, 40);

	tileGrass = IMG_Load(FILE_TILE_GRASS);
	tileWater = IMG_Load(FILE_TILE_WATER);
	tileForest = IMG_Load(FILE_TILE_FOREST);
	tileCursor = IMG_Load(FILE_TILE_CURSOR);
	tileWireframe = IMG_Load(FILE_TILE_WIREFRAME);
	//cursor = IMG_Load(FILE_CURSOR_ARROW);
	p_cursor.x = 0;
    p_cursor.y = 0;
    p_font.x = 0;
    p_font.y = 0;
    p_tileCursor.x = 0;
    p_tileCursor.y = 0;

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

                // Calcule les coordonn�es du tile que l'on survole
                curY = p_cursor.y / TILE_HEIGHT;
                curX = (p_cursor.x - TILE_SPACE*(map.ground.height-curY-1)) / (TILE_WIDTH-TILE_SPACE);

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

		// Mise � jour des tiles
		for (i=0 ; i<map.ground.height ; i++)
		{
			for (j=0 ; j<map.ground.width ; j++)
			{
				// Calcul position tile

				// Largeur - d�callage superposition + d�callage inclinaison
				p_tile.x = j*(TILE_WIDTH - TILE_SPACE) + (map.ground.height-i-1)*TILE_SPACE;
				p_tile.y = i*TILE_HEIGHT;

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

                //tileToBlit = tileWireframe;
				SDL_BlitSurface(tileToBlit, NULL, screen, &p_tile);

				// Dessine le curseur de tile
				p_tileCursor.x = curX*(TILE_WIDTH - TILE_SPACE) + (map.ground.height-curY-1)*TILE_SPACE;
                p_tileCursor.y = curY*TILE_HEIGHT;
				SDL_BlitSurface(tileCursor, NULL, screen, &p_tileCursor);
			}
		}

        // Texte
        sprintf(textBuffer, "Tile %3d,%3d | %3d | x: %5d", curX, curY, TILE_SPACE*(map.ground.height-curY), p_cursor.x);
        textSurface = TTF_RenderText_Solid(font, textBuffer, fontColor);
        if (!textSurface) {
            fprintf(stderr, "Error initializing font @ map.c");
        }
        else {
            p_font.x = screen->w - textSurface->w;
            p_font.y = screen->h - textSurface->h;
            SDL_BlitSurface(textSurface, NULL, screen, &p_font);
            SDL_FreeSurface(textSurface);
        }

		//SDL_BlitSurface(cursor, NULL, screen, &p_cursor);

		SDL_Flip(screen);
	}

    freeMap(map);
	SDL_FreeSurface(tileGrass);
	SDL_FreeSurface(tileWater);
	SDL_FreeSurface(tileForest);
	SDL_FreeSurface(tileWireframe);
	SDL_FreeSurface(tileCursor);
	SDL_FreeSurface(tileToBlit);
	SDL_FreeSurface(cursor);
	TTF_CloseFont(font);
	TTF_Quit();
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
	Lib�re la m�moire utilis�e par une map
*/
void freeMap(Map map)
{
	free(map.ground.ground);
}

/**
	Charge un terrain de jeu � partir d'un nom de fichier
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