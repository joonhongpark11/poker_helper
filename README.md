# poker_helper

This program is a poker helper designed to help people playing poker using statistical methods. 

# Testing
I made testing using googleTest. You can see the details about googleTest [here](https://github.com/google/googletest)<br>
You need to do several steps for using google test.<br>
1. clone googleTest.<br>
- go to the main directory. `cd /path/to/poker_helper`.
- clone googletest `git clone https://github.com/google/googletest.git`
2. make test executable<br>
- create build directory `mkdir build`
- go to the build directory `cd build`
- Run CMake to generate Makefiles: `cmake ..`
- Build the project:`make`
3. Use executable<br>
- go to build directory `cd build`
- `./test` --> testing
- `./main` --> main
4. Retest
- You don't have to re-clone googleTest or make build folder.
- After editing the test, please do the following:
- Do `make` in `builder`
- Run `./test`


<details>
<summary><h2>Development Record</h2></summary>

- 2024/06/11: Finished basic functions for hand detection. Made testing files using googleTest. Started working on game.cpp.

- 2024/06/12: Realized that I was using class in a wrong way. Trying to fix all the functions.

- 2024/06/13: Fixed hand detection functions and testing. I used completeHand() for testing and each boolean function, which means twice, and it causes duplicate cards issue.

- 2024/06/14: Started making the main function for the game. I need to deal with coins from now.

</details>

# To-do List
1. I need to make a game object and it should have fields: total_betting_amount, cardsOnField. Also Player needs field: bettingAmount which tracks how much the player is betting on each game.


- poker step

1. choose player number 
2. make players
3. draw deck(52)
4. run a function that picks one cards for everyone for the order. 
Highest number is the winner. If draw, check the suit. Space -> Heart -> diamonds -> clubs
Dealer will be placed left side of the winner. 
every game, the dealer 


- each game
0. small blind and big blind
1. pre-flop(first betting): dealt two cards
- betting from after big blind. (need to check the direction)
2. flop(second betting): three community cards are dealt. 
- betting starts from small blind(left of the dealer)
3. turn(third betting): fourth card is dealt
4. river(fourth betting): final card is dealt
5. showdown: check who wins