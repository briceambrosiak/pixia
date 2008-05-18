/**
    Projet Jeu Pixia pour ESIAL CSH
    -------------------------------

    Editeur de carte

    Créé le 17 mai 2008

    Par Gaétan SCHMITT et Brice AMBROSIAK

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

#include "librairie.h"
#include "biblio.h"
#include "constants.h"


/**
	Chargement des options
*/
int optionsLoad(int *larg, int *haut, int *coul, int *volume)
{
    //Déclarations-----------------------------------------------

    FILE* fichier;
    int caract, i;
    int ok = 1;
    long val[4] = {0};

    //----------------------------------------------------------

    // Ouverture du fichier (s'il existe)
    fichier = fopen(FILE_OPTIONS, "r");
    if(fichier == NULL)
    {
    	// Ecriture d'un fichier par défaut
		optionsSaveDefault();

		fichier = fopen(FILE_OPTIONS, "r");
		if(fichier == NULL) {
			fprintf(stderr, "Impossible d'ouvrir le fichier d'options [options.c]");
			exit(EXIT_FAILURE);
		}
    }
    //------------------------------------------------------------
    //Parcours du fichier
    i = 0;
    caract = ~EOF;
    while(caract != EOF){
        caract = fgetc(fichier);
        if(caract == '#') // Ignore la ligne
            while(caract != '\n')
                caract = fgetc(fichier);
        if(caract != '\n'){
            fseek(fichier, -1, SEEK_CUR);
            fscanf(fichier, "%ld", &val[i]);
            i++;
        }
    }
    fclose(fichier);
    //------------------------------------------------------------
    //Test des resultats
    //Largeur
    if(val[0]==1280||val[0]==1024||val[0]==800)
        *larg = val[0];
    else
        ok = 0;
    //Hauteur
    if(val[1]==800||val[1]==768||val[1]==600)
        *haut = val[1];
    else
        ok = 0;
    //Profondeur de couleur
    if(val[2]==32||val[2]==16)
        *coul = val[2];
    else
        ok = 0;
    //Volume son
    if(val[3]==0||val[3]==25||val[3]==50||val[3]==75||val[3]==100)
        *volume = val[3];
    else
        ok = 0;

    return ok;
}



/**
	Sauvegarde des options
*/
char optionsSave(int larg, int haut, int coul, int volume)
{
    //Déclarations-----------------------------------------------

    FILE* fichier;
    char ok = 1;

    //----------------------------------------------------------

    // Ouverture
    fichier = fopen(FILE_OPTIONS, "w");
    if(fichier == NULL){
        fprintf(stderr, "Fichier d'options introuvable [options.c]");
        exit(EXIT_FAILURE);
    }
    //------------------------------------------------------------
    // Ecriture du fichier
    fprintf(fichier, "# résolution : hauteur puis largeur\n");
    fprintf(fichier, "%d\n", larg);
    fprintf(fichier, "%d\n", haut);
    fprintf(fichier, "# profondeur des couleurs (en bits)\n");
    fprintf(fichier, "%d\n", coul);
    fprintf(fichier, "# volume (en pourcentage)\n");
    fprintf(fichier, "%d\n", volume);

    fclose(fichier);

    return ok;
}

/**
	Sauvegarde les valeurs par défaut des options
*/
void optionsSaveDefault()
{
	optionsSave(1024, 768, 32, 100);
}

Map getMap(int larg, int haut)
{
    //DECLARATION---------------------
    int height, width;
	Map map;
	Ground ground;
	//------------------------------

    height = 80;
    width = 160;
    map.name = "Difficil";

	ground.height = height;
	ground.width = width;
	//ground.ground = malloc(ground.height * ground.width * sizeof(int));

	map.entities = NULL;
	map.ground = ground;

	return map;
}



