#include "renderer.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

constexpr float PI = 3.141592653589793f;
constexpr size_t MAX_RAYCAST_DEPTH = 16;

void Renderer::drawRays(sf::RenderTarget &target, const Player &player, const Map &map)
{
   float angle = player.angle * PI / 180.0f;
   float vtan = -std::tan(angle);
   float htan = 1.0f / std::tan(angle);
   float cellSize = map.getCellSize();

   sf::Vector2f rayPos, offset;
   if (std::cos(angle) > 0.001f)
   {
      rayPos.x = std::floor(player.position.x / cellSize) * cellSize + cellSize;
      rayPos.y = (player.position.x - rayPos.x) * vtan + player.position.y;
      offset.x = cellSize;
      offset.y = -offset.x * vtan;
   }
   else if (std::cos(angle) < -0.001f)
   {
      rayPos.x = std::floor(player.position.x / cellSize) * cellSize;
      rayPos.y = (player.position.x - rayPos.x) * vtan + player.position.y;
      offset.x = -cellSize;
      offset.y = -offset.x * vtan;
   }
   else
   {
      return;
   }

   const auto grid = map.getGrid();
   for (size_t i = 0; i < MAX_RAYCAST_DEPTH; i++)
   {
      int mapX = (int)(rayPos.x / cellSize);
      int mapY = (int)(rayPos.y / cellSize);

      if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
      {
         break;
      }
      rayPos += offset;
   }

   sf::Vertex line[] = {
       sf::Vertex(player.position),
       sf::Vertex(rayPos),
   };
   target.draw(line, 2, sf::Lines);
   return;

   if (sin(angle) > 0.001f)
   {
      rayPos.y = std::floor(player.position.y / cellSize) * cellSize + cellSize;
      rayPos.x = (player.position.y - rayPos.y) * htan + player.position.x;
      offset.y = cellSize;
      offset.x = -offset.x * htan;
   }
   else if (sin(angle) < -0.001f)
   {
      rayPos.y = std::floor(player.position.y / cellSize) * cellSize;
      rayPos.x = (player.position.y - rayPos.y) * htan + player.position.x;
      offset.y = -cellSize;
      offset.x = -offset.y * htan;
   }
   else
   {
      return;
   }
}
