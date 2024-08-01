#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../include/map.h"
#include "../include/player.h"
#include "../include/renderer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Raycaster", sf::Style::Close | sf::Style::Titlebar);

    Map map(48.0f, "./assets/map.png");

    Player player;
    player.position = sf::Vector2f(50, 50);

    Renderer renderer;
    renderer.init();

    sf::Clock gameClock;
    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        player.update(deltaTime);

        window.clear();
        renderer.draw3dView(window, player, map);
        window.display();

        window.setTitle("Raycaster - FPS: " + std::to_string(1.0f / deltaTime));
    }
}
