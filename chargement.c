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
    SDL_Surface /* *fondCharg, *pourcentage,*/ *texte, *pixia, *bgb, *bgg;
    SDL_Rect p_texte, p_pixia, p_b, p_g, p_1l1, p_1l2, p_1l3, p_2l1, p_2l2, p_2l3, p_2l4;
    TTF_Font *police;
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Event event;
    char continuer = 1;
    int inter = 0, i, esp=0;

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

    base.t_water=IMG_Load("images/tiles/eau.png");
    base.t_gwll=IMG_Load("images/tiles/eaubg.png");
    base.t_gwlr=IMG_Load("images/tiles/eaubd.png");
    base.t_gwhl=IMG_Load("images/tiles/eauhg.png");
    base.t_gwhr=IMG_Load("images/tiles/eauhd.png");
    base.t_grass=IMG_Load("images/tiles/herbe.png");
    base.t_forest1=IMG_Load("images/tiles/arbre.png");
    base.t_forest2=IMG_Load("images/tiles/2arbres.png");
    base.t_forest3a=IMG_Load("images/tiles/3aarbres.png");
    base.t_forest3b=IMG_Load("images/tiles/3barbres.png");
    base.t_mount1=IMG_Load("images/tiles/monbg.png");
    base.t_mount2=IMG_Load("images/tiles/monhg.png");
    base.t_mount3=IMG_Load("images/tiles/monbd.png");
    base.t_mount4=IMG_Load("images/tiles/monhd.png");
    base.t_mine=IMG_Load("images/tiles/pierres.png");
    base.t_ruins=IMG_Load("images/tiles/ruines.png");

    base.tiles[WATER] = base.t_water;
    base.tiles[GWLL] = base.t_gwll;
    base.tiles[GWLR] = base.t_gwlr;
    base.tiles[GWHL] = base.t_gwhl;
    base.tiles[GWHR] = base.t_gwhr;
    base.tiles[GRASS] = base.t_grass;
    base.tiles[FOREST1] = base.t_forest1;
    base.tiles[FOREST2] = base.t_forest2;
    base.tiles[FOREST3A] = base.t_forest3a;
    base.tiles[FOREST3B] = base.t_forest3b;
    base.tiles[MOUNTAIN1] = base.t_mount1;
    base.tiles[MOUNTAIN2] = base.t_mount2;
    base.tiles[MOUNTAIN3] = base.t_mount3;
    base.tiles[MOUNTAIN4] = base.t_mount4;
    base.tiles[MINE] = base.t_mine;
    base.tiles[RUINS] = base.t_ruins;


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

    base.t_dino=IMG_Load("images/tiles/dino.png");
    base.t_house=IMG_Load("images/tiles/habitation.png");
    base.t_sawmill=IMG_Load("images/tiles/scierie.png");
    base.t_stower=IMG_Load("images/tiles/tour.png");
    base.t_btower=IMG_Load("images/tiles/gtour.png");
    base.t_minecamp=IMG_Load("images/tiles/mine.png");
    base.t_well=IMG_Load("images/tiles/puit.png");
    base.t_field=IMG_Load("images/tiles/champ.png");
    base.t_sheep=IMG_Load("images/tiles/champm.png");
    base.t_guardians=IMG_Load("images/tiles/regiment.png");
    base.t_fire=IMG_Load("images/tiles/feu.png");
    base.t_humains=IMG_Load("images/tiles/humains.png");

    base.tiles[DINO] = base.t_dino;
    base.tiles[HOUSE] = base.t_house;
    base.tiles[SAWMILL] = base.t_sawmill;
    base.tiles[SMALLTOWER] = base.t_stower;
    base.tiles[BIGTOWER] = base.t_btower;
    base.tiles[MINECAMP] = base.t_minecamp;
    base.tiles[WELL] = base.t_well;
    base.tiles[FIELD] = base.t_field;
    base.tiles[SHEEP] = base.t_sheep;
    base.tiles[GUARDIANS] = base.t_guardians;
    base.tiles[FIRE] = base.t_fire;
    base.tiles[HUMAINS] = base.t_humains;

    base.nom[HOUSE] = " Maison ";
    base.nom[SAWMILL] = " Scierie ";
    base.nom[SMALLTOWER] = " Tour ";
    base.nom[BIGTOWER] = " Donjon ";
    base.nom[MINECAMP] = " Mine ";
    base.nom[WELL] = " Puits ";
    base.nom[FIELD] = " Champ ";
    base.nom[SHEEP] = " Troupeau ";
    base.nom[GUARDIANS] = " Regiment ";

    //Chargement de l'HUD
    SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));
    texte = TTF_RenderText_Solid(police, "Chargement en cours :   HUD : cadre de jeu...", couleurBlanche);
    SDL_BlitSurface(texte, NULL, ecran, &p_texte);
    SDL_Flip(ecran);

    base.berlinP = TTF_OpenFont("berlin.ttf", 11);
    base.berlinPM = TTF_OpenFont("berlin.ttf", 14);
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
    for(i=0;i<9;i++){
        base.cache[i] = IMG_Load("images/backgrounds/cache.jpg");
    }

    base.bleute.r = 190;
    base.bleute.g = 190;
    base.bleute.b = 250;

    //Ecriture sur cache des infos des Tiles:
    p_1l1.x =p_1l2.x =p_1l3.x =p_2l1.x =p_2l2.x =p_2l3.x = p_2l4.x= 30;
    esp = 20;
    p_1l1.y = 160;
    p_1l2.y = p_1l1.y+esp;
    p_1l3.y = p_1l2.y+esp;
    p_2l1.y = p_1l3.y+2*esp;
    p_2l2.y = p_2l1.y+esp;
    p_2l3.y = p_2l2.y+1.5*esp;
    p_2l4.y = p_2l3.y+esp;
    //La Maison
    WRITETXT(base.cache[0], "Petite habitation de", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[0], "pierre, elle permet", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[0], "de loger la population.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[0], "Pour grossir, votre population", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[0], "en a grand besoin...", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[0], "Coût : 100 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[0], "           100 bois", base.berlinP, base.bleute, p_2l4);
    //La Scierie
    WRITETXT(base.cache[1], "Voici le camp des", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[1], "bûcherons, avec tous", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[1], "leurs outils.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[1], "La scierie est indispensable", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[1], "afin de récolter le bois.", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[1], "Coût : 200 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[1], "           100 bois", base.berlinP, base.bleute, p_2l4);
    //Petite Tour
    WRITETXT(base.cache[2], "Faite de pierres et munie", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[2], "de meurtrières, cette", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[2], "tour de garde est idéale.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[2], "Parmis les défenses les moins", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[2], "coûteuses...", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[2], "Coût : 700 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[2], "           300 bois", base.berlinP, base.bleute, p_2l4);
    //Grosse tour
    WRITETXT(base.cache[3], "Tellement plus solide", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[3], "et puissant qu'une tour:", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[3], "le donjon... ", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[3], "Défense ultime de votre ville,", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[3], "son coût reste très élevé. ", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[3], "Coût : 2400 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[3], "           1400 bois", base.berlinP, base.bleute, p_2l4);
    //Mine
    WRITETXT(base.cache[4], "Cette haute grue est", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[4], "bien plus qu'appréciable", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[4], "pour travailler la pierre.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[4], "Indispensable à la récolte", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[4], "de pierres !", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[4], "Coût : 200 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[4], "           600 bois", base.berlinP, base.bleute, p_2l4);
    //Puit
    WRITETXT(base.cache[5], "Large et profond puits", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[5], "de pierre, dont l'eau", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[5], "reste toujours fraiche.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[5], "Aimé du peuple, il permet", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[5], "aussi de combattre le feu !", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[5], "Coût : 600 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[5], "           100 bois", base.berlinP, base.bleute, p_2l4);
    //Champ
    WRITETXT(base.cache[6], "Large champ de blé", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[6], "doré au soleil tropical,", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[6], "la récolte sera bonne !", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[6], "Ce champ rapporte bien plus", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[6], "de nourriture qu'un troupeau.", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[6], "Coût : 900 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[6], "           1200 bois", base.berlinP, base.bleute, p_2l4);
    //troupeau : disparaît... rajouter le berger ?
    ///TODO: a voir
    WRITETXT(base.cache[7], "Beau petit troupeau", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[7], "de moutons... un peu", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[7], "de viande fraîche !", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[7], "Premier moyen d'avoir de la", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[7], "nourriture à bas coût. (tmp)", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[7], "Coût : 50 pierres", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[7], "           100 bois", base.berlinP, base.bleute, p_2l4);
    //régiment
    WRITETXT(base.cache[8], "Ah ces valeureux", base.berlinPM, base.bleute, p_1l1);
    WRITETXT(base.cache[8], "Guerriers ! Toujours", base.berlinPM, base.bleute, p_1l2);
    WRITETXT(base.cache[8], "prêts à mourir pour nous.", base.berlinPM, base.bleute, p_1l3);
    WRITETXT(base.cache[8], "Seule défense movible, ils sont", base.berlinP, base.bleute, p_2l1);
    WRITETXT(base.cache[8], "très utiles, bien que faibles.", base.berlinP, base.bleute, p_2l2);
    WRITETXT(base.cache[8], "Coût : 500 Nourriture", base.berlinP, base.bleute, p_2l3);
    WRITETXT(base.cache[8], "           100 bois", base.berlinP, base.bleute, p_2l4);


    bgb = IMG_Load("images/backgrounds/bgb.jpg");
    bgg = IMG_Load("images/backgrounds/bgg.jpg");

    switch(ecran->w){
        case 1280:
            inter = 120;
            base.p_wood.x = 754;
            base.p_wood.y = 755;
            base.p_food.x = base.p_wood.x+inter+3;
            base.p_food.y = base.p_wood.y;
            base.p_rock.x = base.p_food.x+inter;
            base.p_rock.y = base.p_wood.y;
            base.p_people.x = 25;
            base.p_people.y = 740;
            base.p_menu.x = base.p_people.x;
            base.p_menu.y = 20;
            base.p_time.x = 100;
            base.p_time.y = 35;
            p_pixia.x = 1190;
            p_pixia.y = 750;
            base.p_c_menu.x = 0;
            base.p_c_menu.y = base.p_menu.y+65;
            p_b.x = 0;
            p_b.y = 800 - 62;
            p_g.x = 0;
            p_g.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = ecran->h - 20;
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
            p_b.x = 0;
            p_b.y = 768 - 62;
            p_g.x = 0;
            p_g.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = ecran->h - 20;
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
            p_b.x = 0;
            p_b.y = 600 - 62;
            p_g.x = 0;
            p_g.y = 0;
            base.p_info_t.x = 20;
            base.p_info_t.y = ecran->h - 20;
            break;
        default:
            fprintf(stderr, "Erreur de résolution : chargement.c");
            exit(EXIT_FAILURE);
            break;
    }

    base.p_choix.x = 90;
    base.p_choix.y = ecran->h/2-30;
    base.p_info_t2.x = 70;
    base.p_info_t2.y = ecran->h/2+40;
    base.p_info_t3.x = 20;
    base.p_info_t3.y = base.p_info_t2.y+20;
    base.p_cache.x = 10;
    base.p_cache.y = base.p_choix.y-50;

    base.p_c_quitter.x = ((ecran->w)*3/5) - ((base.cadr_quitter->w)/2);
    base.p_c_quitter.y = ((ecran->h)/2) - ((base.cadr_quitter->h)/2);

    base.fond = IMG_Load("images/backgrounds/mer.jpg");
    base.p_fond.x = 224;
    base.p_fond.y = 0;

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
    SDL_BlitSurface(bgg, NULL, base.hud, &p_g);
    SDL_BlitSurface(base.ico_menu, NULL, base.hud, &base.p_menu);
    SDL_BlitSurface(base.ico_people, NULL, base.hud, &base.p_people);
    SDL_BlitSurface(base.ico_wood, NULL, base.hud, &base.p_wood);
    SDL_BlitSurface(base.ico_food, NULL, base.hud, &base.p_food);
    SDL_BlitSurface(base.ico_rock, NULL, base.hud, &base.p_rock);

    base.black.r = 0;
    base.black.g = 0;
    base.black.b = 0;
    pixia = TTF_RenderText_Shaded(base.berlinM, "Pixia", base.bleute, base.black);
    SDL_BlitSurface(pixia, NULL, base.hud, &p_pixia);

    //Mise en place de l'horloge
    heure.heures = 0;
    heure.minutes = 0;
    heure.secondes = 0;
    heure.ecran = ecran;
    heure.police = base.berlinM;
    heure.color = base.bleute;
    heure.base = &base;

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
    SDL_FreeSurface(texte);
    SDL_FreeSurface(pixia);
    SDL_FreeSurface(bgb);
    SDL_FreeSurface(bgg);

    startGame(ecran, &base, &heure);

    freeBase(base);
}

void freeBase(S_base base){
    int i;

    freeMap(base.map);
    TTF_CloseFont(base.berlinG);
    TTF_CloseFont(base.berlinM);
    TTF_CloseFont(base.berlinPM);
    TTF_CloseFont(base.berlinP);

    SDL_FreeSurface(base.ico_people);
    SDL_FreeSurface(base.ico_wood);
    SDL_FreeSurface(base.ico_food);
    SDL_FreeSurface(base.ico_rock);
    SDL_FreeSurface(base.ico_menu);
    SDL_FreeSurface(base.ico_menuA);
    SDL_FreeSurface(base.cadr_menu);
    SDL_FreeSurface(base.cadr_quitter);
    SDL_FreeSurface(base.fond);
    for(i=0;i<9;i++)
        SDL_FreeSurface(base.cache[i]);

    SDL_FreeSurface(base.t_water);
    SDL_FreeSurface(base.t_gwll);
    SDL_FreeSurface(base.t_gwlr);
    SDL_FreeSurface(base.t_gwhl);
    SDL_FreeSurface(base.t_gwhr);
    SDL_FreeSurface(base.t_grass);
    SDL_FreeSurface(base.t_forest1);
    SDL_FreeSurface(base.t_forest2);
    SDL_FreeSurface(base.t_forest3a);
    SDL_FreeSurface(base.t_forest3b);
    SDL_FreeSurface(base.t_mount1);
    SDL_FreeSurface(base.t_mount2);
    SDL_FreeSurface(base.t_mount3);
    SDL_FreeSurface(base.t_mount4);
    SDL_FreeSurface(base.t_mine);
    SDL_FreeSurface(base.t_ruins);
    SDL_FreeSurface(base.t_dino);
    SDL_FreeSurface(base.t_house);
    SDL_FreeSurface(base.t_sawmill);
    SDL_FreeSurface(base.t_stower);
    SDL_FreeSurface(base.t_btower);
    SDL_FreeSurface(base.t_minecamp);
    SDL_FreeSurface(base.t_well);
    SDL_FreeSurface(base.t_field);
    SDL_FreeSurface(base.t_sheep);
    SDL_FreeSurface(base.t_guardians);
    SDL_FreeSurface(base.t_fire);
    SDL_FreeSurface(base.t_humains);
}




