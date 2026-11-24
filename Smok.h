#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Smok
{
    sf::Texture Tsmok;
    sf::Sprite sprite;
    sf::Clock zegarKlatek;
    const int szerokoscKlatki = 192;
    const int wysokoscKlatki = 192;
    int kierunek = 3;
    int klatka = 0;

    void ustawKlatke()
    {
        int rzad;
        switch (kierunek)
        {
        case 1:
            rzad = 3;
            break; // gora
        case 2:
            rzad = 2;
            break; // prawo
        case 3:
            rzad = 0;
            break; // dol
        case 4:
            rzad = 1;
            break; // lewo
        }

        sprite.setTextureRect(sf::IntRect(
            {klatka * static_cast<int>(szerokoscKlatki),
             rzad * static_cast<int>(wysokoscKlatki)},
            {static_cast<int>(szerokoscKlatki),
             static_cast<int>(wysokoscKlatki)}));
    }

public:
    Smok(std::string sciezka) : sprite(Tsmok)
    {
        Tsmok.loadFromFile(sciezka);

        sprite.setOrigin({szerokoscKlatki / 2.f, wysokoscKlatki / 2.f});
        sprite.setScale({0.5f, 0.5f});
        sprite.setPosition({600.f, 450.f});
        ustawKlatke();
    }

    void ruch(float dx, float dy)
    {
        if (dx < 0.f)
            kierunek = 4;
        else if (dx > 0.f)
            kierunek = 2;
        else if (dy < 0.f)
            kierunek = 1;
        else
            kierunek = 3;

        sprite.move({dx, dy});

        if (zegarKlatek.getElapsedTime().asSeconds() >= 0.24f)
        {
            if (kierunek == 4 || kierunek == 1)
                klatka = (klatka + 2) % 3;
            else
                klatka = (klatka + 1) % 3;

            zegarKlatek.restart();
        }

        ustawKlatke();
    }

    void cofnijRuch(float dx, float dy)
    {
        sprite.move({-dx, -dy});
    }

    void ograniczDoScian(float szerokosc, float wysokosc)
    {
        sf::FloatRect granice = sprite.getGlobalBounds();
        sf::Vector2f pozycja = sprite.getPosition();

        if (granice.position.x < 0.f)
            pozycja.x -= granice.position.x;
        else if (granice.position.x + granice.size.x > szerokosc)
            pozycja.x -= granice.position.x + granice.size.x - szerokosc;

        if (granice.position.y < 0.f)
            pozycja.y -= granice.position.y;
        else if (granice.position.y + granice.size.y > wysokosc)
            pozycja.y -= granice.position.y + granice.size.y - wysokosc;

        sprite.setPosition(pozycja);
    }

    sf::FloatRect getBounds() const
    {
        sf::FloatRect granice = sprite.getGlobalBounds();
        granice.position.y += 15.f;
        granice.size.y -= 15.f;
        return granice;
    }

    void draw(sf::RenderTarget &target)
    {
        target.draw(sprite);
    }
};
