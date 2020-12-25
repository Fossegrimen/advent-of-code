
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct PreviousRecord
{
    size_t record1;
    size_t record2;
};

int main()
{
    std::vector<size_t> spokenNumberVector(60000002, 0);

    size_t lastSpokenNumber;
    size_t round = 1;

    std::string line;
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');

    std::stringstream _line(line);

    while (_line >> lastSpokenNumber)
    {
        spokenNumberVector[2 * lastSpokenNumber] = round;
        round++;
    }

    struct PreviousRecord* previousRecord = (struct PreviousRecord*)&spokenNumberVector[2 * lastSpokenNumber];

    for (; round < 2021; round++)
    {
        if (previousRecord->record1 > 0)
        {
            if (previousRecord->record2 > 0)
            {
                const size_t diff = previousRecord->record2 - previousRecord->record1;
                previousRecord = (struct PreviousRecord*)&spokenNumberVector[2 * diff];
            }
            else
            {
                previousRecord = (struct PreviousRecord*)&spokenNumberVector[0];
            }
        }

        if (previousRecord->record1 > 0)
        {
            if (previousRecord->record2 != 0)
            {
                previousRecord->record1 = previousRecord->record2;
            }

            previousRecord->record2 = round;
        }
        else
        {
            previousRecord->record1 = round;
        }
    }

    std::cout << (((size_t*)previousRecord - (size_t*)&spokenNumberVector[0]) / 2) << std::endl;

    return 0;
}
