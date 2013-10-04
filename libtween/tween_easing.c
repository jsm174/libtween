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

#include <math.h>
#include "tween_easing.h"

#define PI 3.14159265

/**
 * prototypes
 */

float Tween_LinearEasing(float);
float Tween_QuadraticInEasing(float);
float Tween_QuadraticOutEasing(float);
float Tween_QuadraticInOutEasing(float);
float Tween_CubicInEasing(float);
float Tween_CubicOutEasing(float);
float Tween_CubicInOutEasing(float);
float Tween_QuarticInEasing(float);
float Tween_QuarticOutEasing(float);
float Tween_QuarticInOutEasing(float);
float Tween_QuinticInEasing(float);
float Tween_QuinticOutEasing(float);
float Tween_QuinticInOutEasing(float);
float Tween_SinusoidalInEasing(float);
float Tween_SinusoidalOutEasing(float);
float Tween_SinusoidalInOutEasing(float);
float Tween_ExponentialInEasing(float);
float Tween_ExponentialOutEasing(float);
float Tween_ExponentialInOutEasing(float);
float Tween_CircularInEasing(float);
float Tween_CircularOutEasing(float);
float Tween_CircularInOutEasing(float);
float Tween_ElasticInEasing(float);
float Tween_ElasticOutEasing(float);
float Tween_ElasticInOutEasing(float);
float Tween_BackInEasing(float);
float Tween_BackOutEasing(float);
float Tween_BackInOutEasing(float);
float Tween_BounceInEasing(float);
float Tween_BounceOutEasing(float);
float Tween_BounceInOutEasing(float);

/**
 * easing function pointers array
 */

Tween_Easing_Func tweenEasingFuncs[] = {
    Tween_LinearEasing,
    Tween_QuadraticInEasing,
    Tween_QuadraticOutEasing,
    Tween_QuadraticInOutEasing,
    Tween_CubicInEasing,
    Tween_CubicOutEasing,
    Tween_CubicInOutEasing,
    Tween_QuarticInEasing,
    Tween_QuarticOutEasing,
    Tween_QuarticInOutEasing,
    Tween_QuinticInEasing,
    Tween_QuinticOutEasing,
    Tween_QuinticInOutEasing,
    Tween_SinusoidalInEasing,
    Tween_SinusoidalOutEasing,
    Tween_SinusoidalInOutEasing,
    Tween_ExponentialInEasing,
    Tween_ExponentialOutEasing,
    Tween_ExponentialInOutEasing,
    Tween_CircularInEasing,
    Tween_CircularOutEasing,
    Tween_CircularInOutEasing,
    Tween_ElasticInEasing,
    Tween_ElasticOutEasing,
    Tween_ElasticInOutEasing,
    Tween_BackInEasing,
    Tween_BackOutEasing,
    Tween_BackInOutEasing,
    Tween_BounceInEasing,
    Tween_BounceOutEasing,
    Tween_BounceInOutEasing,
};

/**
 * Tween_LinearEasing()
 */

float Tween_LinearEasing(float k) {
    return k;
}

/**
 * Tween_QuadraticInEasing()
 */

float Tween_QuadraticInEasing(float k) {
    return k * k;
}

/**
 * Tween_QuadraticOutEasing()
 */

float Tween_QuadraticOutEasing(float k) {
    return k * ( 2 - k );
}

/**
 * Tween_QuadraticInOutEasing()
 */

float Tween_QuadraticInOutEasing(float k) {
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * k * k;
    }
    
    --k;
    
    return - 0.5 * ( k * ( k - 2 ) - 1 );
}

/**
 * Tween_CubicInEasing()
 */

float Tween_CubicInEasing(float k) {
    return k * k * k;
}

/**
 * Tween_CubicOutEasing()
 */

float Tween_CubicOutEasing(float k) {
    --k;
    
    return k * k * k + 1;
}

/**
 * Tween_CubicInOutEasing()
 */

float Tween_CubicInOutEasing(float k) {
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * k * k * k;
    }
    
    k -= 2;
    
    return 0.5 * ( k * k * k + 2 );
}

/**
 * Tween_QuarticInEasing()
 */

float Tween_QuarticInEasing(float k) {
    return k * k * k * k;
}

/**
 * Tween_QuarticOutEasing()
 */

float Tween_QuarticOutEasing(float k) {
    --k;
    
    return 1 - ( k * k * k * k );
}

/**
 * Tween_QuarticInOutEasing()
 */

float Tween_QuarticInOutEasing(float k) {
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * k * k * k * k;
    }
    
    k -= 2;
    
    return - 0.5 * ( k * k * k * k - 2 );
}

/**
 * Tween_QuinticInEasing()
 */

float Tween_QuinticInEasing(float k) {
    return k * k * k * k * k;
}

/**
 * Tween_QuinticOutEasing()
 */

float Tween_QuinticOutEasing(float k) {
    --k;
    
    return k * k * k * k * k + 1;
}

/**
 * Tween_QuinticInOutEasing()
 */

float Tween_QuinticInOutEasing(float k) {
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * k * k * k * k * k;
    }
    
    k -= 2;
    
    return 0.5 * ( k * k * k * k * k + 2 );
}

/**
 * Tween_SinusoidalInEasing()
 */

float Tween_SinusoidalInEasing(float k) {
    return 1 - cos( k * PI / 2 );
}

/**
 * Tween_SinusoidalOutEasing()
 */

float Tween_SinusoidalOutEasing(float k) {
    return sin( k * PI / 2 );
}

