/** \file Point2D.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "Point2D.h"
#include "PrimitiveRenderer.h"
Point2D::Point2D(float x, float y) : x(x), y(y) {}
float Point2D::getX() const { return x; }
float Point2D::getY() const { return y; }
void Point2D::setX(float value) { x = value; }
void Point2D::setY(float value) { y = value; }
void Point2D::setPosition(float newX, float newY) { x = newX; y = newY; }
sf::Vector2f Point2D::position() const { return {x, y}; }
void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) const { renderer.drawPoint(*this, color); }

#include "Transform2D.h"
void Point2D::translate(float dx,float dy){*this=Transform2D::translate(*this,dx,dy);}
void Point2D::rotate(float a,const Point2D& c){*this=Transform2D::rotate(*this,a,c);}
void Point2D::scale(float sx,float sy,const Point2D& c){*this=Transform2D::scale(*this,sx,sy,c);}
