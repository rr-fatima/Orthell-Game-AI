# Orthell-Game-AI

It is an orthello game, also commonly known as reversi. 

<br>
Orthello is played on a board that has dimensions n × n, where n is even and ranges from 4 to 26. 
The game uses tiles that are white on one side, and black on the other side
(they can be “flipped” over to change their colour). One player plays white; the other player plays black. 

A “turn” consists of a player laying a tile of his/her own colour on a candidate empty board position,subject to the following two rules:
1. There must be a continuous straight line of tile(s) of the opponent’s colour in at least one of the eight directions from the candidate empty position (North, South, East, West, and diagonals).
2. In the position immediately following the continuous straight line mentioned in #1 above, a tile of the player’s colour must already be placed.

<br>
After playing a tile at a position that meets the criteria above, all of the lines of the opponent’s tiles that meet the criteria above are flipped to the player’s colour.The turns alternate between the players, unless one player has no available move, in which case the only player with an available move is allowed to continue to make moves until a move becomes available for the opponent. At this point, the opponent is allowed to take a turn and the alternating turns between the players resume. 

The game ends when either: (1) the entire board is full, or (2)
neither player has an available move. The winner of the game is the one with more pieces on the board.

# How-the-program-works

The program first ask the user for the board dimensions. Then, the program asks the user if the computer is to be the Black or White player. In this program the Black player always gets the first move. So, if the computer is black, then the computer makes the first move; otherwise, the program prompts the human player to make the first move. The board is printed after every move.

Once the first move is out of the way, the turns proceed as described above, alternating between Black and White unless one of the players has no move to make, which case the program prints a message “W player has no valid move.” (i.e. for the case of the White player) and prompt the Black player for another move. After each turn, the program prints the board, and detect whether the game has been won, or whether there is a draw. If the program detects the
game is over (i.e. a win or a draw), a message is printed and the program terminates. The specific messages to print are: “W player wins.”, “B player wins.” or “Draw!”. If the human player makes an illegal move, the program detects this, prints an error message, and ends the game, declaring the winner (with the corresponding message above).

# Algorithms-used-by-computer-to-make-its-move

The method for the computer to make a move is as follows:

Evaluate All Possible Moves: The computer evaluates each potential move it could make by considering all empty squares on the board.

Simulate Each Move and Apply Minimax: For each candidate position, the computer simulates the move on a temporary board and uses the Minimax algorithm to recursively evaluate the resulting board state up to a fixed depth. This involves alternating between maximizing the computer's score and minimizing the opponent's score for subsequent moves.

Calculate the Evaluation Score: The evaluation score for each simulated board state is calculated based on factors such as mobility (number of valid moves available), control of ideal positions (favoring center and edge tiles), and the number of pieces owned by each player.

Track the Best Move: While calculating the evaluation scores, the computer keeps track of the highest score encountered. It records both the score and the corresponding position.

Choose the Move with the Highest Score: After evaluating all possible moves using the Minimax algorithm, the computer selects the move corresponding to the highest evaluation score. This position is deemed the best move because it maximizes the strategic advantage according to the evaluation criteria.
