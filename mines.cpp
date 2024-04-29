
#include <iostream>

#include <SDL.h>

#include "mines.h"
#include "state.h"

using namespace std;

bool haveAppointment = false;
bool firstVisitH;
bool inConvoH;
bool clickedHenchman;
bool goInside = false;

mines_state::mines_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

     mi = IMG_Load("./gameImages/Mines.png");
     tmi = SDL_CreateTextureFromSurface(rend, mi);
     SDL_FreeSurface(mi);
     mi = nullptr;

     firstVisitH = true;

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

     if(appointmentcardVisible)
        haveAppointment = true;


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

   message = "";
   dialogueLine = 0;

   return true;
}

bool mines_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */

     SDL_GetMouseState(&MouseX, &MouseY);

     SDL_RenderClear(rend);
     SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
     SDL_RenderCopy(rend, tmi, nullptr, &imageRect); // display game image
     if(honeyVisible)
        SDL_RenderCopy(rend, th, nullptr, &honeyRect); // display honey image
     if(flowerVisible)
        SDL_RenderCopy(rend, tf, nullptr, &flowerRect); // display flower image
     if(appointmentcardVisible)
        SDL_RenderCopy(rend, tac, nullptr, &appointmentcardRect); // display appointmentcard image
     if(smoreVisible)
       SDL_RenderCopy(rend, ts, nullptr, &smoreRect); // display smore image


     if(firstVisitH && haveAppointment){
       switch(dialogueLine){
         case 0:
         message = "HALT! Who goes there?";
         textColor = henchmanC;
         inConvoH = true;
         break;

         case 1:
         message = "Uhh, it is I, Mothman P.I.";
         textColor = mothmanC;
         break;

         case 2:
         message = "Who? I've never heard of you.";
         textColor = henchmanC;
         break;

         case 3:
         message = "Well now you have.";
         textColor = mothmanC;
         break;

         case 4:
         message = "What is your purpose here?";
         textColor = henchmanC;
         break;

         case 5:
         message = "I'm investigating why the power went out in town. Would you happen to know anything about that?";
         textColor = mothmanC;
         break;

         case 6:
         message = "I don't know anything about what the boss is doing?";
         textColor = henchmanC;
         break;

         case 7:
         message = "That wasn't the question I asked.";
         textColor = mothmanC;
         break;

         case 8:
         message = "Uhh";
         textColor = henchmanC;
         break;

         case 9:
         message = "What's your boss up to?";
         textColor = mothmanC;
         break;

         case 10:
         message = "Nothing at all. Definetly not anything to do with why the power is out.";
         textColor = henchmanC;
         break;

         case 11:
         message = "Yeah, OK, I don't believe you.";
         textColor = mothmanC;
         break;

         case 12:
         message = "Why not? I'm a very believable person.";
         textColor = henchmanC;
         break;

         case 13:
         message = "That's not the vibe I'm picking up on.";
         textColor = mothmanC;
         break;

         case 14:
         message = "How dare you harsh my vibe.";
         textColor = henchmanC;
         break;

         case 15:
         message = "OK, I'm just going to take a look around then.";
         textColor = mothmanC;
         break;

         case 16:
         message = "OK, but yoy can't go past me.";
         textColor = henchmanC;
         break;

         case 17:
         message = "Why not?";
         textColor = mothmanC;
         break;

         case 18:
         message = "Boss's orders.";
         textColor = henchmanC;
         break;

         case 19:
         message = "Dude you are so suspisious.";
         textColor = mothmanC;
         break;

         case 20:
         message = "I'm just doing my job.";
         textColor = henchmanC;
         break;

         case 21:
         message = "Well what would it take to get past you.";
         textColor = mothmanC;
         break;

         case 22:
         message = "I'm not allowed to let anyone past who doesn't haved an appointment.";
         textColor = henchmanC;
         break;

         case 23:
         message = "Actaully I have an appointment, here is my appointment card.";
         textColor = mothmanC;
         break;

         case 24:
         message = "Let me see that.";
         textColor = henchmanC;
         break;

         case 25:
         message = "You can go past";
         textColor = henchmanC;
         appointmentcardVisible = false;
         inConvoH = false;
         firstVisitH = false;
         dialogueLine = 0;
         goInside = true;
         break;

         default: break;

         }
     }

     if(firstVisitH && !haveAppointment){
       switch(dialogueLine){
         case 0:
         message = "HALT! Who goes there?";
         textColor = henchmanC;
         inConvoH = true;
         break;

         case 1:
         message = "Uhh, it is I, Mothman P.I.";
         textColor = mothmanC;
         break;

         case 2:
         message = "Who? I've never heard of you.";
         textColor = henchmanC;
         break;

         case 3:
         message = "Well now you have.";
         textColor = mothmanC;
         break;

         case 4:
         message = "What is your purpose here?";
         textColor = henchmanC;
         break;

         case 5:
         message = "I'm investigating why the power went out in town. Would you happen to know anything about that?";
         textColor = mothmanC;
         break;

         case 6:
         message = "I don't know anything about what the boss is doing?";
         textColor = henchmanC;
         break;

         case 7:
         message = "That wasn't the question I asked.";
         textColor = mothmanC;
         break;

         case 8:
         message = "Uhh";
         textColor = henchmanC;
         break;

         case 9:
         message = "What's your boss up to?";
         textColor = mothmanC;
         break;

         case 10:
         message = "Nothing at all. Definetly not anything to do with why the power is out.";
         textColor = henchmanC;
         break;

         case 11:
         message = "Yeah, OK, I don't believe you.";
         textColor = mothmanC;
         break;

         case 12:
         message = "Why not? I'm a very believable person.";
         textColor = henchmanC;
         break;

         case 13:
         message = "That's not the vibe I'm picking up on.";
         textColor = mothmanC;
         break;

         case 14:
         message = "How dare you harsh my vibe.";
         textColor = henchmanC;
         break;

         case 15:
         message = "OK, I'm just going to take a look around then.";
         textColor = mothmanC;
         break;

         case 16:
         message = "OK, but yoy can't go past me.";
         textColor = henchmanC;
         break;

         case 17:
         message = "Why not?";
         textColor = mothmanC;
         break;

         case 18:
         message = "Boss's orders.";
         textColor = henchmanC;
         break;

         case 19:
         message = "Dude you are so suspisious.";
         textColor = mothmanC;
         break;

         case 20:
         message = "I'm just doing my job.";
         textColor = henchmanC;
         break;

         case 21:
         message = "Well what would it take to get past you.";
         textColor = mothmanC;
         break;

         case 22:
         message = "I'm not allowed to let anyone past who doesn't haved an appointment.";
         textColor = henchmanC;
         break;

         case 23:
         message = "How do I make an appointment?";
         textColor = mothmanC;
         break;

         case 24:
         message = "That's above my paygrade.";
         textColor = henchmanC;
         break;

         case 25:
         message = "So if I get an appointment, you'll let me past?";
         textColor = mothmanC;
         break;

         case 26:
         message = "Correct.";
         textColor = henchmanC;
         break;

         case 27:
         message = "Actually I have an appointment";
         textColor = mothmanC;
         break;

         case 28:
         message = "Is that so? Please show me your appointment card.";
         textColor = henchmanC;
         break;

         case 29:
         message = "Appointment card?";
         textColor = mothmanC;
         break;

         case 30:
         message = "Yes we give out appointment cards. You show me yours and I'll let you past.";
         textColor = henchmanC;
         break;

         case 31:
         message = "Oh silly me, I must have left it in my other coat. I'll go fetch it.";
         textColor = mothmanC;
         inConvoH = false;
         firstVisitH = false;
         dialogueLine = 0;
         break;

         default: break;

         }
     }

     if(!haveAppointment && !firstVisitH && clickedHenchman){
       message = "I can't go back up to him without an appointment card. Maybe I can find one someplace.";
       textColor = mothmanC;
     }

     if(haveAppointment && !firstVisitH && clickedHenchman){
       switch(dialogueLine){
         case 1:
         message = "Here it is, my appointment card.";
         textColor = mothmanC;
         break;

         case 2:
         message = "Let me see.";
         textColor = henchmanC;
         break;

         case 3:
         message = "Yes this will do. You can go past.";
         textColor = henchmanC;
         appointmentcardVisible = false;
         goInside = true;
         break;

         default: break;
       }

     }

    stringColor(rend, textX, textY, message.c_str(), textColor);
    SDL_RenderPresent(rend);


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
                if(checkCollision(MouseX, MouseY, henchmanRect)){
                  clickedHenchman = true;
                }

                if(!inConvoH && checkCollision(MouseX, MouseY, backRect)){
                  transition("mainArea");
                }

                if(goInside){
                  transition("maze");
                }

                dialogueLine++;

                result = true;
                break;
                default: break;
              }
    default:  break;
    }

    return result;
}
