
#ifndef __INDINER_H__
#define __INDINER_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class indiner_state : public state {
public:
    indiner_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~indiner_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *id;
    SDL_Texture *tid;
};

#endif  /* __INDINER_H__ */
