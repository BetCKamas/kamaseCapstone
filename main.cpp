#include <iostream>
#include <map>

#include <cstdlib>

#include <SDL.h>
#include <SDL_ttf.h>

#include "state.h"
#include "menu.h"
#include "credits.h"
#include "mainArea.h"
#include "goFishGUI.h"

using namespace std;

const int WIDTH = 1200;
const int HEIGHT = 700;

map <string, state *>states;
string current_state = "";
state *current_state_ptr = nullptr;

bool transition(string s) {
    bool result = true;

    if(current_state_ptr) {
        current_state_ptr->leave();
    }

    SDL_Event e;
    while(SDL_PollEvent(&e)); // flush the event queue

    if(states.contains(s)) {
        current_state_ptr = states[s];
        current_state = s;
        current_state_ptr->enter();
    }
    else {
        cerr << "OH NO!!! " << s << " is not a valid state." << endl;
        result = false;
        exit(EXIT_FAILURE);
    }

    return result;
}


int main(int argc, char *argv[]) {
	  //FPSmanager fps;
    //SDL_initFramerate(&fps);

    TTF_Init();

    if (TTF_Init() < 0) {
          cerr << "TTF_Init() fail... " << SDL_GetError() << endl;
          exit(EXIT_FAILURE);
        }

    TTF_Font* font = TTF_OpenFont("./Cute_Font/CuteFont-Regular.ttf", 64);

    SDL_Window *w = nullptr;
    SDL_Surface *s = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        cerr << "SDL_Init() fail... " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    w = SDL_CreateWindow("mothman game", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(w, -1, 0);

    states["menu"] = new menu_state(rend, w, s, font);
    states["credits"] = new credits_state(rend, w, s, font);
    states["mainArea"] = new mainArea_state(rend, w, s, font);
    states["goFishGUI"] = new goFishGUI_state(rend, w, s, font);

    transition("goFishGUI");
    //transition("menu");

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        /*
         * Let event handling update variables needed for drawing
         */
        while(SDL_PollEvent(&e)) {
            if(!current_state_ptr || !current_state_ptr->handle_event(e)) {
                switch(e.type) {
                case SDL_QUIT:  quit = true;  break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:  quit = true;  break;
                    default:  break;
                    }
                default:  break;
                }
            }
        }

        /*
         * Draw everything that matters
         */
        //SDL_SetRenderDrawColor(rend, 0xDD, 0xBB, 0xFF, 0xFF);
        current_state_ptr->draw();
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(w);

    SDL_Quit();

    return EXIT_SUCCESS;

}
