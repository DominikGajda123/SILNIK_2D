/** \file BitmapHandler.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
/** \file BitmapHandler.h
 * \brief Tworzenie, kopiowanie i zapisywanie bitmap.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Lab 5: proste operacje na bitmapach.
/** \brief Tworzenie, wczytywanie, kopiowanie i zapisywanie bitmap. */
class BitmapHandler {
    sf::Image image;
public:
    /** \brief Tworzy obraz o wskazanym rozmiarze. */
    bool create(unsigned width, unsigned height, sf::Color color = sf::Color::Transparent);
    /** \brief Usuwa dane obrazu. */
    void remove();
    /** \brief Wczytuje obraz z pliku. */
    bool load(const std::string& filename);
    /** \brief Zapisuje bitmapowy obraz do pliku. */
    bool save(const std::string& filename) const;
    /** \brief Kopiuje obraz z innego obiektu. */
    bool copyFrom(const BitmapHandler& source, unsigned destX, unsigned destY);
    /** \brief Wczytuje prostokatny fragment bitmapy. */
    bool loadFragment(const std::string& filename, sf::IntRect rect);
    /** \brief Zapisuje fragment bitmapy. */
    bool saveFragment(const std::string& filename, sf::IntRect rect) const;
    /** \brief Zwraca obraz SFML. */
    const sf::Image& getImage() const { return image; }
};
