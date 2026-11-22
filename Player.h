/** \file Player.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
/** \file Player.h
 * \brief Gracz ze sprite sheetami w czterech kierunkach.
 */
#pragma once
#include "SpriteObject.h"
#include <array>
#include <string>

// Jeden obraz 288x24 zawiera 12 klatek po 24x24 piksele.
// Kierunki: 0 dol, 1 gora, 2 lewo, 3 prawo.
/** \brief Postac sterowana WASD z animacjami kierunkowymi. */
class Player : public SpriteObject, public UpdatableObject {
    std::array<sf::Texture, 4> textures;
    sf::Vector2f position;
    int direction = 0;
    int frame = 0;
    float elapsed = 0.f;
    bool walking = false;
    float scaleFactor = 2.f; // 24x24 -> 48x48 na ekranie
    bool loaded = false;
public:
    explicit Player(Point2D start);
    /** \brief Wczytuje cztery arkusze animacji postaci. */
    bool loadAnimations(const std::string& folder);
    /** \brief Aktualizuje stan obiektu na podstawie czasu klatki. */
    void update(float dt) override;
    /** \brief Aktualizuje klatke animacji. */
    void animate(float dt) override;
    /** \brief Rysuje obiekt przez renderer lub okno SFML. */
    void draw(sf::RenderWindow& window) const override;
    /** \brief Rysuje obiekt przez renderer lub okno SFML. */
    void draw(PrimitiveRenderer& renderer) const override;
    /** \brief Przesuwa obiekt. */
    void translate(float dx, float dy) override;
    /** \brief Obraca obiekt wokol punktu. */
    void rotate(float angle, Point2D center) override;
    /** \brief Skaluje obiekt wzgledem punktu. */
    void scale(float sx, float sy, Point2D center) override;
};
