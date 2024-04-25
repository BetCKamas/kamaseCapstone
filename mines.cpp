
#include <iostream>

#include <SDL.h>

#include "mines.h"
#include "state.h"

using namespace std;

string hench_message;

mines_state::mines_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     mi = IMG_Load("./gameImages/Maze.png");
     tmi = SDL_CreateTextureFromSurface(rend, mi);
     SDL_FreeSurface(mi);
     mi = nullptr;
}

mines_state::~mines_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tmi);
     tmi = nullptr;
}

bool mines_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tmi, nullptr, &imageRect); // display game image
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

bool mines_state::leave() {
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

bool mines_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool mines_state::handle_event(const SDL_Event &e) {
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
                // entering cave for the first time
                hench_message = "HALT! Who goes there?";
                message = "Uhh, it is I, Mothman P.I.";
                hench_message = "Who? I've never heard of you.";
                message = "Well now you have.";
                hench_message = "What is your purpose here?";
                message = "I'm investigating why the power went out in town. Would you happen to know anything about that?";
                hench_message = "I don't know anything about what the boss is doing?";
                message = "That wasn't the question I asked.";
                hench_message = "Uhh";
                message = "What's your boss up to?";
                hench_message = "Nothing at all. Definetly not anything to do with why the power is out.";
                message = "Yeah, OK, I don't believe you.";
                hench_message = "Why not? I'm a very believable person.";
                message = "That's not the vibe I'm picking up on.";
                hench_message = "How dare you harsh my vibe.";
                message = "OK, I'm just going to take a look around then.";
                hench_message = "OK, but yoy can't go past me.";
                message = "Why not?";
                hench_message = "Boss's orders.";
                message = "Dude you are so suspisious.";
                hench_message = "I'm just doing my job.";
                message = "Well what would it take to get past you.";
                hench_message = "I'm not allowed to let anyone past who doesn't haved an appointment.";
                message = "How do I make an appointment?";
                hench_message = "That's above my paygrade.";
                message = "So if I get an appointment, you'll let me past?";
                hench_message = "Correct.";
                message = "Actually I have an appointment";
                hench_message = "OK, please show me your appointment card.";
                message = "Appointment card?";
                hench_message = "Yes we give out appointment cards. You show me yours and I'll let you past.";
                message = "Oh silly me, I must have left it in my other coat. I'll go fetch it.";

                // Trying to get the henchman to move without having item
                message = "I can't go back up to him without an appointment card. Maybe I can find one someplace.";

                // going back with appointment card
                message = "Here it is, my appointment card.";
                hench_message = "Let me see.";
                hench_message = "Yes this will do. You can go past.";
                
                // immediately transition to maze

                result = true;
                break;
                default: break;
              }
    default:  break;
    }

    return result;
}