/**
 * Tween_SinusoidalInOutEasing()
 */

float Tween_SinusoidalInOutEasing(float k) {
    return 0.5 * ( 1 - cos( PI * k ) );
}

/**
 * Tween_ExponentialInEasing()
 */

float Tween_ExponentialInEasing(float k) {
    return k == 0 ? 0 : pow( 1024, k - 1 );
}

/**
 * Tween_ExponentialOutEasing()
 */

float Tween_ExponentialOutEasing(float k) {
    return k == 1 ? 1 : 1 - pow( 2, - 10 * k );
}

/**
 * Tween_ExponentialInOutEasing()
 */

float Tween_ExponentialInOutEasing(float k) {
    if ( k == 0 ) {
        return 0;
    }
    
    if ( k == 1 ) {
        return 1;
    }
    
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * pow( 1024, k - 1 );
    }
    
    return 0.5 * ( - pow( 2, - 10 * ( k - 1 ) ) + 2 );
}

/**
 * Tween_CircularInEasing()
 */

float Tween_CircularInEasing(float k) {
    return 1 - sqrt( 1 - k * k );

}

/**
 * Tween_CircularOutEasing()
 */

float Tween_CircularOutEasing(float k) {
    --k;
    
    return sqrt( 1 - ( k * k ) );
}

/**
 * Tween_CircularInOutEasing()
 */

float Tween_CircularInOutEasing(float k) {
    k *= 2;
    
    if ( k < 1 ) {
        return - 0.5 * ( sqrt( 1 - k * k ) - 1);
    }
    
    k -= 2;
    
    return 0.5 * ( sqrt( 1 - k * k) + 1);
}

/**
 * Tween_ElasticInEasing()
 */

float Tween_ElasticInEasing(float k) {
    float s;
    float a = 0.1;
    float p = 0.4;
    
    if ( k == 0 ) {
        return 0;
    }
    
    if ( k == 1 ) {
        return 1;
    }
    
    if ( !a || a < 1 ) {
        a = 1;
        s = p / 4;
    }
    else {
        s = p * asin( 1 / a ) / ( 2 * PI );
    }
    
    k -= 1;
    
    return - ( a * pow( 2, 10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) );
}

/**
 * Tween_ElasticOutEasing()
 */

float Tween_ElasticOutEasing(float k) {
    float s;
    float a = 0.1;
    float p = 0.4;
    
    if ( k == 0 ) {
        return 0;
    };
    
    if ( k == 1 ) {
        return 1;
    }
    
    if ( !a || a < 1 ) {
        a = 1;
        s = p / 4;
    }
    else {
        s = p * asin( 1 / a ) / ( 2 * PI );
    }
    
    return ( a * pow( 2, - 10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) + 1 );
}

/**
 * Tween_ElasticInOutEasing()
 */

float Tween_ElasticInOutEasing(float k) {
    float s;
    float a = 0.1;
    float p = 0.4;
    
    if ( k == 0 ) {
        return 0;
    }
    
    if ( k == 1 ) {
        return 1;
    }
    
    if ( !a || a < 1 ) {
        a = 1;
        s = p / 4;
    }
    else {
        s = p * asin( 1 / a ) / ( 2 * PI );
    }
    
    k *= 2;
    
    if ( k < 1 ) {
        k -= 1;
        
        return - 0.5 * ( a * pow( 2, 10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) );
    }
    
    k -= 1;
    
    return a * pow( 2, -10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) * 0.5 + 1;
}

/**
 * Tween_BackInEasing()
 */

float Tween_BackInEasing(float k) {
    float s = 1.70158;
    return k * k * ( ( s + 1 ) * k - s );
}

/**
 * Tween_BackOutEasing()
 */

float Tween_BackOutEasing(float k) {
    float s = 1.70158;
    
    --k;
    
    return k * k * ( ( s + 1 ) * k + s ) + 1;
}

/**
 * Tween_BackInOutEasing()
 */

float Tween_BackInOutEasing(float k) {
    float s = 1.70158 * 1.525;
    
    k *= 2;
    
    if ( k < 1 ) {
        return 0.5 * ( k * k * ( ( s + 1 ) * k - s ) );
    }
    
    k -= 2;
    
    return 0.5 * ( k * k * ( ( s + 1 ) * k + s ) + 2 );
}

/**
 * Tween_BounceInEasing()
 */

float Tween_BounceInEasing(float k) {
    return 1 - Tween_BounceOutEasing( 1 - k );
}

/**
 * Tween_BounceOutEasing()
 */

float Tween_BounceOutEasing(float k) {
    if ( k < ( 1 / 2.75 ) ) {
        return 7.5625 * k * k;
    }
    else if ( k < ( 2 / 2.75 ) ) {
        k -= ( 1.5 / 2.75 );
        
        return 7.5625 * k * k + 0.75;
    }
    else if ( k < ( 2.5 / 2.75 ) ) {
        k -= ( 2.25 / 2.75 );
        
        return 7.5625 * k * k + 0.9375;
    }

    k -= ( 2.625 / 2.75 );
    
    return 7.5625 * k * k + 0.984375;
}

/**
 * Tween_BounceInOutEasing()
 */

float Tween_BounceInOutEasing(float k) {
    if ( k < 0.5 ) {
        return Tween_BounceInEasing( k * 2 ) * 0.5;
    }
    
    return Tween_BounceOutEasing( k * 2 - 1 ) * 0.5 + 0.5;
}
