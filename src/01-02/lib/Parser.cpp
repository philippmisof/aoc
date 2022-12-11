//
// Created by philipp on 12/9/22.
//

#include "Parser.h"
using namespace std;

Parser::Parser(const std::string &filename)
{
    input = ifstream{filename};
}

bool Parser::read_next_elf(Elf& elf)
{
    elf.read_calories(input);
    return !input.eof();
}

bool Parser::read_next_RPS(RockPaperScissorRound& rps)
{
    input >> rps;
    return !input.eof();
}

bool Parser::read_next_RPS2(RockPaperScissorRound2& rps)
{
    input >> rps;
    return !input.eof();
}