# ENGG1340 Game Project
## Name of the game: Minesweeper
## Proposal

Group nember: Yiu Ka Chun, Oh Seungwoo

Introduction: We are going to make a classical game called Minesweeper using C++. 

Game Rules: The rule of the game is finding all the mines without detonating by using the number on a block which shows the number of mines adjacent to it. We shall refer to some websites detailing the game instruction, such as https://www.instructables.com/How-to-play-minesweeper/.

Features: Depending on the difficulty, there will be more mines in a given field. We plan to offer three difficulty level: easy, medium, and hard. Flags are provided to players to indicate identified possible mines. Random events, including exposing mines to the player, are planned to be implemented.

Code requirements:
1. Generation of random game sets or events: We will randomly assign mines in the field.
2. Data structures for storing game status: We will use 2D-array to store the mines and numbers in the field.
3. Dynamic memory management: There will be a dynamically allocated variable which will be used for setting the number of mines in a field.
4. File input/output (e.g., for loading/saving game status): The performance of player is recognised by how much time he/she played to win the game. The faster the player wins, the higher score he/she can obtain. Players will be asked for their names and ranking will be created in descending order. This ranking will then be saved to a file so that the records won't be erased when players quit the game.
5. Program codes in multiple files: The game would be divided into several parts to ensure scalability and easier debugging.
