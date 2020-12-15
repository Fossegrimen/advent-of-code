
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

#define MAX_ROUNDS 100
#define MAX_WIDTH 60

#define MAX_R (MAX_WIDTH + (2 * MAX_ROUNDS) + 1)
#define MAX_Q MAX_R

#define ORIGO_R ((MAX_WIDTH / 2) + MAX_ROUNDS)
#define ORIGO_Q ORIGO_R

#define START_R (ORIGO_R - (MAX_WIDTH / 2))
#define START_Q START_R

#define END_R (ORIGO_R + (MAX_WIDTH / 2))
#define END_Q END_R

typedef std::vector<std::vector<size_t>> HexagonGrid;

size_t getAdjacentBlackTiles(const HexagonGrid& hexagonGrid, const size_t r, const size_t q);
bool   isBlack(const HexagonGrid& hexagonGrid, const ssize_t r, const ssize_t q);

int main()
{
    HexagonGrid hexagonGrid;
    hexagonGrid.resize(MAX_R);

    for (auto& vector : hexagonGrid)
    {
        vector.resize(MAX_Q, 0);
    }

    std::string line;

    while (std::getline(std::cin, line))
    {
        size_t r = ORIGO_R;
        size_t q = ORIGO_Q;

        size_t pos    = 0;
        size_t offset = 0;

        while ((pos = line.substr(offset, line.size()).find('w')) != std::string::npos)
        {
            offset += pos + 1;
            line.insert(offset, " ");
        }

        pos    = 0;
        offset = 0;

        while ((pos = line.substr(offset, line.size()).find('e')) != std::string::npos)
        {
            offset += pos + 1;
            line.insert(offset, " ");
        }

        std::stringstream _line(line);
        std::string       direction;

        while (_line >> direction)
        {
            if (direction == "nw")
            {
                r--;
            }
            else if (direction == "ne")
            {
                r--;
                q++;
            }
            else if (direction == "w")
            {
                q--;
            }
            else if (direction == "e")
            {
                q++;
            }
            else if (direction == "sw")
            {
                r++;
                q--;
            }
            else if (direction == "se")
            {
                r++;
            }
        }

        hexagonGrid[r][q] = !hexagonGrid[r][q];
    }

    HexagonGrid newHexagonGrid = hexagonGrid;
    size_t round = 1;

    while (round <= MAX_ROUNDS)
    {
        if (round > 1)
        {
            hexagonGrid = newHexagonGrid;
        }

        for (size_t r = (START_R - round); r <= (END_R + round); r++)
        {
            for (size_t q = (START_Q - round); q <= (END_Q + round); q++)
            {
                const size_t blackTiles = getAdjacentBlackTiles(hexagonGrid, r, q);

                if (hexagonGrid[r][q] == 1 && (blackTiles == 0 || blackTiles > 2))
                {
                    newHexagonGrid[r][q] = 0;
                }
                else if (hexagonGrid[r][q] == 0 && blackTiles == 2)
                {
                    newHexagonGrid[r][q] = 1;
                }
                else
                {
                    newHexagonGrid[r][q] = hexagonGrid[r][q];
                }
            }
        }

        round++;
    }

    size_t sum = 0;

    for (const auto& vector : newHexagonGrid)
    {
        sum += std::accumulate(vector.begin(), vector.end(), 0);
    }

    std::cout << sum << std::endl;

    return 0;
}

size_t getAdjacentBlackTiles(const HexagonGrid& hexagonGrid, const size_t r, const size_t q)
{
    size_t blackTiles = 0;

    blackTiles += isBlack(hexagonGrid, r - 1, q);
    blackTiles += isBlack(hexagonGrid, r - 1, q + 1);
    blackTiles += isBlack(hexagonGrid, r,     q - 1);
    blackTiles += isBlack(hexagonGrid, r,     q + 1);
    blackTiles += isBlack(hexagonGrid, r + 1, q - 1);
    blackTiles += isBlack(hexagonGrid, r + 1, q);

    return blackTiles;
}

bool isBlack(const HexagonGrid& hexagonGrid, const ssize_t r, const ssize_t q)
{
    if (r < 0 || r >= MAX_R || q < 0 || q >= MAX_R)
    {
        return false;
    }
    else if (hexagonGrid[r][q] == 1)
    {
        return true;
    }

    return false;
}
