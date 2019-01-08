#ifndef __PIXEL_H__
#define __PIXEL_H__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

// pixel class : contains pixel coordinates X,Y and its intensity [0-255]
class Pixel
{
    // attributes
protected:
    unsigned char _x;
    unsigned char _y;
    unsigned char _value;

    // methods
public:
    Pixel();
    Pixel(unsigned char x, unsigned char y, unsigned char value);

    // getters
    unsigned char getX();
    unsigned char getY();
    unsigned char getValue();

    // setters
    void setX(unsigned char x);
    void setY(unsigned char y);
    void setValue(unsigned char value);

    // operators overloading
    bool operator== (Pixel p);
    bool operator!= (Pixel p);
};

#include "../src/Pixel.hxx"

#endif
