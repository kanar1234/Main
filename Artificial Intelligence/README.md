This directory contains code for the pacman AI
All projects are done in python.

Here is a short descriptions of each project.

Note - Pacman functions and graphics are given.

Review. Calculates cost of fruits purchased from shops and returns the best shop to buy fruits at.
-Note: The pacman models and boards are given.

Basic Search Agent - Finds the shortest path from Pacman to a goal.

Multi Search Agent - A reactive A.I. that collects all food on the board while avoiding ghosts using:
  - Reflex agent: Calculates best action during each step given the board state
  - Minimax agent: Calculates best action by determining future board states
  - Minimax with Alpha-Beta Pruning: Same as minimax but removes options that are not possible to improve time complexity

Q Learning Agent - A reinforcement learning A.I. that chooses the action with the highest chance of a good outcome using.
  - Q Learning: Choosing action based on its optimal q value which is updated through every game

Optimized Learning Agent - A pacman group project where we face against other groups where both sides have two pacmans and 
crossing to the opponents side of the map turns you into a ghost that can eat food.
  - In this project, my team was able to make one pacman offensive while the other defended using an improved reflex agent
