#ifndef __PIXEL_HXX__
#define __PIXEL_HXX__

#include "../include/Pixel.h"

// constructor
Pixel::Pixel() :
    _x(0),
    _y(0),
    _value(0)
{
    // nothing
}

Pixel::Pixel(unsigned int x, unsigned int y, unsigned char value) :
    _x(x),
    _y(y),
    _value(value)
{
    // nothing
}

// getters
unsigned int Pixel::getX()
{
    return _x;
}

unsigned int Pixel::getY()
{
    return _y;
}

unsigned char Pixel::getValue()
{
    return _value;
}

// setters
void Pixel::setX(unsigned int x)
{
    _x = x;
}

void Pixel::setY(unsigned int y)
{
    _y = y;
}

void Pixel::setValue(unsigned char value)
{
    _value = value;
}

// operatorr overloading
bool Pixel::operator== (Pixel p)
{
    return (p.getX() == this->getX()) && (p.getY() == this->getY());
}

bool Pixel::operator!= (Pixel p)
{
    return (p.getX() != this->getX()) || (p.getY() != this->getY());
}

#endif
