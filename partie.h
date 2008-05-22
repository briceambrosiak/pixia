/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	partie.h : Header

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

#ifndef DEF_PARTIE
#define DEF_PARTIE

#define WRITETXT(E, M, P, C, PO)\
    ({\
    SDL_Surface *texte;\
    SDL_Color black = {0, 0, 0};\
    texte = TTF_RenderText_Shaded(P, M, C, black);\
    SDL_BlitSurface(texte, NULL, E, &PO);\
    SDL_FreeSurface(texte);\
    })

#include "chargement.h"

enum{S_NOTHING, S_MENU};

void startGame(SDL_Surface *ecran, S_base *base, S_time *heure);

Uint32 horloge(Uint32 intervalle, void *param);

int min(int a, int b);
int max(int a, int b);

#endif