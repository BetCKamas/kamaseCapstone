
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "credits.h"
#include "state.h"

using namespace std;

credits_state::credits_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

      c = IMG_Load("./gameImages/credits.png");
      tc = SDL_CreateTextureFromSurface(rend, c);
      SDL_FreeSurface(c);
      c = nullptr;

      surfaceBackW = TTF_RenderText_Solid(font, "BACK", WHITE);
      surfaceBackG = TTF_RenderText_Solid(font, "BACK", GREEN);
      textureBackW = SDL_CreateTextureFromSurface(rend, surfaceBackW);
      SDL_FreeSurface(surfaceBackW);
      textureBackG = SDL_CreateTextureFromSurface(rend, surfaceBackG);
      SDL_FreeSurface(surfaceBackG);

      ms = TTF_RenderText_Solid(font, m.c_str(), WHITE);
      tms = SDL_CreateTextureFromSurface(rend, ms);
      SDL_FreeSurface(ms);
      ms = nullptr;

      ms = TTF_RenderText_Solid(font, mTwo.c_str(), WHITE);
      mTs = SDL_CreateTextureFromSurface(rend, ms);
      SDL_FreeSurface(ms);
      ms = nullptr;

      ns = TTF_RenderText_Solid(font, n.c_str(), WHITE);
      tns = SDL_CreateTextureFromSurface(rend, ns);
      SDL_FreeSurface(ns);
      ns = nullptr;

      fs = TTF_RenderText_Solid(font, f.c_str(), WHITE);
      tfs = SDL_CreateTextureFromSurface(rend, fs);
      SDL_FreeSurface(fs);
      fs = nullptr;

      fs = TTF_RenderText_Solid(font, fTwo.c_str(), WHITE);
      fTs = SDL_CreateTextureFromSurface(rend, fs);
      SDL_FreeSurface(fs);
      fs = nullptr;

      is = TTF_RenderText_Solid(font, i.c_str(), WHITE);
      tis = SDL_CreateTextureFromSurface(rend, is);
      SDL_FreeSurface(is);
      is = nullptr;

      is = TTF_RenderText_Solid(font, iTwo.c_str(), WHITE);
      iTws = SDL_CreateTextureFromSurface(rend, is);
      SDL_FreeSurface(is);
      is = nullptr;

      is = TTF_RenderText_Solid(font, iThree.c_str(), WHITE);
      iThs = SDL_CreateTextureFromSurface(rend, is);
      SDL_FreeSurface(is);
      is = nullptr;

      is = TTF_RenderText_Solid(font, iFour.c_str(), WHITE);
      iFs = SDL_CreateTextureFromSurface(rend, is);
      SDL_FreeSurface(is);
      is = nullptr;

}

credits_state::~credits_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tc);
     tc = nullptr;

     SDL_DestroyTexture(textureBackG);
     textureBackG = nullptr;

     SDL_DestroyTexture(textureBackW);
     textureBackW = nullptr;

     SDL_DestroyTexture(tms);
     tms = nullptr;

     SDL_DestroyTexture(tns);
     tns = nullptr;

     SDL_DestroyTexture(tfs);
     tfs = nullptr;

     SDL_DestroyTexture(tis);
     tis = nullptr;
}

bool credits_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool credits_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool credits_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tc, nullptr, nullptr); // display overlay

    int MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);

    bHover = checkCollision(MouseX, MouseY, backRect);
    if(bHover){
      SDL_RenderCopy(rend, textureBackG, NULL, &backRect);
    } else {
      SDL_RenderCopy(rend, textureBackW, NULL, &backRect);
    }

    SDL_RenderCopy(rend, tms, NULL, &mr);
    SDL_RenderCopy(rend, mTs, NULL, &mTr);
    SDL_RenderCopy(rend, tns, NULL, &nr);
    SDL_RenderCopy(rend, tfs, NULL, &fr);
    SDL_RenderCopy(rend, fTs, NULL, &fTr);
    SDL_RenderCopy(rend, tis, NULL, &ir);
    SDL_RenderCopy(rend, iTws, NULL, &iTwr);
    SDL_RenderCopy(rend, iThs, NULL, &iThr);
    SDL_RenderCopy(rend, iFs, NULL, &iFr);


    SDL_RenderPresent(rend);
    return true;
}

bool credits_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
      case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button){
  			     case SDL_BUTTON_LEFT:
                if(bHover){
                  transition("menu"); result = true;; break;
                }

  		  } break;

    default:  break;
    }

    return result;
}
