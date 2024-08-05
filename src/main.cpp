#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <SFML/System/Time.hpp>

#include "../include/map.h"
#include "../include/imgui-SFML.h"
#include "../include/imgui.h"
#include "../include/editor.h"
#include "../include/player.h"
#include "../include/renderer.h"
#include "../include/resources.h"
#include <iostream>
int main(int argc, const char **argv) {
  sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Raycaster",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true);
  if (!ImGui::SFML::Init(window)) {
    std::cerr << "Failed to init ImGui\n";
    return 1;
  }
  if (!Resources::texturesImage.loadFromFile("./assets/textures.png")) {
    std::cerr << "Failed to load textures.png!\n";
  }
  Resources::textures.loadFromImage(Resources::texturesImage);

  Player player{};
  player.position = sf::Vector2f(1.2f, 1.2f);

  Renderer renderer{};
  renderer.init();

  Editor editor{};
  editor.init(window);

  Map map{};
  if (argc > 1) {
    editor.savedFileName = argv[1];
    map.load(editor.savedFileName);
  }
  enum class State { Editor, Game } state = State::Game;
  sf::Clock gameClock;
  while (window.isOpen()) {
    sf::Time deltaTime = gameClock.restart();
    ImGui::SFML::Update(window, deltaTime);
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape) {
        state = state == State::Game ? State::Editor : State::Game;
      }
      if (state == State::Editor) {
        editor.handleEvent(event);
      }
      ImGui::SFML::ProcessEvent(window, event);
    }
    window.clear();
    if (state == State::Game) {
      window.setView(window.getDefaultView());
      player.update(deltaTime.asSeconds(), map);
      renderer.draw3dView(window, player, map);
    } else {
      editor.run(window, map);
    }
    ImGui::SFML::Render(window);
    window.display();
    window.setTitle("Raycaster | " +
                    std::to_string(1.0f / deltaTime.asSeconds()));
  }
  ImGui::SFML::Shutdown();
}