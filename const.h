#include <string>
#ifndef CONST_H
#define CONST_H
using namespace std;

// A land structure includes the land's name, price, rent, owner, and number of houses.
struct Land {
  string name;
  int price;
  int rent;
};

const int default_money = 1500;
const int easy_money = 1000;
const int hard_money = 2000;
const int max_land = 16;

const Land land_array[max_land] = {
{"GO", -1, 0}, 
{"HKU MTR Station", 60, 10}, 
{"Chance", -1, 0}, 
{"Cheung Yu Tower", 100, 20}, 
{"Visiting/In Jail", -1, 0}, 
{"Run Run Shaw Tower", 140, 30}, 
{"Decision", -1, 0}, 
{"The Jockey Club Tower", 180, 40},
{"Free Parking", -1, 0}, 
{"Haking Wong Building", 220, 50}, 
{"University Fee", -1, 0}, 
{"HKU Main Building", 260, 60}, 
{"GO TO JAIL", -1, 0}, 
{"HKU Library", 300, 70}, 
{"Student Union Fee", -1, 0}, 
{"K. K. Leung Building", 350, 80}
};
#endif