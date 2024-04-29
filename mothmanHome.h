
#ifndef __MOTHMANHOME_H__
#define __MOTHMANHOME_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class mothmanHome_state : public state {
public:
    mothmanHome_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~mothmanHome_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *mh;
    SDL_Texture *tmh;

    SDL_Surface *mhl;
    SDL_Texture *tmhl;

    SDL_Surface *te;
    SDL_Texture *tte;
};

#endif  /* __MOTHMANHOME_H__ */
