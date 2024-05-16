#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;
 
class Juego
{
public:
    Juego();
    ~Juego();

    void loop();

private:
    RenderWindow* wind;
    b2World* mundo;
    b2Body* pelota;

    void eventos();
    void actualizar();
    void dibujar();
    void initPhysics();
};



