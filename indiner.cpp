
#include <iostream>

#include <SDL.h>

#include "indiner.h"
#include "state.h"

using namespace std;

indiner_state::indiner_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     id = IMG_Load("./gameImages/Indiner.png");
     tid = SDL_CreateTextureFromSurface(rend, id);
     SDL_FreeSurface(id);
     id = nullptr;
}

indiner_state::~indiner_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tid);
     tid = nullptr;
}

bool indiner_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tid, nullptr, &imageRect); // display game image
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

bool indiner_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */

   for(int i = 0; i < 67; i++){
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

bool indiner_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool indiner_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {

    default:  break;
    }

    return result;
}
