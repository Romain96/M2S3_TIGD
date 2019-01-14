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
    unsigned int _x;
    unsigned int _y;
    unsigned char _value;

    // methods
public:
    Pixel();
    Pixel(unsigned int x, unsigned int y, unsigned char value);

    // getters
    unsigned int getX();
    unsigned int getY();
    unsigned char getValue();

    // setters
    void setX(unsigned int x);
    void setY(unsigned int y);
    void setValue(unsigned char value);

    // operators overloading
    bool operator== (Pixel p);
    bool operator!= (Pixel p);
};

#include "../src/Pixel.hxx"

#endif
