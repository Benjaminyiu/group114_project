# ENGG1340 Game Project
## Name of the game: Minesweeper
## Proposal

Group nember: Yiu Ka Chun, Oh Seungwoo

Introduction: We have made a classical game called Minesweeper using C++. 

Concept of this game: Puzzle style which requires guessing and inferring location of mines.

Motivation (reason for choosing this game): Minesweeper is an almost fully randomized game as the locations of bombs are very likely to be different for each round. Thus, it is easier to meet the code requirement which is "random generation of events".

Game Rules: The rule of the game is finding all the mines without detonating by using the number on a block which shows the number of mines adjacent to it. We shall refer to some websites detailing the game instruction, such as https://www.instructables.com/How-to-play-minesweeper/. We made the following assumption for inputting coordinates:
* the player must input two values for x and y to correctly play the game in order to convert it into (x,y) coordinate system. Only integers are inputted.
* enter only one word for name input after winning the game.

Features: Depending on the difficulty, there will be more mines in a given field. The number of mines in each game will be determined randomly and different in each game. We offered three difficulty level: easy, medium, and hard. Exposing mines to the player as a random event has been implemented. If player wins the game, he/she will receive a score. Ranking of top 10 players based on their scores is created. Player can check the ranking in the game.

Code requirements:
1. Generation of random game sets or events: Mines are randomly assigned in the field. Number of mines in the board is also random. Flags will denote the location of a mine about 1/5 of probability after each input of coordinates.
2. Data structures for storing game status: We used dynamic array to store the mines and numbers in the field. Vector is also used to store the ranking of top 10 players so that only 10 records are stored.
3. Dynamic memory management: There was dynamic 2D arrays built using pointers. Resizable vector as a template in STL was also used to store the ranking.
4. File input/output (e.g., for loading/saving game status): The performance of player is recognised by how much time he/she used to win the game. The faster the player wins, the higher score he/she can obtain. Players will be asked for their names and ranking will be created in descending order of score. This ranking will then be saved to a file so that the records won't be erased when players quit the game.
5. Program codes in multiple files: The game was divided into several parts to ensure scalability and easier debugging. We divided the program into several parts, i.e. gameplay, instruction, and rank programs. They are compiled together to create an executable file 'game'.

Compilation and execution instructions: Using the bash shell, input 'make game' in the game file directory. Optional input of 'make clean' can remove intermediate object files. Then input './game' to load the game executable.

P.S. To facilitate testing, a test file named Cheatboard.txt is generated showing the locations of mines represented by 0. Commenting out lines 219, 228, 234, 237 and 239 in main_page.cpp can remove the generation of Cheatboard.txt.

Testing of program and generation of sample input/output files are done in academy11 server. 6 sample input/output files are attached. However, since the output of each gameplay may vary and rely on random factors, it may not be possible to obtain the same output for a given input every time.
