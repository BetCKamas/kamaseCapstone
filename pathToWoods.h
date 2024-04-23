
#ifndef __PATHTOWOODS_H__
#define __PATHTOWOODS_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class pathToWoods_state : public state {
public:
    pathToWoods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~pathToWoods_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);
};

#endif  /* __PATHTOWOODS_H__ */
