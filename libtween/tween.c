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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tween.h"

/**
 * Tween_CreateEngine()
 */

Tween_Engine* Tween_CreateEngine() {
    Tween_Engine* engine = (Tween_Engine*) malloc(sizeof(Tween_Engine));
    memset(engine, 0, sizeof(Tween_Engine));
    
    return engine;
}

/**
 * Tween_DestroyEngine()
 */

void Tween_DestroyEngine(Tween_Engine* engine) {
    Tween_Node* node = engine->tweens;
    
    while (node) {
        Tween_Node* nextNode = node->next;
        free(node);
        node = nextNode;
    }
    
    free(engine);
}

/**
 * Tween_UpdateEngine()
 */

bool Tween_UpdateEngine(Tween_Engine* engine, uint32_t time) {
    if (!engine->tweens) {
        return false;
    }
    
    Tween_Node* node = engine->tweens;
    Tween_Node* prevNode = NULL;
    
    while (node) {
        if (!Tween_UpdateTween(node->tween, time)) {
            if (prevNode) {
                prevNode->next = node->next;
                free(node);
                node = prevNode->next;
            }
            else {
                engine->tweens = node->next;
                free(node);
                node = engine->tweens;
            }
        }
        else {
            prevNode = node;
            node = node->next;
        }
    }
    
    return true;
}

/**
 * Tween_CreateTween()
 */

Tween* Tween_CreateTween(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, TweenEasing easing, Tween_Callback updateCallback, void* data) {
    Tween* tween = (Tween*) malloc(sizeof(Tween));
    memset(tween, 0, sizeof(Tween));
    
    tween->engine = engine;
    tween->props = props;
    tween->toProps = toProps;
    tween->duration = duration;
    tween->easing = easing;
    tween->updateCallback = updateCallback;
    tween->data = data;
    
    tween->startProps = malloc(sizeof(Tween_Props));
    memset(tween->startProps, 0, sizeof(Tween_Props));
    
    tween->repeatProps = malloc(sizeof(Tween_Props));
    memset(tween->repeatProps, 0, sizeof(Tween_Props));
    
    return tween;
}

/**
 * Tween_CreateTweenEx()
 */

Tween* Tween_CreateTweenEx(Tween_Engine* engine, Tween_Props* props, Tween_Props* toProps, uint32_t duration, uint32_t delay, int repeat, bool yoyo, TweenEasing easing, Tween_Callback startCallback, Tween_Callback updateCallback, Tween_Callback completeCallback, void* data) {
    Tween* tween = Tween_CreateTween(engine, props, toProps, duration, easing, updateCallback, data);
    
    tween->delay = delay;
    tween->repeat = repeat;
    tween->yoyo = yoyo;
    tween->startCallback = startCallback;
    tween->completeCallback = completeCallback;
    
    return tween;
}

/**
 * Tween_ChainTweens()
 */

void Tween_ChainTweens(Tween* tween, Tween* tween2) {
    Tween_Node* node = (Tween_Node*) malloc(sizeof(Tween_Node));
    memset(node, 0, sizeof(Tween_Node));
    node->tween = tween2;
    
    if (tween->chain == NULL) {
        tween->chain = node;
    }
    else {
        Tween_Node* tempNode = tween->chain;
        while(tempNode->next) {
            tempNode = tempNode->next;
        }
        tempNode->next = node;
    }
}

/**
 * Tween_DestroyTween()
 */

void Tween_DestroyTween(Tween* tween) {
    free(tween->startProps);
    free(tween->repeatProps);
    
    Tween_Node* node = tween->chain;
    
    while (node) {
        Tween_Node* nextNode = node->next;
        free(node);
        node = nextNode;
    }
    
    free(tween);
}

/**
 * Tween_StartTween()
 */

void Tween_StartTween(Tween* tween, uint32_t time) {
    tween->startTime = time;
    tween->startTime += tween->delay;
    
    Tween_CopyProps(tween->props, tween->startProps);
    Tween_CopyProps(tween->props, tween->repeatProps);
    
    Tween_Node* node = (Tween_Node*) malloc(sizeof(Tween_Node));
    memset(node, 0, sizeof(Tween_Node));
    node->tween = tween;
    
    if (!tween->engine->tweens) {
        tween->engine->tweens = node;
    }
    else {
        Tween_Node* tempNode = tween->engine->tweens;
        while(tempNode->next) {
            tempNode = tempNode->next;
        }
        tempNode->next = node;
    }
}

/**
 * Tween_StopTween()
 */

void Tween_StopTween(Tween* tween) {
    Tween_Node* node = tween->engine->tweens;
    Tween_Node* prevNode = NULL;
    
    while (node) {
        if (node->tween == tween) {
            if (prevNode) {
                prevNode->next = node->next;
            }
            else {
                tween->engine->tweens = node->next;
            }
            
            free(node);
            
            break;
        }
        else {
            prevNode = node;
            node = node->next;
        }
    }
}

/**
 * Tween_UpdateTween()
 */

bool Tween_UpdateTween(Tween* tween, uint32_t time) {
    if (time < tween->startTime) {
        return true;
    }
    
    if (!tween->startCallbackFired) {
        if (tween->startCallback) {
            tween->startCallback(tween);
        }
        
        tween->startCallbackFired = true;
    }
    
    float elapsed = (float)(time - tween->startTime) / (float)tween->duration;
    elapsed = (elapsed > 1) ? 1 : elapsed;
    
    Tween_UpdateProps(tween->startProps, tween->toProps, tween->props, tweenEasingFuncs[tween->easing](elapsed));
    
    if (tween->updateCallback) {
        tween->updateCallback(tween);
    }
    
    if (elapsed == 1) {
        if (tween->repeat > 0) {
            tween->repeat--;
            
            if (tween->yoyo) {
                Tween_Props* tempProps = tween->repeatProps;
                tween->repeatProps = tween->toProps;
                tween->toProps = tempProps;
                
                tween->reversed = !tween->reversed;
            }
            
            Tween_CopyProps(tween->repeatProps, tween->startProps);
            tween->startTime = time + tween->delay;
            
            return true;
        }
        else {
            
            if (tween->completeCallback) {
                tween->completeCallback(tween);
            }
            
            Tween_Node* node = tween->chain;
            
            while (node) {
                Tween_StartTween(node->tween, time);
                node = node->next;
            }
            
            return false;
        }
    }
    
    return true;
}
