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

SDL_Rect gRect;
int gRotation;

void update(Tween* tween) {
    gRect.x = tween->props->x;
    gRect.y = tween->props->y;
    gRotation = tween->props->rotation;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    SDL_Window* window = SDL_CreateWindow("Window", 0, 25, 1024, 768, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 160, 221, 233)); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_free(surface);

    gRect.x = 100;
    gRect.y = 100;
    gRect.w = 125;
    gRect.h = 125;
    gRotation = 0;
    
    Tween_Engine* engine = Tween_CreateEngine();
   
    Tween_Props props = Tween_MakeProps(gRect.x, gRect.y, gRect.w, gRect.h, gRotation);

    Tween_Props toProps = Tween_MakeProps(700, 200, 0, 0, 359);
    Tween* tween = Tween_CreateTween(engine, &props, &toProps, 2000,
       TWEEN_EASING_ELASTIC_IN_OUT, update, NULL);
    tween->delay = 1000;
    
    Tween_Props toBackProps = Tween_MakeProps(gRect.x, gRect.y, 0, 0, gRotation);
    Tween* tweenBack = Tween_CreateTween(engine, &props, &toBackProps, 3000, 
       TWEEN_EASING_ELASTIC_IN_OUT, update, NULL);
    
    Tween_ChainTweens(tween, tweenBack);
    Tween_ChainTweens(tweenBack, tween);
    
    Tween_StartTween(tween, SDL_GetTicks());
    
    int terminate = 0;
    
    while(!terminate) {
        uint32_t tick = SDL_GetTicks();
        Tween_UpdateEngine(engine, tick);
        
        SDL_Event event;
        SDL_PollEvent(&event);
        
        switch (event.type) {
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
        SDL_RenderCopyEx(renderer, texture, NULL, &gRect, gRotation, 0, SDL_FLIP_NONE);
        
        SDL_RenderPresent(renderer);
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
