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

#ifndef __TWEEN_EASING_H
#define __TWEEN_EASING_H

typedef enum {
    TWEEN_EASING_LINEAR,
    TWEEN_EASING_QUADRATIC_IN,
    TWEEN_EASING_QUADRATIC_OUT,
    TWEEN_EASING_QUADRATIC_IN_OUT,
    TWEEN_EASING_CUBIC_IN,
    TWEEN_EASING_CUBIC_OUT,
    TWEEN_EASING_CUBIC_IN_OUT,
    TWEEN_EASING_QUARTIC_IN,
    TWEEN_EASING_QUARTIC_OUT,
    TWEEN_EASING_QUARTIC_IN_OUT,
    TWEEN_EASING_QUINTIC_IN,
    TWEEN_EASING_QUINTIC_OUT,
    TWEEN_EASING_QUINTIC_IN_OUT,
    TWEEN_EASING_SINUSOIDAL_IN,
    TWEEN_EASING_SINUSOIDAL_OUT,
    TWEEN_EASING_SINUSOIDAL_IN_OUT,
    TWEEN_EASING_EXPONENTIAL_IN,
    TWEEN_EASING_EXPONENTIAL_OUT,
    TWEEN_EASING_EXPONENTIAL_IN_OUT,
    TWEEN_EASING_CIRCULAR_IN,
    TWEEN_EASING_CIRCULAR_OUT,
    TWEEN_EASING_CIRCULAR_IN_OUT,
    TWEEN_EASING_ELASTIC_IN,
    TWEEN_EASING_ELASTIC_OUT,
    TWEEN_EASING_ELASTIC_IN_OUT,
    TWEEN_EASING_BACK_IN,
    TWEEN_EASING_BACK_OUT,
    TWEEN_EASING_BACK_IN_OUT,
    TWEEN_EASING_BOUNCE_IN,
    TWEEN_EASING_BOUNCE_OUT,
    TWEEN_EASING_BOUNCE_IN_OUT,
} Tween_Easing;

typedef float (*Tween_Easing_Func)(float);
extern Tween_Easing_Func tweenEasingFuncs[];

#endif
