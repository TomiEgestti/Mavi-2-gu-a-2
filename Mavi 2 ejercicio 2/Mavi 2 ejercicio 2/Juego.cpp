#include "Juego.h"

Juego::Juego() {
    wind = new sf::RenderWindow(sf::VideoMode(800, 600), "Pelota Rebotante");
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

    CircleShape pelotaShape(20.0f);
    pelotaShape.setOrigin(20.0f, 20.0f);
    pelotaShape.setPosition(pelota->GetPosition().x, pelota->GetPosition().y);
    pelotaShape.setFillColor(sf::Color::Red);
    wind->draw(pelotaShape);

    RectangleShape barreraShape(Vector2f(20.0f, 600.0f));
    barreraShape.setFillColor(Color::Black);

    barreraShape.setPosition(0.0f, 0.0f); 
    wind->draw(barreraShape);
    barreraShape.setPosition(780.0f, 0.0f); 
    wind->draw(barreraShape);

    barreraShape.setSize(sf::Vector2f(800.0f, 20.0f)); 
    barreraShape.setPosition(0.0f, 0.0f); 
    wind->draw(barreraShape);
    barreraShape.setPosition(0.0f, 580.0f); 
    wind->draw(barreraShape);

    wind->display();
}

void Juego::initPhysics() {
    mundo = new b2World(b2Vec2(0.0f, 9.8f));

    b2BodyDef pelotaDef;
    pelotaDef.type = b2_dynamicBody;
    pelotaDef.position.Set(400.0f, 300.0f);
    pelota = mundo->CreateBody(&pelotaDef);
    b2CircleShape pelotaShape;
    pelotaShape.m_radius = 20.0f;
    b2FixtureDef pelotaFixtureDef;
    pelotaFixtureDef.shape = &pelotaShape;
    pelotaFixtureDef.density = 1.0f;
    pelotaFixtureDef.restitution = 1.0f;
    pelota->CreateFixture(&pelotaFixtureDef);
    b2Vec2 initialVelocity(-3.0f, 0.0f); 
    pelota->SetLinearVelocity(initialVelocity);

    b2BodyDef barreraDef;
    b2Body* barrera;
    b2PolygonShape barreraShape;

    b2BodyDef bordeVerticalDef;
    bordeVerticalDef.type = b2_staticBody;
    b2Body* bordeVertical;

    b2PolygonShape formaBordeVertical;
    formaBordeVertical.SetAsBox(5.0f, 300.0f); 

    bordeVerticalDef.position.Set(-5.0f, 300.0f);
    bordeVertical = mundo->CreateBody(&bordeVerticalDef);
    bordeVertical->CreateFixture(&formaBordeVertical, 0.0f);

    bordeVerticalDef.position.Set(805.0f, 300.0f);
    bordeVertical = mundo->CreateBody(&bordeVerticalDef);
    bordeVertical->CreateFixture(&formaBordeVertical, 0.0f);

    b2BodyDef bordeHorizontalDef;
    bordeHorizontalDef.type = b2_staticBody;
    b2Body* bordeHorizontal;

    b2PolygonShape formaBordeHorizontal;
    formaBordeHorizontal.SetAsBox(400.0f, 5.0f); 

    bordeHorizontalDef.position.Set(400.0f, -5.0f);
    bordeHorizontal = mundo->CreateBody(&bordeHorizontalDef);
    bordeHorizontal->CreateFixture(&formaBordeHorizontal, 0.0f);

    bordeHorizontalDef.position.Set(400.0f, 605.0f);
    bordeHorizontal = mundo->CreateBody(&bordeHorizontalDef);
    bordeHorizontal->CreateFixture(&formaBordeHorizontal, 0.0f);
}