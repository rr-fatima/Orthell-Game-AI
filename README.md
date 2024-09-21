# Reversi Game AI

Reversi is a strategy game, also commonly known as Othello.

### Game Setup
Reversi is played on a board that has dimensions n × n, where n is even and ranges from 4 to 26. The game uses tiles that are white on one side and black on the other (they can be “flipped” over to change their color). One player plays white, while the other player plays black.

### Gameplay
A “turn” consists of a player laying a tile of his/her own color on a candidate empty board position, subject to the following two rules:
1. There must be a continuous straight line of tile(s) of the opponent’s color in at least one of the eight directions from the candidate empty position (North, South, East, West, and diagonals).
2. In the position immediately following the continuous straight line mentioned in #1 above, a tile of the player’s color must already be placed.

After playing a tile at a position that meets the criteria above, all lines of the opponent’s tiles that meet the criteria are flipped to the player’s color. The turns alternate between players unless one player has no available move. In that case, the only player with an available move continues to make moves until a move becomes available for the opponent. At this point, the opponent is allowed to take a turn, and the alternating turns between players resume.

The game ends when either:
1. The entire board is full, or
2. Neither player has an available move.

The winner of the game is the player with more pieces on the board.

---

# How the Program Works

The program first asks the user for the board dimensions. Then, it asks if the computer is to be the Black or White player. In this program, the Black player always gets the first move. If the computer is black, it makes the first move; otherwise, the program prompts the human player to make the first move. The board is printed after every move.

Once the first move is made, the turns proceed as described above, alternating between Black and White unless one of the players has no move to make. In that case, the program prints a message “W player has no valid move” (for the case of the White player) and prompts the Black player for another move. After each turn, the program prints the board and checks whether the game has been won or if there is a draw. If the game is over (i.e., a win or a draw), a message is printed, and the program terminates. The specific messages to print are: “W player wins,” “B player wins,” or “Draw!” If the human player makes an illegal move, the program detects this, prints an error message, and ends the game, declaring the winner.

---

# Algorithms Used by the Computer to Make Its Move

The method for the computer to make a move is as follows:

1. **Evaluate All Possible Moves**: The computer evaluates each potential move by considering all empty squares on the board.
2. **Simulate Each Move and Apply Minimax**: For each candidate position, the computer simulates the move on a temporary board and uses the Minimax algorithm to recursively evaluate the resulting board state up to a fixed depth. This involves alternating between maximizing the computer's score and minimizing the opponent's score for subsequent moves.
3. **Calculate the Evaluation Score**: The evaluation score for each simulated board state is calculated based on factors such as mobility (number of valid moves available), control of ideal positions (favoring center and edge tiles), and the number of pieces owned by each player.
4. **Track the Best Move**: While calculating the evaluation scores, the computer keeps track of the highest score encountered, recording both the score and the corresponding position.
5. **Choose the Move with the Highest Score**: After evaluating all possible moves using the Minimax algorithm, the computer selects the move corresponding to the highest evaluation score. This position is deemed the best move because it maximizes the strategic advantage according to the evaluation criteria.

