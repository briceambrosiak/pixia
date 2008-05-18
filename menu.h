/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	menu.h : Header

	Date : 20/03/08
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

#ifndef DEF_MENU
#define DEF_MENU


struct S_boucleMenu
{
    SDL_Surface *ecran;
    SDL_Surface *fondMenu;
    SDL_Surface *nouvPart;
    SDL_Surface *chargPart;
    SDL_Surface *options;
    SDL_Surface *curseur;
    SDL_Rect p_fondMenu;
    SDL_Rect p_nouvPart;
    SDL_Rect p_chargPart;
    SDL_Rect p_options;
    SDL_Rect p_curseur;
    int posButtons[2][3][4];
    FSOUND_SAMPLE *clic;
    int iRes;
    int horSpace;
    int vertSpace;
    int continuer;
    int echap;
    char select;
    int son;
};

// Possibilités du menu
enum {A_NEW_GAME, A_LOAD_GAME, A_OPTIONS, A_QUIT};

char menu(SDL_Surface *ecran);

Uint32 boucleMenu(Uint32 intervalle,
                void *param);

char chargMenu(struct S_boucleMenu *s_p);

#endif


