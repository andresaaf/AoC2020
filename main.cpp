#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day17.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day17_part2(input, part);
}
