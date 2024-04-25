
#include <iostream>

#include <SDL.h>

#include "bigfoot.h"
#include "state.h"

using namespace std;

string bmessage;

bigfoot_state::bigfoot_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     b = IMG_Load("./gameImages/Bigfoottalk.png");
     tb = SDL_CreateTextureFromSurface(rend, b);
     SDL_FreeSurface(b);
     b = nullptr;
}

bigfoot_state::~bigfoot_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

    SDL_DestroyTexture(tb);
    tb = nullptr;
}

bool bigfoot_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tb, nullptr, &imageRect); // display game image
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

bool bigfoot_state::leave() {
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

bool bigfoot_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool bigfoot_state::handle_event(const SDL_Event &e) {
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
                // entering for the first time
                bmessage = "Welcome to Big's. With this power outage we can't offer too much off the menu right now.";
                message = "Oh thats ok, I'm not hungry right now. I just wanted to ask you some questions if that's alright.";
                bmessage = "Questions? What kind of questions?";
                message = "About the power outage.";
                bmessage = "Oh. Theres not much to say really. I was doing some prep working making some bread when the power went.";
                message = "Breadmaking? That's a difficult art to conquer.";
                bmessage = "Secret family recipe. Tradition has been passed down within my family.";
                bmessage = "Lucky for me, bread dough can rise without the power.";
                message = "So you know nothing about the power outage?";
                bmessage = "Nothin.";
                message = "OK, well thank youu for your time."
                bmessage = "Come back any time."

                // coming back for smore
                bmessage = "Welcome back, what can I do ya for";
                message = "Do you by any chance have any smore ingredients?";
                bmessage = "I do.";
                message = "Can I have enough for one smore?";
                bmessage = "Tell you what kid. I am in need of some honey for my bread. You get me some honey, I'll give you one smore. You'll need to toast it yourself.";
                message = "Deal, I'll be back with the honey.";

                // coming back in without honey
                bmessage = "You ready for the honey-smore trade?";
                message = "Not yet, I'll be back.";

                // coming back with honey
                bmessage = "You ready for the honey-smore trade?";
                message = "Here you go";
                bmessage = "*sniff* *sniff*"
                bmessage = "This is some good fresh honey. Its perfect for my bread. Thanks kid, here's your smore.";

                result = true;
                break;
                default: break;

    default:  break;
    }

    return result;
}
