/**
 * libtween
 * Copyright (C) 2013 libtween authors.
 * 
 * Based on tween.js Copyright (c) 2010-2012 Tween.js authors.
 * Easing equations Copyright (c) 2001 Robert Penner http://robertpenner.com/easing/
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SDL.h>
#include "libtween/tween.h"

typedef struct Square {
    SDL_Rect rect;
    int rotation;
} Square;

void update(Tween* tween) {
    Square* square;

    square  = (Square*)tween->data;
    square->rect.x = (int)tween->props.x;
    square->rect.y = (int)tween->props.y;
    square->rotation = (int)tween->props.rotation;
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    Square square;
    Tween_Engine* engine;
    Tween_Props props;
    Tween_Props toProps;
    Tween* tween;
    Tween* tweenBack;
    int terminate;
    uint32_t tick;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    window = SDL_CreateWindow("Window", 0, 25, 1024, 768, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 160, 221, 233)); 
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    square.rect.x = 100;  
    square.rect.y = 100;
    square.rect.w = 125;
    square.rect.h = 125;
    square.rotation = 0;

    engine = Tween_CreateEngine();
   
    props = Tween_MakeProps(square.rect.x, square.rect.y, square.rect.w, square.rect.h, square.rotation);
    toProps = Tween_MakeProps(700, 200, 0, 0, 359);

    tween = Tween_CreateTween(engine, &props, &toProps, 2000, TWEEN_EASING_ELASTIC_IN_OUT, update, &square);
    tween->delay = 1000;
    
    tweenBack = Tween_CreateTween(engine, &toProps, &props, 3000, TWEEN_EASING_ELASTIC_IN_OUT, update, &square);
    
    Tween_ChainTweens(tween, tweenBack);
    Tween_ChainTweens(tweenBack, tween);
    
    Tween_StartTween(tween, SDL_GetTicks());
    
    terminate = 0;
    
    while(!terminate) {
        tick = SDL_GetTicks();
        Tween_UpdateEngine(engine, tick);
        
        SDL_PollEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                terminate = 1;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        terminate = 1;
                        break;
                }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, texture, NULL, &square.rect, square.rotation, 0, SDL_FLIP_NONE);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }
    
    Tween_DestroyTween(tween);
    Tween_DestroyTween(tweenBack);
    
    Tween_DestroyEngine(engine);
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
