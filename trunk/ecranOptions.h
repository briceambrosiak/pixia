/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	ecranOptions.h : Header

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

#ifndef DEF_ECRANOPTIONS
#define DEF_ECRANOPTIONS

void ecranOptions(SDL_Surface *ecran);
char chargImOp(int largeur,
                SDL_Surface **fondOptions,
                SDL_Surface **valide,
                SDL_Rect *p_fondOptions,
                SDL_Rect *p_resolution,
                SDL_Rect *p_couleur,
                SDL_Rect *p_volume,
                SDL_Rect *p_actif);
char boucleOp(SDL_Surface *ecran,
				SDL_Surface *fondOptions,
				SDL_Surface *valide,
				SDL_Rect p_fondOptions,
				SDL_Rect *p_resolution,
				SDL_Rect *p_couleur,
				SDL_Rect *p_volume,
				SDL_Rect *p_actif);

#endif

