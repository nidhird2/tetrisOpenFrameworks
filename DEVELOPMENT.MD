# Development

4/18 - Started with adding tetromino and gameboard class. 

       Chose to hardcode the possible orientations for each tetromino so that no rotate method is necessary.
       Wrote method to draw tetromino given a location, constructor randomly selects a shape.
       
4/25 - Changed tetromino data so shape is held in 4x4 bool array.

       Created colors array that is referred upon when drawing a tetromino.
       Added keyboard inputs and added auto-drop for pieces.
       Split checking collision into 4 methods: checking left, right, bottom, and checking overlap.
       
TO-DO:
       Checking overlap still needs fixing.
       Need to fix finding full lines/clearing full lines methods.
       Also need to move starting tetromino higher on the board.
       Need to draw boundary for the gameboard.
       
4/27 - border, spacebar, fixing rotations

       Added a border for the gameboard for the screen (by reccomendation). Same width as the grid/tetrominos.
       Also added spacebar functionality for a "hard drop". 
       Also changed rotating so that the pieces rotate counter-clockwise.


4/28 - Added method(s) for clearing full lines. Orginally, this was going to be split so that one method would return for a full line or        -1, and another ran the method and cleared lines when int i > -1. However, this kept going into an infinite loop so I wrote a           method to see if a line (at a given index) is full. This is less efficient, but still works.
      Changed tetromino data to be stored in 5x5 arrays (to account for rotating with a hinge in the middle).

4/29 - Wrote code for exiting the game.
       Changed the way the border is printed (border weight and scale can now be specified in game.h to alter how thick/thin the border looks.
       Added gameInfo to the screen, current score, lines cleared, and upcoming piece.
       Added methods in tetromino.cpp and game.cpp for drawing the "projection" of the current piece (by reccomendation) for easier gameplay. It was either this or draw a grid in the background - I wasn't entirely sure that just a grid would help enough, so I did the projection. A grid in the background might be a future addition.
       
       
4/30 - Added pause, restart, and exit buttons. Buttons still need labels. Also added seperate screens for when the game is paused and the game is over. These screens are still bare and need more work though.

5/1 - Added labels for buttons and realized that I was repeating a lot of code for buttons (seeing as there is at least one of the buttons in each of the screens). So, drawing each button was split into a seperate helper method. 
      Added a help button and screen (by reccomendation). While most people know how to play tetris, it's not always the case, and
      controls can sometimes vary from game-to-game so a directions screen was necessarry.

5/2- Used ofSoundPlayer within OF for background music and sounds. There is a sound for when a piece is locked into place and added to the game board. There is another sound for every time the game speeds up.
     Added a trueTypeFont (verdana) to make game look nicer. Replaced all uses of ofDrawBitMapScreen() with verdana. This also allowed
     me to control the font size.
     Wrote a beginning screen. This way, when the application is launched, the user can choose when the gameplay starts (as opposed
     to straight-away). This was also a reccomendation.
     Decided to keep track of top 5 scores by reading and writing to a text file.
     Added comments.
