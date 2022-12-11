//
// Created by philipp on 12/9/22.
//

#ifndef ADVENT_OF_CODE_2022_ELF_H
#define ADVENT_OF_CODE_2022_ELF_H

#include <vector>
#include <iostream>

class Elf
{
public:
    Elf() = default;
    //explicit Elf(const std::vector<unsigned int>& food_rv);
    explicit Elf(std::vector<unsigned int>&& food_rv);

    unsigned int get_total_calories() const;
    std::istream& read_calories(std::istream& stream);

    friend std::ostream& operator<<(std::ostream& stream, Elf const& elf);

private:
    std::vector<unsigned int> food;
};

#endif //ADVENT_OF_CODE_2022_ELF_H
