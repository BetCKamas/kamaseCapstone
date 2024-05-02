
#ifndef __CREDITS_H__
#define __CREDITS_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class credits_state : public state {
public:
    credits_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font);
    ~credits_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);

    TTF_Font* font;

    SDL_Surface *c;
    SDL_Texture *tc;

    SDL_Color WHITE = {255, 255, 255};
    SDL_Color GREEN = {0, 255, 0};

    SDL_Surface* surfaceBackW;
    SDL_Surface* surfaceBackG;
    SDL_Texture* textureBackW;
    SDL_Texture* textureBackG;
    SDL_Surface* ms;
    SDL_Texture* mTs;
    SDL_Texture* tms;
    SDL_Surface* ns;
    SDL_Texture* tns;
    SDL_Surface* fs;
    SDL_Texture* fTs;
    SDL_Texture* tfs;
    SDL_Surface* is;
    SDL_Texture* iTws;
    SDL_Texture* iThs;
    SDL_Texture* iFs;
    SDL_Texture* tis;

    SDL_Rect backRect { 20, 10, w/8, h/10};

    bool bHover;

    string m = "Music: Detective Stories from Francesco";
    string mTwo = "Biondi (Free Groove) on Pixabay"; // https://pixabay.com/music/crime-scene-detective-stories-198357/
    string n = "Transition Noise: forestwalk from Pixabay"; // https://pixabay.com/sound-effects/forestwalk-92096/
    string f = "Menu Font: Cute Font by TypoDesign Lab. Inc";
    string fTwo = "on Google Fonts"; // https://fonts.google.com/specimen/Cute+Font
    string i = "Inspiration: Spy Fox by Humongeous";
    string iTwo = "Entertainment, Nancy Drew Game Franchise by";
    string iThree = "HER Interactive, and Frog Detective by";
    string iFour = "Grace Bruxner and Thomas Bowker.";

    SDL_Rect mr { 30, 20+h/10, w-70, 64};
    SDL_Rect mTr { 80, mr.y+40, w-240, 64};
    SDL_Rect nr { 30, mTr.y+100, w-70, 64};
    SDL_Rect fr { 30, nr.y+100, w-70, 64};
    SDL_Rect fTr { 80, fr.y+40, w-800, 64};
    SDL_Rect ir { 30, fTr.y+100, w-130, 64};
    SDL_Rect iTwr { 80, ir.y+40, w-120, 64};
    SDL_Rect iThr { 80, iTwr.y+40, w-220, 64};
    SDL_Rect iFr { 80, iThr.y+40, w-250, 64};
};

#endif  /* __CREDITS_H__ */
