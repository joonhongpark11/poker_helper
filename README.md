# poker_helper

This program is a poker helper designed to help people playing poker using statistical methods. 

# Testing
I made testing using googleTest. You can see the details about googleTest [here](https://github.com/google/googletest)<br>
You need to do several steps for using google test.<br>
- clone googleTest.<br>
1. go to the main directory. `cd /path/to/poker_helper`.<br>
2. clone googletest `git clone https://github.com/google/googletest.git`
- create build directory `mkdir build`
- go to the build directory `cd build`
- Run CMake to generate Makefiles:<br>
`cmake ..`
- Build the project<br>
`make`
- Run the tests<br>
`./test`


Go to build. Type make.<br>
./test --> testing<br>
./main --> main


<details>
<summary>Deveopment Record</summary>
* 2024/06/11: Finished basic functions for hand detection. Made testing files using googleTest.
</details>