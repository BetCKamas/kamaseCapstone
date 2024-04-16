import sys
import os

if len(sys.argv) != 2:
    print("Usage:  python3 " + sys.argv[0] + " <state name>")
    print("\nTo generate new shell header and source files")
    print("for a state called \"xyz_state\", run the command...")
    print("\n\tpython3 " + sys.argv[0] + " xyz")
    print("\nThis will create the files xyz.h and xyz.cpp which will")
    print("declare and define the xyz_state class and its core")
    print("methods and variables.")
    exit()

base = sys.argv[1]
source_name = base + ".cpp"
header_name = base + ".h"

# make sure neither the target header or source files already exist
if os.path.exists(source_name):
    print("Error: The target source file, \"" + source_name + "\" already exists")
    exit()

if os.path.exists(header_name):
    print("Error: The target header file, \"" + header_name + "\" already exists")
    exit()

####
# Generate the output files


header_content = '''
#ifndef __QWERTY_H__
#define __QWERTY_H__

#include <SDL.h>

#include "state.h"

using namespace std;

class qwerty_state : public state {
public:
    qwerty_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font);
    ~qwerty_state();
    bool enter();
    bool leave();
    bool draw();
    bool handle_event(const SDL_Event &e);
};

#endif  /* __QWERTY_H__ */
'''

header_content = header_content.replace("qwerty", base)
header_content = header_content.replace("QWERTY", base.upper())

open(header_name, 'w').write(header_content)



source_content = '''
#include <iostream>

#include <SDL.h>

#include "qwerty.h"
#include "state.h"

using namespace std;

qwerty_state::qwerty_state(SDL_Renderer *rend, SDL_Window *win, SDL_Surface *s, TTF_Font *font) : state(rend, win, s, font) {
    /*
     * Initialize all this state's data here (load images, sounds, etc).
     * Keep in mind this only happens once at the start of the appliacation.
     */
}

qwerty_state::~qwerty_state() {
    /*
     * This will only occur when the state is being destroyed, so
     * get rid of any dynamically allocated or loaded resources
     * managed by this state.  Only happens once.
     */
}

bool qwerty_state::enter() {
    /*
     * Called whenever this state is being transitioned into.
     */
    return true;
}

bool qwerty_state::leave() {
    /*
     * Called whenever we are transitioning out of this state.
     */
    return true;
}

bool qwerty_state::draw() {
    /*
     * Use this method to draw/render whatever your state has going on,
     * but remember, the state framework will already have set the draw
     * color and cleared the screen with it and will also call
     * SDL_RenderPresent() for you, too.
     */
    return true;
}

bool qwerty_state::handle_event(const SDL_Event &e) {
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
'''

source_content = source_content.replace("qwerty", base)
source_content = source_content.replace("QWERTY", base.upper())

open(source_name, 'w').write(source_content)
