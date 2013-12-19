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
#include <time.h>  
#include "libtween/tween.h"

typedef struct Bar {
    SDL_Rect rect;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Bar;

double rand_range(double min, double max) {
    return min + ((double)rand() / ((double)RAND_MAX / (max - min)));
}

void update(Tween* tween) {
    Bar* bar;

    bar = (Bar*)tween->data; 
    bar->rect.x = (int)tween->props.x;
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Tween_Engine* engine;
    int loop;
    double startValue;
    double endValue;
    Bar bar[1000];
    Tween_Props props;
    Tween_Props toProps;
    Tween* tween[1000];
    Tween* tweenBack[1000];
    int terminate;
    uint32_t tick;
    SDL_Event event;

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    window = SDL_CreateWindow("Window", 0, 25, 1024, 1000, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    engine = Tween_CreateEngine();

    for (loop = 0; loop < 1000; loop++) {
        startValue = 500 + (rand_range(0, 1) - rand_range(0, 1)) * 250;
        endValue = 500 + (rand_range(0, 1) - rand_range(0, 1)) * 250;
       
        bar[loop].rect.x = startValue;
        bar[loop].rect.y = loop;
        bar[loop].rect.w = 100;
        bar[loop].rect.h = 2;

        bar[loop].r = rand_range(0, 255);
        bar[loop].g = rand_range(0, 255);
        bar[loop].b = rand_range(0, 255);

        props.x = startValue;
        toProps.x = endValue;

        tween[loop] = Tween_CreateTween(engine, &props, &toProps, 4000, TWEEN_EASING_LINEAR, update, &bar[loop]);
        tween[loop]->delay = rand_range(0, 1000);
       
        tweenBack[loop] = Tween_CreateTween(engine, &toProps, &props, 4000, TWEEN_EASING_ELASTIC_IN_OUT, update, &bar[loop]);
        tweenBack[loop]->delay = rand_range(0, 1000);
        
        Tween_ChainTweens(tween[loop], tweenBack[loop]);
        Tween_ChainTweens(tweenBack[loop], tween[loop]);
   
        Tween_StartTween(tween[loop], SDL_GetTicks());
    }

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

        for (loop = 0; loop < 1000; loop++) {
            SDL_SetRenderDrawColor(renderer, bar[loop].r, bar[loop].g, bar[loop].b, 0xFF);
            SDL_RenderFillRect(renderer, &bar[loop].rect);
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    for (loop = 0; loop < 1000; loop++) {
        Tween_DestroyTween(tween[loop]);
        Tween_DestroyTween(tweenBack[loop]);
    }
    
    Tween_DestroyEngine(engine);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
