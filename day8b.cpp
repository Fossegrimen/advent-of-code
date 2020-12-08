
#include <algorithm>
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

    void setOpcode(Opcode opcode)
    {
        this->opcode = opcode;
    }

    int getValue() const
    {
        return value;
    }

    bool operator==(const Opcode& opcode) const
    {
        return this->opcode == opcode;
    }
};

void readInstructions(std::vector<Instruction>& instructions, std::vector<bool>& runList);
size_t replaceNthOccurrence(std::vector<Instruction>& instructions, Opcode opcode, int n);
size_t runCode(std::vector<Instruction>& instructions, std::vector<bool>& runList, int* accumulator);

int main()
{
    std::vector<Instruction> instructions;
    std::vector<bool> runList;

    readInstructions(instructions, runList);

    for (size_t j = 0; j < std::count(instructions.begin(), instructions.end(), Opcode::NOP); j++)
    {
        size_t index = replaceNthOccurrence(instructions, Opcode::NOP, j);
        int accumulator = 0;
        size_t i = runCode(instructions, runList, &accumulator);

        if (i >= instructions.size())
        {
            std::cout << accumulator << std::endl;
            return 0;
        }

        instructions[index].setOpcode(Opcode::NOP);
        std::fill(runList.begin(), runList.end(), false);
    }

    for (size_t j = 0; j < std::count(instructions.begin(), instructions.end(), Opcode::JMP); j++)
    {
        size_t index = replaceNthOccurrence(instructions, Opcode::JMP, j);
        int accumulator = 0;
        size_t i = runCode(instructions, runList, &accumulator);

        if (i >= instructions.size())
        {
            std::cout << accumulator << std::endl;
            return 0;
        }

        instructions[index].setOpcode(Opcode::JMP);
        std::fill(runList.begin(), runList.end(), false);
    }

    return 1;
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

size_t replaceNthOccurrence(std::vector<Instruction>& instructions, Opcode opcode, int n)
{
    size_t index = 0;

    for (Instruction& instruction : instructions)
    {
        if (instruction.getOpcode() == opcode)
        {
            if (n == 0)
            {
                break;
            }

            n--;
        }

        index++;
    }

    if (opcode == Opcode::JMP)
    {
        instructions[index].setOpcode(Opcode::NOP);
    }
    else if (opcode == Opcode::NOP)
    {
        instructions[index].setOpcode(Opcode::JMP);
    }

    return index;
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
