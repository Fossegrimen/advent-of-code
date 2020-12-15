
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> SeatMatrix;

size_t getOccupiedAdjacentSeats(const SeatMatrix& seatMatrix, const size_t y, const size_t x);
bool   isOccupiedInLine(const SeatMatrix& currentRound, const ssize_t y, const ssize_t x, const ssize_t delta_y, const ssize_t delta_x);

int main()
{
    SeatMatrix  currentRound;
    std::string line;

    while (std::cin >> line)
    {
        currentRound.push_back(std::vector<char>(line.begin(), line.end()));
    }

    SeatMatrix nextRound = currentRound;
    bool       running   = true;

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
                else if (currentRound[y][x] == '#' && occupiedSeats >= 5)
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

    occupiedSeats += isOccupiedInLine(seatMatrix, y, x, -1, -1);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x, -1,  0);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x, -1,  1);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x,  0, -1);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x,  0,  1);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x,  1, -1);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x,  1,  0);
    occupiedSeats += isOccupiedInLine(seatMatrix, y, x,  1,  1);

    return occupiedSeats;
}

bool isOccupiedInLine(const SeatMatrix& seatMatrix, const ssize_t y, const ssize_t x, const ssize_t delta_y, const ssize_t delta_x)
{
    const ssize_t _y = y + delta_y;
    const ssize_t _x = x + delta_x;

    if (_y < 0 || _y >= seatMatrix.size() || _x < 0 || _x >= seatMatrix[0].size())
    {
        return false;
    }
    else if (seatMatrix[_y][_x] == 'L')
    {
        return false;
    }
    else if (seatMatrix[_y][_x] == '#')
    {
        return true;
    }

    return isOccupiedInLine(seatMatrix, _y, _x, delta_y, delta_x);
}
