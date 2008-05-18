/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	nouvellePartie.h : Header

	Date : 21/03/08
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

#ifndef DEF_NOUVELLEPARTIE
#define DEF_NOUVELLEPARTIE

// Actions possibles
enum {B_EASY, B_NORMAL, B_HARD, B_BACK};

void nouvellePartie(SDL_Surface *ecran);
char loopNewGame(SDL_Surface *ecran);
char chargImg(int largeur,
                SDL_Surface **fond,
                SDL_Surface **facile,
                SDL_Surface **moyen,
                SDL_Surface **dur,
                SDL_Rect *p_fond,
                SDL_Rect *p_facile,
                SDL_Rect *p_moyen,
                SDL_Rect *p_dur);

#endif

