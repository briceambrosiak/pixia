/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	options.c : Chargement & sauvegarde des options

	Date : 18/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "options.h"


/**
	Chargement des options
*/
char optionsLoad(int *larg, int *haut, int *coul, int *volume)
{
    //Déclarations-----------------------------------------------

    FILE* fichier;
    int caract, i;
    char ok = 1;
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
    int caract, i;
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
    fprintf(fichier, "%ld\n", larg);
    fprintf(fichier, "%ld\n", haut);
    fprintf(fichier, "# profondeur des couleurs (en bits)\n");
    fprintf(fichier, "%ld\n", coul);
    fprintf(fichier, "# volume (en pourcentage)\n");
    fprintf(fichier, "%ld\n", volume);

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


