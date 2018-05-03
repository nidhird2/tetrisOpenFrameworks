# Tetris

This is a tetris game that uses openframeworks. Tetris is a game in which blocks fall down and are moved into place on the gameboard by the user. If a gameboard contains a full line of blocks, the row will be erased, and all the rows will fall down by the amount of rows erased. The score is increased based on the amount of lines cleared at a time. Over time, the speed at which the block fall down will increase. The game ends when there is no room for a new block to spawn. A typical game can last anywhere from 2-5 minutes (for the average user). This game also keeps track of high scores by reading/writing from/to a text file (optional, not necessary).

# How to Run

This is an openframeworks applications, meaning that openframeworks files will need to downloaded. If you have not already done so, download it here: http://openframeworks.cc/download/.
Fork this repository into the openframeoworks folder, under the directory apps/myApps. 
Then go to the project generator program (inside project generator directory) under the openframeworks folder. Choose a path and then run.
Make sure ot include all of my bin/data files under bin/data. You can choose to keep my sounds or pick your own (but keep the file names the same). You can also choose to reset highscores.txt by replacing all five numbers with a zero.
When you run the generated project, you should be on a welcome to tetris screen (with music playing in the background).


# Resources 

I got background music from: https://www.youtube.com/watch?v=E8FQBjVlERk.
I got sound effects (tone1.wav and powerUpSound.wav from: http://kenney.nl/assets

Code Inspo:
For timing my project (forcing the block to move down every ___ milliseconds) see: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Tetris.cpp
specfically, look at thread.sleep();
