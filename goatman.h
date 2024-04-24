
#ifndef __GOATMAN_H__
#define __GOATMAN_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class goatman_state : public state {
public:
    goatman_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~goatman_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *g;
    SDL_Texture *tg;
};

#endif  /* __GOATMAN_H__ */
