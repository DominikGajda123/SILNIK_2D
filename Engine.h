/** \file Engine.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
/** \file Engine.h
 * \brief Glowna petla, okno i zdarzenia silnika 2D.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/** \brief Okno aplikacji, petla glowna, zdarzenia klawiatury i myszy oraz demonstracja funkcji. */

class Engine {
    sf::RenderWindow window;
    sf::Color background = sf::Color(25, 30, 45);
    bool keyboardEnabled = true;
    bool mouseEnabled = true;
    bool running = true;
    /** \brief Zapisuje komunikat bledu do konsoli i pliku. */
    void logError(const std::string& message);
public:
    Engine(unsigned width = 900, unsigned height = 650, unsigned fps = 60,
           bool fullscreen = false, bool keyboard = true, bool mouse = true);
    /** \brief Uruchamia petle glowna i obsluguje zdarzenia oraz rysowanie. */
    void run();
    /** \brief Zamyka okno i zatrzymuje petle. */
    void close();
    /** \brief Czysci okno lub plotno wskazanym kolorem. */
    void clear(const sf::Color& color);
    sf::RenderWindow& getWindow();
};
