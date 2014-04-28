(* ::Package:: *)

BeginPackage["Collatz`"]

(* by defining a usage outside the private block
 * we make sure that these symbols are available to public use *)
Collatz::usage = 
	"Collatz[n] givs a list of the iterates in the 3n+1 problem starting from n. The conjuecture is that this sequence always terminates"

Begin["`Private`"]

Collatz[1] := {1}

Collatz[n_Integer] := Prepend[Collatz[3 n + 1], n] /; OddQ[n] && n>0
Collatz[n_Integer] := Prepend[Collatz[n/2], n] /; EvenQ[n] && n > 0

End[ ]

EndPackage[ ]



