/** \file SpriteObject.h
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

// Lab 5: rozszerzenie hierarchii z laboratorium 4.
/** \brief Interfejs animacji klatek. */
class AnimatedObject : public virtual GameObject {
public:
    virtual void animate(float dt) = 0;
};
/** \brief Obiekt bitmapowy rysowany w oknie. */
class BitmapObject : public DrawableObject, public TransformableObject {
public:
    // Rysowanie sprite'ow wykonuje metoda draw() w klasie potomnej.
    virtual void draw(sf::RenderWindow& window) const = 0;
};
/** \brief Bazowy typ animowanych obiektow bitmapowych. */
class SpriteObject : public BitmapObject, public AnimatedObject {
public:
    virtual ~SpriteObject() = default;
};
