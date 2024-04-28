
#include <iostream>

#include <SDL.h>

#include "woods.h"
#include "state.h"

using namespace std;

string eyes_message;
bool firstVisitE = false;
bool askForSmore = false;
bool haveSmore = false;
bool noMoreDialogue = false;


woods_state::woods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     w = IMG_Load("./gameImages/woods.png");
     tw = SDL_CreateTextureFromSurface(rend, w);
     SDL_FreeSurface(w);
     w = nullptr;

     firstVisitE = true;
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

    if(firstVisitE){
      switch(dialogueLine){
        case 0:
        message = "A campfire? But whose? I don't see anyone.";
        textColor = mothmanC;
        break;

        case 1:
        eyes_message = "Hello";
        textColor = eyesC;
        break;

        case 2:
        message = "AHHH!";
        textColor = mothmanC;
        break;

        case 3:
        eyes_message = "Sorry, I like the warmth from the fire but I like to stay in the dark tree line.";
        textColor = eyesC;
        break;

        case 4:
        message = "Phew. I was worried that you were a human camper.";
        textColor = mothmanC;
        break;

        case 5:
        eyes_message = "How do you know I'm not a human camper?";
        textColor = eyesC;
        break;

        case 6:
        message = "I don't think human campers are cool enough to be a pair of red eyes without a body.";
        textColor = mothmanC;
        break;

        case 7:
        eyes_message = "*blushing*";
        textColor = eyesC;
        break;

        case 8:
        eyes_message = "Yeah you right";
        textColor = eyesC;
        break;

        case 9:
        message = "But you should be careful though. We dont need a forest fire to occur.";
        textColor = mothmanC;
        break;

        case 10:
        eyes_message = "Yes, yes, of course. But what are you doing out here? I've never seen you here before...";
        textColor = eyesC;
        break;

        case 11:
        message = "Right. I'm investigating why the power has gone out in town.";
        textColor = mothmanC;
        break;

        case 12:
        eyes_message = "And you thought the best place to figure that out was the forest?";
        textColor = eyesC;
        break;

        case 13:
        message = "As an investigator you must leave no stones unturned.";
        textColor = mothmanC;
        break;

        case 14:
        eyes_message = "There are a lot of stones out here.";
        textColor = eyesC;
        break;

        case 15:
        message = "Riiiiigggght. Can I ask you some questions?";
        textColor = mothmanC;
        break;

        case 16:
        eyes_message = "First you need to do something for me.";
        textColor = eyesC;
        break;

        case 17:
        message = "And what would that be?";
        textColor = mothmanC;
        break;

        case 18:
        eyes_message = "I want a smore.";
        textColor = eyesC;
        break;

        case 19:
        message = "You setup a campfire, but forgot to get ingredients for smores?";
        textColor = mothmanC;
        break;

        case 20:
        eyes_message = "Normally I just want the warmth, but I have a rather large hankering for a smore. Talking makes me peckish.";
        textColor = eyesC;
        break;

        case 21:
        message = "I'll get you a smore and then you'll answer my questions, deal?";
        textColor = mothmanC;
        break;

        case 22:
        eyes_message =  "Deal.";
        textColor = eyesC;
        break;

        case 23:
        message = "OK, I'll be back with your smore.";
        textColor = mothmanC;
        dialogueLine = 0;
        firstVisitE = false;
        askForSmore = true;
        break;

        default: break;
      }
    }

    if(askForSmore){
      switch(dialogueLine){
        case 1:
        eyes_message = "You have my smore yet?";
        textColor = eyesC;
        break;

        case 2:
        message = "Not yet. I'll be back.";
        textColor = mothmanC;
        break;

        default: break;
      }
    }

    if(haveSmore){
      switch(dialogueLine){
        case 1:
        message = "Heres your smore.";
        textColor = mothmanC;
        break;

        case 2:
        eyes_message = "MMH! Delicious.";
        textColor = eyesC;
        break;

        case 3:
        message = "So you'll answer my questions now?";
        textColor = mothmanC;
        break;

        case 4:
        eyes_message = "A deals a deal. What do you want to know?";
        textColor = eyesC;
        break;

        case 5:
        message = "Did you cause the power outage?";
        textColor = mothmanC;
        break;

        case 6:
        eyes_message = "You yourself said that I have no body.";
        textColor = eyesC;
        break;

        case 7:
        message = "That doesn't mean you didn't do it. I am an equal opportunity investigator.";
        textColor = mothmanC;
        break;

        case 8:
        eyes_message = "Fair, but I had nothing to do with it. I didn't even know the power was out until you told me.";
        textColor = eyesC;
        break;

        case 9:
        message = "Hmmmmm...I dont suppose you've noticed anything weird?";
        textColor = mothmanC;
        break;

        case 10:
        eyes_message = "Actually, yes. The mountain has an abnormal warmth eminating from it.";
        textColor = eyesC;
        break;

        case 11:
        message = "Is that so?";
        textColor = mothmanC;
        break;

        case 12:
        eyes_message = "Yes, I almost stayed there to enjoy the warmth. But the fire is prettier to look at than stones.";
        textColor = eyesC;
        break;

        case 13:
        message = "Thanks.";
        textColor = mothmanC;
        break;

        case 14:
        eyes_message = "Also, take this. I found it near the mountain earlier. Maybe you can find a use for it.";
        textColor = eyesC;
        break;

        case 15:
        eyes_message = "Good luck getting your power back on. Go to the mountain. The answer lies there.";
        textColor = eyesC;
        haveSmore = false;
        noMoreDialogue = true;
        break;

        default: break;
      }
    }

    if(noMoreDialogue){
      eyes_message = "Good luck getting your power back on. Go to the mountain. The answer lies there.";
      textColor = eyesC;
    }

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
         dialogueLine++;
         result = true;
         break;
    default:  break;
    }

    return result;
}
