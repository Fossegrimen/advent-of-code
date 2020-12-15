
#include <cstdlib>
#include <iostream>
#include <queue>

typedef std::queue<size_t> PlayerCards;

void         getPlayerCards(PlayerCards& playerCards);
PlayerCards* playGame(PlayerCards& player1Cards, PlayerCards& player2Cards);

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
        winnersCards->pop();
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

        playerCards.push(std::atol(line.c_str()));
    }
}

PlayerCards* playGame(PlayerCards& player1Cards, PlayerCards& player2Cards)
{
    while (!player1Cards.empty() && !player2Cards.empty())
    {
        const size_t card1 = player1Cards.front();
        player1Cards.pop();

        const size_t card2 = player2Cards.front();
        player2Cards.pop();

        if (card1 > card2)
        {
            player1Cards.push(card1);
            player1Cards.push(card2);
        }
        else if (card2 > card1)
        {
            player2Cards.push(card2);
            player2Cards.push(card1);
        }
        else
        {
            std::cout << "Infinite loop" << std::endl;
            exit(1);
        }
    }

    return player2Cards.empty() ? &player1Cards : &player2Cards;
}
