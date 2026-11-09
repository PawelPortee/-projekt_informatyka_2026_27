#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int wybor = 0;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Menu");
    sf::Clock zegar;
    sf::Font font;
    if(font.openFromFile("arial.ttf")==true)
    {
        std::cout << "Czcionka się załadowały" << std::endl;
    }
    else
    {
        std::cout << "Ładowanie czacionki spadło z rowerka" << std::endl;
       
    }
    const int N = 3;
    std::string opcje[N] = {"Nowa Gra","Opcja 2","Wyjście"};
    std::vector<sf::Text> menu;
for (int i = 0; i < N; ++i)
{
   menu.emplace_back(
    font,
    sf::String::fromUtf8(opcje[i].begin(), opcje[i].end()),
    72
);
    menu.back().setPosition({250.f, 50.f + i * 150.f});
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
                else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Up)
                        wybor = (wybor + N - 1) % N;
                    if (key->code == sf::Keyboard::Key::Down)
                        wybor = (wybor + 1) % N;
                    if (key->code == sf::Keyboard::Key::Enter)
                        if(wybor==2)
                        {
                            window.close();
                        }
                    
                }
            }
    
        
    
        window.clear();
        for (int i = 0; i < N; i++)
        {
            window.draw(menu[i]);
        }
        window.display();
    }
    

    return 0;
}