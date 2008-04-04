/**
	Pixia - Projet C ESIAL 1A
	--------------------------

	ecranOptions.c : Affichage du menu des options

	Date : 20/03/08
	Author : Gaétan Schmitt, Brice Ambrosiak
*/

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <FMOD/fmod.h>

#include "constants.h"

#include "ecranOptions.h"

/**
	Affiche l'écran d'options
*/
void ecranOptions(SDL_Surface *ecran)
{
    //---DECLARATIONS---------------------------------------------
    SDL_Surface *fondOptions=NULL, *valide;
    SDL_Rect p_fondOptions, p_resolution[3], p_couleur[2], p_volume[5], p_actif[3];
    char ok;

    //------------------------------------------------------------
    //Chargement des images du menu et leur position
    ok = chargImOp(ecran->w, &fondOptions, &valide,
                    &p_fondOptions, p_resolution, p_couleur, p_volume, p_actif);
    if(ok != 1){
        fprintf(stderr, "Erreur de chargement d'images options (chargImOpt) [ecranOptions.c]");
        exit(EXIT_FAILURE);
    }

	//--------------------------------------------------------
    // Boucle
	ok = boucleOp(ecran, fondOptions, valide,
			p_fondOptions, p_resolution, p_couleur, p_volume, p_actif);

    //<<<<< UN TIMER A LA PLACE ???? >>>>>

    //--------------------------------------------------------
    //Suppression espace mémoire de menu
    SDL_FreeSurface(fondOptions);
    SDL_FreeSurface(valide);
}

// Pour Pixia par Gaétan Schmitt le 20/03/08

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/**
	Chargement des images et coordonnées du menu d'options
*/
char chargImOp(int largeur,
                SDL_Surface **fondOptions,
                SDL_Surface **valide,
                SDL_Rect *p_fondOptions,
                SDL_Rect *p_resolution,
                SDL_Rect *p_couleur,
                SDL_Rect *p_volume,
                SDL_Rect *p_actif){
    //----DECLARATION---------------------------------------------
    int hauteur;
    //-----------------------------------------------------------
    switch(largeur){
        case 1280:
            hauteur = 800;
            *fondOptions = IMG_Load(FILE_BG_OPTIONS);
            p_fondOptions->x = (largeur-1024)/2;
            p_fondOptions->y = (hauteur-768)/2;
            p_resolution[0].x = 886+128;
            p_resolution[0].y = 228+16;
            p_resolution[1].x = 886+128;
            p_resolution[1].y = 264+16;
            p_resolution[2].x = 886+128;
            p_resolution[2].y = 297+16;
            p_couleur[0].x = 656+128;
            p_couleur[0].y = 558+16;
            p_couleur[1].x = 758+128;
            p_couleur[1].y = 558+16;
            p_volume[0].x = 421+128;
            p_volume[0].y = 621+16;
            p_volume[1].x = 516+128;
            p_volume[1].y = 621+16;
            p_volume[2].x = 611+128;
            p_volume[2].y = 621+16;
            p_volume[3].x = 699+128;
            p_volume[3].y = 621+16;
            p_volume[4].x = 809+128;
            p_volume[4].y = 621+16;
            p_actif[0].x = 705+128;
            p_actif[0].y = 194+16;
            p_actif[1].x = 172+128;
            p_actif[1].y = 561+16;
            p_actif[2].x = 198+128;
            p_actif[2].y = 628+16;
            break;
        case 1024:
            *fondOptions = IMG_Load(FILE_BG_OPTIONS);
            p_fondOptions->x = 0;
            p_fondOptions->y = 0;
            p_resolution[0].x = 886;
            p_resolution[0].y = 228;
            p_resolution[1].x = 886;
            p_resolution[1].y = 264;
            p_resolution[2].x = 886;
            p_resolution[2].y = 297;
            p_couleur[0].x = 656;
            p_couleur[0].y = 558;
            p_couleur[1].x = 758;
            p_couleur[1].y = 558;
            p_volume[0].x = 421;
            p_volume[0].y = 621;
            p_volume[1].x = 516;
            p_volume[1].y = 621;
            p_volume[2].x = 611;
            p_volume[2].y = 621;
            p_volume[3].x = 699;
            p_volume[3].y = 621;
            p_volume[4].x = 809;
            p_volume[4].y = 621;
            p_actif[0].x = 705;
            p_actif[0].y = 194;
            p_actif[1].x = 172;
            p_actif[1].y = 561;
            p_actif[2].x = 198;
            p_actif[2].y = 628;
            break;
        case 800:
            *fondOptions = IMG_Load(FILE_BG_OPTIONS_P);
            p_fondOptions->x = 0;
            p_fondOptions->y = 0;
            p_resolution[0].x = 684;
            p_resolution[0].y = 173;
            p_resolution[1].x = 684;
            p_resolution[1].y = 200;
            p_resolution[2].x = 684;
            p_resolution[2].y = 227;
            p_couleur[0].x = 509;
            p_couleur[0].y = 427;
            p_couleur[1].x = 590;
            p_couleur[1].y = 427;
            p_volume[0].x = 327;
            p_volume[0].y = 480;
            p_volume[1].x = 401;
            p_volume[1].y = 480;
            p_volume[2].x = 473;
            p_volume[2].y = 480;
            p_volume[3].x = 545;
            p_volume[3].y = 480;
            p_volume[4].x = 631;
            p_volume[4].y = 480;
            p_actif[0].x = 546;
            p_actif[0].y = 149;
            p_actif[1].x = 129;
            p_actif[1].y = 436;
            p_actif[2].x = 148;
            p_actif[2].y = 487;
            break;
        default:
            fprintf(stderr, "Erreur de largeur (chargImOp)[chargImOp.c]");
            exit(EXIT_FAILURE);
            break;
    }
    *valide = IMG_Load(FILE_IMG_VALID);

    return 1;
}


