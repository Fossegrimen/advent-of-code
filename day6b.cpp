
#include <iostream>
#include <string>
#include <unordered_map>

size_t countAnswers(std::unordered_map<char, size_t>* group, size_t people);

int main()
{
    std::unordered_map<char, size_t> group;
    size_t sum = 0;
    size_t people = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            sum += countAnswers(&group, people);
            people = 0;
            group.clear();
        }
        else
        {
            people++;

            for (size_t i = 0; i < line.size(); i++)
            {
                group[line[i]] = group[line[i]] + 1;
            }
        }
    }

    sum += countAnswers(&group, people);
    std::cout << sum << std::endl;

    return 0;
}

size_t countAnswers(std::unordered_map<char, size_t>* group, size_t people)
{
    auto itr = group->begin();

    while (itr != group->end()) {
        if (itr->second != people) {
           group->erase(itr);
        }

        itr++;
    }

    return group->size();
}
