
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <vector>

typedef std::deque<size_t> PlayerCards;

void getPlayerCards(PlayerCards& playerCards);
bool playGame(PlayerCards& player1Cards, PlayerCards& player2Cards);

int main()
{
    PlayerCards player1Cards;
    PlayerCards player2Cards;

    getPlayerCards(player1Cards);
    getPlayerCards(player2Cards);

    size_t score = 0;

    PlayerCards& winnersCards = playGame(player1Cards, player2Cards) ? player1Cards : player2Cards;

    while (!winnersCards.empty())
    {
        score += winnersCards.front() * winnersCards.size();
        winnersCards.pop_front();
    }

    std::cout << score << std::endl;

    return 0;
}

void getPlayerCards(PlayerCards& playerCards)
{
    std::string line;
    std::getline(std::cin, line);

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        playerCards.push_back(std::atol(line.c_str()));
    }
}

bool playGame(PlayerCards& player1Cards, PlayerCards& player2Cards)
{
    while (!player1Cards.empty() && !player2Cards.empty())
    {
        const size_t card1 = player1Cards.front();
        const size_t card2 = player2Cards.front();

        player1Cards.pop_front();
        player2Cards.pop_front();

        bool winner = (card1 > card2);

        if (winner)
        {
            player1Cards.push_back(card1);
            player1Cards.push_back(card2);
        }
        else
        {
            player2Cards.push_back(card2);
            player2Cards.push_back(card1);
        }
    }

    return player2Cards.empty() ? true : false;
}
