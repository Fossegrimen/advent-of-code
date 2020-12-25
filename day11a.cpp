
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> SeatMatrix;

size_t getOccupiedAdjacentSeats(const SeatMatrix& seatMatrix, const size_t y, const size_t x);
bool   isOccupied(const SeatMatrix& seatMatrix, const ssize_t y, const ssize_t x);

int main()
{
    SeatMatrix  currentRound;
    std::string line;

    while (std::cin >> line)
    {
        currentRound.push_back(std::vector<char>(line.begin(), line.end()));
    }

    SeatMatrix nextRound = currentRound;
    bool running         = true;

    while (running)
    {
        currentRound = nextRound;
        running      = false;

        for (size_t y = 0; y < currentRound.size(); y++)
        {
            for (size_t x = 0; x < currentRound[0].size(); x++)
            {
                const size_t occupiedSeats = getOccupiedAdjacentSeats(currentRound, y, x);

                if (currentRound[y][x] == 'L' && occupiedSeats == 0)
                {
                    nextRound[y][x] = '#';
                    running         = true;
                }
                else if (currentRound[y][x] == '#' && occupiedSeats >= 4)
                {
                    nextRound[y][x] = 'L';
                    running         = true;
                }
                else
                {
                    nextRound[y][x] = currentRound[y][x];
                }
            }
        }
    }

    size_t occupiedSeats = 0;

    for (size_t y = 0; y < nextRound.size(); y++)
    {
        occupiedSeats += std::count(nextRound[y].begin(), nextRound[y].end(), '#');
    }

    std::cout << occupiedSeats << std::endl;

    return 0;
}

size_t getOccupiedAdjacentSeats(const SeatMatrix& seatMatrix, const size_t y, const size_t x)
{
    size_t occupiedSeats = 0;

    occupiedSeats += isOccupied(seatMatrix, y - 1, x - 1);
    occupiedSeats += isOccupied(seatMatrix, y - 1, x);
    occupiedSeats += isOccupied(seatMatrix, y - 1, x + 1);
    occupiedSeats += isOccupied(seatMatrix, y,     x - 1);
    occupiedSeats += isOccupied(seatMatrix, y,     x + 1);
    occupiedSeats += isOccupied(seatMatrix, y + 1, x - 1);
    occupiedSeats += isOccupied(seatMatrix, y + 1, x);
    occupiedSeats += isOccupied(seatMatrix, y + 1, x + 1);

    return occupiedSeats;
}

bool isOccupied(const SeatMatrix& seatMatrix, const ssize_t y, const ssize_t x)
{
    if (y < 0 || y >= (ssize_t)seatMatrix.size() || x < 0 || x >= (ssize_t)seatMatrix[0].size())
    {
        return false;
    }
    else if (seatMatrix[y][x] == '#')
    {
        return true;
    }

    return false;
}
