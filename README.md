# nMonopoly
**nMonopoly** is a text-based remake of the classic board game [**Monopoly**](https://en.wikipedia.org/wiki/Monopoly_(game)) made with C++.


# Group information
Member: 

@Bobibobibu Bobby Lee Kin Chung   University No.: 3035789784   Contact: u3578978@connect.hku.hk

@fung2682 Jeffrey Fung Hon Yin   University No.: 3035784497   Contact: fung2682@connect.hku.hk
       
       
# Rule
In **nMonopoly**, the player will compete with 1-3 Computers, collecting rent from their opponents, with the goal being to drive them into bankruptcy. The looping game-board consists of 16 spaces containing 8 properties, 1 Chance spaces, 1 Decision spaces, an University Fee space, a Student Union Fee space, and the 4 special spaces: GO, In Jail, Free Parking, and Go to Jail.

## Dice
Players take turn with a random initial player to roll a six-sided dice and advance their pieces forward.

## Money
Each player starts with **$1500**. A player whose piece reaches the end of the board and return to the beginning will gain **$200**. Players can also gain or loss by rent, taxes, Chance, and Decision.

## Chance and Decision
When a player's piece land on a **Chance or Decision** space, a random event is triggered. Each events will lead to different outcomes.

## Jail
When a player's piece land on the **Go to Jail** or affected by some specific events, their turn ends immediately and they are sent to jail, with their piece moved to **In Jail** space and pay $100.

## Properties
When a player's piece land on an unowned property space, they can choose to buy the property for its listed price. If the property is owned, they will pay the owner a given rent.
If the player owns the property they land on and all other properties of the group, they can choose to develop it by building a house on it for $100. Each house built will double the rent of the property. Up to 5 houses can be built on one propety.

## Winning
A player wins when:
- All other player has bankrupted, or
- Having the highest money after 100 turns for each player

# Feature
- ASCII art title screen
- Save an interrupted game to continue later
- Remake Propeties' names and Chance and Decision cards to have the theme of HKU
- Some output is animated
- Optional difficulty can be set to affect the starting money
- Leaderboard system to record the score when the user wins, grouped by the difficulty

# Coding Elements Implementation
- Generation of random game sets or events: Dice rolls and Chance and Decision events are random
- Data structures for storing game status: Structs are used to store dynamic data of properties, players and tokens.
- Dynamic memory management: Decide the size of array by the number of computers
- File input/output (e.g., for loading/saving game status): Save and load an interrupted game, store leaderboard record and store static data of properties and events
- Program codes in multiple files: separate the parts of menu and core game to two different files, with core game becomes a library, also extract some function (e.g. token, interface control, constant) as separated libraries and copypasta as separated text file to make the main code looks cleaner and facilitate maintainence.
- Proper indentation and naming styles: Done
- In-code documentation: Done
