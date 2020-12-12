#include "days.hpp"

using namespace std;

namespace
{
    enum class Direction
    {
        North,
        East,
        South,
        West,
        Left,
        Right,
        Forward
    };
    struct Move
    {
        Direction dir;
        uint32_t len;
    };

    struct Position
    {
        int x;
        int y;
        Direction dir;
    };
}

void day12(istream& in, int part)
{
    static map<char, Direction> char_to_dir = { {
        {'N', Direction::North},
        {'S', Direction::South},
        {'E', Direction::East},
        {'W', Direction::West},
        {'L', Direction::Left},
        {'R', Direction::Right},
        {'F', Direction::Forward}
    } };
    char dir;
    uint32_t len;

    vector<Move> moves;
    while (in >> dir >> len)
    {
        moves.push_back(Move{ char_to_dir[dir], len });
    }

    Position ship{ 0, 0, Direction::East };

    if (part == 1)
    {
        for (auto move : moves)
        {
            switch (move.dir)
            {
            case Direction::North:
                ship.y += move.len;
                break;
            case Direction::East:
                ship.x += move.len;
                break;
            case Direction::South:
                ship.y -= move.len;
                break;
            case Direction::West:
                ship.x -= move.len;
                break;
            case Direction::Left:
            {
                auto turns = (static_cast<int>(ship.dir) - (move.len % 360) / 90) % 4;
                if (turns < 0)
                    turns = 4 - turns;
                ship.dir = static_cast<Direction>(turns);
                break;
            }
            case Direction::Right:
            {
                auto turns = (static_cast<int>(ship.dir) + (move.len % 360) / 90) % 4;
                if (turns < 0)
                    turns = 4 - turns;
                ship.dir = static_cast<Direction>(turns);
                break;
            }
            case Direction::Forward:
                switch (ship.dir)
                {
                case Direction::North:
                    ship.y += move.len;
                    break;
                case Direction::East:
                    ship.x += move.len;
                    break;
                case Direction::South:
                    ship.y -= move.len;
                    break;
                case Direction::West:
                    ship.x -= move.len;
                    break;
                }
                break;
            }
        }

        cout << ship.x << ", " << ship.y << ": " << (int)ship.dir << '\n';
        cout << "Manhattan distance: " << (abs(ship.x) + abs(ship.y));
    }
    else
    {
        Position waypoint{ 10, 1, Direction::East };

        for (auto move : moves)
        {
            switch (move.dir)
            {
            case Direction::North:
                waypoint.y += move.len;
                break;
            case Direction::East:
                waypoint.x += move.len;
                break;
            case Direction::South:
                waypoint.y -= move.len;
                break;
            case Direction::West:
                waypoint.x -= move.len;
                break;
            case Direction::Left:
            {
                int turns = ((move.len % 360) / 90) % 4;
                if (turns < 0)
                    turns = 4 - turns;
                for (int i = 0; i < turns; ++i)
                {
                    auto temp_x = waypoint.x;
                    waypoint.x = -waypoint.y;
                    waypoint.y = temp_x;
                }
                break;
            }
            case Direction::Right:
            {
                int turns = ((move.len % 360) / 90) % 4;
                if (turns < 0)
                    turns = 4 - turns;
                for (int i = 0; i < turns; ++i)
                {
                    auto temp_x = waypoint.x;
                    waypoint.x = waypoint.y;
                    waypoint.y = -temp_x;
                }
                break;
            }
            case Direction::Forward:
                ship.x += move.len * waypoint.x;
                ship.y += move.len * waypoint.y;
                break;
            }
        }

        cout << ship.x << ", " << ship.y << ": " << (int)ship.dir << '\n';
        cout << "Manhattan distance: " << (abs(ship.x) + abs(ship.y));
    }
}
