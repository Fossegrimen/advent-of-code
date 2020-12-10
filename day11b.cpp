
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

size_t getOccupiedAdjacentSeats(std::vector<std::string>& currentRound, const size_t width, const size_t height, size_t x, size_t y);
bool checkOccupiedSeatInLine(std::vector<std::string>& currentRound, const size_t width, const size_t height, size_t x, size_t y, size_t delta_x, size_t delta_y);
bool checkBounds(const size_t width, const size_t height, size_t x, size_t y);

int main()
{
    std::vector<std::string> currentRound;
    std::vector<std::string> nextRound;
    std::string line;

    while (std::cin >> line)
    {
        currentRound.push_back(line);
    }

    const size_t width = currentRound[0].size();
    const size_t height = currentRound.size();

    line.clear();
    nextRound.clear();

    while (currentRound != nextRound)
    {
        size_t x = 0;
        size_t y = 0;

        if (!nextRound.empty())
        {
            currentRound = nextRound;
            nextRound.clear();
        }

        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                size_t occupiedSeats = getOccupiedAdjacentSeats(currentRound, width, height, x, y);

                if (currentRound[y][x] == 'L' && occupiedSeats == 0)
                {
                    line.push_back('#');
                }
                else if (currentRound[y][x] == '#' && occupiedSeats >= 5)
                {
                    line.push_back('L');
                }
                else
                {
                    line.push_back(currentRound[y][x]);
                }
            }

            nextRound.push_back(line);
            line.clear();
        }
    }

    size_t occupiedSeats = 0;

    for (size_t y = 0; y < height; y++)
    {
        occupiedSeats += std::count(nextRound[y].begin(), nextRound[y].end(), '#');
    }

    std::cout << occupiedSeats << std::endl;

    return 0;
}

size_t getOccupiedAdjacentSeats(std::vector<std::string>& currentRound, const size_t width, const size_t height, size_t x, size_t y)
{
    size_t occupiedSeats = 0;

    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x-1, y-1, -1, -1);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x,   y-1,  0, -1);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x+1, y-1,  1, -1);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x-1, y,   -1,  0);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x+1, y,    1,  0);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x-1, y+1, -1,  1);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x,   y+1,  0,  1);
    occupiedSeats += checkOccupiedSeatInLine(currentRound, width, height, x+1, y+1,  1,  1);

    return occupiedSeats;
}

bool checkOccupiedSeatInLine(std::vector<std::string>& currentRound, const size_t width, const size_t height, size_t x, size_t y, size_t delta_x, size_t delta_y)
{
    if (!checkBounds(width, height, x, y))
    {
        return false;
    }
    else if (currentRound[y][x] == 'L')
    {
        return false;
    }
    else if (currentRound[y][x] == '#')
    {
        return true;
    }

    return checkOccupiedSeatInLine(currentRound, width, height, x + delta_x, y + delta_y, delta_x, delta_y);
}

bool checkBounds(const size_t width, const size_t height, size_t x, size_t y)
{
    if (x >= 0 && x <= (width - 1) && y >= 0 && y <= (height - 1))
    {
        return true;
    }

    return false;
}
