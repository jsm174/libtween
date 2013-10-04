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

#ifndef __TWEEN_H
#define __TWEEN_H

#include <stdint.h>
#include <stdbool.h>

#include "tween_easing.h"

typedef struct Tween_Node {
    struct Tween* tween;
    struct Tween_Node* next;
} Tween_Node;

typedef struct Tween_Engine {
    Tween_Node* tweens;
    uint32_t (*timerFunction)(void);
} Tween_Engine;

typedef struct Tween_Props {
    float x;
    float y;
    float width;
    float height;
    float rotation;
    float r;
    float g;
    float b;
    float a;
} Tween_Props;

typedef void (*Tween_Callback)(struct Tween*);

typedef struct Tween {
    Tween_Engine* engine;
    Tween_Props* props;
    Tween_Props* toProps;
    uint32_t duration;
    uint32_t delay;
    int repeat;
    bool yoyo;
    TweenEasing easing;
    Tween_Callback startCallback;
    Tween_Callback updateCallback;
    Tween_Callback completeCallback;
    void* data;
    uint32_t startTime;
    bool startCallbackFired;
    Tween_Props* startProps;
    Tween_Props* repeatProps;
    bool reversed;
    Tween_Node* chain;
} Tween;

Tween_Engine* Tween_CreateEngine();
bool Tween_UpdateEngine(Tween_Engine* engine, uint32_t time);
void Tween_DestroyEngine(Tween_Engine* engine);

Tween* Tween_CreateTween(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, TweenEasing easing, Tween_Callback updateCallback, void* data);
Tween* Tween_CreateTweenEx(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, uint32_t delay, int repeat, bool yoyo, TweenEasing easing, Tween_Callback startCallback, Tween_Callback updateCallback, Tween_Callback completeCallback, void* data);
void Tween_ChainTweens(Tween* tween, Tween* tween2);
void Tween_StartTween(Tween* tween, uint32_t time);
bool Tween_UpdateTween(Tween* tween, uint32_t time);
void Tween_StopTween(Tween* tween);
void Tween_DestroyTween(Tween* tween);

/**
 * Tween_MakeProps()
 */

static __inline__ Tween_Props Tween_MakeProps(float x, float y, float width, float height, float rotation) {
    Tween_Props props;
    props.x = x;
    props.y = y;
    props.width = width;
    props.height = height;
    props.rotation = rotation;
    props.r = 0;
    props.g = 0;
    props.b = 0;
    props.a = 0;
    
    return props;
}

/**
 * Tween_MakePropsEx()
 */

static __inline__ Tween_Props Tween_MakePropsEx(float x, float y, float width, float height, float rotation, float r, float g, float b, float a) {
    Tween_Props props;
    props.x = x;
    props.y = y;
    props.width = width;
    props.height = height;
    props.rotation = rotation;
    props.r = r;
    props.g = g;
    props.b = b;
    props.a = a;
    
    return props;
}

/**
 * Tween_CopyProps()
 */

static __inline__ void Tween_CopyProps(Tween_Props* props, Tween_Props* props2) {
    props2->x = props->x;
    props2->y = props->y;
    props2->width = props->width;
    props2->height = props->height;
    props2->rotation = props->rotation;
    props2->r = props->r;
    props2->g = props->g;
    props2->b = props->b;
    props2->a = props->a;
}

/**
 * Tween_UpdateProps()
 */

static __inline__ void Tween_UpdateProps(Tween_Props* startProps, Tween_Props* toProps, Tween_Props* props, float value) {
    props->x = startProps->x + (toProps->x - startProps->x) * value;
    props->y = startProps->y + (toProps->y - startProps->y) * value;
    props->width = startProps->width + (toProps->width - startProps->width) * value;
    props->height = startProps->height + (toProps->height - startProps->height) * value;
    props->rotation = startProps->rotation + (toProps->rotation - startProps->rotation) * value;
    props->r = startProps->r + (toProps->r - startProps->r) * value;
    props->g = startProps->g + (toProps->g - startProps->g) * value;
    props->b = startProps->b + (toProps->b - startProps->b) * value;
    props->a = startProps->a + (toProps->a - startProps->a) * value;
}

#endif
