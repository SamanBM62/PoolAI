#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

int main()
{
    sf::RenderWindow window{sf::VideoMode({1920u, 1080u}),
         "Not sure what to put?", 
         sf::Style::Titlebar | sf::Style::Close};
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if(event->is<sf::Event::KeyPressed>()) {
                std::cout << "whattttt" << std::endl;
            }
        }

        window.clear();
        window.display();
    }
}
