/**
    Projet Jeu Pixia pour ESIAL CSH
    -------------------------------

    Editeur de carte

    Créé le 17 mai 2008

    Par Gaétan SCHMITT et Brice AMBROSIAK

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

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "carte.h"
#include "biblio.h"
#include "constants.h"
#include "librairie.h"

void editer(SDL_Surface *ecran, Info info){
    //DECLARATION-------------------------------------------
    Map map;
    SDL_Event event;
    SDL_Surface *tiles[9];
    SDL_Surface *tileToBlit;
    SDL_Surface *t_grass1;
    SDL_Surface *t_water1;
    SDL_Surface *t_forest1;
    SDL_Surface *t_mount1;
    SDL_Surface *t_field1;
    SDL_Surface *t_house1;
    SDL_Surface *t_stower1;
    SDL_Surface *t_btower1;
    SDL_Surface *t_sawmill1;
    SDL_Surface *fond, *cache;
    int ok, continuer=1, i, j, choix=0;
    SDL_Rect p_tile, p_info_t, p_ex, p_info_t2, p_info_p;
    char *nom[9];
    char bat0[] = "herbe";
    char bat1[] = "eau";
    char bat2[] = "foret";
    char bat3[] = "montagne";
    char bat4[] = "champ";
    char bat5[] = "maison";
    char bat6[] = "tourelle";
    char bat7[] = "tour";
    char bat8[] = "scierie";
    //------------------------------------------------------

    map = getMap(info.largeur, info.hauteur, info.nom);

    t_grass1 = IMG_Load("../images/tiles/herbe.png");
    t_water1 = IMG_Load("../images/tiles/eau.png");
    t_forest1 = IMG_Load("../images/tiles/arbre.png");
    t_mount1 = IMG_Load("../images/tiles/mine.png");  //Mauvais tile
    t_field1 = IMG_Load("../images/tiles/champ.png");
    t_house1 = IMG_Load("../images/tiles/habitation.png");
    t_stower1 = IMG_Load("../images/tiles/tour.png");
    t_btower1 = IMG_Load("../images/tiles/gtour.png");
    t_sawmill1 = IMG_Load("../images/tiles/scierie.png");

    tiles[0] = t_grass1;
    tiles[1] = t_water1;
    tiles[2] = t_forest1;
    tiles[3] = t_mount1;
    tiles[4] = t_field1;
    tiles[5] = t_house1;
    tiles[6] = t_stower1;
    tiles[7] = t_btower1;
    tiles[8] = t_sawmill1;

    nom[0] = bat0;
    nom[1] = bat1;
    nom[2] = bat2;
    nom[3] = bat3;
    nom[4] = bat4;
    nom[5] = bat5;
    nom[6] = bat6;
    nom[7] = bat7;
    nom[8] = bat8;

    fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 90, 100, 32, 0, 0, 0 ,0);
    SDL_FillRect(fond, NULL, COLOR_BLACK(ecran));
    cache = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 30, 32, 0, 0, 0 ,0);
    SDL_FillRect(cache, NULL, COLOR_BLACK(ecran));

    tileToBlit = t_grass1;

    p_info_t.x = 10;
    p_info_t.y = ecran->h-20;

    p_info_p.x = 0;
    p_info_p.y = ecran->h-30;

    p_info_t2.x = 10;
    p_info_t2.y = 70;

    p_ex.x = 10;
    p_ex.y = 20;

    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

    SDL_BlitSurface(fond, NULL, ecran, NULL);
    SDL_BlitSurface(tiles[choix], NULL, ecran, &p_ex);
    WRITETXT(ecran, nom[choix], info.berlinP, info.bleute, p_info_t2);

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
                //WATER, GRASS, FOREST, MOUNTAIN, FIELD, HOUSE, SMALLTOWER, BIGTOWER, SAWMILL
                case GRASS:
                    tileToBlit =t_grass1;
                    break;
                case WATER:
                    tileToBlit = t_water1;
                    break;
                case FOREST:
                    tileToBlit = t_forest1;
                    break;
                case MOUNTAIN:
                    tileToBlit = t_mount1;
                    break;
                case FIELD:
                    tileToBlit = t_field1;
                    break;
                case HOUSE:
                    tileToBlit = t_house1;
                    break;
                case SMALLTOWER:
                    tileToBlit = t_stower1;
                    break;
                case BIGTOWER:
                    tileToBlit = t_btower1;
                    break;
                case SAWMILL:
                    tileToBlit = t_sawmill1;
                    break;
                default:
                    tileToBlit = t_grass1;
                    break;
            }

            SDL_BlitSurface(tileToBlit, NULL, ecran, &p_tile);
        }
    }

    SDL_Flip(ecran);

    while(continuer){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                        case SDLK_s:
                            ok = saveMap(map, info.nom);
                            if (ok == -1)
                                WRITETXT(ecran, "Error while saving map!", info.berlinP, info.bleute, p_info_t);
                            else
                                WRITETXT(ecran, "Map saved!", info.berlinP, info.bleute, p_info_t);

                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){

                    }
                    if (event.button.button == SDL_BUTTON_RIGHT){
                         ok = saveMap(map, info.nom);
                            if (ok == -1)
                                WRITETXT(ecran, "Error while saving map!", info.berlinP, info.bleute, p_info_t);
                            else
                                WRITETXT(ecran, "Map saved!", info.berlinP, info.bleute, p_info_t);

                    }
                    break;
                default:
                    break;
            }
            if (event.button.button == SDL_BUTTON_WHEELUP){
                choix = (choix+1)%9;
                SDL_BlitSurface(fond, NULL, ecran, NULL);
                SDL_BlitSurface(cache, NULL, ecran, &p_info_p);
                SDL_BlitSurface(tiles[choix], NULL, ecran, &p_ex);
                WRITETXT(ecran, nom[choix], info.berlinP, info.bleute, p_info_t2);
            }
            if (event.button.button == SDL_BUTTON_WHEELDOWN){
                if(choix==0)
                    choix = 8;
                else
                    choix = (choix-1);
                SDL_BlitSurface(fond, NULL, ecran, NULL);
                SDL_BlitSurface(cache, NULL, ecran, &p_info_p);
                SDL_BlitSurface(tiles[choix], NULL, ecran, &p_ex);
                WRITETXT(ecran, nom[choix], info.berlinP, info.bleute, p_info_t2);
            }

        }

        SDL_Flip(ecran);

    }

    //Dernière sauvegarde
    ok = saveMap(map, info.nom);
    if(ok!=1){
        fprintf(stderr, "Erreur de sauvegarde");
        exit(EXIT_FAILURE);
    }

    //Libération de la mémoire
    freeMap(map);

    SDL_FreeSurface(tileToBlit);
    SDL_FreeSurface(t_grass1);
    SDL_FreeSurface(t_water1);
    SDL_FreeSurface(t_forest1);
    SDL_FreeSurface(t_mount1);
    SDL_FreeSurface(t_field1);
    SDL_FreeSurface(t_house1);
    SDL_FreeSurface(t_stower1);
    SDL_FreeSurface(t_btower1);
    SDL_FreeSurface(t_sawmill1);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(cache);
}

