/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	options.h : Header

	Date : 18/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#ifndef DEF_OPTIONS
#define DEF_OPTIONS

char optionsLoad(int *larg, int *haut, int *coul, int *volume);
char optionsSave(int larg, int haut, int coul, int volume);
void optionsSaveDefault();

#endif


