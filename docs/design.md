# __Design Overview__


## __Overview:__
This project is a Chess CLI and Engine that allows game PGN creation, move validation
and eventually position evaluation.


## __Architecture:__
The project will be made out of multiple components.

### __Command Execution:__
Using a Command Line design pattern the project will execute commands by first:<br>
parsing an input, then creating the appropriate `Command object`<br> and finally the command object
will be passed to an `Invoker object` which will then execute the command.<br><br>
In order to manage the changing state of the application a `Context object` will include all the state variables<br>
of the application and will be passed to the invoker together with the command.<br>
Each `Command` object will inherit and implement the `Execute(args)` method.

### __Game Representation:__
The application will allow for the creation of a `Game instance` Which will be used 
for creating PGN files and FEN strings, evalutaing positions and editings PGNs.

In order to represent a game there will be a `Position object` which holds the board representation of a singular position
using a `Board object` which will be able to determine the validity of moves.
a full game will comprise of a `Game object` which is an object that holds multiple positions.


### __Position Evaluation:__
Lastly the application will be capable of evaluating a position in a game using a Deep neural network <br>
trained using Reinforcement learning techniques.
Additionally the application will support representation and evaluation of Chess variations like<br>
Duck Chess, Crazyhouse, Horde, 3 Check and Atomic


## __Command List__

<u>__General Commands:__</u>
* `Help` - Get list of commands with explaination
* `Clear`-  clears console
* `Quit` - Close application<br>

<u>__Commands Out of Game:__</u>
* `Load` [PGN directory] - Loads an existing chess game and enters game state
* `Create` [Starting position FEN string | none = Default starting position] - Creates a new game instance and enters game state
* `Evaluate` [FEN string | PGN directory] - Calculates the evaluation of the current position
* `Analyze` [FEN string | PGN directory] (`-s` = switch turn, `-n` = number of moves to show, `-r` = show moves from worst to best) - Evaluates possible continuations<br>

<u>__Commands In Game State:__</u>
* `Move` [move notation] - Attempts to make a move on the current game
* `Show` (`-a` = all positions) - Prints Current position in visual form
* `Fen` (`-a` = all positions) - Shows Fen string of position
* `History` - Shows all moves that have been played in chess notation
* `Position` [index of position in current game] - Goes to a specific position in the game
* `Truncate` - Removes all positions ahead of current position
* `Save` [directory | none = saves to current directory] - Saves game to PGN file
* `Exit` [directory | none = saves to current directory] (`-n` | `--no-save` = won't save) - Leaves Game state and saves the game
* `Evaluate` - Calculates the evaluation of the current position
* `Analyze` (`-s` = switch turn, `-n` = number of moves to show, `-r` = show moves from worst to best) - Evaluates possible continuations

