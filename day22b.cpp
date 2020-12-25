
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
    const size_t player1maxCard = *max_element(player1Cards.begin(), player1Cards.end());
    const size_t player2maxCard = *max_element(player2Cards.begin(), player2Cards.end());

    if (player1maxCard > player2maxCard &&
        player1maxCard > (player1Cards.size() + player2Cards.size()))
    {
        return true;
    }

    std::vector<PlayerCards> previousPlayer1Cards;

    while (!player1Cards.empty() && !player2Cards.empty())
    {
        for (size_t i = 0; i < previousPlayer1Cards.size(); i++)
        {
            if (previousPlayer1Cards[i] == player1Cards)
            {
                return true;
            }
        }

        previousPlayer1Cards.push_back(player1Cards);

        const size_t card1 = player1Cards.front();
        const size_t card2 = player2Cards.front();

        player1Cards.pop_front();
        player2Cards.pop_front();

        bool winner = true;

        if (card1 <= player1Cards.size() && card2 <= player2Cards.size())
        {
            PlayerCards newPlayer1Cards(player1Cards.begin(), player1Cards.begin() + card1);
            PlayerCards newPlayer2Cards(player2Cards.begin(), player2Cards.begin() + card2);

            winner = playGame(newPlayer1Cards, newPlayer2Cards);
        }
        else
        {
            winner = (card1 > card2);
        }

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
