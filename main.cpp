#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day9.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day9(input, part);
}
