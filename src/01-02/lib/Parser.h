//
// Created by philipp on 12/9/22.
//

#ifndef ADVENT_OF_CODE_2022_PARSER_H
#define ADVENT_OF_CODE_2022_PARSER_H

#include <fstream>
#include <string>
#include "Elf.h"
#include "RockPaperScissor.h"

class Parser
{
public:
    explicit Parser(const std::string& filename);
    bool read_next_elf(Elf& elf);
    bool read_next_RPS(RockPaperScissorRound& rps);
    bool read_next_RPS2(RockPaperScissorRound2& rps);
    //void reset(); Would need some tweaks

private:
    std::ifstream input;
};


#endif //ADVENT_OF_CODE_2022_PARSER_H
