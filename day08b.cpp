
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
    Opcode  opcode;
    ssize_t value;

public:
    Instruction(Opcode opcode, ssize_t value) : opcode ( opcode ), value ( value ){};

    Opcode getOpcode() const
    {
        return opcode;
    }

    void setOpcode(Opcode opcode)
    {
        this->opcode = opcode;
    }

    ssize_t getValue() const
    {
        return value;
    }

    bool operator==(const Opcode& opcode) const
    {
        return this->opcode == opcode;
    }
};

typedef std::vector<Instruction> InstructionList;
typedef std::vector<bool> PreviouslyRunList;

void readInstructions(InstructionList& instructions, PreviouslyRunList& runList);
size_t replaceNthOccurrence(InstructionList& instructions, const Opcode opcode, size_t n);
size_t runCode(const InstructionList& instructions, PreviouslyRunList& runList, ssize_t& reg);

int main()
{
    InstructionList   instructions;
    PreviouslyRunList runList;

    readInstructions(instructions, runList);

    for (size_t i = 0; i < 2; i++)
    {
        Opcode opcode;

        if (i == 0)
        {
            opcode = Opcode::NOP;
        }
        else
        {
            opcode = Opcode::JMP;
        }

        for (size_t j = 0; j < (size_t)std::count(instructions.begin(), instructions.end(), opcode); j++)
        {
            const size_t index = replaceNthOccurrence(instructions, opcode, j);

            ssize_t      reg = 0;
            const size_t ip  = runCode(instructions, runList, reg);

            if (ip >= instructions.size())
            {
                std::cout << reg << std::endl;
                return 0;
            }

            std::fill(runList.begin(), runList.end(), false);

            instructions[index].setOpcode(opcode);
        }
    }

    return 1;
}

void readInstructions(InstructionList& instructions, PreviouslyRunList& runList)
{
    std::string opcodeString;
    ssize_t     value;

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

size_t replaceNthOccurrence(InstructionList& instructions, const Opcode opcode, size_t n)
{
    size_t index = 0;

    for (const auto& instruction : instructions)
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

size_t runCode(const InstructionList& instructions, PreviouslyRunList& runList, ssize_t& reg)
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
                reg += instructions[i].getValue();
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
