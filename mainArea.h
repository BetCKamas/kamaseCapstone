
#ifndef __MAINAREA_H__
#define __MAINAREA_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class mainArea_state : public state {
public:
    mainArea_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~mainArea_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *ma = nullptr;
    SDL_Texture *tma = nullptr;

};

#endif  /* __MAINAREA_H__ */
