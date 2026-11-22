/** \file Shapes.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include "GameObject.h"
#include "PrimitiveRenderer.h"
#include <vector>
/** \brief Wielokat z przesuwaniem, obrotem i skalowaniem. */
class PolygonObject : public ShapeObject {
 std::vector<Point2D> points;
 sf::Color color;
public:
 PolygonObject(std::vector<Point2D> pts,sf::Color c):points(std::move(pts)),color(c){}
    /** \brief Rysuje obiekt przez renderer lub okno SFML. */
 void draw(PrimitiveRenderer& r) const override {r.drawPolygon(points,color);}
    /** \brief Przesuwa obiekt. */
 void translate(float x,float y) override {for(auto& p:points)p=Transform2D::translate(p,x,y);}
    /** \brief Obraca obiekt wokol punktu. */
 void rotate(float a,Point2D c) override {for(auto& p:points)p=Transform2D::rotate(p,a,c);}
    /** \brief Skaluje obiekt wzgledem punktu. */
 void scale(float x,float y,Point2D c) override {for(auto& p:points)p=Transform2D::scale(p,x,y,c);}
};
