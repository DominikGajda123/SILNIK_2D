/** \file main.cpp
 * \brief Plik projektu SILNIK 2D - SFML 3.1.
 */
#include "Engine.h"

int main() {
    Engine engine(900, 650, 60, false, true, true);
    engine.run();
    return 0;
}
