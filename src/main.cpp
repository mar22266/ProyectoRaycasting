#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

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
    std::deque<float> frameTimes;       // To store the frame times
    const size_t maxFrameSamples = 100; // Maximum samples for averaging

    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        frameTimes.push_back(deltaTime);

        if (frameTimes.size() > maxFrameSamples)
        {
            frameTimes.pop_front(); // Maintain the size of the deque
        }

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

        // Calculate the average frame time every frame
        float averageFrameTime = 0.0f;
        for (float ft : frameTimes)
        {
            averageFrameTime += ft;
        }
        averageFrameTime /= frameTimes.size();

        // Update the window title with the FPS, calculated as the inverse of the average frame time
        if (!frameTimes.empty())
        {
            int fps = static_cast<int>(1.0f / averageFrameTime);
            window.setTitle("Raycaster - FPS: " + std::to_string(fps));
        }
    }
}
