
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

    ssize_t getValue() const
    {
        return value;
    }
};

typedef std::vector<Instruction> InstructionList;
typedef std::vector<bool> PreviouslyRunList;

void readInstructions(InstructionList& instructions, PreviouslyRunList& runList);
size_t runCode(const InstructionList& instructions, PreviouslyRunList& runList, ssize_t& reg);

int main()
{
    InstructionList   instructions;
    PreviouslyRunList runList;

    readInstructions(instructions, runList);

    ssize_t reg = 0;
    runCode(instructions, runList, reg);

    std::cout << reg << std::endl;

    return 0;
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
