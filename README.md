# ENGG1340 Game Project
## Name of the game: Minesweeper
## Proposal

Group nember: Yiu Ka Chun, Oh Seungwoo

Introduction: We have made a classical game called Minesweeper using C++. 

Game Rules: The rule of the game is finding all the mines without detonating by using the number on a block which shows the number of mines adjacent to it. We shall refer to some websites detailing the game instruction, such as https://www.instructables.com/How-to-play-minesweeper/.

Features: Depending on the difficulty, there will be more mines in a given field. We offered three difficulty level: easy, medium, and hard. Exposing mines to the player as a random event has been implemented. Ranking of top 10 players based on their scores is created. Player can check the ranking in the game.

Code requirements:
1. Generation of random game sets or events: Mines are randomly assigned in the field.
2. Data structures for storing game status: We used dynamic array to store the mines and numbers in the field. Vector is also used to store the ranking of top 10 players so that only 10 records are stored.
3. Dynamic memory management: There will be dynamic 2D arrays built using pointers. Resizable vector as a template in STL was also used.
4. File input/output (e.g., for loading/saving game status): The performance of player is recognised by how much time he/she used to win the game. The faster the player wins, the higher score he/she can obtain. Players will be asked for their names and ranking will be created in descending order of score. This ranking will then be saved to a file so that the records won't be erased when players quit the game.
5. Program codes in multiple files: The game was divided into several parts to ensure scalability and easier debugging. We divided the program into several parts, i.e. gameplay, instruction, and rank programs. They are compiled together to create an executable file game.

Compilation and execution instructions: Using the bash shell, input 'make game' in the game file directory. Optional input of 'make clean' can remove intermediate object files. Then input './game' to load the game executable.
