#include <SDL.h>
#include <SDL_ttf.h>

#include "state.h"

state::state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) {
    this->rend = rend;
    this->win = win;
    this->s = s;
    this->to = to;
    this->font = font;
    SDL_GetRendererOutputSize(rend, &w, &h);

    rectSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    /*
    imageRect.x = 42;
    imageRect.y = 30;
    imageRect.w = 1112;
    imageRect.h = 510;
    */
}

state::~state() {
  SDL_FreeSurface(rectSurface);
}
