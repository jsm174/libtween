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

SDL_Rect gRect01[1000];
Tween_Props gProps01[1000];

Tween_Props gPropsTo01[1000];
Tween* tween[1000];

Tween_Props gPropsBack01[1000];
Tween* tweenBack[1000];

void update(Tween* tween) {
    SDL_Rect* rect = (SDL_Rect*)tween->data;
    rect->x = tween->props->x;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    SDL_Window* window = SDL_CreateWindow("Window", 0, 25, 1024, 1000, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 2, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 160, 221, 233)); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_free(surface);

    Tween_Engine* engine = Tween_CreateEngine();

    int loop;

    for (loop = 0; loop < 1000; loop++) {
        float startValue = 500 + (((float)rand()/(float)RAND_MAX) - ((float)rand()/(float)RAND_MAX)) * 250;
        float endValue = 500 + (((float)rand()/(float)RAND_MAX) - ((float)rand()/(float)RAND_MAX)) * 250;
        
        gRect01[loop].x = startValue;
        gRect01[loop].y = loop;
        gRect01[loop].w = 100;
        gRect01[loop].h = 2;
    
        gProps01[loop].x = startValue;
        gPropsTo01[loop].x = endValue;
        
        tween[loop] = Tween_CreateTween(engine, &gProps01[loop], &gPropsTo01[loop], 4000, 
           TWEEN_EASING_LINEAR, update, NULL);
        tween[loop]->delay = (((float)rand()/(float)RAND_MAX) * 1000);
        tween[loop]->data = &(gRect01[loop]);
        
        gPropsBack01[loop].x = startValue;

        tweenBack[loop] = Tween_CreateTween(engine, &gProps01[loop], &gPropsBack01[loop], 4000, 
           TWEEN_EASING_ELASTIC_IN_OUT, update, NULL);
        tweenBack[loop]->delay = (((float)rand()/(float)RAND_MAX) * 1000);
        tweenBack[loop]->data = &gRect01[loop];
        
        Tween_ChainTweens(tween[loop], tweenBack[loop]);
        Tween_ChainTweens(tweenBack[loop], tween[loop]);
   
        Tween_StartTween(tween[loop], SDL_GetTicks());
    }

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

        for (loop = 0; loop < 1000; loop++) {
           SDL_RenderCopyEx(renderer, texture, NULL, &gRect01[loop], 0, 0, SDL_FLIP_NONE);
        }
        
        SDL_RenderPresent(renderer);
    }

    for (loop = 0; loop < 1000; loop++) {
       Tween_DestroyTween(tween[loop]);
       Tween_DestroyTween(tweenBack[loop]);
    }
    
    Tween_DestroyEngine(engine);
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
