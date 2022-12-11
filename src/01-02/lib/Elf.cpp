//
// Created by philipp on 12/9/22.
//
#include "Elf.h"
#include <numeric>
#include <sstream>

using namespace std;

//Elf::Elf(const vector<unsigned int>& food_rv)
//  : food{food_rv}
//{};

Elf::Elf(vector<unsigned int>&& food_rv)
  : food{move(food_rv)}
{}

unsigned int Elf::get_total_calories() const
{
    return accumulate(food.begin(), food.end(), 0);
}

istream& Elf::read_calories(istream& stream)
{
    unsigned int item_calories;
    string line{};
    while(getline(stream, line))
    {
        if (line.empty()) break;

        istringstream tmp{line};
        tmp >> item_calories;
        food.push_back(item_calories);
    };
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Elf const& elf)
{
    if (elf.food.size() > 0)
    {
        for (auto it = elf.food.begin(); it != --elf.food.end(); ++it)
        {
            stream << *it << " ";
        }
        stream << *(--elf.food.end());
        stream << "\n" << "  TOTAL: " << elf.get_total_calories() << "\n";
    }

    return stream;
}
