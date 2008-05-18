/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	options.h : Header

	Date : 18/03/08
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

#ifndef DEF_OPTIONS
#define DEF_OPTIONS

char optionsLoad(int *larg, int *haut, int *coul, int *volume);
char optionsSave(int larg, int haut, int coul, int volume);
void optionsSaveDefault();

#endif


