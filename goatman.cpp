
#include <iostream>

#include <SDL.h>

#include "goatman.h"
#include "state.h"

using namespace std;

string gmessage;

goatman_state::goatman_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     g = IMG_Load("./gameImages/Talktogoatman.png");
     tg = SDL_CreateTextureFromSurface(rend, g);
     SDL_FreeSurface(g);
     g = nullptr;
}

goatman_state::~goatman_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tg);
     tg = nullptr;
}

bool goatman_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tg, nullptr, &imageRect); // display game image
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

bool goatman_state::leave() {
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

bool goatman_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool goatman_state::handle_event(const SDL_Event &e) {
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
                message = "Hello Boss.";
                gmessage = "Who are you?";
                message = "I'm Mothman P.I.";
                gmessage = "I wasn't aware I had an appointment tonight.";
                message = "I wasn't planning on being here tonight either, but the power in town is out. And I can't help but notice that you do.";
                gmessage = "Is that so? Living in a mountain mine system is quite isolating.";
                message = "So you didn't divert the power from the town to this mountain for your bitcoin mining?";
                gmessage = "How do you know about that?";
                message = "Everyone who comes to see you literally walks through your farming rig.";
                gmessage = "Oh yeah...";
                message = "So what are you doing with all that bitcoin?";
                gmessage = "I need it to be able to play in an online tournamant.";
                message = "A tournament?";
                gmessage = "A go fish tournament.";
                message = "You are farming bitcoin to be able to play go fish?";
                gmessage = "Yes.";
                message = "But the town needs power!";
                gmessage = "Tell you what, let's play a game of go fish, and if you win, I'll cut back on my farm and let power back to the town."
                message = "Let's play.";

                // transition to go fish


                result = true;
                break;
                default: break;

    default:  break;
    }

    return result;
}
