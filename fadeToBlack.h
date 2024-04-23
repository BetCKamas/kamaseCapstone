
#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class fadeToBlack_state : public state {
public:
    fadeToBlack_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~fadeToBlack_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface* rectSurface;
    SDL_Texture* rectTexture[4];
    SDL_Rect rect = imageRect;

};

#endif  /* __FADETOBLACK_H__ */
