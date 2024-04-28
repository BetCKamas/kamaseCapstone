
#include <iostream>

#include <SDL.h>

#include "goatman.h"
#include "state.h"

using namespace std;

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
     dialogueLine = 0;
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

   message = "";

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

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
    SDL_RenderCopy(rend, tg, nullptr, &imageRect); // display game image


    switch(dialogueLine){
         case 0:
         message = "Hello...Boss is it?";
         textColor = mothmanC;
         break;

         case 1:
         message = "Who are you?";
         textColor = goatmanC;
         break;

         case 2:
         message = "I'm Mothman P.I.";
         textColor = mothmanC;
         break;

         case 3:
         message = "I wasn't aware I had an appointment tonight.";
         textColor = goatmanC;
         break;

         case 4:
         message = "I wasn't planning on being here tonight either, but the power in town is out. And I can't";
         textColor = mothmanC;
         stringColor(rend, textX, textY+15, "help but notice that you have power right now.", textColor);
         break;

         case 5:
         message = "Is that so? Living in a mountain mine system is quite isolating.";
         textColor = goatmanC;
         break;

         case 6:
         message = "So you didn't divert the power from the town to this mountain for your bitcoin mining?";
         textColor = mothmanC;
         break;

         case 7:
         message = "How do you know about that?";
         textColor = goatmanC;
         break;

         case 8:
         message = "Everyone who comes to see you literally walks through your farming rig.";
         textColor = mothmanC;
         break;

         case 9:
         message = "Oh yeah...";
         textColor = goatmanC;
         break;

         case 10:
         message = "So what are you doing with all that bitcoin?";
         textColor = mothmanC;
         break;

         case 11:
         message = "I need it to be able to play in an online tournamant.";
         textColor = goatmanC;
         break;

         case 12:
         message = "A tournament?";
         textColor = mothmanC;
         break;

         case 13:
         message = "A go fish tournament.";
         textColor = goatmanC;
         break;

         case 14:
         message = "You are farming bitcoin to be able to play go fish?";
         textColor = mothmanC;
         break;

         case 15:
         message = "Yes.";
         textColor = goatmanC;
         break;

         case 16:
         message = "But the town needs power!";
         textColor = mothmanC;
         break;

         case 17:
         message = "Tell you what, let's play a game of go fish, and if you win, I'll cut back on my farm and";
         textColor = goatmanC;
         stringColor(rend, textX, textY+15, "let power back to the town.", textColor);
         break;

         case 18:
         message = "You'll cut back on your farming if I play you in go fish?";
         textColor = mothmanC;
         break;

         case 19:
         message = "And win, yes.";
         textColor = goatmanC;
         break;

         case 20:
         message = "OK, I'll play you.";
         textColor = mothmanC;
         transition("goFishGUI");
         break;



         default: break;
       }


    stringColor(rend, textX, textY, message.c_str(), textColor);
    SDL_RenderPresent(rend);
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
      case SDL_KEYDOWN:
          switch(e.key.keysym.sym) {
          case SDLK_SPACE:  transition("goFishGUI"); result = true;   break;
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
