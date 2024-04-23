
#ifndef __MENU_H__
#define __MENU_H__

#include <SDL.h>
#include <SDL_ttf.h>

#include "state.h"

using namespace std;

class menu_state : public state {
public:
    menu_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~menu_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    bool pHover, cHover;

    TTF_Font* font;

    SDL_Color WHITE = {255, 255, 255};
    SDL_Color GREEN = {0, 255, 0};
    SDL_Surface* surfaceMessage;
    SDL_Surface* surfaceSubMessage;
    SDL_Surface* surfacePlayBtnW;
    SDL_Surface* surfacePlayBtnG;
    SDL_Surface* surfaceCreditsW;
    SDL_Surface* surfaceCreditsG;


    SDL_Texture* Message;
    SDL_Texture* subMessage;
    SDL_Texture* texturePlayBtnW;
    SDL_Texture* texturePlayBtnG;
    SDL_Texture* textureCreditsW;
    SDL_Texture* textureCreditsG;

    SDL_Rect Message_rect;
    SDL_Rect subHeading;
    SDL_Rect playBtn;
    SDL_Rect credits;

    SDL_Surface *ts = nullptr;
    SDL_Texture *tts = nullptr;

};

#endif  /* __MENU_H__ */
