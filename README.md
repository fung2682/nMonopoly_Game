# nMonopoly
**nMonopoly** is a text-based remake of the classic board game [**Monopoly**](https://en.wikipedia.org/wiki/Monopoly_(game)) made with C++.


# Group infomation
Member: 
@Bobibobibu Bobby Lee Kin Chung   University No.: 3035789784   Contact: u3578978@connect.hku.hk

@fung2682 Jeffrey Fung Hon Yin   University No.: 3035784497   Contact: fung2682@connect.hku.hk
       
       
# Rule
In **nMonopoly**, the player will compete with 3 A.I. players, collecting rent from their opponents, with the goal being to drive them into bankruptcy. The looping game-board consists of 40 spaces containing 28 properties -- 22 cities (grouped into eight distinct color groups), 4 railroads, and 2 utilities -- 3 Chance spaces, 3 Decision spaces, a House Tax space, an Income Tax space, and the 4 special spaces: GO, In Jail, Free Parking, and Go to Jail.

## Dice
Players take turn with random initial player to roll two six-sided dice and advance their pieces forward. If a player rolls a double, they roll the dice again. If a player rolls 3 doubles in the same turn, the player is sent to jail immediately.

## Money
Each player start with **$1500**. A player whose piece reachs the end of the board and return to the beginning will gain **$200**. Money can also be gain or lost by rent, taxes, Chance, and Decision.

## Chance and Decision
When a player's piece land on a **Chance or Decision** space, a random event is triggered. **Chance** events can either have immediate effect or lingering effect on the player, some players, or all players. **Decision** events allows the player to choose between two options which will lead to different outcomes.

## Jail
When a player's piece land on the **Go to Jail** or affected by some specific events, their turn ends immediately and they are sent to jail, with their piece moved to **In Jail** space. When a player is in jail, at the start of their turn, they will roll two dice. If they roll a double, they will get out of jail, else their turn is skipped. If a player have been in jail for at least 3 turns and fail to roll a double, they can pay $100 to get out of the jail.
If a player is in jail, they cannot collect rent or affected by event.

## Properties
When a player's piece land on an unowned propety space, they can choose to buy the propety for its listed price. If the propety is owned and not mortgaged, they will pay the owner a given rent. When a player own all propeties of a color group without mortgaging any of them, the rent of all propeties belong to that color group is doubled.
If the player own the propety they land on and all other propeties of the color group without mortgaging any of them, they can choose to develop it by building a house on it for a listed price. Each house built will increase the rent of the propety. If 4 houses have already been built on the propety, the player can remove all houses and build a hotel instead. A propeties with a hotel can no longer be developed.
No house can be built on non-city propeties, but they have other trait.

## Mortgaging
When a player have negative value of money held, they need to mortgage their propeties to the bank until the value is positive again. The player gains 50% of the listed price of the propety and all houses/hotel on it. Player landing on a mortgage propety will not be collected of rent or develop it. At the start of the turn before rolling the dice, a player can choose to redeem any of their mortgaged propeties with the mortgage price plus 10% of the listed price.

# Feature


# Coding Elements Implementation
