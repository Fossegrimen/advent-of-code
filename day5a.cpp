
#include <iostream>
#include <string>

int main()
{
    size_t highestSeatId = 0;
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

        if (seatId > highestSeatId)
        {
            highestSeatId = seatId;
        }
    }

    std::cout << highestSeatId << std::endl;

    return 0;
}
