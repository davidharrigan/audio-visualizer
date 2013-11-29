
#ifndef COLOR_H
#define COLOR_H

class Color {
public:
   Color();
   Color( float red, float green, float blue, float alpha = 1.0f ); 

   void set( float red, float green, float blue, float alpha = 1.0f );

   float r, g, b, a;
};

#endif /* COLOR_H */
