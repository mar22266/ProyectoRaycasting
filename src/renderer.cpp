#include "../include/renderer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>
#include "algorithm"
#include <iostream>

constexpr float PI = 3.141592653589793f;
constexpr float PLAYER_FOV = 60.0f;
constexpr size_t MAX_RAYCAST_DEPTH = 64;

struct Ray
{
   sf::Vector2f hitPosition;
   sf::Vector2u mapPosition;
   float distance;
   bool hit;
   bool isHitVertical;
};

void Renderer::init()
{
   if (!wallTexture.loadFromFile("./assets/walkstone.png"))
   {
      std::cerr << "Failed to load wall texture" << std::endl;
      return;
   }
   if (wallTexture.getSize().x != wallTexture.getSize().y)
   {
      std::cerr << "Wall texture must be square" << std::endl;
      return;
   }
   wallSprite = sf::Sprite(wallTexture);
}

void Renderer::draw3dView(sf::RenderTarget &target, const Player &player, const Map &map)
{

   sf::RectangleShape rectangle(sf::Vector2(SCREEN_W, SCREEN_H / 2.0f));
   rectangle.setFillColor(sf::Color(135, 206, 235));
   target.draw(rectangle);

   rectangle.setPosition(0, SCREEN_H / 2.0f);
   rectangle.setFillColor(sf::Color(34, 139, 34));
   target.draw(rectangle);

   const sf::Color fogColor = sf::Color(100, 170, 250);
   float maxRenderDistance = MAX_RAYCAST_DEPTH * map.getCellSize();
   const float maxFogDistance = maxRenderDistance / 2.0f;

   float radians = player.angle * PI / 180.0f;
   sf::Vector2f direction{std::cos(radians), std::sin(radians)};
   sf::Vector2f plane{-direction.y, direction.x};

   sf::VertexArray walls{sf::Lines};

   for (size_t i = 0; i < SCREEN_W; i++)
   {
      float cameraX = i * 2.0f / SCREEN_W - 1.0f;
      sf::Vector2f rayPos = player.position / map.getCellSize();
      sf::Vector2f rayDir = direction + plane * cameraX;

      sf::Vector2f deltaDist{
          std::abs(1.0f / rayDir.x),
          std::abs(1.0f / rayDir.y),
      };

      sf::Vector2i mapPos{rayPos};
      sf::Vector2i step;
      sf::Vector2f sideDist;

      if (rayDir.x < 0.0f)
      {
         step.x = -1;
         sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
      }
      else
      {
         step.x = 1;
         sideDist.x = (mapPos.x + 1.0f - rayPos.x) * deltaDist.x;
      }

      if (rayDir.y < 0.0f)
      {
         step.y = -1;
         sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
      }
      else
      {
         step.y = 1;
         sideDist.y = (mapPos.y + 1.0f - rayPos.y) * deltaDist.y;
      }

      bool didHit{}, isHitVertical{};
      size_t depth = 0;
      while (!didHit && depth < MAX_RAYCAST_DEPTH)
      {
         if (sideDist.x < sideDist.y)
         {
            sideDist.x += deltaDist.x;
            mapPos.x += step.x;
            isHitVertical = false;
         }
         else
         {
            sideDist.y += deltaDist.y;
            mapPos.y += step.y;
            isHitVertical = true;
         }
         int x = mapPos.x, y = mapPos.y;
         const auto &grid = map.getGrid();
         if (y >= 0 && y < grid.size() && x >= 0 && x < grid[y].size() && grid[y][x] != sf::Color::Black)
         {
            didHit = true;
         }
         depth++;
      }

      float perpWallDist = isHitVertical ? sideDist.y - deltaDist.y : sideDist.x - deltaDist.x;
      float wallHeight = SCREEN_H / perpWallDist;

      float wallStart = (-wallHeight + SCREEN_H) / 2.0f;
      float wallEnd = (wallHeight + SCREEN_H) / 2.0f;

      walls.append(sf::Vertex(sf::Vector2f((float)i, wallStart)));
      walls.append(sf::Vertex(sf::Vector2f((float)i, wallEnd)));
   }
   target.draw(walls);
}
