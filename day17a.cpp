
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ROUNDS 6
#define MAX_WIDTH 8

#define MAX_Z ((2 * MAX_ROUNDS) + 1)
#define MAX_Y (MAX_WIDTH + (2 * MAX_ROUNDS) + 1)
#define MAX_X MAX_Y

#define ORIGO_Z MAX_ROUNDS
#define ORIGO_Y ((MAX_WIDTH / 2) + MAX_ROUNDS)
#define ORIGO_X ORIGO_Y

#define START_Y (ORIGO_Y - (MAX_WIDTH / 2))
#define START_X START_Y

#define END_Y (ORIGO_Y + (MAX_WIDTH / 2))
#define END_X END_Y

typedef std::vector<std::vector<std::vector<char>>> CubeMap;

size_t getActiveAdjacentCubes(const CubeMap& cubeMap, const ssize_t z, const ssize_t y, const ssize_t x, const bool checkAdjacentLevels);
bool   isActive(const CubeMap& cubeMap, const ssize_t z, const ssize_t y, const ssize_t x);

int main()
{
    CubeMap cubeMap;
    cubeMap.resize(MAX_Z);

    for (auto& matrix : cubeMap)
    {
        matrix.resize(MAX_Y);

        for (auto& vector : matrix)
        {
            vector.resize(MAX_X, '.');
        }
    }

    const size_t z = ORIGO_Z;
    size_t       y = START_Y;
    size_t       x = START_X;

    std::string line;

    while (std::getline(std::cin, line))
    {
        x = START_X;

        for (char character : line)
        {
            cubeMap[z][y][x] = character;
            x++;
        }

        y++;
    }

    CubeMap newCubeMap = cubeMap;
    size_t round = 1;

    while (round <= MAX_ROUNDS)
    {
        if (round > 1)
        {
            cubeMap = newCubeMap;
        }

        for (size_t z = (ORIGO_Z - round); z <= (ORIGO_Z + round); z++)
        {
            for (size_t y = (START_Y - round); y <= (END_Y + round); y++)
            {
                for (size_t x = (START_X - round); x <= (END_X + round); x++)
                {
                    const size_t adjacentCubes = getActiveAdjacentCubes(cubeMap, z, y, x, true);

                    if (cubeMap[z][y][x] == '#' && (adjacentCubes == 2 || adjacentCubes == 3))
                    {
                        newCubeMap[z][y][x] = '#';
                    }
                    else if (cubeMap[z][y][x] == '.' && adjacentCubes == 3)
                    {
                        newCubeMap[z][y][x] = '#';
                    }
                    else
                    {
                        newCubeMap[z][y][x] = '.';
                    }
                }
            }
        }

        round++;
    }

    size_t adjacentCubes = 0;

    for (size_t z = 0; z < MAX_Z; z++)
    {
        for (size_t y = 0; y < MAX_Y; y++)
        {
            adjacentCubes += std::count(newCubeMap[z][y].begin(), newCubeMap[z][y].end(), '#');
        }
    }

    std::cout << adjacentCubes << std::endl;

    return 0;
}

size_t getActiveAdjacentCubes(const CubeMap& cubeMap, const ssize_t z, const ssize_t y, const ssize_t x, const bool checkAdjacentLevels)
{
    size_t adjacentCubes = 0;

    adjacentCubes += isActive(cubeMap, z, y - 1, x - 1);
    adjacentCubes += isActive(cubeMap, z, y - 1, x);
    adjacentCubes += isActive(cubeMap, z, y - 1, x + 1);
    adjacentCubes += isActive(cubeMap, z, y,     x - 1);

    if (!checkAdjacentLevels)
    {
        adjacentCubes += isActive(cubeMap, z, y, x);
    }

    adjacentCubes += isActive(cubeMap, z, y,     x + 1);
    adjacentCubes += isActive(cubeMap, z, y + 1, x - 1);
    adjacentCubes += isActive(cubeMap, z, y + 1, x);
    adjacentCubes += isActive(cubeMap, z, y + 1, x + 1);

    if (checkAdjacentLevels)
    {
        adjacentCubes += getActiveAdjacentCubes(cubeMap, z-1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(cubeMap, z+1, y, x, false);
    }

    return adjacentCubes;
}

bool isActive(const CubeMap& cubeMap, const ssize_t z, const ssize_t y, const ssize_t x)
{
    if (z < 0 || z >= MAX_Z ||
        y < 0 || y >= MAX_Y ||
        x < 0 || x >= MAX_X)
    {
        return false;
    }
    else if (cubeMap[z][y][x] == '#')
    {
        return true;
    }

    return false;
}
