
#include <iostream>

#include <SDL.h>

#include "woods.h"
#include "state.h"

using namespace std;

string eyes_message;

woods_state::woods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     w = IMG_Load("./gameImages/woods.png");
     tw = SDL_CreateTextureFromSurface(rend, w);
     SDL_FreeSurface(w);
     w = nullptr;
}

woods_state::~woods_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

     SDL_DestroyTexture(tw);
     tw = nullptr;
}

bool woods_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */

     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tw, nullptr, &imageRect); // display game image
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

bool woods_state::leave() {
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

bool woods_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool woods_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
      case SDL_BUTTON_LEFT:
         message = "A campfire? But whose? I don't see anyone.";
         eyes_message = "Hello";
         message = "AHHH!";
         eyes_message = "Sorry, I like the warmth from the fire but I like to stay in the dark tree line.";
         message = "Phew. I was worried that you were a human camper.";
         eyes_message = "How do you know I'm not a human camper?";
         message = "I don't think human campers are cool enough to be a pair of red eyes without a body.";
         eyes_message = "*blushing*";
         eyes_message = "Yeah you right";
         message = "But you should be careful though. We dont need a forest fire to occur.";
         eyes_message = "Yes, yes, of course. But what are you doing out here? I've never seen you here before...";
         message = "Right. I'm investigating why the power has gone out in town.";
         eyes_message = "And you thought the best place to figure that out was the forest?";
         message = "As an investigator you must leave no stones unturned.";
         eyes_message = "There are a lot of stones out here.";
         message = "Riiiiigggght. Can I ask you some questions?";
         eyes_message = "First you need to do something for me.";
         message = "And what would that be?";
         eyes_message = "I want a smore.";
         message = "You setup a campfire, but forgot to get ingredients for smores?";
         eyes_message = "Normally I just want the warmth, but I have a rather large hankering for a smore. Talking makes me peckish.";
         message = "I'll get you a smore and then you'll answer my questions, deal?";
         eyes_message =  "Deal.";
         message = "OK, I'll be back with your smore.";

         // coming back to talk agin but no smores
         eyes_message = "You have my smore yet?";
         message = "Not yet. I'll be back.";

         // after getting smore from bigfoot
         message = "Heres your smore.";
         eyes_message = "MMH! Delicious.";
         message = "So you'll answer my questions now?";
         eyes_message = "A deals a deal. What do you want to know?";
         message = "Did you cause the power outage?";
         eyes_message = "You yourself said that I have no body.";
         message = "That doesn't mean you didn't do it. I am an equal opportunity investigator.";
         eyes_message = "Fair, but I had nothing to do with it. I didn't even know the power was out until you told me.";
         message = "Hmmmmm...I dont suppose you've noticed anything weird?";
         eyes_message = "Actually, yes. The mountain has an abnormal warmth eminating from it.";
         message = "Is that so?";
         eyes_message = "Yes, I almost stayed there to enjoy the warmth. But the fire is prettier to look at than stones.";
         message = "Thanks.";
         eyes_message = "Also, take this. I found it near the mountain earlier. Maybe you can find a use for it.";
         eyes_message = "Good luck getting your power back on. Go to the mountain. The answer lies there.";

         // clicking again after above convo repeats last line of it
         eyes_message = "Good luck getting your power back on. Go to the mountain. The answer lies there.";


         result = true;
         break;
    default:  break;
    }

    return result;
}
