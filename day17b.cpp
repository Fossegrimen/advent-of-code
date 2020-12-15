
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ROUNDS 6
#define MAX_WIDTH 8

#define MAX_W ((2 * MAX_ROUNDS) + 1)
#define MAX_Z MAX_W
#define MAX_Y (MAX_WIDTH + (2 * MAX_ROUNDS) + 1)
#define MAX_X MAX_Y

#define ORIGO_W MAX_ROUNDS
#define ORIGO_Z MAX_ROUNDS
#define ORIGO_Y ((MAX_WIDTH / 2) + MAX_ROUNDS)
#define ORIGO_X ORIGO_Y

#define START_Y (ORIGO_Y - (MAX_WIDTH / 2))
#define START_X START_Y

#define END_Y (ORIGO_Y + (MAX_WIDTH / 2))
#define END_X END_Y

typedef std::vector<std::vector<std::vector<std::vector<char>>>> HyperCubeMap;

size_t getActiveAdjacentCubes(const HyperCubeMap& hyperCubeMap, const ssize_t w, const ssize_t z, const ssize_t y, const ssize_t x, const bool checkAdjacentLevels);
bool   isActive(const HyperCubeMap& hyperCubeMap, const ssize_t w, const ssize_t z, const ssize_t y, const ssize_t x);

int main()
{
    HyperCubeMap hyperCubeMap;
    hyperCubeMap.resize(MAX_W);

    for (auto& cube : hyperCubeMap)
    {
        cube.resize(MAX_Z);

        for (auto& matrix : cube)
        {
            matrix.resize(MAX_Y);

            for (auto& vector : matrix)
            {
                vector.resize(MAX_X, '.');
            }
        }
    }

    const size_t w = ORIGO_W;
    const size_t z = ORIGO_Z;
    size_t       y = START_Y;
    size_t       x = START_X;

    std::string line;

    while (std::getline(std::cin, line))
    {
        x = START_X;

        for (char character : line)
        {
            hyperCubeMap[w][z][y][x] = character;
            x++;
        }

        y++;
    }

    HyperCubeMap newHyperCubeMap = hyperCubeMap;
    size_t round = 1;

    while (round <= MAX_ROUNDS)
    {
        if (round > 1)
        {
            hyperCubeMap = newHyperCubeMap;
        }

        for (size_t w = (ORIGO_W - round); w <= (ORIGO_W + round); w++)
        {
            for (size_t z = (ORIGO_Z - round); z <= (ORIGO_Z + round); z++)
            {
                for (size_t y = (START_Y - round); y <= (END_Y + round); y++)
                {
                    for (size_t x = (START_X - round); x <= (END_X + round); x++)
                    {
                        const size_t adjacentCubes = getActiveAdjacentCubes(hyperCubeMap, w, z, y, x, true);

                        if (hyperCubeMap[w][z][y][x] == '#' && (adjacentCubes == 2 || adjacentCubes == 3))
                        {
                            newHyperCubeMap[w][z][y][x] = '#';
                        }
                        else if (hyperCubeMap[w][z][y][x] == '.' && adjacentCubes == 3)
                        {
                            newHyperCubeMap[w][z][y][x] = '#';
                        }
                        else
                        {
                            newHyperCubeMap[w][z][y][x] = '.';
                        }
                    }
                }
            }
        }

        round++;
    }

    size_t adjacentCubes = 0;

    for (size_t w = 0; w < MAX_W; w++)
    {
        for (size_t z = 0; z < MAX_Z; z++)
        {
            for (size_t y = 0; y < MAX_Y; y++)
            {
                adjacentCubes += std::count(newHyperCubeMap[w][z][y].begin(), newHyperCubeMap[w][z][y].end(), '#');
            }
        }
    }

    std::cout << adjacentCubes << std::endl;

    return 0;
}

size_t getActiveAdjacentCubes(const HyperCubeMap& hyperCubeMap, const ssize_t w, const ssize_t z, const ssize_t y, const ssize_t x, const bool checkAdjacentLevels)
{
    size_t adjacentCubes = 0;

    adjacentCubes += isActive(hyperCubeMap, w, z, y - 1, x - 1);
    adjacentCubes += isActive(hyperCubeMap, w, z, y - 1, x);
    adjacentCubes += isActive(hyperCubeMap, w, z, y - 1, x + 1);
    adjacentCubes += isActive(hyperCubeMap, w, z, y,     x - 1);

    if (!checkAdjacentLevels)
    {
        adjacentCubes += isActive(hyperCubeMap, w, z, y, x);
    }

    adjacentCubes += isActive(hyperCubeMap, w, z, y,     x + 1);
    adjacentCubes += isActive(hyperCubeMap, w, z, y + 1, x - 1);
    adjacentCubes += isActive(hyperCubeMap, w, z, y + 1, x);
    adjacentCubes += isActive(hyperCubeMap, w, z, y + 1, x + 1);

    if (checkAdjacentLevels)
    {
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w-1, z-1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w-1, z,   y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w-1, z+1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w,   z-1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w,   z+1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w+1, z-1, y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w+1, z,   y, x, false);
        adjacentCubes += getActiveAdjacentCubes(hyperCubeMap, w+1, z+1, y, x, false);
    }

    return adjacentCubes;
}

bool isActive(const HyperCubeMap& hyperCubeMap, const ssize_t w, const ssize_t z, const ssize_t y, const ssize_t x)
{
    if (w < 0 || w >= MAX_W ||
        z < 0 || z >= MAX_Z ||
        y < 0 || y >= MAX_Y ||
        x < 0 || x >= MAX_X)
    {
        return false;
    }
    else if (hyperCubeMap[w][z][y][x] == '#')
    {
        return true;
    }

    return false;
}
