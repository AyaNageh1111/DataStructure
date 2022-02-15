# DataStructure

## simulation program for a battle between a castle and enemies. The app simulates the battle between them then calculates some statistics from this simulation.

### Input File
The system will receive the information about a list of enemies as input from an
input file. This list represents the scenario to be simulated. For each enemy the system will receive
the following information:
- Arrival Time stamp (Enemy Arrival Time): When the enemy arrives.
- Health: The starting health of the enemy.
- Power: The power of the enemy.
- Reload Period: Time for an enemy to reload its weapon.
- Speed: number of meters an enemy can move in a single time step.
- Type: fighter, freezer or healer

### Simulation Approach & Assumptions

 The programe will use incremental time simulation. The programe will divide the time into discrete time steps of 1 time 
 unit each and simulate the changes in the system in each time step.

### Game Rules
- Each enemy has its own speed and its own fire power.
- All enemies start at 60 meters distance from the castle.
- In general, an enemy moves at its original speed each time step.
But an enemy with (health < 0.5 its original health) moves at its half original speed.
- The minimum possible distance for any enemy to approach to the castle is 2 meters.
- Enemies can move at their reload period but cannot act. (cannot fire nor heal)
- Movement Patterns: By default all enemies move in the forward direction (approaching
castle) but only healers can move backward. When a healer reaches end of forward
direction, it starts moving backward until it reaches end of backward direction where it
turns back and moves forward again and so on.
- Healer can heal only enemies that are at most 2 meters ahead in his moving direction.
- Healer cannot heal killed enemies. Healer cannot heal frosted enemies.
- A castle can attack any enemy type.
- Both castle and enemies can attack each other at the same time step.
- A castle can attack at most N enemies at each time step. (N is loaded from input file).
- A castle can either fire bullets or throw ice to freeze an active enemy.
- At random time steps the castle throws ice instead of bullets. The percentage of ice fire
should be around 20% of all castle fires.
-  If Castle kills a healer within a distance of 5 meters from the castle, it uses healer's
tools to recover its health by a percentage of 3%.
- If an active enemy is hit by castle ice, it gets frosted for some time steps until ice melts
(See formulas section below).
- A frosted enemy is affected by castle fire but is not affected by castle ice.
- A frosted castle cannot attack enemies.
- A frosted castle is affected by fighter attacks only. Freezer enemy has no effect on it.
- The game is “win” if all enemies are killed. The game is “loss” if the castle is destroyed.
Otherwise, the game is "drawn".


### Program Interface

The program can run in one of three modes: interactive, step-by-step or silent mode. When the
program runs, it should ask the user to select the program mode.
