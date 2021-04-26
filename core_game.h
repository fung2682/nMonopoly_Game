#include <string>

#ifndef CORE_H
#define CORE_H
// A player structure includes money, chess position, alive/dead.
struct Player {
    int money;
    int position;
    int status;
    int token;
};

// A propety structure includes the land's owner and number of houses.
struct Propety {
    int owner;  // -1 = empty,
    int house;  // 0-5 = houses,
};

int game(string save);
#endif