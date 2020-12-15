
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

typedef std::queue<char>  OutputQueue;
typedef std::stack<char>  OperatorStack;
typedef std::vector<char> TokenList;

void     shuntingYardAlgorithm(const TokenList& tokens, OutputQueue& outputQueue);
uint64_t evalReversePolishNotation(OutputQueue& outputQueue);

int main()
{
    uint64_t sum = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        TokenList tokens;

        std::stringstream _line(line);
        char token;

        while (_line >> token)
        {
            tokens.push_back(token);
        }

        OutputQueue outputQueue;
        shuntingYardAlgorithm(tokens, outputQueue);
        sum += evalReversePolishNotation(outputQueue);
    }

    std::cout << sum << std::endl;

    return 0;
}

void shuntingYardAlgorithm(const TokenList& tokens, OutputQueue& outputQueue)
{
    OperatorStack operatorStack;

    for (char token : tokens)
    {
        switch (token)
        {
            case '+':
            {
                while (!operatorStack.empty() &&
                       (operatorStack.top() == '+' || operatorStack.top() == '*') &&
                       operatorStack.top() != '(')
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push('+');
                break;
            }
            case '*':
            {
                while (!operatorStack.empty() &&
                       (operatorStack.top() == '+' || operatorStack.top() == '*') &&
                       operatorStack.top() != '(')
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push('*');
                break;
            }
            case ')':
            {
                while (operatorStack.top() != '(')
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }

                if (operatorStack.empty())
                {
                    exit(1);
                }

                operatorStack.pop();
                break;
            }
            case '(':
            {
                operatorStack.push('(');
                break;
            }
            default:
            {
                outputQueue.push(token);
                break;
            }
        }
    }

    while (!operatorStack.empty())
    {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }
}

uint64_t evalReversePolishNotation(OutputQueue& outputQueue)
{
    std::stack<uint64_t> outputStack;

    while (!outputQueue.empty())
    {
        const char token = outputQueue.front();
        outputQueue.pop();

        if (token != '+' && token != '*')
        {
            outputStack.push(token - '0');
        }
        else
        {
            const uint64_t a = outputStack.top();
            outputStack.pop();
            const uint64_t b = outputStack.top();
            outputStack.pop();

            switch (token)
            {
                case '+':
                {
                    outputStack.push(a + b);
                    break;
                }
                case '*':
                {
                    outputStack.push(a * b);
                    break;
                }
            }
        }
    }

    return outputStack.top();
}
