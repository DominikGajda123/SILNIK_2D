/** \file PixelCanvas.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
/** \file PixelCanvas.h
 * \brief Pikselowe plotno do rysowania i wypelniania obszarow.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
/** \brief Pikselowe plotno; rysowanie, wypelnianie, gumka i zapis obrazu. */
class PixelCanvas {
 unsigned width,height;
 std::vector<sf::Color> pixels;
 sf::Texture texture;
 bool dirty=true;
 bool inside(int x,int y)const{return x>=0&&y>=0&&x<int(width)&&y<int(height);}
public:
 PixelCanvas(unsigned w,unsigned h);
    /** \brief Czysci okno lub plotno wskazanym kolorem. */
 void clear(sf::Color color=sf::Color::White);
    /** \brief Odczytuje kolor piksela. */
 sf::Color get(int x,int y)const;
    /** \brief Ustawia kolor piksela. */
 void set(int x,int y,sf::Color c);
    /** \brief Nanosi okragly slad pedzla. */
 void brush(int x,int y,int radius,sf::Color color);
    /** \brief Rysuje linie na plotnie pikselowym. */
 void line(int x0,int y0,int x1,int y1,sf::Color color,int thickness=1);
    /** \brief Rysuje prostokat na plotnie. */
 void rectangle(int x0,int y0,int x1,int y1,sf::Color color,bool filled);
    /** \brief Rysuje elipse na plotnie. */
 void ellipse(int cx,int cy,int rx,int ry,sf::Color color,bool filled);
    /** \brief Rysuje wielokat na plotnie. */
 void polygon(const std::vector<sf::Vector2i>& points,sf::Color color,bool filled);
    /** \brief Wypelnia spojny obszar kolorem. */
 void floodFill(int x,int y,sf::Color fill,bool eight=false);
    /** \brief Wypelnia obszar do wskazanego koloru granicy. */
 void boundaryFill(int x,int y,sf::Color boundary,sf::Color fill);
    /** \brief Wykrywa kolor zamknietej granicy i wypelnia obszar. */
 void boundaryFillAuto(int x,int y,sf::Color fill);
    /** \brief Przesyla piksele plotna do tekstury i rysuje. */
 void render(sf::RenderWindow& window);
    /** \brief Zapisuje bitmapowy obraz do pliku. */
 bool save(const std::string& path)const;
};
