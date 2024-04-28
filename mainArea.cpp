
#include <iostream>
#include <cstdlib>

#include <SDL.h>

#include "mainArea.h"
#include "state.h"

using namespace std;

bool firstVisitMA = false;

mainArea_state::mainArea_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

    dialogueLine = 0;
    firstVisitMA = true;

    ma = IMG_Load("./gameImages/MainArea.png");
    tma = SDL_CreateTextureFromSurface(rend, ma);
    SDL_FreeSurface(ma);
    ma = nullptr;

}

mainArea_state::~mainArea_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

    SDL_DestroyTexture(tma);
    tma = nullptr;


    IMG_Quit();
}

bool mainArea_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
     for(int i = 67; i > 0; i--){
         //cout << "alpha" << endl;
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tma, nullptr, &imageRect); // display game image
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

bool mainArea_state::leave() {
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

bool mainArea_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

     SDL_RenderClear(rend);
     SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
     SDL_RenderCopy(rend, tma, nullptr, &imageRect); // display game image

     textColor = mothmanC;

     if(firstVisitMA){
       stringColor(rend, textX, textY, "The lights are out here too. I wonder whats going on.", textColor);
       stringColor(rend, textX, textY+15, "A mystery is afoot. I should investigate and find out why.", textColor);
     }

     SDL_RenderPresent(rend);
     return true;
}

bool mainArea_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
      case SDL_KEYDOWN:
          switch(e.key.keysym.sym) {
          case SDLK_SPACE:  transition("bigfoot"); firstVisitMA = false; result = true;   break;
          default:  break;
        } break;

        case SDL_MOUSEBUTTONDOWN:
          switch (e.button.button){
               case SDL_BUTTON_LEFT:
                  dialogueLine++;
                  result = true;
                  break;
                  default: break;
          }
    default:  break;
    }

    return result;
}
