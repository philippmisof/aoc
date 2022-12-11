#include <iostream>
#include "Elf.h"
#include "Parser.h"
#include "RockPaperScissor.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void find_best_nurtured_elfs()
{
    Parser input_parser("calories.dat");
    vector<unsigned int> calories{};

    Elf elf{};
    while (input_parser.read_next_elf(elf))
    {
        calories.push_back(elf.get_total_calories());
        elf = Elf{};
    }
    auto max_calories = max_element(calories.begin(), calories.end());
    cout << "Elf " << distance(calories.begin(), max_calories)
        << " has the most calories with " << *max_calories << "\n";


    nth_element(calories.begin(), calories.end()-3,calories.end());
    cout << "The three elves carrying the most calories have "
        << accumulate(calories.end()-3, calories.end(), 0)
        << " calories in total." << "\n\n";
    return;
};

void compute_RPS_score()
{
    Parser input_parser("rock_paper_scissor_cheat.dat");
    vector<unsigned int> scores{};

    RockPaperScissorRound rps{};
    RockPaperScissorDecision const decision{};

    while (input_parser.read_next_RPS(rps))
    {
        scores.push_back(decision.get_score_of_round(rps.opponent, rps.I));
        //cout << scores.back() << "\n";
    }
    unsigned int total = accumulate(scores.begin(), scores.end(), 0);

    cout << "Wrong interpretation of cheat sheet would achieve a score of " << total << " points.\n";

    scores.clear();
    input_parser = Parser("rock_paper_scissor_cheat.dat");
    RockPaperScissorRound2 rps2{};
    RockPaperScissorDecision2 const decision2{};

    while (input_parser.read_next_RPS2(rps2))
    {
        scores.push_back(decision2.get_score_of_round(rps2.opponent, rps2.outcome));
        //cout << scores.back() << "\n";
    }
    total = accumulate(scores.begin(), scores.end(), 0);

    cout << "Correct interpretation of cheat sheet would achieve a score of " << total << " points.\n";
    return;
};


int main()
{
    find_best_nurtured_elfs();
    compute_RPS_score();

    return 0;
}
