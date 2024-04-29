
#include <iostream>

#include <SDL.h>

#include "mothmanHome.h"
#include "state.h"

using namespace std;

bool beginning;

mothmanHome_state::mothmanHome_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     mh = IMG_Load("./gameImages/Mothmanhome.png");
     tmh = SDL_CreateTextureFromSurface(rend, mh);
     SDL_FreeSurface(mh);
     mh = nullptr;

     mhl = IMG_Load("./gameImages/Mothmanhomelight.png");
     tmhl = SDL_CreateTextureFromSurface(rend, mhl);
     SDL_FreeSurface(mhl);
     mhl = nullptr;

     te = IMG_Load("./gameImages/TheEnd.png");
     tte = SDL_CreateTextureFromSurface(rend, te);
     SDL_FreeSurface(te);
     te = nullptr;

     beginning = true;
}

mothmanHome_state::~mothmanHome_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tmh);
     tmh = nullptr;

     SDL_DestroyTexture(tmhl);
     tmhl = nullptr;
}

bool mothmanHome_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tmhl, nullptr, &imageRect); // display game image
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

     dialogueLine = 0;

     return true;
}

bool mothmanHome_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */

   for(int i = 0; i < 67; i++){
       Uint8 a =  Uint8(i*2);
       SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_BLEND);
       SDL_SetSurfaceAlphaMod(rectSurface, a);
       SDL_FillRect(rectSurface, NULL, SDL_MapRGBA(rectSurface->format, 0, 0, 0, a));
       rectTexture[i] = SDL_CreateTextureFromSurface(rend, rectSurface);
       SDL_RenderCopy(rend, rectTexture[i], NULL, NULL);
       SDL_RenderPresent(rend);
       SDL_Delay(5);
       SDL_SetSurfaceBlendMode(rectSurface, SDL_BLENDMODE_NONE);
       SDL_DestroyTexture(rectTexture[i]);
   }
   return true;
}

bool mothmanHome_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

     SDL_GetMouseState(&MouseX, &MouseY);

     SDL_RenderClear(rend);
     SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
     if(dialogueLine == 0)
        SDL_RenderCopy(rend, tmhl, nullptr, &imageRect); // display game image
     else
        SDL_RenderCopy(rend, tmh, nullptr, &imageRect); // display game image

     if(beginning){
         switch(dialogueLine){
           case 0:
             message = "What a long day. Some relaxation is much needed.";
             break;
           case 1:
             message = "*electricity pops*";
             break;
           case 2:
             message = "Huh? What? No.";
             break;
           case 3:
             message = "Where? Where is my light?";
             break;
           case 4:
             message = "I guess I could go into town tonight. Theres a nice street lamp next to Big's restaurant";
             break;

           defualt: break;

         }
       } else {
            switch(dialogueLine){
              case 1:
                SDL_RenderCopy(rend, tte, nullptr, &imageRect);
                break;
              case 2:
                transition("menu");
                break;

              default:
              SDL_RenderCopy(rend, tmhl, nullptr, &imageRect);
              message = "Ahh, lamp.";
              break;
            }
       }

     textColor = mothmanC;

     stringColor(rend, textX, textY, message.c_str(), textColor);
     SDL_RenderPresent(rend);

     return true;
}

bool mothmanHome_state::handle_event(const SDL_Event &e) {
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
                dialogueLine++;
                if(dialogueLine == 5){
                  beginning = false;
                  transition("mainArea");
                }
                result = true;
                break;
  		  } break;
    default:  break;
    }

    return result;
}
