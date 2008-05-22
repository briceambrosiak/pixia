/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	chargement.c : Charge tous les composants du jeu

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

#include <FMOD/fmod.h>

#include "constants.h"
#include "chargement.h"
#include "partie.h"
#include "map.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int rmask = 0xff000000;
    int gmask = 0x00ff0000;
    int bmask = 0x0000ff00;
    int amask = 0x000000ff;
#else
    int rmask = 0x000000ff;
    int gmask = 0x0000ff00;
    int bmask = 0x00ff0000;
    int amask = 0xff000000;
#endif

void startMap(SDL_Surface *ecran, int spec)
{
    //-----DECLARATIONS---------------------------------------
    S_base base;        //Contient l'ensemble des éléments au jeu
    S_time heure;      //Gère l'horloge du jeu
    SDL_Surface /* *fondCharg, *pourcentage,*/ *texte, *pixia, *bgb, *bghg, *bghd, *bgg;
    SDL_Rect p_texte, p_pixia, p_hg, p_hd, p_b, p_g, p_d;
    TTF_Font *police;
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Event event;
    char continuer = 1;
    int inter = 0;

    //--------------------------------------------------------

    ///TODO : Choix de map

    //Affichage de l'ecran de chargement
    police = TTF_OpenFont("calibri.ttf", 24);
    p_texte.x = 50;
    p_texte.y = 750;

    //Construction de l'écran

    //Chargement des tiles
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    texte = TTF_RenderText_Solid(police, "Chargement en cours :   tiles : éléments de décor...", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    base.t_grass1 = IMG_Load("images/tiles/herbe.png");
    base.t_water1 = IMG_Load("images/tiles/eau.png");
    base.t_forest1 = IMG_Load("images/tiles/arbre.png");
    base.t_mount1 = IMG_Load("images/tiles/mine.png");  //Mauvais tile
    base.t_field1 = IMG_Load("images/tiles/champ.png");
    base.t_house1 = IMG_Load("images/tiles/habitation.png");
    base.t_stower1 = IMG_Load("images/tiles/tour.png");
    base.t_btower1 = IMG_Load("images/tiles/gtour.png");
    base.t_sawmill1 = IMG_Load("images/tiles/scierie.png");

    //Chargement de la map
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    texte = TTF_RenderText_Solid(police, "Chargement en cours :   map : lecture du fichier et mise en cache...", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    switch(spec){
        case 1:
            base.map = loadMap("map1.map");
            break;
        case 2:
            base.map = loadMap("map2.map");
            break;
        case 3:
            base.map = loadMap("map3.map");
            break;
        default:
            fprintf(stderr, "Erreur choix de difficulté [chargement.c]");
            exit(EXIT_FAILURE);
            break;
    }

    //Chargement des entités
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    texte = TTF_RenderText_Solid(police, "Chargement en cours :   tilds : entités de jeu...", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    //Chargement de l'HUD
    SDL_FillRect(ecran, NULL, COLOR_BLEUTE(ecran));
    texte = TTF_RenderText_Solid(police, "Chargement en cours :   HUD : cadre de jeu...", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    base.berlinP = TTF_OpenFont("berlin.ttf", 11);
    base.berlinM = TTF_OpenFont("berlin.ttf", 24);
    base.berlinG = TTF_OpenFont("berlin.ttf", 45);

    base.ico_food = IMG_Load("images/tiles/food.jpg");
    base.ico_wood = IMG_Load("images/tiles/wood.jpg");
    base.ico_rock = IMG_Load("images/tiles/rock.jpg");
    base.ico_people = IMG_Load("images/tiles/people.jpg");
    base.ico_menu = IMG_Load("images/tiles/menu.jpg");
    base.ico_menuA = IMG_Load("images/tiles/menuA.jpg");

    base.cadr_menu = IMG_Load("images/backgrounds/menu.jpg");
    base.cadr_quitter = IMG_Load("images/backgrounds/quitter.jpg");

    bgb = IMG_Load("images/backgrounds/bgb.jpg");
    bghg = IMG_Load("images/backgrounds/bghg.png");
    bghd = IMG_Load("images/backgrounds/bghd.png");
    bgg = IMG_Load("images/backgrounds/bgg.jpg");

    switch(ecran->w){
        case 1280:
            inter = 120;
            base.p_wood.x = 794;
            base.p_wood.y = 755;
            base.p_food.x = base.p_wood.x+inter+3;
            base.p_food.y = base.p_wood.y;
            base.p_rock.x = base.p_food.x+inter;
            base.p_rock.y = base.p_wood.y;
            base.p_people.x = 25;
            base.p_people.y = 740;
            base.p_menu.x = base.p_people.x;
            base.p_menu.y = 20;
            base.p_time.x = 1163;
            base.p_time.y = 20;
            p_pixia.x = 1190;
            p_pixia.y = 750;
            base.p_c_menu.x = 0;
            base.p_c_menu.y = base.p_menu.y+65;
            p_hg.x = 59;
            p_hg.y = 0;
            p_hd.x = 1280 - 60 - 98;
            p_hd.y = 0;
            p_b.x = 0;
            p_b.y = 800 - 62;
            p_g.x = 0;
            p_g.y = 0;
            p_d.x = 1280 - 60;
            p_d.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = 800 - 20;
            break;
        case 1024:
            inter = 100;
            base.p_wood.x = 530;
            base.p_wood.y = 727;
            base.p_food.x = base.p_wood.x+inter+3;
            base.p_food.y = base.p_wood.y;
            base.p_rock.x = base.p_food.x+inter;
            base.p_rock.y = base.p_wood.y;
            base.p_people.x = 20;
            base.p_people.y = 720;
            base.p_menu.x = base.p_people.x;
            base.p_menu.y = 11;
            base.p_time.x = 903;
            base.p_time.y = 11;
            p_pixia.x = 2;
            p_pixia.y = 25;
            base.p_c_menu.x = 0;
            base.p_c_menu.y = base.p_menu.y+65;
            p_hg.x = 59;
            p_hg.y = 0;
            p_hd.x = 768 - 60 - 98;
            p_hd.y = 0;
            p_b.x = 0;
            p_b.y = 768 - 62;
            p_g.x = 0;
            p_g.y = 0;
            p_d.x = 1024 - 60;
            p_d.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = 768 - 20;
            break;
        case 800:
            inter = 80;
            base.p_wood.x = 465;
            base.p_wood.y = 565;
            base.p_food.x = base.p_wood.x+inter+3;
            base.p_food.y = base.p_wood.y;
            base.p_rock.x = base.p_food.x+inter;
            base.p_rock.y = base.p_wood.y;
            base.p_people.x = 15;
            base.p_people.y = 557;
            base.p_menu.x = base.p_people.x;
            base.p_menu.y = 4;
            base.p_time.x = 704;
            base.p_time.y = 7;
            p_pixia.x = 2;
            p_pixia.y = 25;
            base.p_c_menu.x = 0;
            base.p_c_menu.y = base.p_menu.y+65;
            p_hg.x = 59;
            p_hg.y = 0;
            p_hd.x = 600 - 60 - 98;
            p_hd.y = 0;
            p_b.x = 0;
            p_b.y = 600 - 62;
            p_g.x = 0;
            p_g.y = 0;
            p_d.x = 800 - 60;
            p_d.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = 600 - 20;
            break;
        default:
            fprintf(stderr, "Erreur de résolution : chargement.c");
            exit(EXIT_FAILURE);
            break;
    }

    base.p_c_quitter.x = ((ecran->w)/2) - ((base.cadr_quitter->w)/2);
    base.p_c_quitter.y = ((ecran->h)/2) - ((base.cadr_quitter->h)/2);

    base.bleute.r = 190;
    base.bleute.g = 190;
    base.bleute.b = 250;

    base.p_food_t.x = base.p_food.x+38;
    base.p_food_t.y = base.p_food.y;
    base.p_wood_t.x = base.p_wood.x+40;
    base.p_wood_t.y = base.p_wood.y;
    base.p_rock_t.x = base.p_rock.x+36;
    base.p_rock_t.y = base.p_rock.y;
    base.p_people_t.x = base.p_people.x+44;
    base.p_people_t.y = base.p_people.y+10;

    base.p_hud.x = 0;
    base.p_hud.y = 0;

    base.hud = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w, ecran->h, 32,
    rmask, gmask, bmask, amask);

    SDL_BlitSurface(bgb, NULL, base.hud, &p_b);
    SDL_BlitSurface(bghg, NULL, base.hud, &p_hg);
    SDL_BlitSurface(bghd, NULL, base.hud, &p_hd);
    SDL_BlitSurface(bgg, NULL, base.hud, &p_g);
    SDL_BlitSurface(bgg, NULL, base.hud, &p_d);
    SDL_BlitSurface(base.ico_menu, NULL, base.hud, &base.p_menu);
    SDL_BlitSurface(base.ico_people, NULL, base.hud, &base.p_people);
    SDL_BlitSurface(base.ico_wood, NULL, base.hud, &base.p_wood);
    SDL_BlitSurface(base.ico_food, NULL, base.hud, &base.p_food);
    SDL_BlitSurface(base.ico_rock, NULL, base.hud, &base.p_rock);

    SDL_Color black = {0, 0, 0};
    pixia = TTF_RenderText_Shaded(base.berlinM, "Pixia", base.bleute, black);
    SDL_BlitSurface(pixia, NULL, base.hud, &p_pixia);

    //Mise en place de l'horloge
    heure.heures = 0;
    heure.minutes = 0;
    heure.secondes = 0;
    heure.ecran = ecran;
    heure.police = base.berlinM;
    heure.color = base.bleute;
    heure.pos = base.p_time;
    heure.base = &base;

    heure.fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 110, 28, 32, 0, 0, 0, 0);
    SDL_FillRect(heure.fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    //Pause avant lancement
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    p_texte.x = 325;
    texte = TTF_RenderText_Solid(police, "Appuyer sur n'importe quelle touche pour démarrer la partie.", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    while(continuer){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYUP:
                    continuer = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    continuer = 0;
                    break;
                default:
                    break;
            }
        }
    }

    //Exit du chargement
    TTF_CloseFont(police);

    ///TODO : Options de chargement à finir
    //SDL_FreeSurface(fondCharg);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(pixia);
    SDL_FreeSurface(bgb);
    SDL_FreeSurface(bghg);
    SDL_FreeSurface(bghd);
    SDL_FreeSurface(bgg);
    //SDL_FreeSurface(pourcentage);

    startGame(ecran, &base, &heure);

    freeBase(base);
}

void freeBase(S_base base){
    freeMap(base.map);

    SDL_FreeSurface(base.ico_people);
    SDL_FreeSurface(base.ico_wood);
    SDL_FreeSurface(base.ico_food);
    SDL_FreeSurface(base.ico_rock);
    SDL_FreeSurface(base.ico_menu);
    SDL_FreeSurface(base.ico_menuA);
    SDL_FreeSurface(base.cadr_menu);
    SDL_FreeSurface(base.cadr_quitter);
    SDL_FreeSurface(base.t_grass1);
    SDL_FreeSurface(base.t_water1);
    SDL_FreeSurface(base.t_forest1);
    SDL_FreeSurface(base.t_mount1);
    SDL_FreeSurface(base.t_field1);
    SDL_FreeSurface(base.t_house1);
    SDL_FreeSurface(base.t_stower1);
    SDL_FreeSurface(base.t_btower1);
    SDL_FreeSurface(base.t_sawmill1);
}




