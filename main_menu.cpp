#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstdio>
#include "token.h"
#include "interface.h"
#include "const.h"
#include "core_game.h"
using namespace std;
struct Record {
    string name;
    int score;
};

// Facilitate sort
bool cmp(Record a, Record b) {
    if (a.score == b.score) {
        return a.name < b.name;
    }
    else
    {
        return a.score > b.score;
    }
}

// Whether the text file exists
bool existfile(string file) {
    ifstream fin;
    fin.open(file);
    if (fin.good()) {
        fin.close();
        return true;
    }
    else {
        fin.close();
        return false;
    }
}

// Print the context in the text file
void printfile(string file) {
    ifstream fin;
    string temp;
    fin.open(file);
    if (fin.fail()) {
        clrscr;
        cout << file << " not found!\nPress <ENTER> to terminate the game.";
        cin.ignore();
        getchar();
        exit(1);
    }
    while (getline(fin, temp)) {
        cout << temp << "\n";
    }
    fin.close();
}

string startgame() {
    // Initialise
    int num_player, mode;
    int token_type[4];
    ofstream fout;
    string str, save;
    // Choose number of player
    do {
        clrscr();
        cout << "-> 1. Start Game\n";
        cout << "Choose the number of player (2-4): ";
        cin >> str;
    } while (str != "2" and str != "3" and str != "4"); 
    num_player = stoi(str);
    cout << "Number of Player is " << num_player << ".\n";
    delay(1000);
    // Choose difficulty
    do {
        clrscr(); 
        cout << "-> 1. Start Game\nNumber of player: " << num_player << "\n";
        cout << "Choose your difficulty:\n";
        cout << "1. Easy: Players has $500 more initial capital than computers.\n2. Normal\n3. Hard: Computer has $500 more initial capital than players.\n";
        cout << "Option: ";
        cin >> str;
    } while (str != "1" and str != "2" and str != "3");
    if (str == "1") {
        cout << "Easy Mode selected.\n";
        mode = 1;
    }
    else if (str == "2") {
        cout << "Normal Mode selected.\n";
        mode = 2;
    }
    else if (str == "3") {
        cout << "Hard Mode selected.\n";
        mode = 3;
    }
    delay(1000);
    // Choose token
    do {
        clrscr(); 
        cout << "-> 1. Start Game\nNumber of player: " << num_player << "\n" << "Difficulty: " << mode << "\n";
        cout << "Choose your token: \n";
        for (int i = 0; i < token_size; i++) {
            cout << i + 1 << ". " << token(i) << " ";
        }
        cout << "\n";
        cout << "Option: ";
        cin >> str;
    } while (atoi(str.c_str()) <= 0 or atoi(str.c_str()) > token_size);
    token_type[0] = str[0] - '1';
    cout << "Your token is " << token(token_type[0]) << ".\n";
    for (int i = 1; i < num_player; i++) {
        token_type[i] = rand() % token_size;
        cout << "Computer "<< i <<" token is " << token(token_type[i]) << ".\n";
    }
    delay(1000 * num_player);
    clrscr();
    // Starting game
    cout << "-> 1. Start Game\nNumber of player: " << num_player << "\n" << "Difficulty: " << mode << "\n" << "Token: " << token(token_type[0]) << "\n";
    cout <<  "Initialising...\n";
    for (int i = 0; i > -1; i++) {
        if (!existfile("save" + to_string(i) + ".txt")) {
            save = "save" + to_string(i) + ".txt";
            break;
        }
    }
    fout.open(save);
    fout << num_player << " " << mode <<" 0\n";
    fout << default_money << " " << token_type[0] << " 0 0" << "\n";
    for (int i = 1; i < num_player; i++) {
        if (mode == 1) {
            fout << easy_money << " ";
        }
        else if (mode == 2) {
            fout << default_money << " ";
        }
        else if (mode == 3) {
            fout << hard_money << " ";
        }
        fout << token_type[i] << " 0 0"  << "\n";  
    }
    for (int i = 0; i < 16; i++) {
        fout << "-1 0\n";
    }
    fout.close();
    cout << "Save file " << save << " created.\n";
    cout << "Press <ENTER> to start the game.\n";
    cin.ignore();
    getchar();
    return save;    
}

