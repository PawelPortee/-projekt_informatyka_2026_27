#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "klocek.h"
#include "Smok.h"

int main()
{
    std::setlocale(LC_ALL, "pl_PL.UTF-8");
    int wybor = 0;
    bool czygra = false;
    sf::RenderWindow window(sf::VideoMode({1200, 900}), "Menu");
    sf::Clock zegar;
    sf::Font font;
    Smok smok("Smuk.png");
    window.setFramerateLimit(60);
    if (font.openFromFile("arial.ttf") == true)
    {
        std::cout << "Czcionka się załadowała" << std::endl;
    }
    else
    {
        std::cout << "Ładowanie czcionki spadło z rowerka" << std::endl;
    }
    const int N = 3;
    std::string opcje[N] = {"Nowa Gra", "Opcja 2", "Wyjście"};
    std::vector<sf::Text> menu;
    for (int i = 0; i < N; ++i)
    {
        menu.emplace_back(
            font,
            sf::String::fromUtf8(opcje[i].begin(), opcje[i].end()),
            72);
        menu.back().setPosition({450.f, 50.f + i * 250.f});
    }
    while (window.isOpen())
    {
        float t = zegar.getElapsedTime().asSeconds();
        for (int i = 0; i < N; i++)
        {
            if (i == wybor)
                menu[i].setFillColor(sf::Color::Red);
            else
                menu[i].setFillColor(sf::Color::White);
        }

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Up)
                {
                    wybor = (wybor + N - 1) % N;
                }
                if (key->code == sf::Keyboard::Key::Down)
                {
                    wybor = (wybor + 1) % N;
                }
                if (key->code == sf::Keyboard::Key::Enter)
                {

                    if (wybor == 0)
                    {
                        czygra = true;
                        std::cout << "Wybrano nową grę" << std::endl;
                    }
                    if (wybor == 2)
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        if (czygra == false)
        {
            for (int i = 0; i < N; i++)
            {
                window.draw(menu[i]);
            }
            window.display();
        }
        else
        {
            const float predkoscSmoka = 4.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                smok.ruch(-predkoscSmoka, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                smok.ruch(predkoscSmoka, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                smok.ruch(0.f, -predkoscSmoka);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                smok.ruch(0.f, predkoscSmoka);

            smok.draw(window);
            window.display();
        }
    }

    return 0;
}