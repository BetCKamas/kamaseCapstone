
#include <iostream>

#include <SDL.h>

#include "pathToWoods.h"
#include "state.h"

using namespace std;

bool noflowerForBees = false;
bool giveFlowerToBees = false;
bool firstTalkToBees = true;
bool secondTalkToBees = false;
bool clickedonbees = false;

pathToWoods_state::pathToWoods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     ptw = IMG_Load("./gameImages/PathToWoods.png");
     tptw = SDL_CreateTextureFromSurface(rend, ptw);
     SDL_FreeSurface(ptw);
     ptw = nullptr;

     askBeesForHoney = false;
     noflowerForBees = true;
     flowerForBees = false;
}

pathToWoods_state::~pathToWoods_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

    SDL_DestroyTexture(tptw);
    tptw = nullptr;
}

bool pathToWoods_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
     for(int i = 67; i > 0; i--){
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
         SDL_RenderCopy(rend, tptw, nullptr, &imageRect); // display game image
         if(honeyVisible)
            SDL_RenderCopy(rend, th, nullptr, &honeyRect); // display honey image
         if(flowerVisible)
            SDL_RenderCopy(rend, tf, nullptr, &flowerRect); // display flower image
         if(appointmentcardVisible)
            SDL_RenderCopy(rend, tac, nullptr, &appointmentcardRect); // display appointmentcard image
         if(smoreVisible)
            SDL_RenderCopy(rend, ts, nullptr, &smoreRect); // display smore image

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

     message = "";
     dialogueLine = 0;

     if(flowerVisible)
        flowerForBees = true;

     return true;
}

bool pathToWoods_state::leave() {
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

     message = "";
     dialogueLine = 0;

     return true;
}

bool pathToWoods_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

    SDL_GetMouseState(&MouseX, &MouseY);

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
    SDL_RenderCopy(rend, tptw, nullptr, &imageRect); // display game image

    if(honeyVisible){
       SDL_RenderCopy(rend, th, nullptr, &honeyRect); // display honey image
    }
    if(flowerVisible){
       SDL_RenderCopy(rend, tf, nullptr, &flowerRect); // display flower image
    }
    if(appointmentcardVisible){
       SDL_RenderCopy(rend, tac, nullptr, &appointmentcardRect); // display appointmentcard image
    }
    if(smoreVisible){
       SDL_RenderCopy(rend, ts, nullptr, &smoreRect); // display smore image
    }

    if(askBeesForHoney && firstTalkToBees && clickedonbees){
       switch(dialogueLine){
         case 1:
         message = "Excuse me?";
         textColor = mothmanC;
         break;

         case 2:
         message = "*bzzt-bzzt* We're asleep. Come back later.";
         textColor = beesC;
         break;

         case 3:
         message = "I'm sorry to bother you, but do you have any honey?";
         textColor = mothmanC;
         break;

         case 4:
         message = "Tell you what kid. Since I'm feeling generous, you bring me a flower. I'll give you some honey.";
         textColor = beesC;
         askBeesForHoney = false;
         honeyRequest = true;
         firstTalkToBees = false;
         secondTalkToBees = true;
         dialogueLine = 0;
         break;

         default: break;

       }
    }

    if(flowerForBees &&  secondTalkToBees && clickedonbees){
      switch (dialogueLine){
        case 1:
        message = "I have the flower, here you go.";
        textColor = mothmanC;
        break;

        case 2:
        message = "This is a good flower. Here's your honey kid.";
        textColor = beesC;
        honeyVisible = true;
        flowerVisible = false;
        flowerForBees = false;
        clickedonbees = false;
        secondTalkToBees = false;
        break;

        default: break;

      }
    }


    stringColor(rend, textX, textY, message.c_str(), textColor);
    SDL_RenderPresent(rend);
    return true;
}

bool pathToWoods_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {
      // add transition to woods and back to town
      case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button){
          case SDL_BUTTON_LEFT:
             if(checkCollision(MouseX, MouseY, moveBackDR)){
              transition("mainArea");
             }
             if(checkCollision(MouseX, MouseY, moveIntoWoodsR)){
                transition("woods");
              }

             if(checkCollision(MouseX, MouseY, beesR)){
               clickedonbees = true;
             }


             dialogueLine++;

             result = true;
             break;
             default: break;
           } break;
    default:  break;
    }

    return result;
}
