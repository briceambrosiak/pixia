/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	partie.c : Corps du jeu

	Date : 21/04/08
	Author : Ga�tan Schmitt, Brice Ambrosiak

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

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <FMOD/fmod.h>

#include "partie.h"
#include "constants.h"
#include "chargement.h"
#include "map.h"
#include "engine.h"

void startGame(SDL_Surface *ecran, S_base *base, S_time *heure){
    //-------DECLARATIONS------------------------------------
    char continuer = 1;
    SDL_Event event;
    SDL_Rect p_tile;
    SDL_TimerID time;
    int i, j, select = S_NOTHING, ok, decalX=0, decalY=0, changChoix=1, save=0, menu=0;
    int mouse_x = 20, mouse_y = 20, choix=0, modifHUD = 1;
    int refresh = 1, refreshTime=0;

    //-------------------------------------------------------
    SDL_ShowCursor(SDL_ENABLE);
    heure->p_refresh = &refresh;

    decalX=ecran->w/2-(base->map.ground.width*TILE_WIDTH)/2+75;
    decalY=ecran->h/2-(base->map.ground.height*TILE_HEIGHT)/2;

    //Premier affichage
    SDL_BlitSurface(base->fond, NULL, ecran, &base->p_fond);

    time = SDL_AddTimer(1000, horloge, heure);

    WRITETXT(base->hud, "0:00:00", base->berlinM, base->bleute, base->p_time);

    SDL_Flip(ecran);

    while(continuer){
        while(SDL_PollEvent(&event)){
            switch(event.type){
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
                            select = S_MENU;
                            menu = 1;
                            changChoix = 1;
                            refresh = 1;

                            SDL_BlitSurface(base->cadr_menu, NULL, ecran, &base->p_c_menu);
                            break;
                        case SDLK_a:
                            SDL_BlitSurface(base->ico_menuA, NULL, ecran, &base->p_menu);
                            SDL_BlitSurface(base->cadr_quitter, NULL, ecran, &base->p_c_quitter);
                            SDL_Flip(ecran);
                            ok = 0;
                            while(ok==0){
                                while(SDL_PollEvent(&event)){
                                    if(event.type==SDL_KEYDOWN){
                                        if(event.key.keysym.sym==SDLK_o){
                                            continuer = 0;
                                            ok = 1;
                                        }
                                        else if(event.key.keysym.sym==SDLK_n){
                                            ok = 1;
                                        }
                                    }
                                }
                            }
                            break;
                        case SDLK_s:
                            save = saveMap(base->map, "Sauvegarde.map");
                            changChoix = 1;
                            refresh = 1;
                        break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT:
                            if(select != S_NOTHING){
                                if(select == S_MENU){
                                    menu = 1;
                                    changChoix = 1;
                                    refresh = 1;
                                }
                            }
                            break;

                        case SDL_BUTTON_RIGHT:
                            continuer = 0;
                            break;

                        case SDL_BUTTON_WHEELUP:
                            choix = (choix+1)%9;
                            modifHUD = 1;
                            refresh = 1;
                            break;

                        case SDL_BUTTON_WHEELDOWN:
                            if(choix==0)
                                choix = 8;
                            else
                                choix = (choix-1);
                            modifHUD = 1;
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
            decalX = min((base->map.ground.width*TILE_WIDTH)/2+ecran->w/2-(base->map.ground.width*TILE_WIDTH)/2, decalX+MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_x > (ecran->w)-5) {
            decalX = max(-(base->map.ground.width*TILE_WIDTH)/2+ecran->w/2-(base->map.ground.width*TILE_WIDTH)/2, decalX-MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_y > ecran->h-5) {
            decalY = max(-(base->map.ground.height*TILE_HEIGHT)/2+ecran->h/2-(base->map.ground.height*TILE_WIDTH)/2, decalY-MOVE_OFFSET);
            refresh = 1;
        }
        else if(mouse_y < 5) {
			decalY = min((base->map.ground.height*TILE_HEIGHT)/2+ecran->h/2, decalY+MOVE_OFFSET);
            refresh = 1;
        }

        if(refresh == 1 && (SDL_GetTicks()-refreshTime >= REFRESH_TIME_LIMIT)){
            SDL_BlitSurface(base->fond, NULL, ecran, &base->p_fond);
             // Mise � jour des tiles
            for (i=0 ; i<base->map.ground.height ; i++)
            {
                for (j=0 ; j<base->map.ground.width ; j++)
                {
                    // Calcul position tile
                    p_tile.x = j * (TILE_WIDTH - TILE_SPACE) + (base->map.ground.height-i)*TILE_SPACE + decalX;
                    p_tile.y = i * TILE_HEIGHT + decalY;

                    base->tileToBlit = base->tiles[base->map.ground.ground[i*base->map.ground.height + j]];
                        //Decors :
                        //WATER, GWLL, GWLR, GWHL, GWHR, GRASS, FOREST1, FOREST2, FOREST3A, FOREST3B,
                        //MOUNTAIN1, MOUNTAIN2, MOUNTAIN3, MOUNTAIN4, MINE, RUINS,
                        //Entites :
                        //DINO, HOUSE, SAWMILL, SMALLTOWER, BIGTOWER, MINECAMP, WELL,
                        //FIELD, SHEEP, GUARDIANS, FIRE, HUMAINS

                    SDL_BlitSurface(base->tileToBlit, NULL, ecran, &p_tile);
                }
            }

            //HUD
            //modif
            if(modifHUD){
                SDL_BlitSurface(base->cache[choix], NULL, base->hud, &base->p_cache);
				SDL_BlitSurface(base->tiles[choix+HOUSE], NULL, base->hud, &base->p_choix);
				WRITETXT(base->hud, base->nom[choix+HOUSE], base->berlinM, base->bleute, base->p_info_t2);
                modifHUD = 0;
            }

            SDL_BlitSurface(base->hud, NULL, ecran, &(base->p_hud));

            WRITETXT(ecran, "155+", base->berlinM, base->bleute, base->p_food_t);
            WRITETXT(ecran, "155=", base->berlinM, base->bleute, base->p_wood_t);
            WRITETXT(ecran, "155-", base->berlinM, base->bleute, base->p_rock_t);
            WRITETXT(ecran, "546+++", base->berlinM, base->bleute, base->p_people_t);

            if(changChoix){
                if(menu){
                    SDL_BlitSurface(base->ico_menuA, NULL, ecran, &base->p_menu);
                    SDL_BlitSurface(base->cadr_menu, NULL, ecran, &base->p_c_menu);
                }
                if (save == 1){
                    WRITETXT(ecran, "Map saved!", base->berlinP, base->bleute, base->p_info_t);
                    save = 0;
                }
                else if(save ==-1){
                    WRITETXT(ecran, "Error while saving map!", base->berlinP, base->bleute, base->p_info_t);
                    save = 0;
                }

            }

            if(event.motion.x > base->p_menu.x+1 &&
                event.motion.x < base->p_menu.x+42 &&
                event.motion.y > base->p_menu.y &&
                event.motion.y < base->p_menu.y+54){
                SDL_BlitSurface(base->ico_menuA, NULL, ecran, &base->p_menu);
                select = S_MENU;
            }
            else{
                if(select == S_MENU){
                    select = S_NOTHING;
                    SDL_BlitSurface(base->ico_menu, NULL, ecran, &base->p_menu);
                }
            }

            SDL_Flip(ecran);

            refresh = 0;
            refreshTime = SDL_GetTicks();
        }
        SDL_Delay(REFRESH_DELAY_TIME);
    }
    SDL_RemoveTimer(time);

    SDL_ShowCursor(SDL_DISABLE);
}

Uint32 horloge(Uint32 intervalle, void *param){
    S_time *heure = param;

    if(heure->secondes == 59){
        heure->secondes = 0;
        if(heure->minutes == 59){
            heure->minutes = 0;
            heure->heures++;
        }
        else{
            heure->minutes++;
        }
    }
    else{
        heure->secondes++;
    }

    sprintf(heure->total, "%d:%.2d:%.2d  ", heure->heures, heure->minutes, heure->secondes);

    WRITETXT(heure->base->hud, heure->total, heure->police, heure->color, heure->base->p_time);

    *(heure->p_refresh) = 1;

    return intervalle;
}





