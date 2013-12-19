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

double Tween_LinearEasing(double);
double Tween_QuadraticInEasing(double);
double Tween_QuadraticOutEasing(double);
double Tween_QuadraticInOutEasing(double);
double Tween_CubicInEasing(double);
double Tween_CubicOutEasing(double);
double Tween_CubicInOutEasing(double);
double Tween_QuarticInEasing(double);
double Tween_QuarticOutEasing(double);
double Tween_QuarticInOutEasing(double);
double Tween_QuinticInEasing(double);
double Tween_QuinticOutEasing(double);
double Tween_QuinticInOutEasing(double);
double Tween_SinusoidalInEasing(double);
double Tween_SinusoidalOutEasing(double);
double Tween_SinusoidalInOutEasing(double);
double Tween_ExponentialInEasing(double);
double Tween_ExponentialOutEasing(double);
double Tween_ExponentialInOutEasing(double);
double Tween_CircularInEasing(double);
double Tween_CircularOutEasing(double);
double Tween_CircularInOutEasing(double);
double Tween_ElasticInEasing(double);
double Tween_ElasticOutEasing(double);
double Tween_ElasticInOutEasing(double);
double Tween_BackInEasing(double);
double Tween_BackOutEasing(double);
double Tween_BackInOutEasing(double);
double Tween_BounceInEasing(double);
double Tween_BounceOutEasing(double);
double Tween_BounceInOutEasing(double);

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

double Tween_LinearEasing(double k) {
    return k;
}

/**
 * Tween_QuadraticInEasing()
 */

double Tween_QuadraticInEasing(double k) {
    return k * k;
}

/**
 * Tween_QuadraticOutEasing()
 */

double Tween_QuadraticOutEasing(double k) {
    return k * ( 2 - k );
}

/**
 * Tween_QuadraticInOutEasing()
 */

double Tween_QuadraticInOutEasing(double k) {
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

double Tween_CubicInEasing(double k) {
    return k * k * k;
}

/**
 * Tween_CubicOutEasing()
 */

double Tween_CubicOutEasing(double k) {
    --k;
    
    return k * k * k + 1;
}

/**
 * Tween_CubicInOutEasing()
 */

double Tween_CubicInOutEasing(double k) {
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

double Tween_QuarticInEasing(double k) {
    return k * k * k * k;
}

/**
 * Tween_QuarticOutEasing()
 */

double Tween_QuarticOutEasing(double k) {
    --k;
    
    return 1 - ( k * k * k * k );
}

/**
 * Tween_QuarticInOutEasing()
 */

double Tween_QuarticInOutEasing(double k) {
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

double Tween_QuinticInEasing(double k) {
    return k * k * k * k * k;
}

/**
 * Tween_QuinticOutEasing()
 */

double Tween_QuinticOutEasing(double k) {
    --k;
    
    return k * k * k * k * k + 1;
}

/**
 * Tween_QuinticInOutEasing()
 */

double Tween_QuinticInOutEasing(double k) {
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

double Tween_SinusoidalInEasing(double k) {
    return 1 - cos( k * PI / 2 );
}

/**
 * Tween_SinusoidalOutEasing()
 */

double Tween_SinusoidalOutEasing(double k) {
    return sin( k * PI / 2 );
}

/**
 * Tween_SinusoidalInOutEasing()
 */

double Tween_SinusoidalInOutEasing(double k) {
    return 0.5 * ( 1 - cos( PI * k ) );
}

/**
 * Tween_ExponentialInEasing()
 */

double Tween_ExponentialInEasing(double k) {
    return k == 0 ? 0 : pow( 1024, k - 1 );
}

/**
 * Tween_ExponentialOutEasing()
 */

double Tween_ExponentialOutEasing(double k) {
    return k == 1 ? 1 : 1 - pow( 2, - 10 * k );
}

/**
 * Tween_ExponentialInOutEasing()
 */

double Tween_ExponentialInOutEasing(double k) {
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

double Tween_CircularInEasing(double k) {
    return 1 - sqrt( 1 - k * k );

}

/**
 * Tween_CircularOutEasing()
 */

double Tween_CircularOutEasing(double k) {
    --k;
    
    return sqrt( 1 - ( k * k ) );
}

/**
 * Tween_CircularInOutEasing()
 */

double Tween_CircularInOutEasing(double k) {
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

double Tween_ElasticInEasing(double k) {
    double s;
    double a = 0.1;
    double p = 0.4;
    
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

double Tween_ElasticOutEasing(double k) {
    double s;
    double a = 0.1;
    double p = 0.4;
    
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

double Tween_ElasticInOutEasing(double k) {
    double s;
    double a = 0.1;
    double p = 0.4;
    
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

double Tween_BackInEasing(double k) {
    double s = 1.70158;
    return k * k * ( ( s + 1 ) * k - s );
}

/**
 * Tween_BackOutEasing()
 */

double Tween_BackOutEasing(double k) {
    double s = 1.70158;
    
    --k;
    
    return k * k * ( ( s + 1 ) * k + s ) + 1;
}

/**
 * Tween_BackInOutEasing()
 */

double Tween_BackInOutEasing(double k) {
    double s = 1.70158 * 1.525;
    
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

double Tween_BounceInEasing(double k) {
    return 1 - Tween_BounceOutEasing( 1 - k );
}

/**
 * Tween_BounceOutEasing()
 */

double Tween_BounceOutEasing(double k) {
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

double Tween_BounceInOutEasing(double k) {
    if ( k < 0.5 ) {
        return Tween_BounceInEasing( k * 2 ) * 0.5;
    }
    
    return Tween_BounceOutEasing( k * 2 - 1 ) * 0.5 + 0.5;
}
