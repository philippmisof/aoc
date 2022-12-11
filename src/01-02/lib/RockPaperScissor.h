//
// Created by philipp on 12/9/22.
//

#ifndef ADVENT_OF_CODE_2022_ROCKPAPERSCISSOR_H
#define ADVENT_OF_CODE_2022_ROCKPAPERSCISSOR_H

#include <unordered_map>
#include <array>
#include <iostream>

struct RockPaperScissorRound
{
public:
    char opponent;
    char I;

    friend std::istream& operator>>(std::istream& is, RockPaperScissorRound& rps);
};


class RockPaperScissorDecision
{
public:
    unsigned int get_score_of_round(char const opponent, char const I) const;
private:
    const std::unordered_map<char, unsigned int> choice_score{
            {'X', 1},
            {'Y', 2},
            {'Z', 3}
    };
    const std::unordered_map<char, unsigned int> outcome_score = {
            {'l', 0},
            {'d', 3},
            {'w', 6}
    };
    const std::array<std::array<char, 3>, 3> truth_table{{
            {'d', 'w', 'l'},
            {'l', 'd', 'w'},
            {'w', 'l', 'd'}
    }};

    constexpr char outcome(char const opponent, char const I) const;
};

// This part is messy, was too lazy to avoid code duplication
struct RockPaperScissorRound2
{
public:
    char opponent;
    char outcome;

    friend std::istream& operator>>(std::istream& is, RockPaperScissorRound2& rps);
};


class RockPaperScissorDecision2
{
public:
    unsigned int get_score_of_round(char const opponent, char const outcome) const;
private:
    const std::unordered_map<char, unsigned int> choice_score{
            {'A', 1},
            {'B', 2},
            {'C', 3}
    };

    const std::unordered_map<char, unsigned int> outcome_score = {
            {'X', 0},
            {'Y', 3},
            {'Z', 6}
    };
    const std::array<std::array<char, 3>, 3> outcome_table{{
            {'C', 'A', 'B'},
            {'A', 'B', 'C'},
            {'B', 'C', 'A'}
    }};

    constexpr char my_choice(char const opponent, char const outcome) const;
};



#endif //ADVENT_OF_CODE_2022_ROCKPAPERSCISSOR_H
