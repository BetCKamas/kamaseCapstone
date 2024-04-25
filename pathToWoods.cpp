
#include <iostream>

#include <SDL.h>

#include "pathToWoods.h"
#include "state.h"

using namespace std;

pathToWoods_state::pathToWoods_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
}

pathToWoods_state::~pathToWoods_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool pathToWoods_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool pathToWoods_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool pathToWoods_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
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
      case SDL_BUTTON_LEFT:
        // for when clicking on bee hive first time
         message = "Excuse me? Is anyone home?";
         bee-message = "*bzzt-bzzt*";
         bee-message = "We're asleep. Come back later.";
         message = "I'm sorry to bother you, but do you have any honey?";
         bee-message = "Tell you what kid. Since I'm feeling generous, you bring me a flower. I'll give you some honey."

         // clicking on bee hive after the above
         bee-message = "*bzzt-bzzt*";
         bee-message = "Unless you have a flower, let us sleep kid.";
         // have flower
         message = "I have the flower, here you go.";
         bee-message = "This is a good flower. Here's your honey kid."

         result = true;
         break;
    default:  break;
    }

    return result;
}
