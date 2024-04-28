
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

    SDL_Surface *h = nullptr;
    SDL_Surface *ac = nullptr;
    SDL_Surface *f = nullptr;


    SDL_Rect woodsR {imageRect.x, (imageRect.y + (imageRect.h / 3)), imageRect.w/6, imageRect.h/5};
    SDL_Rect dinerR {imageRect.x + (imageRect.w/3) - 25, (imageRect.y + 2*(imageRect.h / 5) + 25), imageRect.w/3, imageRect.h/4};
    SDL_Rect minesR {dinerR.x+dinerR.w+25, imageRect.y+(imageRect.h/3)-15, imageRect.w/8, imageRect.h/3};


};

#endif  /* __MAINAREA_H__ */
