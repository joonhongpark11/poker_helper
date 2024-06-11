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


<details>
<summary><h2>Deveopment Record</h2></summary>
* 2024/06/11: Finished basic functions for hand detection. Made testing files using googleTest.
</details>