// Choose a save file to load
string loadgame() {
    ifstream fin;
    int saveint;
    string save = "save0.txt", s, str;
    if (existfile(save)) {
        // List available save file and their basic information
        do {
            clrscr();
            cout << "-> 2. Load Game\n";
            cout << "Choose the save file to load:\n\n";
            for (int i = 0; i > -1; i++) {
                if (existfile("save" + to_string(i) + ".txt")) {
                    save = "save" + to_string(i) + ".txt";
                    saveint = i;
                    fin.open(save);
                    fin >> s;
                    cout << i + 1 << ". Number of players: " << s;
                    fin >> s;
                    cout << " Difficulty: ";
                    if (s == "1") {
                        cout << "Easy";
                        }
                    else if (s == "2") {
                        cout << "Normal";
                    }
                    else if (s == "3") {
                        cout << "Hard";
                    }
                    fin >> s;
                    cout << " Round " << s << "\n\n";
                    fin.close();
                }
                else {
                    break;
                };           
            }
            cout << "Option: ";
            cin >> str;
        } while (atoi(str.c_str()) <= 0 or atoi(str.c_str()) > saveint + 1);
        save = "save" + string(1, str[0] - 1) + ".txt";
        cout << "Loading " << save << "...\n";
        cout << "Press <ENTER> to continue.";
        cin.ignore();
        getchar();
        return save;
    }
    else {
        clrscr;
        cout << "Save file " << save << " not found!\nPlease don't delete any save file.\nPress <ENTER> to terminate the program.";
        cin.ignore();
        getchar();
        exit(2);
    }
}

void leaderboard() {
    string str;
    int mode;
    ifstream fin;
    vector<Record> record;
    // Choose difficulty
    do {
        clrscr(); 
        cout << "-> 3. Leaderboard";
        cout << "Choose the difficulty:\n";
        cout << "1. Easy\n2. Normal\n3. Hard\n";
        cout << "Option: ";
        cin >> str;
    } while (str != "1" and str != "2" and str != "3");
    if (str == "1") {
        cout << "Easy Mode selected.\n";
        mode = 1;
    }
    else if (str == "2") {
        cout << "Normal Mode selected.\n";
        mode = 2;
    }
    else if (str == "3") {
        cout << "Hard Mode selected.\n";
        mode = 3;
    }
    delay(1000);
    clrscr();
    // Open leaderboard text file
    if (mode == 1) {
        fin.open("easy_record.txt");
        cout << "Easy:\n";
    }
    else if (mode == 2) {
        fin.open("medium_record.txt");
        cout << "Normal:\n";
    }
    else if (mode == 3) {
        fin.open("hard_record.txt");
        cout << "Hard: \n";
    }
    if (fin.peek() == EOF) {
        cout << "There is no record for this difficulty. Go create one!\n";
    }
    else {
        while (fin >> str) {
            // Read name from leaderboard text file
            record.push_back({str, 0});
            // Read score from leaderboard text file
            fin >> str;
            if ( str != "0" and atoi(str.c_str()) == 0 ) {
                cout << "Corrupted leaderboard. \nPlease don't modify any leaderboard file.\nPress <ENTER> to terminate the program.";
                cin.ignore();
                getchar();
                exit(4);
            }
            else {
                (*(record.end() - 1)).score = atoi(str.c_str());
            }
        }
        fin.close();
        sort(record.begin(), record.end(), cmp);
        for (int i = 0; i < record.size() and i < 20; i++) {
            cout << i + 1 << ". " << record[i].name << ": " << record[i].score << "\n";
        }
    }
    cout << "Press <ENTER> to continue.";
    cin.ignore();
    getchar();
}

int main() {
    char c;
    int saveint;
    string str, save;
    clrscr();
    printfile("logo_se.txt");
    delay(500);
    clrscr();
    printfile("logo_sw.txt");
    delay(500);
    clrscr();
    printfile("logo_nw.txt");
    delay(500);
    clrscr();
    printfile("logo_ne.txt");
    delay(500);
    clrscr();
    do {
        printfile("logo_se.txt");
        cout << "1. Start Game\n\n";  
        cout << "2. Load Game\n\n";
        cout << "3. Leaderboard\n\n";
        cout << "Option: ";
        cin >> str;
        if (str == "1") {
            save = startgame();
            game(save);
        }
        else if (str == "2") {
            save = loadgame();
            game(save);
        }
        else if (str == "3") {
            leaderboard();
        }   
    } while (str != "1" and str != "2");
    remove(save.c_str());
    saveint = save[4] - '0' + 1;
    while (existfile("save" + to_string(saveint) + ".txt")) {
        rename(("save" + to_string(saveint) + ".txt").c_str(),( "save" + to_string(saveint - 1) + ".txt").c_str());
        saveint++;
    }
}
