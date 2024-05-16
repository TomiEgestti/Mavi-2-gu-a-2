#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

class Juego {
public:
    Juego();
    ~Juego();

    void loop();

private:
    sf::RenderWindow* wind;
    b2World* mundo;
    b2Body* bloque;
    b2Body* suelo;

    void eventos();
    void actualizar();
    void dibujar();
    void initPhysics();
};