# **2048 Game Solver**


Note: I built this entirely from scratch for my Data Structure and Algorithms assignment. No AI tools were used to code this. It's just me, way too much coffee, and a lot of trial and error. I ended up getting a 95% on the face to face demonstration of this project.

This is a fully functional 2048 game built for the terminal.

This project uses Monte Carlo simulations, deterministic recursive tree searches, and heavily tuned heuristics to calculate the best moves.


The Progression 
1. The Board & Human Player: 
   Firstly the board rendering base code was already provided to us. I still did some modifications on it by introducing grid pointers and writing the merge logic. Once the Human Player was manually moving tiles and working, my base code was done.


2. The Random Player: 
   The baseline. It just throws a random number generator at the wall and picks left, right, up, or down. It's very bad at the game, but it proved the simulation loop and terminal rendering didn't crash.


3. Best-First Player & Smart Player (The Greedy players): 
   Next, I wanted some actual logic. Best-First looks exactly one step ahead. Smart Player uses hardcoded nested loops to look two steps ahead.

- - Both scored the board using a basic heuristic: rewarding empty cells and tiles that got larger in a specific direction. They scored higher than random, but they suffered from the exact same fatal flaw, they were way too greedy. They would chase an immediate score bump, completely ruin the board structure, and trap themselves in a corner.

4. The "Zigzag" Failure (An important lesson for me): 
   Before I hit on the final solutions, I tried to be clever. If you watch competitive 2048 players, they build this perfect descending "snake" or zigzag pattern. So, I tried to force the AI to do that. I built a weighted vector and multiplied it against the corresponding cells on the board to artificially weight a zigzag shape.

- - It was a complete disaster. The bot focused so much on perfectly ordering the tiles that it ignored actually winning the game. It would literally choose a move that killed it just to keep the snake intact for one more turn. I scrapped it.

5. Monte Carlo Player : 
   I realized hardcoding rigid rules (like the zigzag) was a trap. So I let statistics take the wheel (and it was also a requirement for the assignment haha)

- - Instead of guessing the best move, the Monte Carlo player runs 50 random game simulations to a depth of 30 steps for every single possible valid move. It averages the scores from those random expansions and just picks the highest expected value.

- - Why 50 sims and 30 depth? I messed around with these numbers a lot. Anything higher than 50/30 caused massive computational bottlenecks, the terminal would just hang forever between turns. Anything lower, and the sample size was too small to give good advice.

- - Watching this thing simulate thousands of futures to pick the optimal path and win about half the time was incredible.

6. Best Player (**The assignment saver!!!**): 
   Even though Monte Carlo was cool, my custom Task 6 "Best Player" actually wins the most games. I ditched the messy nested loops from the Smart Player and implemented a clean recursive lookahead.

Why a depth of 5? I capped the recursive lookahead at lookahead(tempboard, 5). Depth 4 was too blind to avoid traps, but depth 6 meant the recursion tree exploded, my laptop sounded like a jet engine taking off, and it took way too long to compute a single turn. 5 was the perfect sweet spot between intelligence and performance.

The Heuristics (Why it actually wins): The scoring logic took forever to tune. Originally, I had the heuristic heavily prioritizing the 1024 tile. The problem? It got so obsessed with keeping that 1024 safe that it would actively avoid merging it into a 2048. I had to decrease the priority of intermediate tiles.

Now, the golden rule is anchoring: the absolute highest tile must stay in one of the four corners. If a move forces the max tile out of the corner, I nuke the score. If it stays in the corner, I juice the score massively (e.g., if the max is 2048 and in a corner, it gets multiplied by 5000). I also slapped a massive reward for empty cells (board.countEmptyCells() * 500) to force the bot to keep the board breathing and prevent clustering.  
+2

### Tech Stack

Just standard C++ and CMake. No external libraries

Built and tested locally.
