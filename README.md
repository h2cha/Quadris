# Quadris

## How to run
<code>
cd $path_to_Quadris/Quadris/source && <br>
make <br>
./quadris -startlevel 1<br>
</code>

## Command line options
See the command options below: <br>
-startlevel [N]: start the game with level N <br>
-scriptfile [filename]: play the game based on the instructions in the file <br>
-text: text only view <br>
-seed N: sets the random seed to N, 0 by default <br>
</code>

## How to play
right: moves the block 1 unit right <br>
left: moves the block 1 unit left <br>
down: moves the block 1 unit down <br>
clockwise: rotates the block clockwise <br>
counterclockwise: rotates the block counterclockwise <br>
drop: drops the block <br>
levelup: increments the level <br>
leveldown: decrements the level <br>

Autocomplete is implemented (e.g. ri or righ will be interpreted as right)


## Notes
Level down from 1 to 0 is not handled since it needs input from a file.

### Multiple command
-0 and 1 are permitted as a prefix <br>
-Works on right, left, down, clockwise, counterclockwise, levelup, and leveldown <br>

### Heavy blocks:
./quadris -startlevel 3 <br>
./quadris -startlevel 4 <br>
Down 1 for each block operating command except replacing command


### Scoring
./quadris -startlevel 1 <br>
I dr I 4ri dr L 8ri dr				→ 2 L1-blocks + 1 line at L1 = 12

levelup I dr I 4ri dr L 8ri dr			→ 2 L2-blocks + 1line at L2  = 27

I levelup dr I 4ri dr L 8ri dr			→ 1 L1-block + 1 L2-block + 1 line at L2 = 22

O dr O 2ri dr O 4ri dr O 6ri dr O 8ri dr
I dr I 4ri dr O 8ri dr I cl 10ri dr			→ 7 L1-blocks + 3 lines at L1 = 44

### Extra features examples
#### Level 4 1x1 block:
./quadris -startlevel 4 <br>
4dr dr

./quadris -startlevel 4 <br>
I dr I 4ri dr L 8ri dr 4dr dr



#### Sequence file <br>
T ri ri down left levelup cl cl co


#### Rename commands:
If new is existing command, the existing command has now no effect.

./quadris -startlevel 1 <br>
rename down up


