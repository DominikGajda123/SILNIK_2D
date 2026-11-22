/** \file Point2D.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include <SFML/Graphics.hpp>
/** \brief Rysowanie prymitywow przez okno SFML i algorytmy rysowania. */
class PrimitiveRenderer;

/** \brief Punkt 2D, dostep do wspolrzednych i przeksztalcenia. */

class Point2D {
    float x, y;
public:
    /** \brief Przesuwa obiekt. */
    void translate(float dx, float dy);
    /** \brief Obraca obiekt wokol punktu. */
    void rotate(float degrees, const Point2D& center);
    /** \brief Skaluje obiekt wzgledem punktu. */
    void scale(float sx, float sy, const Point2D& center);
    Point2D(float x = 0, float y = 0);
    /** \brief Zwraca wspolrzedna X. */
    float getX() const;
    /** \brief Zwraca wspolrzedna Y. */
    float getY() const;
    /** \brief Ustawia wspolrzedna X. */
    void setX(float value);
    /** \brief Ustawia wspolrzedna Y. */
    void setY(float value);
    /** \brief Ustawia wspolrzedne punktu. */
    void setPosition(float newX, float newY);
    /** \brief Zwraca pozycje jako wektor SFML. */
    sf::Vector2f position() const;
    /** \brief Rysuje obiekt przez renderer lub okno SFML. */
    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::White) const;
};
