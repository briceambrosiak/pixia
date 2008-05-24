/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	chargement.h : Header

	Date : 21/04/08
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

#ifndef DEF_CHARGEMENT
#define DEF_CHARGEMENT

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "map.h"

typedef struct S_base S_base;
struct S_base
{
    //Les Tiles
    //Decors :
    //WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
    //MOUNTAIN1, MOUNTAIN2, MOUNTAIN3, MOUNTAIN4, MINE, RUINS,
    //Entites :
    //DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
    //FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS

    SDL_Surface *tiles[28];
    SDL_Surface *tileToBlit;
    //décors :
    SDL_Surface *t_water;
    SDL_Surface *t_gwll;
    SDL_Surface *t_gwlr;
    SDL_Surface *t_gwhl;
    SDL_Surface *t_gwhr;
    SDL_Surface *t_grass;
    SDL_Surface *t_forest1;
    SDL_Surface *t_forest2;
    SDL_Surface *t_forest3a;
    SDL_Surface *t_forest3b;
    SDL_Surface *t_mount1;
    SDL_Surface *t_mount2;
    SDL_Surface *t_mount3;
    SDL_Surface *t_mount4;
    SDL_Surface *t_mine;
    SDL_Surface *t_ruins;
    //Entités :
    SDL_Surface *t_dino;
    SDL_Surface *t_house;
    SDL_Surface *t_sawmill;
    SDL_Surface *t_stower;
    SDL_Surface *t_btower;
    SDL_Surface *t_minecamp;
    SDL_Surface *t_well;
    SDL_Surface *t_field;
    SDL_Surface *t_sheep;
    SDL_Surface *t_guardians;
    SDL_Surface *t_fire;
    SDL_Surface *t_humains;

    char *nom[28];

    //La map
    Map map;

    //HUD
    TTF_Font *berlinP;
    TTF_Font *berlinPM;
    TTF_Font *berlinM;
    TTF_Font *berlinG;

    SDL_Surface *hud;
    SDL_Surface *fond;
    SDL_Surface *cache[9];

    SDL_Surface *ico_people;
    SDL_Surface *ico_wood;
    SDL_Surface *ico_food;
    SDL_Surface *ico_rock;
    SDL_Surface *ico_menu;
    SDL_Surface *ico_menuA;

    SDL_Surface *cadr_menu;
    SDL_Surface *cadr_quitter;

    SDL_Color bleute;
    SDL_Color black;

    //Emplacement des icones
    SDL_Rect p_people;
    SDL_Rect p_wood;
    SDL_Rect p_food;
    SDL_Rect p_rock;
    //Emplacement des textes associés
    SDL_Rect p_info_t;
    SDL_Rect p_info_t2;
    SDL_Rect p_info_t3;
    SDL_Rect p_people_t;
    SDL_Rect p_wood_t;
    SDL_Rect p_food_t;
    SDL_Rect p_rock_t;
    //Autres icones
    SDL_Rect p_menu;
    SDL_Rect p_time;
    SDL_Rect p_hud;
    SDL_Rect p_choix;
    SDL_Rect p_cache;

    //cadres
    SDL_Rect p_c_menu;
    SDL_Rect p_c_quitter;
    SDL_Rect p_fond;
};

typedef struct S_time S_time;
struct S_time
{
    SDL_Surface *ecran;
    int *p_refresh;
    int heures;
    int minutes;
    int secondes;
    TTF_Font *police;
    SDL_Color color;

    S_base *base;

    char total[20];
};

// ----------------------------------------------------------------------------

void startMap(SDL_Surface *ecran, int spec);

void freeBase(S_base base);

#endif


