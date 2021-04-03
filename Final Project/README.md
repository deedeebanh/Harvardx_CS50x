# CHECKERS
#### Video Demo:  <https://youtu.be/TIbO9ZBzb-Q>
#### Description:
This is the game draughts or checkers. The game was written in Python 3 and the GUI was created using the Pygame library. The code was written using the pygame framework to create the checker board, checker pieces, and the checker movement updates on the display. Free icons were imported from @flaticon (www.flaticon.com). The code is original and was written for self-education purposes, do not use for commercial use.

I chose checkers because even in its simplicity, there's elegance to the way the game is played. I have always wanted to make a game on my own, and choosing checkers as my first game code has been a challenging and rewarding experience. I first have to learn python, and then learn pygame to create the GUI. It was quite frustrated at time to implement the algorithm (I know the logic works), but quite hard to understand the movement in the 2-dimensional space of pixels. After many iterations, I have come to what I think is the most elegant way to display the logic at the moment.

At first I was using the pixel locations to move the pieces; however, it becomes very messy very quickly. But if I allocate the positioning in just 8x8 chessboard position, and convert the event position (the moving piece) to the board position by knowing that each square is equalled to the number of pixel divided by 8, the problem becomes clearer and easier to solve. 

The first part of approaching to code this game in pygame is the set up. I chose 600x600pixel for the display as it seems to be a good size for a 13" laptop (using mine as an example). I have a couple of functions in this game: drawCheckersBoard, drawCheckersPieces, isLegalPosition, isVacantPosition, isLegalMove.

drawCheckersBoard and drawCheckersPieces are self-explanatory. They are the code to update the display for both the background and the checkers pieces themselves. The checker pieces can be either pawn or king, and the icons are updated based on those identifiers.

isLegalPosition describes the dark squares. The pawns or kings can only move to an adjacent dark squares. If the player drag the pieces to a light square, the code will reject and place the piece back to its original position.

isVacantPosition describes where the piece is dragged to. If the square is already occupied, i.e. not vacant, then the piece will go back to its original position; otherwise, if vacant, the player is allowed to drag the checkers piece to that square.

isLegalMove is a larger logic piece where it houses the logic for both player 1 and player 2 and whether the piece is a pawn or a king. First the movement has to be within bound (or within the 8x8 checkerboard), then the algorithm checks if the clicked on checkers piece is from player1 or player2 and if it is a pawn or a king. If a pawn, you can only move one square or two squares forwards; if a king, you can move one square or two square forwards and backwards. If moving two squares forwards, there must be an enemy checker's piece in the immediate one square in between (I called it midWay). If there's an enemy piece in between and the moving-to square is vacant, then the moving piece is allowed to capture the enemy. By capturing, I moved the enemy piece's positioning to out of the display. Since the display is 600x600, I moved the enemy piece's positioning to a random location in 2000x2000 as I do not want to actually remove the piece from the list as it will shift all other positions in the same list.

Finally, in the main While loop is where the assembly lies. Using pygame event.pos, I know where the checkers pieces are dragged to in the pixel global positioning. I convert the pixel by dividing it by the square size and find out where it is located on the 8x8 checkerboard. If the mouse is not pressed anymore, the logic to check whether the position is legal, is vacant, and is allowed to move to are kicked in. If all is True, then update the checkers piece to that location, and capture some enemy on the way, if allowed, or move the piece back to its original position if not allowed.


To run this game, you must first install python 3 and pygame. The files included in this package are the icons with the extension *.png and the main runfile called main.py. If the software is installed properly, you can go to the command line, change the directory to the proper location where the files are located, and type "python main.py". This will bring the GUI up and you can start playing the game! 

Credit to pygame tutorial from @FreeCodeCamp (https://youtu.be/FfWpgLFMI7w), and pygame interface help from @Pygame (https://www.pygame.org) and @StackOverflow (https://stackoverflow.com). Thank you @CS50x for introducing me to programming and making this game possible.
