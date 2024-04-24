
#ifndef __MINES_H__
#define __MINES_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class mines_state : public state {
public:
    mines_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~mines_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *mi;
    SDL_Texture *tmi;
};

#endif  /* __MINES_H__ */
