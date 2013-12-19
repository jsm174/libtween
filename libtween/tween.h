/**
 * libtween
 * Copyright (C) 2013 libtween authors.
 * 
 * Based on tween.js Copyright (c) 2010-2013 Tween.js authors.
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

#include "tween_easing.h"

#ifndef TWEEN_INLINE
#if defined(__GNUC__)
#define TWEEN_INLINE __inline__
#elif defined(_MSC_VER)
#define TWEEN_INLINE __inline
#ifndef __inline__
#define __inline__ __inline
#endif
#else
#define TWEEN_INLINE inline
#ifndef __inline__
#define __inline__ inline
#endif
#endif
#endif

#ifndef TWEEN_FORCE_INLINE
#if defined(_MSC_VER)
#define TWEEN_FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define TWEEN_FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#define TWEEN_FORCE_INLINE static TWEEN_INLINE
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tween_Node {
    struct Tween* tween;
    struct Tween_Node* next;
} Tween_Node;

typedef struct Tween_Engine {
    Tween_Node* tweens;
} Tween_Engine;

typedef struct Tween_Props {
    double x;
    double y;
    double width;
    double height;
    double rotation;
    double r;
    double g;
    double b;
    double a;
} Tween_Props;

typedef void (*Tween_Callback)(struct Tween*);

typedef struct Tween {
    Tween_Engine* engine;
    Tween_Props props;
    Tween_Props toProps;
    uint32_t duration;
    uint32_t delay;
    int repeat;
    int yoyo;
    Tween_Easing easing;
    Tween_Callback startCallback;
    Tween_Callback updateCallback;
    Tween_Callback completeCallback;
    void* data;
    uint32_t startTime;
    int startCallbackFired;
    Tween_Props startProps;
    Tween_Props repeatProps;
    int reversed;
    Tween_Node* chain;
} Tween;

Tween_Engine* Tween_CreateEngine();
int Tween_UpdateEngine(Tween_Engine* engine, uint32_t time);
void Tween_DestroyEngine(Tween_Engine* engine);

Tween* Tween_CreateTween(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, Tween_Easing easing, Tween_Callback updateCallback, void* data);
Tween* Tween_CreateTweenEx(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, uint32_t delay, int repeat, int yoyo, Tween_Easing easing, Tween_Callback startCallback, Tween_Callback updateCallback, Tween_Callback completeCallback, void* data);
void Tween_ChainTweens(Tween* tween, Tween* tween2);
void Tween_StartTween(Tween* tween, uint32_t time);
int Tween_UpdateTween(Tween* tween, uint32_t time);
void Tween_StopTween(Tween* tween);
void Tween_DestroyTween(Tween* tween);

/**
 * Tween_MakeProps()
 */

TWEEN_FORCE_INLINE Tween_Props Tween_MakeProps(double x, double y, double width, double height, double rotation) {
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

TWEEN_FORCE_INLINE Tween_Props Tween_MakePropsEx(double x, double y, double width, double height, double rotation, double r, double g, double b, double a) {
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

TWEEN_FORCE_INLINE void Tween_CopyProps(Tween_Props* props, Tween_Props* props2) {
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
 * Tween_SwapProps()
 */

TWEEN_FORCE_INLINE void Tween_SwapProps(Tween_Props* props, Tween_Props* props2) {
    Tween_Props tempProps;
    Tween_CopyProps(props, &tempProps);
    Tween_CopyProps(props2, props);
    Tween_CopyProps(&tempProps, props2);
}

/**
 * Tween_UpdateProps()
 */

TWEEN_FORCE_INLINE void Tween_UpdateProps(Tween_Props* startProps, Tween_Props* toProps, Tween_Props* props, double value) {
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

#ifdef __cplusplus
}
#endif

#endif
