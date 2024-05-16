#include "Juego.h"
Juego::Juego() {
    wind = new sf::RenderWindow(sf::VideoMode(800, 600), "Cubo cayendo");
    initPhysics();
}

Juego::~Juego() {
    delete wind;
    delete mundo;
}

void Juego::loop() {
    while (wind->isOpen()) {
        eventos();
        actualizar();
        dibujar();
    }
}

void Juego::eventos() {
    Event evento;
    while (wind->pollEvent(evento)) {
        if (evento.type == Event::Closed)
            wind->close();
    }
}

void Juego::actualizar() {
    mundo->Step(1.0f / 60, 8, 8);
}

void Juego::dibujar() {
    wind->clear(Color::White);

    // Dibujar el suelo
    sf::RectangleShape sueloShape(sf::Vector2f(800.0f, 20.0f));
    sueloShape.setPosition(0.0f, 580.0f);
    sueloShape.setFillColor(Color::Green);
    wind->draw(sueloShape);

    // Dibujar el bloque
    RectangleShape bloqueShape(Vector2f(40.0f, 40.0f));
    bloqueShape.setPosition(bloque->GetPosition().x - 20.0f, bloque->GetPosition().y - 20.0f);
    bloqueShape.setFillColor(Color::Blue);
    wind->draw(bloqueShape);

    wind->display();
}

void Juego::initPhysics() {
    mundo = new b2World(b2Vec2(0.0f, 9.81f));

    // Crear el suelo
    b2BodyDef sueloDef;
    sueloDef.position.Set(400.0f, 590.0f);
    suelo = mundo->CreateBody(&sueloDef);
    b2PolygonShape sueloShape;
    sueloShape.SetAsBox(400.0f, 10.0f);
    suelo->CreateFixture(&sueloShape, 0.0f);

    // Crear el bloque
    b2BodyDef bloqueDef;
    bloqueDef.type = b2_dynamicBody;
    bloqueDef.position.Set(400.0f, 100.0f);
    bloque = mundo->CreateBody(&bloqueDef);
    b2PolygonShape bloqueShape;
    bloqueShape.SetAsBox(20.0f, 20.0f);
    b2FixtureDef bloqueFixtureDef;
    bloqueFixtureDef.shape = &bloqueShape;
    bloqueFixtureDef.density = 1.0f;
    bloque->CreateFixture(&bloqueFixtureDef);
}