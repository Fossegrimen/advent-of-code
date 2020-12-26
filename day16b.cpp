
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<size_t> Ticket;
typedef std::vector<std::vector<size_t>> Rules;
typedef std::vector<std::vector<size_t>> Tickets;

void readRules(Rules& rules);
void readOwnTicket(Ticket& ticket);
void readTickets(const Rules& rules, Tickets& tickets);
bool isValid(const Rules& rules, const size_t value);
bool isValid(const Ticket& ticket, const size_t value);

int main()
{
    Ticket  ticket;
    Tickets tickets;
    Rules   rules;

    readRules(rules);
    readOwnTicket(ticket);
    readTickets(rules, tickets);

    std::vector<std::vector<size_t>> validColumnsPerRuleMatrix;

    for (size_t i = 0; i < tickets[0].size(); i++)
    {
        std::vector<size_t> columns;

        for (size_t j = 0; j < rules.size(); j++)
        {
            bool valid = true;

            for (size_t k = 0; k < tickets.size(); k++)
            {
                if (!isValid(rules[j], tickets[k][i]))
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
            {
                columns.push_back(j);
            }
        }

        validColumnsPerRuleMatrix.push_back(columns);
    }

    for (size_t i = 0; i < validColumnsPerRuleMatrix.size(); i++)
    {
        for (std::vector<size_t>& columnsA : validColumnsPerRuleMatrix)
        {
            if (columnsA.size() != 1)
            {
                continue;
            }

            for (std::vector<size_t>& columnsB : validColumnsPerRuleMatrix)
            {
                if (columnsA == columnsB)
                {
                    continue;
                }

                columnsB.erase(std::remove(columnsB.begin(), columnsB.end(), columnsA[0]), columnsB.end());
            }
        }
    }

    size_t product = 1;

    for (size_t i = 0; i < validColumnsPerRuleMatrix.size(); i++)
    {
        if (validColumnsPerRuleMatrix[i][0] < 6)
        {
            product *= ticket[i];
        }
    }

    std::cout << product << std::endl;

    return 0;
}

void readRules(Rules& rules)
{
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

        std::vector<size_t> _rules;
        size_t rule;

        while (_line >> rule)
        {
            _rules.push_back(rule);
        }

        rules.push_back(_rules);
    }
}

void readOwnTicket(Ticket& ticket)
{
    std::string line;

    std::getline(std::cin, line);
    std::getline(std::cin, line);

    line = std::regex_replace(line, std::regex(","), " ");

    std::stringstream _line(line);
    size_t value;

    while (_line >> value)
    {
        ticket.push_back(value);
    }
}

void readTickets(const Rules& rules, Tickets& tickets)
{
    std::string line;

    std::getline(std::cin, line);
    std::getline(std::cin, line);

    while (std::getline(std::cin, line))
    {
        line = std::regex_replace(line, std::regex(","), " ");
        std::stringstream _line(line);

        Ticket ticket;
        bool valid = true;

        size_t value = 0;

        while (_line >> value)
        {
            ticket.push_back(value);

            if (!isValid(rules, value))
            {
                valid = false;
            }
        }

        if (valid)
        {
            tickets.push_back(ticket);
        }
    }
}

bool isValid(const Rules& rules, const size_t value)
{
    for (const auto& vect : rules)
    {
        if ((value >= vect[0] && value <= vect[1]) ||
            (value >= vect[2] && value <= vect[3]))
            {
                return true;
            }
    }

    return false;
}

bool isValid(const Ticket& ticket, const size_t value)
{
    if ((value >= ticket[0] && value <= ticket[1]) ||
        (value >= ticket[2] && value <= ticket[3]))
    {
        return true;
    }

    return false;
}
