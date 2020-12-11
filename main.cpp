#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day11.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day11(input, part);
}
