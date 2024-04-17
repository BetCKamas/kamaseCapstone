#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

bool transition(std::string s);
bool checkCollision(int MouseX, int MouseY, SDL_Rect a);

class state {
public:
    SDL_Renderer *rend;
	  SDL_Window *win;
	  SDL_Surface *s;
    TTF_Font *font;
    SDL_Rect imageRect;
    int textX = 35;
    int textY = 590;

    int w;
    int h;


    state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font);
    ~state();

    virtual bool enter() = 0;
    virtual bool leave() = 0;
    virtual bool draw() = 0;
    virtual bool handle_event(const SDL_Event &e) = 0;
};

extern std::map <std::string, state *>states;


#endif  /* __STATE_H__ */
