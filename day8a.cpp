
#include <iostream>
#include <string>
#include <vector>

enum class Opcode
{
    ACC,
    JMP,
    NOP
};

class Instruction
{
private:
    Opcode opcode;
    int value;

public:
    Instruction(Opcode opcode, int value)
    {
        this->opcode = opcode;
        this->value = value;
    }

    Opcode getOpcode() const
    {
        return opcode;
    }

    int getValue() const
    {
        return value;
    }
};

void readInstructions(std::vector<Instruction>& instructions, std::vector<bool>& runList);
size_t runCode(std::vector<Instruction>& instructions, std::vector<bool>& runList, int* accumulator);

int main()
{
    std::vector<Instruction> instructions;
    std::vector<bool> runList;

    readInstructions(instructions, runList);

    int accumulator = 0;

    runCode(instructions, runList, &accumulator);
    std::cout << accumulator << std::endl;

    return 0;
}

void readInstructions(std::vector<Instruction>& instructions, std::vector<bool>& runList)
{
    std::string opcodeString;
    int value;

    while (std::cin >> opcodeString && std::cin >> value)
    {
        if (opcodeString == "acc")
        {
            instructions.push_back(Instruction(Opcode::ACC, value));
        }
        else if (opcodeString == "nop")
        {
            instructions.push_back(Instruction(Opcode::NOP, value));
        }
        else if (opcodeString == "jmp")
        {
            instructions.push_back(Instruction(Opcode::JMP, value));
        }

        runList.push_back(false);
    }
}

size_t runCode(std::vector<Instruction>& instructions, std::vector<bool>& runList, int* accumulator)
{
    size_t i = 0;

    while (i < instructions.size())
    {
        if (runList[i])
        {
            break;
        }
        else
        {
            runList[i] = true;
        }

        switch (instructions[i].getOpcode())
        {
            case Opcode::ACC:
            {
                *accumulator += instructions[i].getValue();
                break;
            }
            case Opcode::NOP:
            {
                break;
            }
            case Opcode::JMP:
            {
                i += instructions[i].getValue();
                continue;
            }
        }

        i++;
    }

    return i;
}
