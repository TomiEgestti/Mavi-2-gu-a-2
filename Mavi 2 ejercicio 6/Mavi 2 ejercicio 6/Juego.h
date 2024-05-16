#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

class Juego {
public:
    Juego();

    void loop();

private:
    void eventos();
    void actualizar();
    void dibujar();

    RenderWindow window;
    CircleShape cannon;
    RectangleShape bullet;
    Vector2f bulletVelocity;
};