#include <SDL.h>
#include <SDL_ttf.h>

#include "state.h"

state::state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font) {
    this->rend = rend;
    this->win = win;
    this->s = s;
    this->font = font;
    SDL_GetRendererOutputSize(rend, &w, &h);

    imageRect.x = 42;
    imageRect.y = 30;
    imageRect.w = 1112;
    imageRect.h = 510;
}

state::~state() {
}
