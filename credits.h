
#ifndef __CREDITS_H__
#define __CREDITS_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class credits_state : public state {
public:
    credits_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font);
    ~credits_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);
};

#endif  /* __CREDITS_H__ */
