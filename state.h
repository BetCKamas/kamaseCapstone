#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <map>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool transition(std::string s);
bool checkCollision(int MouseX, int MouseY, SDL_Rect a);

class state {
public:
    SDL_Renderer *rend;
	  SDL_Window *win;
	  SDL_Surface *s;
    SDL_Texture *to;
    TTF_Font *font;
    SDL_Rect imageRect {42, 30, 1112, 510};

    SDL_Surface* rectSurface;
    SDL_Texture* rectTexture[67];
    SDL_Rect rect = imageRect;

    int textX = 35;
    int textY = 590;

    int w;
    int h;


    std::string message;
    const Uint32 mothmanC = (Uint32)0x964B00ff;
    const Uint32 bigfootC = (Uint32)0xff8080ff;
    const Uint32 eyesC = (Uint32)0xff064228;
    const Uint32 goatmanC = (Uint32)0xffff0000;
    const Uint32 henchmanC = (Uint32)0xffff9f00;
    Uint32 textColor;

    int dialogueLine = 0;



    state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~state();

    virtual bool enter() = 0;
    virtual bool leave() = 0;
    virtual bool draw() = 0;
    virtual bool handle_event(const SDL_Event &e) = 0;
};

extern std::map <std::string, state *>states;
extern char winnerGoFish;


#endif  /* __STATE_H__ */
