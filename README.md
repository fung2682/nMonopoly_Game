# nMonopoly
**nMonopoly** is a text-based remake of the classic board game [**Monopoly**](https://en.wikipedia.org/wiki/Monopoly_(game)) made with C++.


# Group information
Member: 

@Bobibobibu Bobby Lee Kin Chung   University No.: 3035789784   Contact: u3578978@connect.hku.hk

@fung2682 Jeffrey Fung Hon Yin   University No.: 3035784497   Contact: fung2682@connect.hku.hk
       
       
# Rule
In **nMonopoly**, the player will compete with 1-5 A.I. players, collecting rent from their opponents, with the goal being to drive them into bankruptcy. The looping game-board consists of 40 spaces containing 28 properties -- 22 cities (grouped into eight distinct colour groups), 4 railroads, and 2 utilities -- 3 Chance spaces, 3 Decision spaces, a House Tax space, an Income Tax space, and the 4 special spaces: GO, In Jail, Free Parking, and Go to Jail.

## Dice
Players take turn with a random initial player to roll two six-sided dice and advance their pieces forward. If a player rolls a double, they roll the dice again. If a player rolls 3 doubles in the same turn, the player is sent to jail immediately.

## Money
Each player starts with **$1500**. A player whose piece reaches the end of the board and return to the beginning will gain **$200**. Players can also gain or loss by rent, taxes, Chance, and Decision.

## Chance and Decision
When a player's piece land on a **Chance or Decision** space, a random event is triggered. **Chance** events can either have an immediate effect or lingering effect on the player, some players, or all players. **Decision** events allow the player to choose between two options which will lead to different outcomes.

## Jail
When a player's piece land on the **Go to Jail** or affected by some specific events, their turn ends immediately and they are sent to jail, with their piece moved to **In Jail** space. When a player is in jail, at the start of their turn, they will roll two dice. If they roll a double, they will get out of jail, else their turn is skipped. If a player has been in jail for at least 3 turns and fails to roll a double, they can pay $100 to get out of the jail.
If a player is in jail, they cannot collect rent or affected by events.

## Properties
When a player's piece land on an unowned property space, they can choose to buy the property for its listed price. If the property is owned and not mortgaged, they will pay the owner a given rent. When a player owns all properties of a colour group without mortgaging any of them, the rent of all properties belong to that colour group is doubled.
If the player owns the property they land on and all other properties of the colour group without mortgaging any of them, they can choose to develop it by building a house on it for a listed price. Each house built will increase the rent of the property. If 4 houses have already been built on the property, the player can remove all houses and build a hotel instead. Properties with a hotel can no longer be developed.
No house can be built on non-city properties, but they have other traits.

## Mortgaging
When a player has negative value of money held, they need to mortgage their properties to the bank until the value is positive again. The player gains 50% of the listed price of the property and all houses/hotel on it. A player landing on a mortgaged property will not be collected of rent or develop it. At the start of the turn before rolling the dice, a player can choose to redeem any of their mortgaged properties with the mortgage price plus 10% of the listed price.

## Winning
A player wins when:
- All other player has bankrupted, or
- Having the highest score (including money, properties, and houses in the listed price) after 100 turns for each player

# Feature
- ASCII interface in-game, with both full-text and dynamic output
- Using a textbox system to handle input and output, eliminating the need for the user to scroll up and down
- Save an interrupted game to continue later
- Remake Chance cards to be more interesting, involving strategy and heavily impact gameplay
- Some dynamic output is animated, with the option to remove it
- Optional difficulty can be set to affect the starting money and luck of rolling dice of both player and A.I.
- Leaderboard system to record the score when the user wins, grouped by the difficulty
- Achievement system for progression and challenge

# Coding Elements Implementation
- Generation of random game sets or events: Dice rolls and Chance and Decision events are random
- Data structures for storing game status: Classes/Structs are used to store dynamic data of properties, players, and events
- Dynamic memory management: Decide the size of numerous array by the number of players
- File input/output (e.g., for loading/saving game status): Save and load an interrupted game, store leaderboard record and store static data of properties and events
- Program codes in multiple files: Actions related to properties and events will be stored in separate files with their classes/structs
