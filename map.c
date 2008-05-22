/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	map.c : Fichier de la carte

	Date : 17/05/08
	Author : Gaétan Schmitt, Brice Ambrosiak

	Copyright 2008 Gaétan SCHMITT, Brice Ambrosiak

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

//Include du header
#include "map.h"
#include "constants.h"


/**
	Charge une map test (herbe uniquement)
*/
Map getMap(int difficulty)
{
    //DECLARATION---------------------
    int height, width;
	Map map;
	Ground ground;
	//------------------------------

    switch(difficulty){
        case 1:
            height = 20;
            width = 40;
            map.name = "Facile";
            break;
        case 2:
            height = 40;
            width = 80;
            map.name = "Moyen";
            break;
        case 3:
            height = 80;
            width = 160;
            map.name = "Difficil";
            break;
        default:
            fprintf(stderr, "Erreur de choix de taille de map [map.c : getMap]");
            exit(EXIT_FAILURE);
            break;
    }

	ground.height = height;
	ground.width = width;
	ground.ground = malloc(ground.height * ground.width * sizeof(GroundTile));

	map.entities = NULL;
	map.ground = ground;

	return map;
}

/**
	Renvoie une map composée uniquement d'herbe
*/
Map getClearMap(int width, int height, char* name)
{
    //DECLARATION---------------------
    int i;
	Map map;
	Ground ground;
	//------------------------------

    map.name = name;

	ground.height = height;
	ground.width = width;
	ground.ground = malloc(ground.height * ground.width * sizeof(int));

    map.entities = NULL;
	map.ground = ground;

    for (i=0 ; i<map.ground.width*map.ground.height ; i++){
        map.ground.ground[i] = GRASS;
	}

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
	int i = 0;

	file = fopen(filename, "r");

	// Si impossible d'ouvrir le fichier
	if (file == NULL)
        fprintf(stderr, "Can't load map @ map.c");

    // Lecture infos terrain
    //fread(&map.ground.width, sizeof(int), 1, file);
    //fread(&map.ground.height, sizeof(int), 1, file);
    //fscanf(fichier, "%ld %ld %ld", &score[0], &score[1], &score[2]);
    fscanf(file, "<%d>", &map.ground.width);
    fscanf(file, "<%d>", &map.ground.height);


    //map.ground.ground = malloc(map.ground.width * map.ground.height * sizeof(int));
    map.ground.ground = malloc(map.ground.width * map.ground.height * sizeof(int));

    // Lecture tiles terrain
	for (i=0 ; i<map.ground.width*map.ground.height ; i++){
        //fread(&map.ground.ground[i], sizeof(int), 1, file);
        fscanf(file, "[%d]\n", (int*)&map.ground.ground[i]);
	}

	fclose(file);

	return map;
}

/**
	Sauvegarde la carte passée en paramètre dans le fichier spécifié
*/
int saveMap(Map map, char* filename)
{
	FILE* file;
	int i = 0;

	file = fopen(filename, "w+");

	// Si impossible d'écrire le fichier
	if (file == NULL) return -1;

	// Sauvegarde terrain

    // Ecriture infos terrain
    //fwrite(&map.ground.width, sizeof(int), 1, file);
    //fwrite(&map.ground.height, sizeof(int), 1, file);
    fprintf(file, "<%d>", map.ground.width);
    fprintf(file, "<%d>", map.ground.height);

	// Ecriture tiles terrain
	for (i=0 ; i<map.ground.width*map.ground.height ; i++){
        //fwrite(&map.ground.ground[i], sizeof(int), 1, file);
        fprintf(file, "[%d]\n", map.ground.ground[i]);
	}

	fclose(file);

	return 1;
}
