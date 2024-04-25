
#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "resultGoFish.h"
#include "state.h"

using namespace std;

resultGoFish_state::resultGoFish_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
}

resultGoFish_state::~resultGoFish_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool resultGoFish_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
     for(int i = 67; i > 0; i--){
         //cout << "alpha" << endl;
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         //SDL_RenderCopy(rend, tgt, nullptr, &imageRect); // display game image
         Uint8 a =  Uint8(i*2);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_BLEND);
         SDL_SetSurfaceAlphaMod(rectSurface, a);
         SDL_FillRect(rectSurface, NULL, SDL_MapRGBA(rectSurface->format, 0, 0, 0, a));
         rectTexture[i] = SDL_CreateTextureFromSurface(rend, rectSurface);
         SDL_RenderCopy(rend, rectTexture[i], NULL, &imageRect);
         SDL_RenderPresent(rend);
         SDL_Delay(5);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_NONE);
         SDL_DestroyTexture(rectTexture[i]);
     }
     return true;
}

bool resultGoFish_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
     for(int i = 0; i < 67; i++){
         //cout << "alpha" << endl;
         Uint8 a =  Uint8(i*2);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_BLEND);
         SDL_SetSurfaceAlphaMod(rectSurface, a);
         SDL_FillRect(rectSurface, NULL, SDL_MapRGBA(rectSurface->format, 0, 0, 0, a));
         rectTexture[i] = SDL_CreateTextureFromSurface(rend, rectSurface);
         SDL_RenderCopy(rend, rectTexture[i], NULL, &imageRect);
         SDL_RenderPresent(rend);
         SDL_Delay(5);
         SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_NONE);
         SDL_DestroyTexture(rectTexture[i]);
     }

     return true;
}

bool resultGoFish_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

     SDL_RenderClear(rend);
     SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay

     switch(winnerGoFish){
       case 't': // tied
         SDL_SetRenderDrawColor(rend, (Uint8)0x00, (Uint8)0x00, (Uint8)0xFF, 0xFF);
         message = "We have tied. So close, but no cigar. Are you ready to try again?";
         break;
       case 'c': // case computer wins
         SDL_SetRenderDrawColor(rend, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0x00, 0xFF);
         message = "You have lost. The lights stay off until you beat me. Are you ready to try again?";
         break;
       case 'p': // case player wins
         SDL_SetRenderDrawColor(rend, (Uint8)0xFF, (Uint8)0xA5, (Uint8)0x00, 0xFF);
         message = "You have won. I will turn the lights back on.";
         break;
       default: break;
     }
     textColor = GREEN;
     SDL_RenderFillRect(rend, &imageRect);
     stringColor(rend, textX, textY, message.c_str(), textColor);
     SDL_RenderPresent(rend);

     return true;
}

bool resultGoFish_state::handle_event(const SDL_Event &e) {
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
                // if won go to mainArea with light on and then to mothmanHome
                // if lost or tied go back to gofishgui

                result = true;
                break;
    default:  break;
    }

    return result;
}
