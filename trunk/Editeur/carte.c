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
#include "../constants.h"
#include "librairie.h"

void editer(SDL_Surface *ecran, Info info, int bLoadMap)
{
    //DECLARATION-------------------------------------------
    Map map;
    SDL_Event event;
    SDL_Surface *tiles[28];
    SDL_Surface *tileToBlit;
    //Decors :
    //WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
    //MOUNTAIN1, MOUNTAIN2, MINE, RUINS,
    //Entites :
    //DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
    //FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS
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

    SDL_Surface *fond, *cache;
    int ok, continuer=1, i, j, choix=0, decalX=0, decalY=0, refresh=1, changChoix=1, taille=1, save=0;
    int mouse_x = 20, mouse_y = 20;
    int refreshTime = 0;
    SDL_Rect p_tile, p_info_t, p_ex, p_info_t2, p_info_t3, p_info_p;
    char *nom[28];
    char staille[] = "Taille:1";
    //------------------------------------------------------

    if (bLoadMap) {
		map = loadMap(info.nom);
		info.hauteur = map.ground.height;
		info.largeur = map.ground.width;
	}
	else {
		map = getClearMap(info.largeur, info.hauteur, info.nom);
	}

	t_water=IMG_Load("../images/tiles/eau.png");
    t_gwll=IMG_Load("../images/tiles/eaubg.png");
    t_gwlr=IMG_Load("../images/tiles/eaubd.png");
    t_gwhl=IMG_Load("../images/tiles/eauhg.png");
    t_gwhr=IMG_Load("../images/tiles/eauhd.png");
    t_grass=IMG_Load("../images/tiles/herbe.png");
    t_forest1=IMG_Load("../images/tiles/arbre.png");
    t_forest2=IMG_Load("../images/tiles/2arbres.png");
    t_forest3a=IMG_Load("../images/tiles/3aarbres.png");
    t_forest3b=IMG_Load("../images/tiles/3barbres.png");
    t_mount1=IMG_Load("../images/tiles/monbg.png");
    t_mount2=IMG_Load("../images/tiles/monhg.png");
    t_mount3=IMG_Load("../images/tiles/monbd.png");
    t_mount4=IMG_Load("../images/tiles/monhd.png");
    t_mine = IMG_Load("../images/tiles/pierres.png");
    t_ruins=IMG_Load("../images/tiles/ruines.png");
    t_dino=IMG_Load("../images/tiles/dino.png");
    t_house=IMG_Load("../images/tiles/habitation.png");
    t_sawmill=IMG_Load("../images/tiles/scierie.png");
    t_stower=IMG_Load("../images/tiles/tour.png");
    t_btower=IMG_Load("../images/tiles/gtour.png");
    t_minecamp=IMG_Load("../images/tiles/mine.png");
    t_well=IMG_Load("../images/tiles/puit.png");
    t_field=IMG_Load("../images/tiles/champ.png");
    t_sheep=IMG_Load("../images/tiles/champm.png");
    t_guardians=IMG_Load("../images/tiles/regiment.png");
    t_fire=IMG_Load("../images/tiles/feu.png");
    t_humains=IMG_Load("../images/tiles/humains.png");

    //Decors :
    //WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
    //MOUNTAIN1, MOUNTAIN2, MINE, RUINS,
    //Entites :
    //DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
    //FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS
    tiles[WATER] = t_water;
    tiles[GWLL] = t_gwll;
    tiles[GWLR] = t_gwlr;
    tiles[GWHL] = t_gwhl;
    tiles[GWHR] = t_gwhr;
    tiles[GRASS] = t_grass;
    tiles[FOREST1] = t_forest1;
    tiles[FOREST2] = t_forest2;
    tiles[FOREST3A] = t_forest3a;
    tiles[FOREST3B] = t_forest3b;
    tiles[MOUNTAIN1] = t_mount1;
    tiles[MOUNTAIN2] = t_mount2;
    tiles[MOUNTAIN3] = t_mount3;
    tiles[MOUNTAIN4] = t_mount4;
    tiles[MINE] = t_mine;
    tiles[RUINS] = t_ruins;
    tiles[DINO] = t_dino;
    tiles[HOUSE] = t_house;
    tiles[SAWMILL] = t_sawmill;
    tiles[SMALLTOWER] = t_stower;
    tiles[BIGTOWER] = t_btower;
    tiles[MINECAMP] = t_minecamp;
    tiles[WELL] = t_well;
    tiles[FIELD] = t_field;
    tiles[SHEEP] = t_sheep;
    tiles[GUARDIANS] = t_guardians;
    tiles[FIRE] = t_fire;
    tiles[HUMAINS] = t_humains;

    //Decors :
    //WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
    //MOUNTAIN1, MOUNTAIN2, MINE, RUINS,
    //Entites :
    //DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
    //FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS
	nom[WATER] = "eau";
    nom[GWLL] = "bord";
    nom[GWLR] = "bord";
    nom[GWHL] = "bord";
    nom[GWHR] = "bord";
    nom[GRASS] = "herbe";
    nom[FOREST1] = "foret1";
    nom[FOREST2] = "foret2";
    nom[FOREST3A] = "foret3";
    nom[FOREST3B] = "foret3";
    nom[MOUNTAIN1] = "montagne1";
    nom[MOUNTAIN2] = "montagne2";
    nom[MOUNTAIN3] = "montagne3";
    nom[MOUNTAIN4] = "montagne4";
    nom[MINE] = "pierres";
    nom[RUINS] = "ruines";
    nom[DINO] = "dino";
    nom[HOUSE] = "maison";
    nom[SAWMILL] = "scierie";
    nom[SMALLTOWER] = "tour";
    nom[BIGTOWER] = "donjon";
    nom[MINECAMP] = "mine";
    nom[WELL] = "puits";
    nom[FIELD] = "champ";
    nom[SHEEP] = "troupeau";
    nom[GUARDIANS] = "regiment";
    nom[FIRE] = "feu";
    nom[HUMAINS] = "humains";

    fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 90, 100, 32, 0, 0, 0 ,0);
    SDL_FillRect(fond, NULL, COLOR_BLACK(ecran));
    cache = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 30, 32, 0, 0, 0 ,0);
    SDL_FillRect(cache, NULL, COLOR_BLACK(ecran));

    tileToBlit = tiles[GRASS];

    p_info_t.x = 10;
    p_info_t.y = ecran->h-20;

    p_info_p.x = 0;
    p_info_p.y = ecran->h-30;

    p_info_t2.x = 10;
    p_info_t2.y = 70;

    p_info_t3.x = 10;
    p_info_t3.y = 95;

    p_ex.x = 10;
    p_ex.y = 20;

    decalX=ecran->w/2-(map.ground.width*TILE_WIDTH)/2;
    decalY=ecran->h/2;//(map.ground.height*TILE_WIDTH)/2;

    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

    while(continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;

				case SDL_MOUSEMOTION:
					mouse_x = event.motion.x;
					mouse_y = event.motion.y;
					break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;

                        case SDLK_s:
                            save = saveMap(map, info.nom);
                            changChoix = 1;
                            refresh = 1;
                            break;

                        case SDLK_1:
                            taille = 1;
                            changChoix = 1;
                            refresh = 1;
                            break;

                        case SDLK_2:
                            taille = 2;
                            changChoix = 1;
                            refresh = 1;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button)
					{
                    case SDL_BUTTON_LEFT:
                        ok = remplacer(event.motion.x-decalX, event.motion.y-decalY, choix, map);
                        if(ok==2)
                            refresh = 1;
                        if(taille>1){
                            ok = remplacer(event.motion.x-decalX-(TILE_WIDTH/1.2), event.motion.y-decalY, choix, map);
                            ok = remplacer(event.motion.x-decalX+(TILE_WIDTH/1.5), event.motion.y-decalY, choix, map);
                            ok = remplacer(event.motion.x-decalX, event.motion.y-decalY-(TILE_HEIGHT), choix, map);
                            ok = remplacer(event.motion.x-decalX-TILE_WIDTH/2, event.motion.y-decalY+(TILE_HEIGHT), choix, map);

							if(ok==2)
                                refresh = 1;
                        }
						break;

                    case SDL_BUTTON_RIGHT:
                        ok = saveMap(map, info.nom);
                        save = ok;
                        refresh = 1;
                        changChoix = 1;
						break;

                    case SDL_BUTTON_WHEELUP:
                        choix = (choix+1)%28;
                        changChoix = 1;
						refresh = 1;
						break;

                    case SDL_BUTTON_WHEELDOWN:
                        if(choix==0)
                            choix = 27;
                        else
                            choix = (choix-1);
                        changChoix = 1;
                        refresh = 1;
						break;
					}

                    break;

                default:
                    break;
            }
        }

        if(mouse_x < 5) {
            decalX += MOVE_OFFSET;
            decalX = min((map.ground.width*TILE_WIDTH)/2+ecran->w/2-(map.ground.width*TILE_WIDTH)/2, decalX+MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_x > (ecran->w)-5) {
            decalX = max(-(map.ground.width*TILE_WIDTH)/2+ecran->w/2-(map.ground.width*TILE_WIDTH)/2, decalX-MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_y > ecran->h-5) {
            decalY = max(-(map.ground.height*TILE_HEIGHT)/2+ecran->h/2-(map.ground.height*TILE_WIDTH)/2, decalY-MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_y < 5) {
			decalY = min((map.ground.height*TILE_HEIGHT)/2+ecran->h/2, decalY+MOVE_OFFSET);
            refresh = 1;
        }

        while(SDL_GetTicks()-refreshTime <= REFRESH_TIME_LIMIT){
            SDL_Delay(1);
        }

        if(refresh == 1 && (SDL_GetTicks()-refreshTime >= REFRESH_TIME_LIMIT))
        {
            SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

             // Mise à jour des tiles
            for (i=0 ; i<map.ground.height ; i++)
            {
                for (j=0 ; j<map.ground.width ; j++)
                {
                    // Calcul position tile
                    p_tile.x = j * (TILE_WIDTH - TILE_SPACE) + (map.ground.height-i)*TILE_SPACE + decalX;
                    p_tile.y = i * TILE_HEIGHT + decalY;

					tileToBlit = tiles[map.ground.ground[i*map.ground.width + j]];

					SDL_BlitSurface(tileToBlit, NULL, ecran, &p_tile);
                }

            }

             if (changChoix) {
				SDL_BlitSurface(fond, NULL, ecran, NULL);
				SDL_BlitSurface(tiles[choix], NULL, ecran, &p_ex);
				WRITETXT(ecran, nom[choix], info.berlinP, info.bleute, p_info_t2);
				sprintf(staille,"Taille:%.1d", taille);
				WRITETXT(ecran, staille, info.berlinP, info.bleute, p_info_t3);
				if (save == 1){
                    WRITETXT(ecran, "Map saved!", info.berlinP, info.bleute, p_info_t);
                    save = 0;
				}
                else if(save == -1){
                    WRITETXT(ecran, "Error while saving map!", info.berlinP, info.bleute, p_info_t);
                    save = 0;
                }
				changChoix = 0;
			}

			SDL_Flip(ecran);

            refresh = 0;
            refreshTime = SDL_GetTicks();
        }

		//SDL_Delay(REFRESH_DELAY_TIME);
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
    SDL_FreeSurface(t_water);
    SDL_FreeSurface(t_gwll);
    SDL_FreeSurface(t_gwlr);
    SDL_FreeSurface(t_gwhl);
    SDL_FreeSurface(t_gwhr);
    SDL_FreeSurface(t_grass);
    SDL_FreeSurface(t_forest1);
    SDL_FreeSurface(t_forest2);
    SDL_FreeSurface(t_forest3a);
    SDL_FreeSurface(t_forest3b);
    SDL_FreeSurface(t_mount1);
    SDL_FreeSurface(t_mount2);
    SDL_FreeSurface(t_mount3);
    SDL_FreeSurface(t_mount4);
    SDL_FreeSurface(t_mine);
    SDL_FreeSurface(t_ruins);
    SDL_FreeSurface(t_dino);
    SDL_FreeSurface(t_house);
    SDL_FreeSurface(t_sawmill);
    SDL_FreeSurface(t_stower);
    SDL_FreeSurface(t_btower);
    SDL_FreeSurface(t_minecamp);
    SDL_FreeSurface(t_well);
    SDL_FreeSurface(t_field);
    SDL_FreeSurface(t_sheep);
    SDL_FreeSurface(t_guardians);
    SDL_FreeSurface(t_fire);
    SDL_FreeSurface(t_humains);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(cache);
}


/**
    Trouve la case ciblée et modifie son contenu
*/
int remplacer(int posX, int posY, int choix, Map map)
{
    int change = 2, i=-1, j=-1;

    i = (posY + 5)/TILE_HEIGHT - 3;
    j = (posX - (map.ground.height-i)*TILE_SPACE)/(TILE_WIDTH - TILE_SPACE);

    if(i >= 0 && i < map.ground.height){
        if(j >= 0 && j < map.ground.width){
            map.ground.ground[i*map.ground.width + j] = choix;
        }
    }
    else{
        change = 0; //Echec
    }

    return change;
}


