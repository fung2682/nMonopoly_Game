#include "interface.h"
using namespace std;

// Clear the terminal
void clrscr() {
    system("CLS");
}

// Delay the problem for msec milliseconds
void delay(int msec) {
    this_thread::sleep_for(chrono::milliseconds(msec));
}