/** \file BitmapHandler.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "BitmapHandler.h"

bool BitmapHandler::create(unsigned width, unsigned height, sf::Color color) {
    if (!width || !height) return false;
    image = sf::Image({width, height}, color);
    return true;
}
void BitmapHandler::remove() { image = sf::Image(); }
bool BitmapHandler::load(const std::string& filename) { return image.loadFromFile(filename); }
bool BitmapHandler::save(const std::string& filename) const {
    if (!image.getSize().x || !image.getSize().y) return false;
    return image.saveToFile(filename);
}
bool BitmapHandler::copyFrom(const BitmapHandler& source, unsigned destX, unsigned destY) {
    auto src = source.image.getSize(), dst = image.getSize();
    if (!src.x || !src.y || destX >= dst.x || destY >= dst.y) return false;
    for (unsigned y = 0; y < src.y && y + destY < dst.y; ++y)
        for (unsigned x = 0; x < src.x && x + destX < dst.x; ++x)
            image.setPixel({x + destX, y + destY}, source.image.getPixel({x, y}));
    return true;
}
bool BitmapHandler::loadFragment(const std::string& filename, sf::IntRect rect) {
    BitmapHandler full;
    if (!full.load(filename)) return false;
    auto size = full.image.getSize();
    if (rect.position.x < 0 || rect.position.y < 0 || rect.size.x <= 0 || rect.size.y <= 0 ||
        static_cast<unsigned>(rect.position.x + rect.size.x) > size.x ||
        static_cast<unsigned>(rect.position.y + rect.size.y) > size.y) return false;
    create(static_cast<unsigned>(rect.size.x), static_cast<unsigned>(rect.size.y));
    for (int y = 0; y < rect.size.y; ++y)
        for (int x = 0; x < rect.size.x; ++x)
            image.setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)},
                full.image.getPixel({static_cast<unsigned>(rect.position.x + x),
                                     static_cast<unsigned>(rect.position.y + y)}));
    return true;
}
bool BitmapHandler::saveFragment(const std::string& filename, sf::IntRect rect) const {
    auto size = image.getSize();
    if (rect.position.x < 0 || rect.position.y < 0 || rect.size.x <= 0 || rect.size.y <= 0 ||
        static_cast<unsigned>(rect.position.x + rect.size.x) > size.x ||
        static_cast<unsigned>(rect.position.y + rect.size.y) > size.y) return false;
    BitmapHandler part;
    part.create(static_cast<unsigned>(rect.size.x), static_cast<unsigned>(rect.size.y));
    for (int y = 0; y < rect.size.y; ++y)
        for (int x = 0; x < rect.size.x; ++x)
            part.image.setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)},
                image.getPixel({static_cast<unsigned>(rect.position.x + x),
                                static_cast<unsigned>(rect.position.y + y)}));
    return part.save(filename);
}
