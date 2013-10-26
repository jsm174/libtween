libtween 0.2
------------

*** What is libtween?

libtween is a tweening engine written in C. 

It is a port of "Javascript Tweening Engine" by @sole and others at:

   https://github.com/sole/tween.js

*** How do I build the source?

   ./configure
   make
   sudo make install

*** Usage

To use libtween

   1) create callback function that updates properties of an object
   2) create a Tween_Engine
   3) create Tween_Props structures that represents the start and to properties of an object
   4) create a Tween with Tween_Engine, Tween_Props, duration, easing, and callback parameters 
   5) start the Tween
   6) update the Tween_Engine in an animation loop
   7) destroy Tween
   8) destroy Tween_Engine
 
   RECT gRect;

   void update(Tween* tween) {
     gRect.x = tween->props->x;
     gRect.y = tween->props->y;
   }
   
   .
   .
   .

      Tween_Engine* engine = Tween_CreateEngine();
      Tween_Props props = Tween_MakeProps(x1, y1, w1, h1, rot1);
      Tween_Props toProps = Tween_MakeProps(x2, y2, w2, h2, rot2);
      Tween* tween = Tween_CreateTween(engine, &props, &toProps, duration,
         TWEEN_EASING_ELASTIC_IN_OUT, update, NULL);
         Tween_Start(engine, SDL_GetTicks()); 

      while(!terminate) {
         Tween_UpdateEngine(engine, SDL_GetTicks());
      
         .
         .
      }
   
      Tween_Destroy(tween);
      Tween_Engine(engine);

*** Examples

Currently libtween comes with two examples, hello_world and bars. 

These examples closely match the tween.js examples at:

   http://sole.github.io/tween.js/examples/00_hello_world.html
   http://sole.github.io/tween.js/examples/01_bars.html

To run the examples, you must have SDL2 installed on your system

*** Differences from tween.js

libtween is a thorough port of tween.js with a few differences. Tween_Props structures are used simulate javascript properties and contains the following variables:

    x, y, width, height, rotation, r, g, b, a

Tween_Props currently has no concept of arrays. Because of this, the interpolation features of tween.js have not been ported.
