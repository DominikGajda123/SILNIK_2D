/** \file PrimitiveRenderer.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
/** \file PrimitiveRenderer.h
 * \brief Rysowanie prymitywow i algorytmow graficznych.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"

/** \brief Rysowanie prymitywow przez okno SFML i algorytmy rysowania. */

class PrimitiveRenderer {
    sf::RenderWindow& window;
public:
    explicit PrimitiveRenderer(sf::RenderWindow& window);
    /** \brief Rysuje okrag algorytmicznie. */
    void drawAlgorithmCircle(Point2D center,int radius,sf::Color color);
    /** \brief Rysuje elipse algorytmicznie. */
    void drawAlgorithmEllipse(Point2D center,int rx,int ry,sf::Color color);
    /** \brief Rysuje wielokat po sprawdzeniu przeciec krawedzi. */
    bool drawPolygon(const std::vector<Point2D>& points,sf::Color color);
    /** \brief Rysuje punkt. */
    void drawPoint(const Point2D& point, sf::Color color = sf::Color::White);
    /** \brief Rysuje odcinek. */
    void drawLine(const Point2D& a, const Point2D& b, sf::Color color = sf::Color::White);
    /** \brief Rysuje odcinek algorytmem przyrostowym DDA. */
    void drawIncrementalLine(const Point2D& a, const Point2D& b, sf::Color color = sf::Color::White);
    /** \brief Rysuje prostokat. */
    void drawRectangle(float x, float y, float width, float height, sf::Color color, bool filled = true);
    /** \brief Rysuje okrag lub kolo. */
    void drawCircle(float x, float y, float radius, sf::Color color, bool filled = true);
    /** \brief Rysuje trojkat. */
    void drawTriangle(const Point2D& a, const Point2D& b, const Point2D& c, sf::Color color);
    /** \brief Rysuje lamana. */
    void drawPolyline(const std::vector<Point2D>& points, sf::Color color, bool closed = false, bool incremental = false);
};
