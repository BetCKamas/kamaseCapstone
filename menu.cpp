
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "menu.h"
#include "state.h"

using namespace std;

bool checkCollision(int MouseX, int MouseY, SDL_Rect a) {
    if (a.x + a.w >= MouseX && a.x <= MouseX && a.y + a.h >= MouseY && a.y <= MouseY) {
        return true;
    }
    return false;
}

menu_state::menu_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font) : state(rend, win, s, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

    Message_rect.x = w/4; // X coordinate
    Message_rect.y = 0; // Y coordinate
    Message_rect.w = w/2; // Width
    Message_rect.h = h/5; // Height

    subHeading.x = w/4 + Message_rect.w/6;
    subHeading.y = Message_rect.h - 30;
    subHeading.w = w/3;
    subHeading.h = 50;

    playBtn.x = w/6 - 20;
    playBtn.y = h - h/6;
    playBtn.w = w/4;
    playBtn.h = h/5;

    credits.x = w - playBtn.w  - w/6;
    credits.y = playBtn.y;
    credits.w = playBtn.w + 32;
    credits.h = playBtn.h;

    surfaceMessage = TTF_RenderText_Solid(font, "Mothman P.I.", WHITE);
    surfaceSubMessage = TTF_RenderText_Solid(font, "in Blackout City", WHITE);
    surfacePlayBtnW = TTF_RenderText_Solid(font, "PLAY", WHITE);
    surfacePlayBtnG = TTF_RenderText_Solid(font, "PLAY", GREEN);
    surfaceCreditsW = TTF_RenderText_Solid(font, "CREDITS", WHITE);
    surfaceCreditsG = TTF_RenderText_Solid(font, "CREDITS", GREEN);

    Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
    subMessage = SDL_CreateTextureFromSurface(rend, surfaceSubMessage);
    texturePlayBtnW = SDL_CreateTextureFromSurface(rend, surfacePlayBtnW);
    texturePlayBtnG = SDL_CreateTextureFromSurface(rend, surfacePlayBtnG);
    textureCreditsW = SDL_CreateTextureFromSurface(rend, surfaceCreditsW);
    textureCreditsG = SDL_CreateTextureFromSurface(rend, surfaceCreditsG);

    ts = IMG_Load("TitleScreen.png");
    tts = SDL_CreateTextureFromSurface(rend, ts);
    SDL_FreeSurface(ts);
    ts = nullptr;
}

menu_state::~menu_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
     SDL_FreeSurface(surfaceMessage);
     SDL_DestroyTexture(Message);

     SDL_FreeSurface(surfaceSubMessage);
     SDL_DestroyTexture(subMessage);

     SDL_FreeSurface(surfacePlayBtnW);
     SDL_DestroyTexture(texturePlayBtnW);

     SDL_FreeSurface(surfacePlayBtnG);
     SDL_DestroyTexture(texturePlayBtnG);

     SDL_FreeSurface(surfaceCreditsW);
     SDL_DestroyTexture(textureCreditsW);

     SDL_FreeSurface(surfaceCreditsG);
     SDL_DestroyTexture(textureCreditsG);

     SDL_DestroyTexture(tts);
     tts = nullptr;

     TTF_Quit();
     IMG_Quit();

}

bool menu_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool menu_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool menu_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tts, nullptr, nullptr); // display overlay
    SDL_SetRenderDrawColor(rend, 0xFF, 0xA5, 0x00, 0xFF);

    int MouseX, MouseY;

    SDL_GetMouseState(&MouseX, &MouseY);

    SDL_RenderCopy(rend, Message, NULL, &Message_rect);
    SDL_RenderCopy(rend, subMessage, NULL, &subHeading);

    pHover = checkCollision(MouseX, MouseY, playBtn);
    if(pHover){
      SDL_RenderCopy(rend, texturePlayBtnG, NULL, &playBtn);
    } else {
      SDL_RenderCopy(rend, texturePlayBtnW, NULL, &playBtn);
      pHover = false;
    }

    cHover = checkCollision(MouseX, MouseY, credits);
    if(cHover) {
      SDL_RenderCopy(rend, textureCreditsG, NULL, &credits);
    } else {
      SDL_RenderCopy(rend, textureCreditsW, NULL, &credits);
      cHover = false;
    }
    SDL_RenderPresent(rend);

    return true;
}

bool menu_state::handle_event(const SDL_Event &e) {
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
                if(cHover){
                  transition("credits"); result = true;; break;
                }
                if(pHover){
                  transition("mainArea"); result = true;; break;
                }
  		  } break;

    default:  break;
    }

    return result;
}
