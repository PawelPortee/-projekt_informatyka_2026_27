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
    int kierunek;
    int klatka;

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
        sprite.setPosition({1000.f, 450.f});
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

        if (zegarKlatek.getElapsedTime().asSeconds() >= 0.12f)
        {
            klatka = (klatka + 1) % 3;
            zegarKlatek.restart();
        }

        ustawKlatke();
    }

    void draw(sf::RenderTarget &target)
    {
        target.draw(sprite);
    }
};
