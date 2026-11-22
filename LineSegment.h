/** \file LineSegment.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include "Point2D.h"
/** \brief Rysowanie prymitywow przez okno SFML i algorytmy rysowania. */
class PrimitiveRenderer;

/** \brief Odcinek wyznaczony przez dwa punkty. */

class LineSegment {
    Point2D start, end;
public:
    /** \brief Przesuwa obiekt. */
    void translate(float dx, float dy);
    /** \brief Obraca obiekt wokol punktu. */
    void rotate(float degrees, Point2D center);
    /** \brief Skaluje obiekt wzgledem punktu. */
    void scale(float sx, float sy, Point2D center);
    LineSegment(Point2D start, Point2D end);
    Point2D getStart() const;
    Point2D getEnd() const;
    void setStart(Point2D point);
    void setEnd(Point2D point);
    /** \brief Rysuje obiekt przez renderer lub okno SFML. */
    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::White,
              bool incremental = false) const;
};
