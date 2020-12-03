#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day3.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day3(input, part);
}
