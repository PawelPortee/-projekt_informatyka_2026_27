#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "klocek.h"
#include "Smok.h"

int main()
{
    int szerokosc = 1200;
    int wysokosc = 900;
    std::setlocale(LC_ALL, "pl_PL.UTF-8");
    int wybor = 0;
    bool czygra = false;
    sf::RenderWindow window(sf::VideoMode({szerokosc, wysokosc}), "Menu");
    sf::Clock zegar;
    sf::Font font;
    Smok smok("Smuk.png");
    std::vector<Klocek> klocki = {
        Klocek(300.f, 250.f, 220.f, 80.f),
        Klocek(900.f, 250.f, 100.f, 220.f),
        Klocek(350.f, 700.f, 280.f, 100.f),
        Klocek(900.f, 680.f, 180.f, 140.f)};
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
            for (const Klocek &klocek : klocki)
                klocek.draw(window);

            const float predkoscSmoka = 2.f;
            float dx = 0.f;
            float dy = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                dx -= predkoscSmoka;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                dx += predkoscSmoka;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                dy -= predkoscSmoka;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                dy += predkoscSmoka;

            if (dx != 0.f && dy != 0.f)
            {
                dx *= 0.7071f;
                dy *= 0.7071f;
            }

            if (dx != 0.f || dy != 0.f)
            {
                smok.ruch(dx, dy);

                sf::FloatRect graniceSmoka = smok.getBounds();
                for (const Klocek &klocek : klocki)
                {
                    sf::FloatRect graniceKlocka = klocek.getBounds();
                    if (graniceSmoka.position.x < graniceKlocka.position.x + graniceKlocka.size.x &&
                        graniceSmoka.position.x + graniceSmoka.size.x > graniceKlocka.position.x &&
                        graniceSmoka.position.y < graniceKlocka.position.y + graniceKlocka.size.y &&
                        graniceSmoka.position.y + graniceSmoka.size.y > graniceKlocka.position.y)
                    {
                        smok.cofnijRuch(dx, dy);
                        break;
                    }
                }
            }

            smok.ograniczDoScian((szerokosc), (wysokosc));
            smok.draw(window);
            window.display();
        }
    }

    return 0;
}