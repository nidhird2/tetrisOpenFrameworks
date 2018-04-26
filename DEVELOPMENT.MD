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
