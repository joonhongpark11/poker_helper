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

- 2024/06/15: Finished making functions for drawing hole cards for each player. Surprised by the quality of object orientied programming.

- 2024/06/16: Working on choosing the player's action. I need to study more about actions like raise, call, bet.

- 2024/06/17: realized that player's actions are complicated and very case dependent, so I need to divide into a lot of cases. I am currently finalizing the poker game, and will start fixing the actions. 

- 2024/06/18: Finished making the frame of the program. I need to edit the details from now. It seems like determining the hand is also wrong. I need to fix it.

- 2024/06/19: I tested several things, but I got a lot of errors. I think I need to check everything from the beginning. I started rewriting the test cases and fixing functions.

- 2024/06/20: Editing the functions and testing.

- 2024/06/22: made a few more important functions. Next job is running these functions accordingly and make a game cycle work.

- 2024/06/23: Organized code a bit.

- 2024/06/24: Keep organizing the codes. Changed github account!

</details>


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