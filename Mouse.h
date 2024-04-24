#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

class Mouse{
public:
  SDL_Renderer *rend;
  SDL_Texture* tmouse;
  SDL_Rect rect;
  SDL_Rect point;

  Mouse(SDL_Renderer *rend){
    this->rend = rend;
    tmouse = IMG_LoadTexture(rend, "mouse.png");
    rect.w = 25;
    rect.h = 25;
    point.w = 1;
    point.h = 1;
    SDL_ShowCursor(false);


  }

  void update(){
    SDL_GetMouseState(&rect.x, &rect.y);
    point.x = rect.x;
    point.y = rect.y;
  }

  void draw(){
    SDL_RenderCopy(rend, tmouse, NULL, &rect);
    SDL_RenderPresent(rend);
  }

};

#endif
