//
// Created by philipp on 12/9/22.
//

#include "RockPaperScissor.h"
#include <sstream>

using namespace std;

unsigned int RockPaperScissorDecision::get_score_of_round(char const opponent, char const I) const
{
    unsigned int score = choice_score.at(I);
    char const out = outcome(opponent, I);
    score += outcome_score.at(out);
    return score;
}

constexpr char RockPaperScissorDecision::outcome(char const opponent, char const I) const
{
    unsigned int o_index = int(opponent) - int('A');
    unsigned int I_index = int(I) - int('X');

    return truth_table.at(o_index).at(I_index);
};

istream& operator>>(istream& is, RockPaperScissorRound& rps)
{
    string line{};
    if(getline(is, line))
    {
        istringstream tmp{line};
        tmp >> rps.opponent;
        tmp >> rps.I;
    }
    return is;
}

// A lot of code duplication...

unsigned int RockPaperScissorDecision2::get_score_of_round(char const opponent, char const outcome) const
{
    unsigned int score = outcome_score.at(outcome);
    char const choice = my_choice(opponent, outcome);
    score += choice_score.at(choice);
    return score;
}

constexpr char RockPaperScissorDecision2::my_choice(char const opponent, char const outcome) const
{
    unsigned int op_index = int(opponent) - int('A');
    unsigned int out_index = int(outcome) - int('X');

    return outcome_table.at(op_index).at(out_index);
};

istream& operator>>(istream& is, RockPaperScissorRound2& rps)
{
    string line{};
    if(getline(is, line) && !line.empty())
    {
        istringstream tmp{line};
        tmp >> rps.opponent;
        tmp >> rps.outcome;
    }
    return is;
}