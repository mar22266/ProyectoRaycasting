#include "map.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

Map::Map(float cellSize, int width, int height)
    : cellSize(cellSize), grid(height, std::vector<int>(width, 0)) {}

Map::Map(float cellSize, std::vector<std::vector<int>> grid)
    : cellSize(cellSize), grid(grid) {}

void Map::draw(sf::RenderTarget &target)
{
    if (grid.empty())
    {
        return;
    }

    sf::RectangleShape background(sf::Vector2f((float)grid[0].size() * cellSize, (float)grid.size() * cellSize));
    background.setFillColor(sf::Color::Green);
    target.draw(background);

    sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));

    for (std::size_t y = 0; y < grid.size(); y++)
    {
        for (std::size_t x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x] == 0)
            {
                cell.setFillColor(sf::Color(70, 70, 70)); // gray color
            }
            else if (grid[y][x] == 1)
            {
                cell.setFillColor(sf::Color(255, 155, 0)); // white color
            }
            cell.setPosition(sf::Vector2f(x, y) * cellSize + sf::Vector2f(cellSize * 0.025f, cellSize * 0.025f));
            target.draw(cell);
        }
    }
}

const std::vector<std::vector<int>> &Map::getGrid() const
{
    return grid;
}
float Map::getCellSize() const
{
    return cellSize;
}