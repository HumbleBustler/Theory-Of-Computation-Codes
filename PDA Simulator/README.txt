A computer program to simulate Push-down Automata.

ASSUMPTIONS and DIRECTIONS:
1. Path is relative to directory in which the 'PDA Simulator.py' resides.
2. PDA is only effective to extent to the clarity of transition rules specified in files.
3. Four files are given as examples :
	(a) 0n-1-2n -> Transitions for [0^(n)1^(2n)]
	(b) 0n1n    -> Transitions for [0^(n)1^(n) ]
	(c) n0n1    -> Transitions for [number of 1's = number of 0's]
	(d) wcwR    -> string (w) followed by 'c' followed by string(reverse(w)).
4. Refer to Screenshots of examples for more clarity.
5. IO handles opening the transition rules file, reading rules and parsing them 
   to appropriate variables.