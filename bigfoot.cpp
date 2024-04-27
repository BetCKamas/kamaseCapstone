
#include <iostream>

#include <SDL.h>

#include "bigfoot.h"
#include "state.h"

using namespace std;

string message;
int dialogueLine = 0;
bool firstVisit = false;
bool hereForSmore = false;
bool honeyRequest = false;
bool haveHoney = false;
bool noOtherDialogue = false;

bigfoot_state::bigfoot_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     b = IMG_Load("./gameImages/Bigfoottalk.png");
     tb = SDL_CreateTextureFromSurface(rend, b);
     SDL_FreeSurface(b);
     b = nullptr;
     firstVisit = true;
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

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
    SDL_RenderCopy(rend, tb, nullptr, &imageRect); // display game image

    if(firstVisit){
      switch(dialogueLine){
        case 0:
        message = "Welcome to Big's. With this power outage we can't offer too much off the menu right now.";
        textColor = bigfootC;
        break;

        case 1:
        message = "Oh thats ok, I'm not hungry right now. I just wanted to ask you some questions if that's alright.";
        textColor = mothmanC;
        break;

        case 2:
        message= "Questions? What kind of questions?";
        textColor = bigfootC;
        break;

        case 3:
        message = "About the power outage.";
        textColor = mothmanC;
        break;

        case 4:
        message= "Oh. Theres not much to say really. I was doing some prep working making some bread when the power went.";
        textColor = bigfootC;
        break;

        case 5:
        message = "Breadmaking? That's a difficult art to conquer.";
        textColor = mothmanC;
        break;

        case 6:
        message= "Secret family recipe. Tradition has been passed down within my family.";
        textColor = bigfootC;
        break;

        case 7:
        message= "Lucky for me, bread dough can rise without the power.";
        textColor = bigfootC;
        break;

        case 8:
        message = "So you know nothing about the power outage?";
        textColor = mothmanC;
        break;

        case 9:
        message= "Nothin.";
        textColor = bigfootC;
        break;

        case 10:
        message = "OK, well thank you for your time.";
        textColor = mothmanC;
        break;

        case 11:
        message= "Come back any time.";
        textColor = bigfootC;
        firstVisit = false;
        dialogueLine = 0;
        break;

        default : break;
      }
    }

    if(hereForSmore){
      switch(dialogueLine){
        case 1:
        message = "Welcome back, what can I do ya for";
        textColor = bigfootC;
        break;

        case 2:
        message = "Do you by any chance have any smore ingredients?";
        textColor = mothmanC;
        break;

        case 3:
        message = "I do.";
        textColor = bigfootC;
        break;

        case 4:
        message = "Can I have enough for one smore?";
        textColor = mothmanC;
        break;

        case 5:
        message = "Tell you what kid. I am in need of some honey for my bread. You get me some honey, I'll give you one smore. You'll need to toast it yourself.";
        textColor = bigfootC;
        break;

        case 6:
        message = "Deal, I'll be back with the honey.";
        textColor = mothmanC;
        hereForSmore = false;
        break;

        default : break;
      }
    }

    if(honeyRequest){
      switch(dialogueLine){
        case 1:
        message = "You ready for the honey-smore trade?";
        textColor = bigfootC;
        break;

        case 2:
        message = "Not yet, I'll be back.";
        textColor = mothmanC;
        break;

        default : break;
      }
    }

    if(haveHoney) {
      switch(dialogueLine){
        case 1:
        message = "You ready for the honey-smore trade?";
        textColor = bigfootC;
        break;

        case 2:
        message = "Here you go";
        textColor = mothmanC;
        break;

        case 3:
        message = "*sniff* *sniff*";
        textColor = bigfootC;
        break;

        case 4:
        message = "This is some good fresh honey. Its perfect for my bread. Thanks kid, here's your smore.";
        textColor = bigfootC;
        break;

        default : break;
      }
    }

    if(noOtherDialogue){
      message = "Good luck investigator.";
      textColor = bigfootC;
    }


    stringColor(rend, textX, textY, message.c_str(), textColor);
    SDL_RenderPresent(rend);

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