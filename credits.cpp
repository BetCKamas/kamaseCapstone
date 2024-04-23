
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "credits.h"
#include "state.h"

using namespace std;

credits_state::credits_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, SDL_Texture *to, TTF_Font *font) : state(rend, win, s, to, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
}

credits_state::~credits_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool credits_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool credits_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool credits_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderPresent(rend);
    return true;
}

bool credits_state::handle_event(const SDL_Event &e) {
    /*
     * Remember to set the result to true if your state ends up
     * handling whatever this event is.  If not, the event may be
     * handled by the state framework.  In the case of an SDL_Quit
     * event, that means it will exit the app.
     */
    bool result = false;

    switch(e.type) {

    default:  break;
    }

    return result;
}
