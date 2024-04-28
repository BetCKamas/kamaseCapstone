
#ifndef __BIGFOOT_H__
#define __BIGFOOT_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class bigfoot_state : public state {
public:
    bigfoot_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~bigfoot_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    SDL_Surface *b;
    SDL_Texture *tb;

    SDL_Rect moveBackMAR {imageRect.x, imageRect.y+350, imageRect.w, imageRect.h-350};
    SDL_Rect bigfootR {imageRect.x+682, imageRect.y, 218, 300};

};

#endif  /* __BIGFOOT_H__ */
