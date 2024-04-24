
#ifndef __RESULTGOFISH_H__
#define __RESULTGOFISH_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class resultGoFish_state : public state {
public:
    resultGoFish_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~resultGoFish_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *rgf;
    SDL_Texture *trgf;
};

#endif  /* __RESULTGOFISH_H__ */
