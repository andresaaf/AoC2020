#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day5.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day5(input, part);
}
