#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "const.h"
#include "interface.h"
#include "core_game.h"
#include "token.h"
using namespace std;

int game(string save) {
    // Initialize game variables.
    int num_of_players, mode;
    int current_round_player = 0, total_rounds;
    bool game_end = false;
    int win_case; // 0 = 1 player left, 1 = 100 rounds passed, 2 = draw after 100 rounds.
    int winner;
    string name;
    char c;
    string str;
    srand(time(NULL));
    int dice, card_picker; // Random variables.
    Player * player_array = new Player [num_of_players];
    Propety propety_array[max_land];
    ifstream fin;
    ofstream fout;

    clrscr();
    fin.open(save);
    if ( fin.fail() ) {
        clrscr();
        cout << save << " not found!\nPlease don't delete any save file.\nPress <ENTER> to terminate the program.";
        cin.ignore();
        getchar();
        exit(2);
    }
    // Read number of players from text file
    fin >> str;
    if ( atoi(str.c_str()) < 2 or atoi(str.c_str()) > 4 ) {
        cout << "Corrupted save (num). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
        cin.ignore();
        getchar();
        exit(3);
    }
    else {
        num_of_players = atoi(str.c_str());
    }
    // Read difficulty from textfile
    fin >> str;
    if ( atoi(str.c_str()) < 1 or atoi(str.c_str()) > 3 ) {
        cout << "Corrupted save (difficulty). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
        cin.ignore();
        getchar();
        exit(3);
    }
    else {
        mode = atoi(str.c_str());
    }
    // Read round number from text file
    fin >> str;
    if ( (str != "0" and atoi(str.c_str()) == 0) or atoi(str.c_str()) < 0 or atoi(str.c_str()) >= 100 * num_of_players) {
        cout << "Corrupted save (round). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
        cin.ignore();
        getchar();
        exit(3);
    }
    else {
        total_rounds = atoi(str.c_str());
        current_round_player = total_rounds % 4;
    }
    // Read player stat from text file
    for (int i = 0; i < num_of_players; i++) {
        // Read money
        fin >> str;
        if ( str != "0" and atoi(str.c_str()) == 0 ) {
            cout << "Corrupted save (money). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
        else {
            player_array[i].money = atoi(str.c_str());
        }
        // Read token
        fin >> str;
        if ( (str != "0" and atoi(str.c_str()) == 0) or atoi(str.c_str()) < 0 or atoi(str.c_str()) >= token_size) {
            cout << "Corrupted save (token). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
        else {
            player_array[i].token = atoi(str.c_str());
        }
        // Read position
        fin >> str;
        if ( (str != "0" and atoi(str.c_str()) == 0) or atoi(str.c_str()) < 0 or atoi(str.c_str()) >= max_land) {
            cout << "Corrupted save (position). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
        else {
            player_array[i].position = atoi(str.c_str());
        }
        // Read status
        fin >> str;
        if ( str == "0" ) {
            player_array[i].status = 0;
        }
        else if ( str == "1" ) {
            player_array[i].status = 1;
        } 
        else {
            cout << "Corrupted save (status). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
    }
    // Read propety stat from text file
    for (int i = 0; i < max_land; i++) {
        // Read owner
        fin >> str;
        if ( (str != "0" and atoi(str.c_str()) == 0) or atoi(str.c_str()) < -1 or atoi(str.c_str()) >= num_of_players) {
            cout << "Corrupted save (owner). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
        else {
            propety_array[i].owner = atoi(str.c_str());
        }
        // Read house
        fin >> str;
        if ( (str != "0" and atoi(str.c_str()) == 0) or atoi(str.c_str()) < 0 or atoi(str.c_str()) > 5) {
            cout << "Corrupted save (house). \nPlease don't modify any save file.\nPress <ENTER> to terminate the program.";
            cin.ignore();
            getchar();
            exit(3);
        }
        else {
            propety_array[i].house = atoi(str.c_str());
        }
    }
    fin.close();
    // Game process (1 loop = 1 round).
    while ( game_end == false ) {
        // Continue round if player is alive.
        while ( player_array[current_round_player].status == 0 ) {
            // Indicate the current player.
            if ( current_round_player == 0 ) {
                cout << "\nCurrent player is Player " << token(player_array[current_round_player].token) << endl;
            }
            else {
                cout << "\nCurrent player is Computer " << current_round_player << " " << token(player_array[current_round_player].token) << endl;
            }
            // Show current player's account balance and chess position.
            cout << "Account Balance: $" << player_array[current_round_player].money << endl;
            cout << "Chess position: " << player_array[current_round_player].position;
            cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
            // Show land owner and rent and number of houses.
            if ( land_array[player_array[current_round_player].position].price != -1 ) {
                if ( propety_array[player_array[current_round_player].position].owner == -1 ) {
                    cout << "(Owner: ---)";
                }
                else if ( propety_array[player_array[current_round_player].position].owner == 0 ) {
                    cout << "(Owner: Player " << token(player_array[current_round_player].token) <<")";
                }
                else {
                    cout << "(Owner: Computer " << propety_array[player_array[current_round_player].position].owner << " " << token(player_array[current_round_player].token) << ")";
                }
                cout << "(Land rent: " << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << ")";
                cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
            }
            // RNG
            dice = rand() % 6 + 1;
            card_picker = rand() % 5 + 1;
            // Round of Computer.
            if ( current_round_player != 0 ) {
                cout << "Computer rolling dice." << endl;
                cout << "Computer got " << dice << ".\n";
                // Check if passed "GO".
                if ( player_array[current_round_player].position + dice >= max_land ) {
                    cout << "Passed \"Go\", $200 is rewarded.\n";
                    player_array[current_round_player].money += 200;
                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                }
                // Update chess position and indicate land name.
                player_array[current_round_player].position = ( player_array[current_round_player].position + dice ) % max_land;
                cout << "Chess position: " << player_array[current_round_player].position;
                cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                // Show land owner and rent and number of houses.
                if ( land_array[player_array[current_round_player].position].price != -1 ) {
                    if ( propety_array[player_array[current_round_player].position].owner == -1 ) {
                        cout << "(Owner: ---)";
                    }
                    else if ( propety_array[player_array[current_round_player].position].owner == 0 ) {
                        cout << "(Owner: Player " << token(player_array[current_round_player].token) <<")";
                    }
                    else {
                        cout << "(Owner: Computer " << propety_array[player_array[current_round_player].position].owner << " " << token(player_array[current_round_player].token) << ")";
                    }
                    cout << "(Land rent: " << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << ")";
                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                }
                // Case of empty land.
                if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner == -1) ) {
                    cout << "Land price = $" << land_array[player_array[current_round_player].position].price << endl;
                    if ( (player_array[current_round_player].money - land_array[player_array[current_round_player].position].price) > 0 ) {
                        propety_array[player_array[current_round_player].position].owner = current_round_player;
                        cout << "Computer has bought \"" << land_array[player_array[current_round_player].position].name << "\".\n";
                        player_array[current_round_player].money -= land_array[player_array[current_round_player].position].price;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else {
                        cout << "Computer do not buy the land.\n";
                    }
                }
                // Case of owned land.
                else if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner != current_round_player) ) {
                    if (propety_array[player_array[current_round_player].position].owner = 0) {
                        cout << "Land owned by Player, $";
                    }
                    else {
                        cout << "Land owned by Computer " << propety_array[player_array[current_round_player].position].owner << ", $";
                    }
                    cout << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << " rent is paid.\n";
                    player_array[current_round_player].money -= land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                    player_array[propety_array[player_array[current_round_player].position].owner].money += land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                }
                // Case of self-owned land.
                else if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner == current_round_player) ) {
                    // Case of "HKU MTR Station", "Run Run Shaw Tower", "Haking Wong Building", "HKU Library".
                    if ( (player_array[current_round_player].position == 1) or (player_array[current_round_player].position == 5) or (player_array[current_round_player].position == 9) or (player_array[current_round_player].position == 13) ) {
                        // Check ownership of all properties in the group.
                        if ( propety_array[player_array[current_round_player].position + 2].owner == current_round_player ) {
                            // Check if maximum number of houses built is reached.
                            if ( propety_array[player_array[current_round_player].position].house < 5 ) {
                                // Check if the computer has enough money to build a house.
                                if ( (player_array[current_round_player].money - 100) > 0 ) {
                                    cout << "Computer owns all properties of this group. Computer builds a house ($100).\n";
                                    player_array[current_round_player].money -= 100;
                                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                                    cout << "New Land Rent: $" << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << endl;
                                    propety_array[player_array[current_round_player].position].house++;
                                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                                }
                                else {
                                    cout << "Computer do not build a house.\n";
                                }
                            }
                            else {
                                cout << "Max (5) number of houses built. Round ended.\n";
                            }
                        }
                        else {
                            cout << "Computer do not own all properties of this group. Round ended.\n";
                        }
                    }
                    // Case of 4 remaining land.
                    else
                        // Check ownership of all properties in the group.
                        if ( propety_array[player_array[current_round_player].position - 2].owner == current_round_player ) {
                            // Check if maximum number of houses built is reached.
                            if ( propety_array[player_array[current_round_player].position].house < 5 ) {
                                // Check if the computer has enough money to build a house.
                                if ( (player_array[current_round_player].money - 100) > 0 ) {
                                    cout << "Computer owns all properties of this group. Computer builds a house ($100).\n";
                                    player_array[current_round_player].money -= 100;
                                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                                    cout << "New Land Rent: $" << land_array[player_array[current_round_player].position].rent << endl;
                                    propety_array[player_array[current_round_player].position].house++;
                                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                                }
                                else {
                                    cout << "Computer do not build a house.\n";
                                }
                            }
                            else {
                                cout << "Max (5) number of houses built.\n";
                            }
                        }
                        else {
                            cout << "Computer do not own all properties of this group. Round ended.\n";
                        }
                }
                // Case of University / Student Union Fee.
                else if ( player_array[current_round_player].position == 10 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 University Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                }
                else if ( player_array[current_round_player].position == 14 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 Student Union Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                }
                // Case of "Go To Jail".
                else if ( player_array[current_round_player].position == 12 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 Jail Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                    player_array[current_round_player].position = 4;
                    cout << "Computer chess is moved back to \"Visiting/In Jail\".\n";
                }
                // Case of "Chance".
                else if ( player_array[current_round_player].position == 2 ) {
                    cout << "The \"Chance\" card writes: \n";
                    // Five cards of Chance.
                    if ( card_picker == 1 ) {
                        cout << "Got an A+ in ENGG1340 exam. Travel to \"GO\" and receive $200.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 0;
                        cout << "Chess position: " << player_array[current_round_player].position;
                        cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                    }
                    else if ( card_picker == 2 ) {
                        cout << "Caught plagiarising asignment. Go to Jail immediately and pay $100.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 4;
                        cout << "Computer chess is moved back to \"Visiting/In Jail\".\n";
                    }
                    else if ( card_picker == 3 ) {
                        cout << "Late return of books to the HKU Library. Pay $50 charge.\n";
                        player_array[current_round_player].money -= 50;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 4 ) {
                        cout << "Broke the equipment of Engineering Department. Pay $150 charge.\n";
                        player_array[current_round_player].money -= 250;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 5 ) {
                        cout << "Won App-Designing Competition by Department of Computer Science. Receive $200 prize.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                }
                // Case of "Decision".
                else if ( player_array[current_round_player].position == 6 ) {
                    cout << "The \"Decision\" card writes: \n";
                    // Five cards of Decision.
                    if ( card_picker == 1 ) {
                        cout << "Got a 4.3 GPA in Hong Kong University. Travel to \"GO\" and receive $200.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 0;
                        cout << "Chess position: " << player_array[current_round_player].position;
                        cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                    }
                    else if ( card_picker == 2 ) {
                        cout << "Caught cheating during in-class test. Go to Jail immediately and pay $100.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 4;
                        cout << "Computer chess is moved back to \"Visiting/In Jail\".\n";
                    }
                    else if ( card_picker == 3 ) {
                        cout << "Going to be late for class. Pay $100 for a taxi ride.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 4 ) {
                        cout << "Broke a computer in Chi Wah Learning Commons. Penalised $150.\n";
                        player_array[current_round_player].money -= 150;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 5 ) {
                        cout << "Succesfully applied for an internship of software developing. Rewarded $150.\n";
                        player_array[current_round_player].money += 150;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                }
            }
            // Round of Player.
            else {
                cout << "ENTER 'r' to role dice. ENTER 's' to save game. ";
                cin >> str;
                while ( str != "r" and str != "s" ) {
                    cout << "Please try again." << endl;
                    cin >> str;
                }
                // Save data to game save
                if ( str == "s" ) {
                    fout.open(save);
                    fout << num_of_players << " " << mode << " " << total_rounds << "\n";
                    for (int i = 0; i < num_of_players; i++) {
                        fout << player_array[i].money << " " << player_array[i].token << " " << player_array[i].position << " " << player_array[i].status << "\n";
                    }
                    for (int i = 0; i < max_land; i++) {
                        fout << propety_array[i].owner << " " << propety_array[i].house << "\n";
                    }
                    fout.close();
                    cout << save << " saved.\n";
                    cout << "ENTER 'r' to role dice. ";
                    cin >> str;
                    while ( str != "r") {
                        cout << "Please try again." << endl;
                        cin >> str;
                    }
                }
                cout << "You got " << dice << ".\n";
                // Check if passed "GO".
                if ( player_array[current_round_player].position + dice >= max_land ) {
                    cout << "Passed \"Go\", $200 is rewarded.\n";
                    player_array[current_round_player].money += 200;
                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                }
                // Update player's chess position and indicate land name.
                player_array[current_round_player].position = ( player_array[current_round_player].position + dice ) % max_land;
                cout << "Chess position: " << player_array[current_round_player].position;
                cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                // Show land owner and rent.
                if ( land_array[player_array[current_round_player].position].price != -1 ) {
                    if ( propety_array[player_array[current_round_player].position].owner == -1 ) {
                        cout << "(Owner: ---)";
                    }
                    else if ( propety_array[player_array[current_round_player].position].owner == 0 ) {
                        cout << "(Owner: Player " << token(player_array[current_round_player].token) <<")";
                    }
                    else {
                        cout << "(Owner: Computer " << propety_array[player_array[current_round_player].position].owner << " " << token(player_array[current_round_player].token) << ")";
                    }
                    cout << "(Land rent: " << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << ")";
                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                }
                // Case of empty land.
                if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner == -1) ) {
                    cout << "Land price = $" << land_array[player_array[current_round_player].position].price << endl;
                    cout << "Purchase \"" << land_array[player_array[current_round_player].position].name << "\"? y/n\n";
                    cin >> str;
                    while ( (str != "y") and (str != "n") ) {
                        cout << "Please try again." << endl;
                        cin >> str;
                    }
                    if ( str == "y" ) {
                        propety_array[player_array[current_round_player].position].owner = current_round_player;
                        cout << "You bought \"" << land_array[player_array[current_round_player].position].name << "\".\n";
                        cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                        player_array[current_round_player].money -= land_array[player_array[current_round_player].position].price;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else {
                        cout << "Round ended.\n";
                    }
                }
                // Case of owned land.
                else if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner != current_round_player) ) {
                    if ( propety_array[player_array[current_round_player].position].owner == 0 ) {
                        cout << "Land owned by Player, $";
                        cout << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << " rent is paid.\n";
                        player_array[current_round_player].money -= land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                        player_array[propety_array[player_array[current_round_player].position].owner].money += land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else {
                        cout << "Land owned by Computer " << propety_array[player_array[current_round_player].position].owner << ", $";
                        cout << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << " rent is paid.\n";
                        player_array[current_round_player].money -= land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                        player_array[propety_array[player_array[current_round_player].position].owner].money += land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house);
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                }
                // Case of self-owned land.
                else if ( (land_array[player_array[current_round_player].position].price != -1) and (propety_array[player_array[current_round_player].position].owner == current_round_player) ) {
                    // Case of "HKU MTR Station", "Run Run Shaw Tower", "Haking Wong Building", "HKU Library".
                    if ( (player_array[current_round_player].position == 1) or (player_array[current_round_player].position == 5) or (player_array[current_round_player].position == 9) or (player_array[current_round_player].position == 13) ) {
                        // Check ownership of properties in the same set.
                        if ( propety_array[player_array[current_round_player].position + 2].owner == current_round_player ) {
                            // Check if maximum number of houses buit is reached.
                            if ( propety_array[player_array[current_round_player].position].house < 5 ) {
                                cout << "You owned all properties of this group. Build a house? y/n\n";
                                cin >> str;
                                while ( (str != "y") and (str != "n") ) {
                                    cout << "Please try again." << endl;
                                    cin >> str;
                                }
                                if ( str == "y" ) {
                                    cout << "You build a house ($100).\n";
                                    player_array[current_round_player].money -= 100;
                                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                                    cout << "New Land Rent: $" << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << endl;
                                    propety_array[player_array[current_round_player].position].house++;
                                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                                }
                                else {
                                    cout << "Round ended.\n";
                                }
                            }
                            else {
                                cout << "Max (5) number of houses built.Round ended.\n";
                            }
                        }
                        else {
                            cout << "You do not own all properties of this group. Round ended.\n";
                        }
                    }
                    // Case of 4 remaining land.
                    else
                        // Check ownership of properties in the same set.
                        if ( propety_array[player_array[current_round_player].position - 2].owner == current_round_player ) {
                            // Check if maximum number of houses buit is reached.
                            if ( propety_array[player_array[current_round_player].position].house < 5 ) {
                                cout << "You owned all properties of this group. Build a house? y/n\n";
                                cin >> str;
                                while ( (str != "y") and (str != "n") ) {
                                    cout << "Please try again." << endl;
                                    cin >> str;
                                }
                                if ( str == "y" ) {
                                    cout << "You build a house ($100).\n";
                                    player_array[current_round_player].money -= 100;
                                    cout << "New account balance: $" << player_array[current_round_player].money << endl;
                                    cout << "New Land Rent: $" << land_array[player_array[current_round_player].position].rent * pow(2, propety_array[player_array[current_round_player].position].house) << endl;
                                    propety_array[player_array[current_round_player].position].house++;
                                    cout << "(Number of houses: " << propety_array[player_array[current_round_player].position].house << ")\n";
                                }
                                else {
                                    cout << "Round ended.\n";
                                }
                            }
                            else {
                                cout << "Max (5) number of houses built.\n";
                            }
                        }
                        else {
                            cout << "You do not own all properties of this group. Round ended.\n";
                        }
                }
                // Case of University / Student Union Fee.
                else if ( player_array[current_round_player].position == 10 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 University Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                }
                else if ( player_array[current_round_player].position == 14 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 Student Union Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                }
                // Case of "Go To Jail".
                else if ( player_array[current_round_player].position == 12 ) {
                    player_array[current_round_player].money -= 100;
                    cout << "$100 Jail Fee is paid. New account balance: $" << player_array[current_round_player].money << endl;
                    player_array[current_round_player].position = 4;
                    cout << "Player " << current_round_player << "'s chess is moved back to \"Visiting/In Jail\".\n";
                }
                // Case of "Chance".
                else if ( player_array[current_round_player].position == 2 ) {
                    // Five cards of Chance.
                    cout << "The \"Chance\" card writes: \n";
                    if ( card_picker == 1 ) {
                        cout << "Got an A+ in ENGG1340 exam. Travel to \"GO\" and receive $200.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 0;
                        cout << "Chess position: " << player_array[current_round_player].position;
                        cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                    }
                    else if ( card_picker == 2 ) {
                        cout << "Caught plagiarising asignment. Go to Jail immediately and pay $100.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 4;
                        cout << "Computer chess is moved back to \"Visiting/In Jail\".\n";
                    }
                    else if ( card_picker == 3 ) {
                        cout << "Late return of books to the HKU Library. Pay $50 charge.\n";
                        player_array[current_round_player].money -= 50;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 4 ) {
                        cout << "Broke the equipment of Engineering Department. Pay $150 charge.\n";
                        player_array[current_round_player].money -= 250;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 5 ) {
                        cout << "Won App-Designing Competition by Department of Computer Science. Receive $200 prize.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                }
                // Case of "Decision".
                else if ( player_array[current_round_player].position == 6 ) {
                    cout << "The \"Decision\" card writes: \n";
                    // Five cards of Decision.
                    if ( card_picker == 1 ) {
                        cout << "Got a 4.3 GPA in Hong Kong University. Travel to \"GO\" and receive $200.\n";
                        player_array[current_round_player].money += 200;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 0;
                        cout << "Chess position: " << player_array[current_round_player].position;
                        cout << " (" << land_array[player_array[current_round_player].position].name << ")\n";
                    }
                    else if ( card_picker == 2 ) {
                        cout << "Caught cheating during in-class test. Go to Jail immediately and pay $100.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                        player_array[current_round_player].position = 4;
                        cout << "Computer chess is moved back to \"Visiting/In Jail\".\n";
                    }
                    else if ( card_picker == 3 ) {
                        cout << "Going to be late for class. Pay $100 for a taxi ride.\n";
                        player_array[current_round_player].money -= 100;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 4 ) {
                        cout << "Broke a computer in Chi Wah Learning Commons. Penalised $150.\n";
                        player_array[current_round_player].money -= 150;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                    else if ( card_picker == 5 ) {
                        cout << "Succesfully applied for an internship of software developing. Rewarded $150.\n";
                        player_array[current_round_player].money += 150;
                        cout << "New account balance: $" << player_array[current_round_player].money << endl;
                    }
                }
            }


            // Check if the player lose after the round.
            if ( player_array[current_round_player].money <= 0 )
                player_array[current_round_player].status = 1;
                for (int i = 0; i < max_land; i++) {
                    if (propety_array[i].owner == current_round_player) {
                        propety_array[i].owner = -1;
                    }
                }
            // Check if the game ends (one player remaining).
            int alive_player_count = 0;
            for ( int i = 0; i < num_of_players; i++ ) {
                if ( player_array[i].status == 0 )
                    alive_player_count++;
            }
            if ( alive_player_count == 1 ) {
                game_end = true;
                win_case = 0;
                for ( int i = 0; i < num_of_players; i++ ) {
                    if ( player_array[i].status == 0 )
                        winner = i;
                }
            }
            // Check if the game ends (100 rounds passed).
            else if ( total_rounds >= 100 * num_of_players ) {
                game_end = true;
                win_case = 1;
                int most_money = 0;
                for ( int i = 0; i < num_of_players; i++ ) {
                    if ( player_array[i].money > most_money ) {
                        winner = i;
                        most_money = player_array[i].money;
                    }
                    else if ( player_array[i].money == most_money ) {
                        win_case = 2;
                    }
                }
            }
            if ( game_end == true )
                break;

            // Switch to next player.
            if ( current_round_player == num_of_players - 1 )
            current_round_player -= ( num_of_players - 1 );
            else
                current_round_player++;
            // Increment total_rounds by 1.
            total_rounds++;
        }

        // If player not alive, simply switch to next player.
        if ( current_round_player == num_of_players - 1 )
            current_round_player -= ( num_of_players - 1 );
        else
            current_round_player++;
        // Increment total_rounds by 1.
        total_rounds++;

    }
    // Print end-game messages.
    if ( game_end == true ) {
        cout << "\nThe game has ended." << endl;
        for ( int i = 0; i < num_of_players; i++ ) {
            if ( i != 0 )
                cout << "Computer "<< i << "'s account balance: $" << player_array[i].money << endl;
            else
                cout << "Player's account balance: $" << player_array[0].money << endl;
        }

        if ( win_case == 0 ) {
            if ( winner != 0 ) {
                cout << "The computer won. Try harder next time!\n\n";
            }
            else {
                cout << "You won.\n";
                cout << "Congratulations!\n";
                if ( mode == 1 ){
                    fout.open("easy_record.txt");
                }
                else if ( mode == 2 ){
                    fout.open("medium_record.txt");
                }
                else if ( mode == 3 ){
                    fout.open("hard_record.txt");
                }
                cout << "Enter your name: ";
                cin >> name;
                fout << name << " " << player_array[0].money;
                fout.close();
                cout << "Leaderboard saved.\n";
            }
        }
        else if ( win_case == 1 ) {
            cout << "100 rounds passed and ";
            if ( winner != 0 ) {
                cout << "the computer won. Try harder next time!\n\n";
            }
            else {
                cout << "you won.\n";
                cout << "Congratulations!\n";
                if ( mode == 1 ) {
                    fout.open("easy_record.txt", ios_base::app);
                }
                else if ( mode == 2 ) {
                    fout.open("medium_record.txt", ios_base::app);
                }
                else if ( mode == 3 ) {
                    fout.open("hard_record.txt", ios_base::app);
                }
                cout << "Enter your name: ";
                cin >> name;
                fout << name << " " << player_array[0].money << "\n";
                fout.close();               
                cout << "Leaderboard saved.\n";
            }
        }
        else {
            cout << "100 rounds passed and the result is a draw.\n\n";
        }
    }
    delete [] player_array;
    return 0;
}