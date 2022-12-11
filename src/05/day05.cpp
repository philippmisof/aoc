//
// Created by philipp on 12/10/22.
//
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector<char> stack_t;
typedef unordered_map<unsigned int, stack_t> stacks_t;

struct Move
{
    unsigned int number;
    unsigned int from;
    unsigned int to;
};

istream& operator>>(istream& is, Move& move)
{
    string discard{};
    is >> discard
        >> move.number
        >> discard
        >> move.from
        >> discard
        >> move.to;
    return is;
}

vector<Move> read_moves(istream& is)
{
    vector<Move> moves{};
    string line{};
    while(getline(is, line))
    {
        istringstream tmp{line};
        Move move{};
        tmp >> move;
        moves.push_back(move);
    }
    return moves;
}


typedef unordered_map<unsigned int, unsigned int> stack_map_t;
stack_map_t get_stack_map(string& line)
{
    stack_map_t map{};
    istringstream tmp{line};
    unsigned int stack_index;
    while (tmp >> stack_index)
    {
        // For numbers with more than one digit it only works for right aligned
        // numbers
        unsigned int position{static_cast<unsigned int>(tmp.tellg()) - 1};
        map.insert({stack_index, position});
    }
    return map;
}

void read_stacks_at_height(string const& line, stacks_t& stacks, stack_map_t const& stack_map)
{
    for (auto const& p : stack_map)
    {
        char crate = line[p.second];
        if (!isspace(crate))
            stacks[p.first].push_back(crate);
    }
    return;
}

stacks_t read_stacks(istream& is)
{
    vector<string> block{};
    string line{};
    while (getline(is, line))
    {
        if (line.empty()) break;
        block.push_back(line);
    }
    stack_map_t stack_map = get_stack_map(block.back());

    stacks_t stacks{};
    for (auto p: stack_map)
    {
        stacks.insert({ p.first, stack_t{} });
    }

    for (int i = block.size() - 2; i >= 0; --i)
    {
        read_stacks_at_height(block[i], stacks, stack_map);
    }
    return stacks;
}

void do_moves(stacks_t& stacks, vector<Move> const& moves, int const crate_mover)
{
    for (auto m : moves)
    {
        auto& dest_stack = stacks[m.to];
        dest_stack.resize(dest_stack.size() + m.number);
        auto& orig_stack = stacks[m.from];

        if (crate_mover == 9000)
            move(orig_stack.rbegin(), next(orig_stack.rbegin(), m.number), prev(dest_stack.end(), m.number));
            //reverse(prev(orig_stack.end(), m.number), orig_stack.end());
        else if (crate_mover == 9001)
            move(prev(orig_stack.end(), m.number), orig_stack.end(), prev(dest_stack.end(), m.number));
        else cout << "Unknown Crate Mover!!!!";
        orig_stack.resize(orig_stack.size() - m.number);
    }
    return;
}

void print_top_crates(stacks_t& stacks)
{
    for (auto const& p: stacks) cout << p.first;
    cout << "\n";
    for (auto const& p: stacks) cout << p.second.back();
    cout << "\n";

}

void print_stacks(stacks_t const& stacks)
{
    size_t highest_stack = 0;
    for (auto const& p: stacks)
    {
        highest_stack = max(highest_stack, p.second.size());
    }
    for (int i = highest_stack - 1; i >= 0; --i)
    {
        for (auto const& p: stacks)
        {
            if (p.second.size() > i) cout << "[" << p.second[i] << "] ";
            else cout << "    ";
        }
        cout << "\n";
    }
    for (auto const& p: stacks)
    {
        cout << " " << p.first << "  ";
    }
    cout << "\n";
    return;
}

int main()
{
    ifstream input("crates_reordering.dat");
    if (!input) return EXIT_FAILURE;

    stacks_t stacks = read_stacks(input);
    vector<Move> moves = read_moves(input);

    stacks_t stacks9000{stacks};
    do_moves(stacks9000, moves, 9000);

    cout << "The CrateMover 9000 would arrive at\n";
    print_top_crates(stacks9000);
    cout << "\n";
    print_stacks(stacks9000);

    do_moves(stacks, moves, 9001);

    cout << "The CrateMover 9001 would arrive at\n";
    print_top_crates(stacks);
    cout << "\n";
    print_stacks(stacks);
    return EXIT_SUCCESS;
}