/**
	Boucle du menu d'options
*/
char boucleOp(SDL_Surface *ecran,
                    SDL_Surface *fondOptions,
                    SDL_Surface *valide,
                    SDL_Rect p_fondOptions,
                    SDL_Rect *p_resolution,
                    SDL_Rect *p_couleur,
                    SDL_Rect *p_volume,
                    SDL_Rect *p_actif){
    //---DECLARATION---------------------------------------------------
    SDL_Surface *actif;
    char continuer=1, select=0, ok, reso, coul, vol;
    int o_largeur, o_hauteur, o_couleur, o_volume;
    SDL_Rect p_curseur, p_resoOk, p_coulOk, p_volOk, p_actOk;
    SDL_Event event;
    FSOUND_SAMPLE *clic;

    //----------------------------------------------------------------
    // Chargement des options
    ok = optionsLoad(&o_largeur, &o_hauteur, &o_couleur, &o_volume);
    if(ok != 1){
        fprintf(stderr, "Erreur de lecture des options [main.c]");
        exit(EXIT_FAILURE);
    }
    switch(o_largeur){
        case 1280:
            p_resoOk = p_resolution[0];
            reso = 0;
            break;
        case 1024:
            p_resoOk = p_resolution[1];
            reso = 1;
            break;
        case 800:
            p_resoOk = p_resolution[2];
            reso = 2;
            break;
        default:
            fprintf(stderr, "Erreur1 dans switch(o_largeur) [boucleOp.c]");
            exit(EXIT_FAILURE);
            break;
    }
    switch(o_couleur){
        case 32:
            p_coulOk = p_couleur[0];
            coul = 0;
            break;
        case 16:
            p_coulOk = p_couleur[1];
            coul = 1;
            break;
        default:
            fprintf(stderr, "Erreur2 dans switch(o_largeur) [boucleOp.c]");
            exit(EXIT_FAILURE);
            break;
    }
    switch(o_volume){
        case 0:
            p_volOk = p_volume[0];
            vol = 0;
            break;
        case 25:
            p_volOk = p_volume[1];
            vol = 1;
            break;
        case 50:
            p_volOk = p_volume[2];
            vol = 2;
            break;
        case 75:
            p_volOk = p_volume[3];
            vol = 3;
            break;
        case 100:
            p_volOk = p_volume[4];
            vol = 4;
            break;
        default:
            fprintf(stderr, "Erreur3 dans switch(o_largeur) [boucleOp.c]");
            exit(EXIT_FAILURE);
            break;
    }
    actif = IMG_Load(FILE_IMG_ACTIVE);
    p_actOk = p_actif[0];

    clic = FSOUND_Sample_Load(FSOUND_FREE, FILE_SOUND_CLIC, 0, 0, 0);

    //----------------------------------------------------------------
    //Premier affichage:
    SDL_BlitSurface(fondOptions, NULL, ecran, &p_fondOptions);
    SDL_BlitSurface(valide, NULL, ecran,&p_resoOk);
    SDL_BlitSurface(valide, NULL, ecran,&p_coulOk);
    SDL_BlitSurface(valide, NULL, ecran,&p_volOk);
    SDL_BlitSurface(actif, NULL, ecran, &p_actOk);
    SDL_Flip(ecran);

    //-----------------------------------------------------------------
    //Boucle Menu

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer=0;
                        break;
                    case SDLK_RETURN:
                        continuer=0;
                        break;
                    case SDLK_UP:
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        if(select==0)
                            select = 2;
                        else
                            select--;
                        break;
                    case SDLK_DOWN:
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        if(select==2)
                            select = 0;
                        else
                            select++;
                        break;
                    case SDLK_LEFT:
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        if(select==0)
                            if(reso==0)
                                reso = 2;
                            else
                                reso--;
                        else if(select==1)
                            if(coul==0)
                                coul = 1;
                            else
                                coul = 0;
                        else
                            if(vol==0)
                                vol = 4;
                            else
                                vol--;
                        break;
                    case SDLK_RIGHT:
                        FSOUND_PlaySound(FSOUND_FREE, clic);
                        if(select==0)
                            if(reso==2)
                                reso = 0;
                            else
                                reso++;
                        else if(select==1)
                            if(coul==1)
                                coul = 0;
                            else
                                coul = 1;
                        else
                            if(vol==4)
                                vol = 0;
                            else
                                vol++;
                        break;
                }
                break;
        }
        SDL_BlitSurface(fondOptions, NULL, ecran, &p_fondOptions);
        p_resoOk = p_resolution[reso];
        p_coulOk = p_couleur[coul];
        p_volOk = p_volume[vol];
        p_actOk = p_actif[select];
        SDL_BlitSurface(valide, NULL, ecran,&p_resoOk);
        SDL_BlitSurface(valide, NULL, ecran,&p_coulOk);
        SDL_BlitSurface(valide, NULL, ecran,&p_volOk);
        SDL_BlitSurface(actif, NULL, ecran, &p_actOk);
        SDL_Flip(ecran);
    }

    switch(reso){
        case 0:
            o_largeur = 1280;
            o_hauteur = 800;
            break;
        case 1:
            o_largeur = 1024;
            o_hauteur = 768;
            break;
        case 2:
            o_largeur = 800;
            o_hauteur = 600;
            break;
    }
    if(coul==0)
        o_couleur = 32;
    else
        o_couleur = 16;
    switch(vol){
        case 0:
            o_volume = 0;
            break;
        case 1:
            o_volume = 25;
            break;
        case 2:
            o_volume = 50;
            break;
        case 3:
            o_volume = 75;
            break;
        case 4:
            o_volume = 100;
            break;
    }

    // Sauvegarde options
    ok = optionsSave(o_largeur, o_hauteur, o_couleur, o_volume);

    FSOUND_Sample_Free(clic);
    SDL_FreeSurface(actif);
    return ok;
}




