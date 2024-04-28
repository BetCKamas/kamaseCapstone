
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

    SDL_Surface *ptw;
    SDL_Texture *tptw;

    SDL_Rect moveIntoWoodsR {imageRect.x, imageRect.y, imageRect.w/5, imageRect.h};
    SDL_Rect moveBackDR {imageRect.x + imageRect.w - imageRect.w/5, imageRect.y, imageRect.w/5, imageRect.h};
    SDL_Rect beesR {imageRect.x+360, imageRect.y+165, 100, 110};
};

#endif  /* __PATHTOWOODS_H__ */
