
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<size_t> seatIds;
    std::string line;

    while (std::cin >> line)
    {
        size_t row = 0;
        size_t column = 0;

        for (size_t i = 0; i < 7; i++)
        {
            if (line[i] == 'B')
            {
                row += (1 << (6 - i));
            }
        }

        for (size_t i = 0; i < 3; i++)
        {
            if (line[i + 7] == 'R')
            {
                column += (1 << (2 - i));
            }
        }

        size_t seatId = (row * 8) + column;
        seatIds.push_back(seatId);
    }

    std::sort(seatIds.begin(), seatIds.end());
    size_t previousSeat = seatIds[0] - 1;

    for (size_t seatId: seatIds)
    {
        if (seatId != (previousSeat + 1))
        {
            std::cout << (seatId - 1) << std::endl;
            return 0;
        }

        previousSeat = seatId;
    }

    return 1;
}
