#include "Juego.h"
Juego::Juego() {
    wind = new RenderWindow(VideoMode(800, 600), "Caja en plano inclinado");
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

void Juego::initPhysics() {
    mundo = new b2World(b2Vec2(0.0f, 9.8f));

    b2BodyDef cajaDef;
    cajaDef.type = b2_dynamicBody;
    cajaDef.position.Set(400.0f, 100.0f);
    caja = mundo->CreateBody(&cajaDef);
    b2PolygonShape formacaja;
    formacaja.SetAsBox(50.0f, 50.0f);
    b2FixtureDef cajaFix;
    cajaFix.shape = &formacaja;
    cajaFix.density = 1.0f;
    cajaFix.friction = 0.3f; 
    caja->CreateFixture(&cajaFix);

    b2BodyDef sueloDef;
    sueloDef.type = b2_staticBody;
    b2PolygonShape formasuelo;
    float radians = 30 * b2_pi / 180; 
    formasuelo.SetAsBox(300.0f, 10.0f, b2Vec2(400.0f, 500.0f), radians); 
    b2FixtureDef sueloFix;
    sueloFix.shape = &formasuelo;
    mundo->CreateBody(&sueloDef)->CreateFixture(&sueloFix);
}

void Juego::dibujar() {
    wind->clear(Color::White);

    RectangleShape sueloshape(Vector2f(600.0f, 20.0f));
    sueloshape.setFillColor(Color::Green);
    sueloshape.setOrigin(sueloshape.getSize().x / 2, sueloshape.getSize().y / 2);
    sueloshape.setPosition(400.0f, 500.0f);
    sueloshape.setRotation(30.0f);
    wind->draw(sueloshape);

    RectangleShape cajashape(Vector2f(100.0f, 100.0f));
    cajashape.setOrigin(50.0f, 50.0f);
    cajashape.setPosition(caja->GetPosition().x, caja->GetPosition().y);
    cajashape.setRotation(caja->GetAngle() * 180.0f / b2_pi);
    cajashape.setFillColor(Color::Red);
    wind->draw(cajashape);

    wind->display();
}