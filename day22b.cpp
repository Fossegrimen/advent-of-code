
#include <cstdlib>
#include <deque>
#include <iostream>
#include <vector>

typedef std::deque<size_t> PlayerCards;

void         getPlayerCards(PlayerCards& playerCards);
PlayerCards* playGame(PlayerCards& player1Cards, PlayerCards& player2Cards);
PlayerCards* playRecursiveCombat(PlayerCards& player1Cards, PlayerCards& player2Cards);

int main()
{
    PlayerCards player1Cards;
    PlayerCards player2Cards;

    getPlayerCards(player1Cards);
    getPlayerCards(player2Cards);

    size_t score = 0;
    PlayerCards* winnersCards = playGame(player1Cards, player2Cards);

    while (!winnersCards->empty())
    {
        score += winnersCards->front() * winnersCards->size();
        winnersCards->pop_front();
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

PlayerCards* playGame(PlayerCards& player1Cards, PlayerCards& player2Cards)
{
    std::vector<PlayerCards> previousPlayer1Cards;
    std::vector<PlayerCards> previousPlayer2Cards;

    while (!player1Cards.empty() && !player2Cards.empty())
    {
        for (size_t i = 0; i < previousPlayer1Cards.size(); i++)
        {
            if (previousPlayer1Cards[i].size() != player1Cards.size() ||
                previousPlayer2Cards[i].size() != player2Cards.size())
            {
                continue;
            }

            if (previousPlayer1Cards[i] == player1Cards &&
                previousPlayer2Cards[i] == player2Cards)
            {
                return &player1Cards;
            }
        }

        previousPlayer1Cards.push_back(player1Cards);
        previousPlayer2Cards.push_back(player2Cards);

        const size_t card1 = player1Cards.front();
        const size_t card2 = player2Cards.front();

        PlayerCards* winningPlayer = nullptr;
        PlayerCards* losingPlayer = nullptr;

        if (card1 < player1Cards.size() && card2 < player2Cards.size())
        {
            winningPlayer = playRecursiveCombat(player1Cards, player2Cards);
            losingPlayer = (&player2Cards == winningPlayer) ? &player1Cards : &player2Cards;
        }
        else
        {
            if (card1 > card2)
            {
                winningPlayer = &player1Cards;
                losingPlayer = &player2Cards;
            }
            else if (card2 > card1)
            {
                winningPlayer = &player2Cards;
                losingPlayer = &player1Cards;
            }
            else
            {
                std::cout << "Infinite loop" << std::endl;
                exit(1);
            }
        }

        winningPlayer->push_back(winningPlayer->front());
        winningPlayer->push_back(losingPlayer->front());

        winningPlayer->pop_front();
        losingPlayer->pop_front();
    }

    return player2Cards.empty() ? &player1Cards : &player2Cards;
}

PlayerCards* playRecursiveCombat(PlayerCards& player1Cards, PlayerCards& player2Cards)
{
    PlayerCards newPlayer1Cards = player1Cards;
    PlayerCards newPlayer2Cards = player2Cards;

    size_t newSize1 = newPlayer1Cards.front();
    newPlayer1Cards.pop_front();

    size_t newSize2 = newPlayer2Cards.front();
    newPlayer2Cards.pop_front();

    while (newSize1 != newPlayer1Cards.size())
    {
        newPlayer1Cards.pop_back();
    }

    while (newSize2 != newPlayer2Cards.size())
    {
        newPlayer2Cards.pop_back();
    }

    PlayerCards* winningPlayer = playGame(newPlayer1Cards, newPlayer2Cards);

    return (winningPlayer == &newPlayer1Cards) ? &player1Cards : &player2Cards;
}
