
#include <iostream>
#include <cstdlib>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include "mainArea.h"
#include "state.h"

using namespace std;

mainArea_state::mainArea_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font) : state(rend, win, s, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */

    ma = IMG_Load("MainArea.png");
    tma = SDL_CreateTextureFromSurface(rend, ma);
    SDL_FreeSurface(ma);
    ma = nullptr;

    o = IMG_Load("Overlay.png");
    to = SDL_CreateTextureFromSurface(rend, o);
    SDL_FreeSurface(o);
    o = nullptr;
}

mainArea_state::~mainArea_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */

    SDL_DestroyTexture(tma);
    tma = nullptr;

    SDL_DestroyTexture(to);
    to = nullptr;

    IMG_Quit();
}

bool mainArea_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool mainArea_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool mainArea_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
     SDL_RenderClear(rend);
     SDL_RenderCopy(rend, to, nullptr, nullptr); // display overlay
     SDL_RenderCopy(rend, tma, nullptr, &imageRect); // display game image

     stringColor(rend, textX, textY, "testing text location", 0xffffffff);

     SDL_RenderPresent(rend);
     return true;
}

bool mainArea_state::handle_event(const SDL_Event &e) {
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
