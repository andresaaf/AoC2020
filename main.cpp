#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day10.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day10(input, part);
}
