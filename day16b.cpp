
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::vector<size_t> Ticket;
typedef std::vector<std::vector<size_t>> RulesMatrix;
typedef std::vector<std::vector<size_t>> TicketMatrix;

bool isValid(RulesMatrix rulesMatrix, size_t value);
bool isValid(Ticket ticket, size_t value);

int main()
{
    Ticket ticket;
    TicketMatrix ticketMatrix;
    RulesMatrix rulesMatrix;

    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        line = std::regex_replace(line, std::regex("([[:alpha:]]+)"), "");
        line = std::regex_replace(line, std::regex(".?: "), "");
        line = std::regex_replace(line, std::regex("-"), " ");
        line = std::regex_replace(line, std::regex(" or "), " ");

        std::stringstream _line(line);

        std::vector<size_t> rules;
        size_t rule;

        while (_line >> rule)
        {
            rules.push_back(rule);
        }

        rulesMatrix.push_back(rules);
    }

    std::getline(std::cin, line);

    if (std::getline(std::cin, line))
    {
        line = std::regex_replace(line, std::regex(","), " ");

        std::stringstream _line(line);
        size_t value;

        while (_line >> value)
        {
            ticket.push_back(value);
        }
    }

    std::getline(std::cin, line);
    std::getline(std::cin, line);

    while (std::getline(std::cin, line))
    {
        line = std::regex_replace(line, std::regex(","), " ");

        std::vector<size_t> ticket;
        bool valid = true;

        std::stringstream _line(line);
        size_t value = 0;

        while (_line >> value)
        {
            ticket.push_back(value);

            if (!isValid(rulesMatrix, value))
            {
                valid = false;
            }
        }

        if (valid)
        {
            ticketMatrix.push_back(ticket);
        }
    }

    std::vector<std::vector<size_t>> okMatrix;

    for (size_t i = 0; i < ticketMatrix[0].size(); i++)
    {
        std::vector<size_t> vect;

        for (size_t k = 0; k < rulesMatrix.size(); k++)
        {
            bool valid = true;

            for (size_t j = 0; j < ticketMatrix.size(); j++)
            {
                if (!isValid(rulesMatrix[k], ticketMatrix[j][i]))
                {
                    valid = false;
                }
            }

            if (valid)
            {
                vect.push_back(k);
            }
        }

        okMatrix.push_back(vect);
    }

    for (size_t l = 0; l < 10; l++)
    {
        for (size_t i = 0; i < okMatrix.size(); i++)
        {
            if (okMatrix[i].size() == 1)
            {
                for (size_t j = 0; j < okMatrix.size(); j++)
                {
                    if (i != j)
                    {
                        okMatrix[j].erase(std::remove(okMatrix[j].begin(), okMatrix[j].end(), okMatrix[i][0]), okMatrix[j].end());
                    }
                }
            }
        }
    }

    size_t product = 1;

    for (size_t i = 0; i < okMatrix.size(); i++)
    {
        if (okMatrix[i][0] < 6)
        {
            product *= ticket[i];
        }
    }

    std::cout << product << std::endl;

    return 0;
}

bool isValid(RulesMatrix rulesMatrix, size_t value)
{
    for (const auto& vect : rulesMatrix)
    {
        if ((value >= vect[0] && value <= vect[1]) ||
            (value >= vect[2] && value <= vect[3]))
            {
                return true;
            }
    }

    return false;
}

bool isValid(Ticket ticket, size_t value)
{
    if ((value >= ticket[0] && value <= ticket[1]) ||
        (value >= ticket[2] && value <= ticket[3]))
    {
        return true;
    }

    return false;
}
