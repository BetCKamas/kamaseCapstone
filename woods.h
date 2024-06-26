
#ifndef __WOODS_H__
#define __WOODS_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class woods_state : public state {
public:
    woods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~woods_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *w;
    SDL_Texture *tw;

    SDL_Surface *e;
    SDL_Texture *te;

    SDL_Rect eyesR {imageRect.x+240, imageRect.y+140, 150, 47};

    SDL_Rect moveBackPathR {imageRect.x + imageRect.w - imageRect.w/5, imageRect.y, imageRect.w/5, imageRect.h};

};

#endif  /* __WOODS_H__ */
