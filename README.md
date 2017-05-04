# Qwixx 
- - -
This is originally a board game which I am required to implement using C++ for my Game Development Assginment, the rules for the game can be found here

[Qwixx Rules](http://www.nsv.de/spielregeln/qwixx-classic-english.pdf)

The features in my Qwixx game are : 
+ Support 2 - 5 Players
+ Choice between AI Players and Human Players
+ AI is pretty good and has been able to reach a score of 102
+ Nicely formatted CLI

AI Process (Single Move): 
+ Determine if the white-white dice value can be placed closer to the start of any row
+ Determine if the shortest distance between value and last cross is within a given limit
+ Otherwise, pass/fail turn

AI Process (Double Move):
+ Do Single Move (if failed, store in a variable)
+ Determine the smallest value white-colour combo and attempt to place it
+ Determine the largest value white-colour combo and attempt to place it
+ BruteForce : Try all combinations of white-colour combo and attempt to place it
+ If Single Move was failed/passed, incremenet the fails on the player