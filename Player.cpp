/** \file Player.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "Player.h"
#include "PrimitiveRenderer.h"
#include "Transform2D.h"
#include <cmath>
#include <algorithm>

Player::Player(Point2D start) : position(start.getX(), start.getY()) {}
bool Player::loadAnimations(const std::string& folder) {
    const char* names[] = {"Walk Down.png", "Walk Up.png", "Walk Left.png", "Walk Right.png"};
    loaded = true;
    for (int i = 0; i < 4; ++i) {
        if (!textures[i].loadFromFile(folder + "/" + names[i])) loaded = false;
        else if (textures[i].getSize() != sf::Vector2u{288u, 24u}) loaded = false;
        textures[i].setSmooth(false); // pixel art bez rozmycia
    }
    return loaded;
}
void Player::update(float dt) {
    const float speed = 160.f;
    float dx = 0.f, dy = 0.f;
    using K = sf::Keyboard::Key;
    if (sf::Keyboard::isKeyPressed(K::A)) dx -= 1.f;
    if (sf::Keyboard::isKeyPressed(K::D)) dx += 1.f;
    if (sf::Keyboard::isKeyPressed(K::W)) dy -= 1.f;
    if (sf::Keyboard::isKeyPressed(K::S)) dy += 1.f;
    walking = (dx != 0.f || dy != 0.f);
    if (walking) {
        if (dx < 0) direction = 2;
        else if (dx > 0) direction = 3;
        else if (dy < 0) direction = 1;
        else direction = 0;
        float len = std::sqrt(dx * dx + dy * dy);
        translate(dx / len * speed * dt, dy / len * speed * dt);
    }
    position.x = std::clamp(position.x, 0.f, 900.f - 24.f * scaleFactor);
    position.y = std::clamp(position.y, 0.f, 650.f - 24.f * scaleFactor);
    animate(dt);
}
void Player::animate(float dt) {
    if (!walking) { frame = 0; elapsed = 0.f; return; }
    elapsed += dt;
    if (elapsed >= 0.09f) {
        frame = (frame + 1) % 12;
        elapsed = 0.f;
    }
}
void Player::draw(sf::RenderWindow& window) const {
    if (!loaded) return;
    sf::Sprite sprite(textures[direction]);
    sprite.setTextureRect(sf::IntRect({frame * 24, 0}, {24, 24}));
    sprite.setPosition(position);
    sprite.setScale({scaleFactor, scaleFactor});
    window.draw(sprite);
}
void Player::draw(PrimitiveRenderer& renderer) const {
    // Metoda interfejsu DrawableObject; rysowanie sprite'a odbywa sie przez okno SFML.
    (void)renderer;
}
void Player::translate(float dx, float dy) { position.x += dx; position.y += dy; }
void Player::rotate(float angle, Point2D center) {
    Point2D p(position.x, position.y);
    p = Transform2D::rotate(p, angle, center);
    position = {p.getX(), p.getY()};
}
void Player::scale(float sx, float sy, Point2D center) {
    Point2D p(position.x, position.y);
    p = Transform2D::scale(p, sx, sy, center);
    position = {p.getX(), p.getY()};
    scaleFactor *= (std::abs(sx) + std::abs(sy)) * 0.5f;
}
