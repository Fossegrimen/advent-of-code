
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Record
{
    size_t record1;
    size_t record2;
};

int main()
{
    std::vector<Record> spokenNumberVector(30000001, {0, 0});

    size_t lastSpokenNumber;
    size_t round = 1;

    std::string line;
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');

    std::stringstream _line(line);

    while (_line >> lastSpokenNumber)
    {
        spokenNumberVector[lastSpokenNumber].record1 = round;
        round++;
    }

    struct Record* record = &spokenNumberVector[lastSpokenNumber];

    for (; round < 30000001; round++)
    {
        if (record->record1 > 0)
        {
            if (record->record2 > 0)
            {
                const size_t diff = record->record2 - record->record1;
                record = &spokenNumberVector[diff];
            }
            else
            {
                record = &spokenNumberVector[0];
            }
        }

        if (record->record1 > 0)
        {
            if (record->record2 != 0)
            {
                record->record1 = record->record2;
            }

            record->record2 = round;
        }
        else
        {
            record->record1 = round;
        }
    }

    std::cout << (record - &spokenNumberVector[0]) << std::endl;

    return 0;
}
