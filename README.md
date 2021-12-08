# finalproject

Game.cpp and Ai.cpp are the ones I have to submit, and here is my logic I've written down:
I think a good heuristic would be to first determine if it is possible to "save" the angriest person. 
Like if for example none of the 3 elevators can get to a person before they explode, then you would give up on that person. 
Otherwise we do the angriest saveable people first, taking everyone else going the same direction along the way 
And to implement it, if elevator at floor i is going to floor j (i<j) and a person is at floor k (k<i) 
then the elevator has to go to j in j-i ticks, then down to k in j-k ticks, for a total of 2j-i-k ticks 
& similar reasoning for other cases. I've also spoken with someone who's completed the proj and they were 
basically like their barebones project somehow got full credit so you don't need a great AI for full pts, 
so it doesn't have to be in depth as I stated above apparently.
