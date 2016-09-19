##Pablo Eckardt.

##Conway's game of life.

This is my interpretation of conway's game of life. 
Its a small simple population simulator that is a very popular coding exercise.

This was my first **SDL project** to learn how to use the library.

Typing "conway's game of life" on google will render a live and discrete example of the game
to the right of your screen (works in firefox and chrome).

The rules are well described in Wikipedia:

- Any live cell with fewer than two live neighbours dies, as if caused by under-population.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by over-population.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

This is how my implementation looks like:

shortly after executing:
![alt tag](https://github.com/PabloEckardt/SDLConwaysGameOfLife/blob/master/image2.png)

Long after execution:
![alt tag](https://github.com/PabloEckardt/SDLConwaysGameOfLife/blob/master/screen%201.png)	




