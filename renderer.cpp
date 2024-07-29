#include "renderer.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>

constexpr float PI = 3.141592653589793f;
constexpr size_t MAX_RAYCAST_DEPTH = 16;

void Renderer::drawRays(sf::RenderTarget &target, const Player &player, const Map &map)
{
   float angle = player.angle * PI / 180.0f;
   float vtan = -std::tan(angle);
   float htan = -1.0f / std::tan(angle);
   float cellSize = map.getCellSize();

   size_t vdof = 0, hdof = 0;
   float vdist = std::numeric_limits<float>::max();
   float hdist = std::numeric_limits<float>::max();

   sf::Vector2f vRayPos, hRayPos, offset;
   if (std::cos(angle) > 0.001f)
   {
      vRayPos.x = std::floor(player.position.x / cellSize) * cellSize + cellSize;
      vRayPos.y = (player.position.x - vRayPos.x) * vtan + player.position.y;

      offset.x = cellSize;
      offset.y = -offset.x * vtan;
   }
   else if (std::cos(angle) < -0.001f)
   {
      vRayPos.x = std::floor(player.position.x / cellSize) * cellSize - 0.01f;
      vRayPos.y = (player.position.x - vRayPos.x) * vtan + player.position.y;

      offset.x = -cellSize;
      offset.y = -offset.x * vtan;
   }
   else
   {
      vdof = MAX_RAYCAST_DEPTH;
   }

   const auto &grid = map.getGrid();
   for (; vdof < MAX_RAYCAST_DEPTH; vdof++)
   {
      int mapX = (int)(vRayPos.x / cellSize);
      int mapY = (int)(vRayPos.y / cellSize);

      if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
      {
         vdist = std::sqrt((vRayPos.x - player.position.x) * (vRayPos.x - player.position.x) +
                           (vRayPos.y - player.position.y) * (vRayPos.y - player.position.y));
         break;
      }
      vRayPos += offset;
   }

   if (std::sin(angle) > 0.001f)
   {
      hRayPos.y = std::floor(player.position.y / cellSize) * cellSize + cellSize;
      hRayPos.x = (player.position.y - hRayPos.y) * htan + player.position.x;

      offset.y = cellSize;
      offset.x = -offset.y * htan;
   }
   else if (std::sin(angle) < -0.001f)
   {
      hRayPos.y = std::floor(player.position.y / cellSize) * cellSize - 0.01f;
      hRayPos.x = (player.position.y - hRayPos.y) * htan + player.position.x;

      offset.y = -cellSize;
      offset.x = -offset.y * htan;
   }
   else
   {
      hdof = MAX_RAYCAST_DEPTH;
   }

   for (; hdof < MAX_RAYCAST_DEPTH; hdof++)
   {
      int mapX = (int)(hRayPos.x / cellSize);
      int mapY = (int)(hRayPos.y / cellSize);

      if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
      {
         hdist = std::sqrt((hRayPos.x - player.position.x) * (hRayPos.x - player.position.x) +
                           (hRayPos.y - player.position.y) * (hRayPos.y - player.position.y));
         break;
      }
      hRayPos += offset;
   }

   sf::Vertex line[] = {
       sf::Vertex(player.position),
       sf::Vertex(hdist < vdist ? hRayPos : vRayPos),
   };
   target.draw(line, 2, sf::Lines);
}
