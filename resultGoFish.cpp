
#include <iostream>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "resultGoFish.h"
#include "state.h"

using namespace std;

bool endConvo = false;
bool retry = false;
bool winner = false;;

resultGoFish_state::resultGoFish_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     rgf = IMG_Load("./gameImages/Talktogoatman.png");
     trgf = SDL_CreateTextureFromSurface(rend, rgf);
     SDL_FreeSurface(rgf);
     rgf = nullptr;
}

resultGoFish_state::~resultGoFish_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(trgf);
     trgf = nullptr;
}

bool resultGoFish_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
     dialogueLine = 0;
     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, trgf, nullptr, &imageRect); // display game image
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
     message = "";
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
     SDL_RenderCopy(rend, trgf, nullptr, &imageRect); // display overlay

     switch(winnerGoFish){
       case 't': // tied
         switch(dialogueLine){
           case 0:
           message = "We have tied. So close, but no cigar. We go again.";
           textColor = goatmanC;
           break;

           default: transition("goFishGUI"); break;
         }
         break;
       case 'c': // case computer wins
        switch(dialogueLine){
         case 0:
         message = "You have lost. The lights stay off until you beat me. Shall we?";
         textColor = goatmanC;
         break;

         default: transition("goFishGUI"); break;
        }
         break;
       case 'p': // case player wins
         switch(dialogueLine){
           case 0:
           message = "You have won. I will turn the lights back on.";
           textColor = goatmanC;
           break;

           case 1:
           message = "If you ever want to play another game fo go fish, come into the town and find me.";
           textColor = mothmanC;
           break;

           case 2:
           message = "Really?";
           textColor = goatmanC;
           break;

           case 3:
           message = "Go fish is fun, and so is looking at street lights.";
           textColor = mothmanC;
           break;

           case 4:
           message = "Thanks Investagator. I'll take you up on that offer.";
           textColor = goatmanC;
           winner = true;
           break;

           default: endConvo = true; break;
         } break;

       default: break;
     }
     stringColor(rend, textX, textY, message.c_str(), textColor);
     SDL_RenderPresent(rend);

     if(endConvo){
       transition("mothmanHome");
     }

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

                if(winner){
                  transition("mothmanHome");
                }

                dialogueLine++;
                result = true;
                break;
                default: break;
              }
    default:  break;
    }

    SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN + 1);

    return result;
}
