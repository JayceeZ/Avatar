#include "surface.h"
#include <SDL_image.h>

CSurface::CSurface() {}

SDL_Surface* CSurface::OnLoad(char File[]) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(File)) == NULL) {
        return NULL;
    }

    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}
