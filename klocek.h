#pragma once
#include <SFML/Graphics.hpp>

class Klocek
{
    float x, y;
    float szerokosc, wysokosc;
    sf::RectangleShape shape;

public:
    Klocek(float startX, float startY, float szer, float wys,
           sf::Color kolor = sf::Color(255, 0, 0))
        : x(startX),
          y(startY),
          szerokosc(szer),
          wysokosc(wys)
    {
        shape.setSize({szerokosc, wysokosc});
        shape.setOrigin({szerokosc / 2.f, wysokosc / 2.f});
        shape.setPosition({x, y});
        shape.setFillColor(kolor);
    }
    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    void draw(sf::RenderTarget &target) const
    {
        target.draw(shape);
    }
};