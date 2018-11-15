# Sudoku-Solver

Sudoku is a well known number game. The attempt of this project is to view it as a <a href="https://en.wikipedia.org/wiki/Constraint_satisfaction_problem">
Constraint satisfaction problem</a> which leads to pruning from a large set of possible values at every state based on the imposed
contraints at that state. 

The project explores three approaches of solving the problem:
<ul>
<li> Backtracking with brute force</li>
<li> Arc consistency</li>
<li> Forward checking</li>
</ul>

The project also explores the following variable selection heuristic approaches
<ul>
<li> Minimum Remaining Values(MRV)</li>
<li> Maximum Degree(MD)</li>
</ul>

The project explores following value selection heuristic
<ul>
<li> Least Constraining Value(LCV)</li>
<li> Probabilistic Selection</li>
</ul>


***************************************** 
SUDOKU : A CONSTRAINT SATISFACTION PROBLEM
*****************************************

- Project codebase contains different cpp files for different algorithms. 
- We will be considering only MRV+FC+AC as we found it to be a better choice.

-----------------------
Steps to run program
-----------------------
1. Go to codebase folder
2. make clean
3. make
4. ./mrv_fc_ac.o
5. Copy input to terminal


------------
Input Format
------------
- Give command line input in following format

1st line - Number of input sequences
followed by 'n' sequence of 81 comma separated interers ranging [0,9], encoding the initial board position, left-to-right and top-down, with 0 for empty squares; output should be a sequence of numbers ranging [1,9].
(Note - make sure new line character after last entry in last sequence)


------------
Sample Input
------------
2
0,6,4,0,0,3,8,5,1,2,0,0,0,0,0,9,6,0,0,0,5,8,0,0,0,0,0,0,2,0,0,4,1,0,9,0,0,3,6,0,5,0,1,4,0,0,1,0,2,6,0,0,3,0,0,0,0,0,0,4,2,0,0,0,5,8,0,0,0,0,0,9,6,4,2,1,0,0,5,8,0
7,2,0,5,0,0,0,0,6,0,9,5,1,6,0,0,0,0,0,0,0,7,0,0,9,0,4,2,1,0,9,0,0,0,0,3,0,0,9,0,0,0,4,0,0,6,0,0,0,0,4,0,9,1,3,0,2,0,0,6,0,0,0,0,0,0,0,5,3,6,2,0,9,0,0,0,0,1,0,4,5
