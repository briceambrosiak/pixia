/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	partie.c : Corps du jeu

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

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <FMOD/fmod.h>

#include "partie.h"
#include "constants.h"
#include "chargement.h"

void startGame(SDL_Surface *ecran, S_base *base, S_time *heure){
    //-------DECLARATIONS------------------------------------
    char continuer = 1;
    SDL_Event event;
    SDL_Surface *tileToBlit;
    SDL_Rect p_tile;
    SDL_TimerID time;
    int /*tempsActuel = 0, tempsPrecedent = 0,*/ i, j, select = S_NOTHING, ok;

    //-------------------------------------------------------
    SDL_ShowCursor(SDL_ENABLE);

    //Premier affichage
    SDL_FillRect(ecran, NULL, COLOR_BLEUTE(ecran));

    time = SDL_AddTimer(1000, horloge, heure);

    // Mise à jour des tiles
    for (i=0 ; i<base->map.ground.height ; i++)
    {
        for (j=0 ; j<base->map.ground.width ; j++)
        {
            // Calcul position tile
            p_tile.x = j * TILE_WIDTH - TILE_SPACE*j + (base->map.ground.height-i)*TILE_SPACE;
            p_tile.y = i * TILE_HEIGHT;

            switch (base->map.ground.ground[i*base->map.ground.height + j])
            {
                //WATER, GRASS, FOREST, MOUNTAIN, FIELD, HOUSE, SMALLTOWER, BIGTOWER, SAWMILL
                case GRASS:
                    tileToBlit = base->t_grass1;
                    break;

                case WATER:
                    tileToBlit = base->t_water1;
                    break;
                case FOREST:
                    tileToBlit = base->t_forest1;
                    break;
                case MOUNTAIN:
                    tileToBlit = base->t_mount1;
                    break;
                case FIELD:
                    tileToBlit = base->t_field1;
                    break;
                case HOUSE:
                    tileToBlit = base->t_house1;
                    break;
                case SMALLTOWER:
                    tileToBlit = base->t_stower1;
                    break;
                case BIGTOWER:
                    tileToBlit = base->t_btower1;
                    break;
                case SAWMILL:
                    tileToBlit = base->t_sawmill1;
                    break;
                default:
                    tileToBlit = base->t_grass1;
                    break;
            }

            SDL_BlitSurface(tileToBlit, NULL, ecran, &p_tile);
        }
    }

    SDL_BlitSurface(base->hud, NULL, ecran, &(base->p_hud));

    WRITETXT(ecran, "155+", base->berlinM, base->bleute, base->p_food_t);
    WRITETXT(ecran, "155=", base->berlinM, base->bleute, base->p_wood_t);
    WRITETXT(ecran, "155-", base->berlinM, base->bleute, base->p_rock_t);
    WRITETXT(ecran, "546+++", base->berlinM, base->bleute, base->p_people_t);
    WRITETXT(ecran, "0:00:00", base->berlinM, base->bleute, base->p_time);

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
                            select = S_MENU;
                            SDL_BlitSurface(base->ico_menuA, NULL, ecran, &base->p_menu);
                            SDL_BlitSurface(base->cadr_menu, NULL, ecran, &base->p_c_menu);
                            break;
                        case SDLK_a:
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
                            ok = saveMap(base->map, "Sauvegarde.map");
                            if (ok == -1)
                                WRITETXT(ecran, "Error while saving map!", base->berlinP, base->bleute, base->p_info_t);
                            else
                                WRITETXT(ecran, "Map saved!", base->berlinP, base->bleute, base->p_info_t);

                        break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(select != S_NOTHING){
                            if(select == S_MENU){
                                SDL_BlitSurface(base->cadr_menu, NULL, ecran, &base->p_c_menu);
                            }
                        }
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT)
                        continuer = 0;
                    break;
                default:
                    break;
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

    sprintf(heure->total, "%d:%.2d:%.2d", heure->heures, heure->minutes, heure->secondes);

    SDL_BlitSurface(heure->fond, NULL, heure->ecran, &heure->pos);
    WRITETXT(heure->ecran, heure->total, heure->police, heure->color, heure->pos);

    ///TODO : Flip ecran superflu
    SDL_Flip(heure->ecran);

    return intervalle;
}




