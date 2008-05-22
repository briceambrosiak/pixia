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

//Includes classiques
#include <stdlib.h>
#include <stdio.h>

//Include graphiques
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h>

//Includes particuliers
#include "../constants.h"
#include "../options.h"

#include "librairie.h"
#include "carte.h"


int main(int argc, char *argv[]){
 //--------------DECLARATIONS---------------------------------
	FILE* fichier = NULL;
    Info info;
    SDL_Event event;
    SDL_Surface *ecran;
    SDL_Rect p_titre, p_entete, p_q1, p_q2, p_q3, p_r1, p_r2, p_r3;
    int o_largeur, o_hauteur, o_couleur, o_volume, i=0; // Options de jeu (lues d'un fichier)
    int continuer = 1, ok;    //Valeur booleen pour les tests de réussite
    char rep1[11], rep2[4], rep3[4], mess[20], buffer[128], *choix, char_lu;

    //------------------------------------------------------------
    // Chargement des options contenues dans le fichier d'option
    //fprintf(stdout, FILE_OPTIONS);
    //fprintf(stdout, "\n");
    ok = optionsLoad(&o_largeur, &o_hauteur, &o_couleur, &o_volume);
    //fprintf(stdout, FILE_OPTIONS);
    if(ok != 1){
        fprintf(stderr, "Erreur de lecture des options [main.c]");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------
    //Initialisation video
    SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableUNICODE(1);

    //-------------------------------------------------------------
    //Initialisation fenêtre
    SDL_WM_SetIcon(SDL_LoadBMP(FILE_EDITOR_ICON), NULL);               //Icone de fenêtre

    ecran = SDL_SetVideoMode(o_largeur,o_hauteur,o_couleur,     //Création de l'"écran support"
            SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);

    SDL_WM_SetCaption(EDITOR_NAME, NULL);                         //Nom de la fenêtre

    //-------------------------------------------------------------
    //Initialisation de la TTF (affichage de texte)
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    info.berlinP = TTF_OpenFont("berlin.ttf", 12);
    info.berlinM = TTF_OpenFont("berlin.ttf", 18);
    info.berlinG = TTF_OpenFont("berlin.ttf", 30);
    p_titre.x = ecran->w/2 - 110;
    p_titre.y = 20;
    p_entete.x = ecran->w/2 - 146;
    p_entete.y = 200;
    p_q1.x = ecran->w/2 - 130;
    p_q1.y = 250;
    p_q2.x = ecran->w/2 - 130;
    p_q2.y = 270;
    p_q3.x = ecran->w/2 - 120;
    p_q3.y = 290;

    p_r1.x = p_q1.x + 160;
    p_r1.y = p_q1.y;
    p_r2.x = p_q2.x + 240;
    p_r2.y = p_q2.y;
    p_r3.x = p_q1.x + 240;
    p_r3.y = p_q1.y;

     for(i=1;i<10;i++){
        rep1[i] = ' ';
    }
    rep1[0] = '_';
    rep1[10] = '\0';

    rep2[0] = '_';
    rep2[1] = ' ';
    rep2[2] = ' ';
    rep2[3] = '\0';

    rep3[0] = ' ';
    rep3[1] = ' ';
    rep3[2] = ' ';
    rep3[3] = '\0';

    for(i=0;i<20;i++){
        mess[i] = ' ';
    }
    mess[19] = '\0';

    info.bleute.r = 190;
    info.bleute.g = 190;
    info.bleute.b = 250;

    //--------------------------------------------------------------
    // Lancement menu principal
    i = 0;

    while(continuer)
    {
		//Boucle d'évènement (tant qu'un évènement au moins est dans la pile)
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            rep1[0] = 'm';
                            rep1[1] = 'a';
                            rep1[2] = 'p';
                            rep1[3] = '\0';
                            break;

                        case SDLK_RETURN:
                            if(i > 0)
                                continuer = 0;
                            else{
                            	strcpy(mess, "Nom invalide...");
                            }
                            break;

                        case SDLK_BACKSPACE:
                            if(i>0){
                                rep1[i] = ' ';
                                i--;
                                rep1[i] = '_';
                            }
                            break;

                        default:
							// Si c'est un caractère Unicode ASCII, on a directement sa valeur ASCII
							if ( (event.key.keysym.unicode & 0xFF80) == 0 )
							{
								char_lu = event.key.keysym.unicode & 0x7F;

								if (char_lu >= '0' && char_lu <= 'z')
								{
									rep1[i] = char_lu;
									if(i < 9) {
										i++;
										rep1[i] = '_';
									}
								}
							}
							else {
								// Caractère unicode non-ASCII
							}
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

        WRITETXT(ecran, "Editeur de Pixia", info.berlinG, info.bleute, p_titre);
        WRITETXT(ecran, "Quel est le nom de votre carte ?", info.berlinM, info.bleute, p_entete);
        WRITETXT(ecran, "              Nom de la carte ?", info.berlinP, info.bleute, p_q1);

        //Réponses
        WRITETXT(ecran, rep1, info.berlinP, info.bleute, p_r1);
        WRITETXT(ecran, mess, info.berlinP, info.bleute, p_q3);

        SDL_Flip(ecran);

        SDL_Delay(10);

    }

    rep1[i] = '\0';

    info.nom = rep1;
    sprintf(info.nom, "%s.map", info.nom); // Rajoute .map

    // Essaie d'ouvrir le fichier en lecture. Si NULL: fichier inexistant; Sinon: charge la map
	fichier = fopen(info.nom, "r");
	if (fichier != NULL) {
		editer(ecran, info, 1);
	}
	else
	{

		continuer = 1;
		i = 0;
		choix = rep2;

		while(continuer)
		{
			//Boucle d'évènement (tant qu'un évènement au moins est dans la pile)
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_QUIT:
						continuer=0;
						break;

					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								continuer=0;
								break;

							case SDLK_RETURN:
								if(choix==rep2){
									if(i<2){
										choix[1] = ' ';
									}
									if(i<3 && choix[2] == '_'){
										choix[2] = ' ';
									}
									choix = rep3;
									i = 0;
									choix[0] = '_';
								}
								else if(choix==rep3){
									continuer = 0;
								}
								break;

							case SDLK_BACKSPACE:
								if(i>0){
									choix[i] = ' ';
									i--;
									choix[i] = '_';
								}
								else if(i==0 && choix==rep3){
									choix[0] = ' ';
									choix = rep2;
									i = 2;
									choix[2] = '_';
								}
								break;

							default:
								// Si c'est un caractère Unicode ASCII, on a directement sa valeur ASCII
								if ( (event.key.keysym.unicode & 0xFF80) == 0 )
								{
									char_lu = event.key.keysym.unicode & 0x7F;

									if (char_lu >= '0' && char_lu <= '9')
									{
										choix[i] = char_lu;
										if (i < 2) {
											i++;
											choix[i] = '_';
										}
									}
								}
								else {
									// Caractère unicode non-ASCII
								}

								break;
						}
						break;

					case SDL_MOUSEMOTION:
						break;

					case SDL_MOUSEBUTTONUP:
						break;

					default:
						break;
				}
			}
			SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

			WRITETXT(ecran, "Editeur de Pixia", info.berlinG, info.bleute, p_titre);
			WRITETXT(ecran, "Quelle sera la taille de votre carte ?", info.berlinM, info.bleute, p_entete);
			WRITETXT(ecran, "Nombre de cases de hauteur ? (10/50)", info.berlinP, info.bleute, p_q1);
			WRITETXT(ecran, "Nombre de cases de largeur ? (10/100)", info.berlinP, info.bleute, p_q2);

			//Réponses
			WRITETXT(ecran, rep2, info.berlinP, info.bleute, p_r3);
			WRITETXT(ecran, rep3, info.berlinP, info.bleute, p_r2);

			SDL_Flip(ecran);
			SDL_Delay(10);

		}

		//Récupération des tailles données
		sscanf(rep2, "%d", &info.hauteur);
		sscanf(rep3, "%d", &info.largeur);

		ok = 0;

		//Verification de respect des limites
		if(info.hauteur>50 || info.hauteur<10){
			info.hauteur = 20;
			ok = 1;
		}
		if(info.largeur>100 || info.largeur<10){
			info.largeur = 40;
			ok = 1;
		}

		//Par defaut si mal renseigne
		if(ok) {
			SDL_FillRect(ecran, NULL, COLOR_BLACK(ecran));

			WRITETXT(ecran, "Editeur de Pixia", info.berlinG, info.bleute, p_titre);
			WRITETXT(ecran, "Nombre de cases de hauteur ? (10/50)", info.berlinP, info.bleute, p_q1);
			WRITETXT(ecran, "Nombre de cases de largeur ? (10/100)", info.berlinP, info.bleute, p_q2);

			//Réponses
			WRITETXT(ecran, "valeur par defaut(20)", info.berlinP, info.bleute, p_r3);
			WRITETXT(ecran, "valeur par defaut(40)", info.berlinP, info.bleute, p_r2);
			SDL_Flip(ecran);

			for (i=ERROR_MSG_DURATION ; i>0 ; i--) {
				sprintf(buffer, "--> MAL RENSEIGNE [%d]<--  ", i);
				WRITETXT(ecran, buffer, info.berlinM, info.bleute, p_entete);
				SDL_Flip(ecran);
				SDL_Delay(1000);
			}
		}

		editer(ecran, info, 0);
	}

    // Suppression de mémoire et stop module
    TTF_CloseFont(info.berlinP);
    TTF_CloseFont(info.berlinM);
    TTF_CloseFont(info.berlinG);

    TTF_Quit();

    SDL_Quit(); //Cloture de la SDL

    return EXIT_SUCCESS;
}



