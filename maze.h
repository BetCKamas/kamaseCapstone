
#ifndef __MAZE_H__
#define __MAZE_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class maze_state : public state {
public:
    maze_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~maze_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *ma;
    SDL_Texture *tma;
};

#endif  /* __MAZE_H__ */
