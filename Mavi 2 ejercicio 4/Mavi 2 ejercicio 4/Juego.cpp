#include "Juego.h"
Juego::Juego() {
    wind = new sf::RenderWindow(sf::VideoMode(800, 600), "Mover caja");
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
        switch (evento.type) {
        case Event::Closed:
            wind->close();
            break;
        case Event::KeyPressed:
           if (Keyboard::isKeyPressed(Keyboard::Left)) {
                moverizq();
            }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                moverder();
                std::cout << "der";
             }
            break;
        }
    }

}

void Juego::actualizar() {
    mundo->Step(1.0f / 60, 8, 8);
}

void Juego::initPhysics() {
    mundo = new b2World(b2Vec2(0.0f, 9.8f));

    b2Body* piso;
    b2BodyDef pisoDef;
    pisoDef.type = b2_staticBody;
    b2PolygonShape forma;
    forma.SetAsBox(800.0f, 5.0f);
    b2FixtureDef pisoFix;
    pisoFix.shape = &forma;
    pisoFix.density = 0.0f;
    pisoFix.friction = 0.3f;
    pisoDef.position.Set(0.0f, 620.0f);
    piso = mundo->CreateBody(&pisoDef);
    piso->CreateFixture(&pisoFix);

    b2BodyDef cajaDef;
    cajaDef.type = b2_dynamicBody;
    b2FixtureDef cajaFix;
    b2PolygonShape formacaja;
    cajaFix.shape = &formacaja;
    cajaFix.density = 1.0;
    formacaja.SetAsBox(50.0f, 50.0f);
    cajaDef.position.Set(400.0f, 200.0f);

    caja = mundo->CreateBody(&cajaDef);
    caja->CreateFixture(&cajaFix);

}

void Juego::dibujar() {
    wind->clear(Color::White);

    RectangleShape cajashape(Vector2f(40.0f, 40.0f));
    cajashape.setOrigin(20.0f, 20.0f);
    cajashape.setPosition(caja->GetPosition().x, caja->GetPosition().y);
    cajashape.setFillColor(sf::Color::Red);
    wind->draw(cajashape);

    RectangleShape pisoshape(Vector2f(800.0f, 5.0f));
    pisoshape.setFillColor(Color::Black);
    pisoshape.setPosition(0.0f, 580.0f);
    wind->draw(pisoshape);
   
    wind->display();
}

void Juego::moverizq(){
    caja->ApplyLinearImpulseToCenter(b2Vec2(-1000.0f, 0.0f), true);
}

void Juego::moverder() {
    caja->ApplyLinearImpulseToCenter(b2Vec2(1000.0f, 0.0f), true);
}
