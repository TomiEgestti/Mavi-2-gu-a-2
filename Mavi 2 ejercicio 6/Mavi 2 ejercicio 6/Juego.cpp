#include "Juego.h"
Juego::Juego()
    : window(VideoMode(800, 600), "Cañon"),cannon(50.f),
    bullet(Vector2f(10.f, 5.f)) {
    cannon.setFillColor(Color::Red);
    cannon.setPosition(50.f, window.getSize().y - 50.f);

    bullet.setFillColor(Color::Blue);
    bullet.setPosition(0.f, 0.f);
    bulletVelocity = Vector2f(5.f, -2.f); 
}

void Juego::loop() {
    while (window.isOpen()) {
        eventos();
        actualizar();
        dibujar();
    }
}

void Juego::eventos() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            bullet.setPosition(cannon.getPosition()); 
            
            Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            bulletVelocity = mousePos - cannon.getPosition();
         
            float magnitude = sqrt(bulletVelocity.x * bulletVelocity.x + bulletVelocity.y * bulletVelocity.y);
            bulletVelocity /= magnitude;
            
            bulletVelocity *= 5.f;
        }
    }
}

void Juego::actualizar() {
    bullet.move(bulletVelocity); 
}

void Juego::dibujar() {
    window.clear(Color::White);
    window.draw(cannon);
    window.draw(bullet);
    window.display();
}