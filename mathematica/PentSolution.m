(* ::Package:: *)

BeginPackage["PentSolution`"]
(* ccs
 * contains all the details of the pent solution interms of the fiducial 
 * configurations and various useful helper functions  
 *)

PentSolutionsWList::usage = "A paried list of the config and the scalings for that config {\!\(\*SubscriptBox[\(\[Alpha]\), \(i\)]\), \!\(\*SubscriptBox[\(\[Beta]\), \(i\)]\), \!\(\*SubscriptBox[\(\[Gamma]\), \(i\)]\)} in terms of the triple spin products \!\(\*SubscriptBox[\(W\), \(i, j, k\)]\)"
PentSolutionsWList={{{5,4},{-(Subscript[W, 2,3,4]/Subscript[W, 1,2,3]),Subscript[W, 1,3,4]/Subscript[W, 1,2,3],-(Subscript[W, 1,2,4]/Subscript[W, 1,2,3])}},{{5,3},{Subscript[W, 2,3,4]/Subscript[W, 1,2,4],-(Subscript[W, 1,3,4]/Subscript[W, 1,2,4]),-(Subscript[W, 1,2,3]/Subscript[W, 1,2,4])}},{{5,2},{-(Subscript[W, 2,3,4]/Subscript[W, 1,3,4]),-(Subscript[W, 1,2,4]/Subscript[W, 1,3,4]),Subscript[W, 1,2,3]/Subscript[W, 1,3,4]}},{{5,1},{-(Subscript[W, 1,3,4]/Subscript[W, 2,3,4]),Subscript[W, 1,2,4]/Subscript[W, 2,3,4],-(Subscript[W, 1,2,3]/Subscript[W, 2,3,4])}},{{4,5},{-(Subscript[W, 2,3,5]/Subscript[W, 1,2,3]),Subscript[W, 1,3,5]/Subscript[W, 1,2,3],-(Subscript[W, 1,2,5]/Subscript[W, 1,2,3])}},{{4,3},{Subscript[W, 2,3,5]/Subscript[W, 1,2,5],-(Subscript[W, 1,3,5]/Subscript[W, 1,2,5]),-(Subscript[W, 1,2,3]/Subscript[W, 1,2,5])}},{{4,2},{-(Subscript[W, 2,3,5]/Subscript[W, 1,3,5]),-(Subscript[W, 1,2,5]/Subscript[W, 1,3,5]),Subscript[W, 1,2,3]/Subscript[W, 1,3,5]}},{{4,1},{-(Subscript[W, 1,3,5]/Subscript[W, 2,3,5]),Subscript[W, 1,2,5]/Subscript[W, 2,3,5],-(Subscript[W, 1,2,3]/Subscript[W, 2,3,5])}},{{3,5},{-(Subscript[W, 2,4,5]/Subscript[W, 1,2,4]),Subscript[W, 1,4,5]/Subscript[W, 1,2,4],-(Subscript[W, 1,2,5]/Subscript[W, 1,2,4])}},{{3,4},{Subscript[W, 2,4,5]/Subscript[W, 1,2,5],-(Subscript[W, 1,4,5]/Subscript[W, 1,2,5]),-(Subscript[W, 1,2,4]/Subscript[W, 1,2,5])}},{{3,2},{-(Subscript[W, 2,4,5]/Subscript[W, 1,4,5]),-(Subscript[W, 1,2,5]/Subscript[W, 1,4,5]),Subscript[W, 1,2,4]/Subscript[W, 1,4,5]}},{{3,1},{-(Subscript[W, 1,4,5]/Subscript[W, 2,4,5]),Subscript[W, 1,2,5]/Subscript[W, 2,4,5],-(Subscript[W, 1,2,4]/Subscript[W, 2,4,5])}},{{2,5},{-(Subscript[W, 3,4,5]/Subscript[W, 1,3,4]),Subscript[W, 1,4,5]/Subscript[W, 1,3,4],-(Subscript[W, 1,3,5]/Subscript[W, 1,3,4])}},{{2,4},{Subscript[W, 3,4,5]/Subscript[W, 1,3,5],-(Subscript[W, 1,4,5]/Subscript[W, 1,3,5]),-(Subscript[W, 1,3,4]/Subscript[W, 1,3,5])}},{{2,3},{-(Subscript[W, 3,4,5]/Subscript[W, 1,4,5]),-(Subscript[W, 1,3,5]/Subscript[W, 1,4,5]),Subscript[W, 1,3,4]/Subscript[W, 1,4,5]}},{{2,1},{-(Subscript[W, 1,4,5]/Subscript[W, 3,4,5]),Subscript[W, 1,3,5]/Subscript[W, 3,4,5],-(Subscript[W, 1,3,4]/Subscript[W, 3,4,5])}},{{1,5},{-(Subscript[W, 3,4,5]/Subscript[W, 2,3,4]),Subscript[W, 2,4,5]/Subscript[W, 2,3,4],-(Subscript[W, 2,3,5]/Subscript[W, 2,3,4])}},{{1,4},{Subscript[W, 3,4,5]/Subscript[W, 2,3,5],-(Subscript[W, 2,4,5]/Subscript[W, 2,3,5]),-(Subscript[W, 2,3,4]/Subscript[W, 2,3,5])}},{{1,3},{-(Subscript[W, 3,4,5]/Subscript[W, 2,4,5]),-(Subscript[W, 2,3,5]/Subscript[W, 2,4,5]),Subscript[W, 2,3,4]/Subscript[W, 2,4,5]}},{{1,2},{-(Subscript[W, 2,4,5]/Subscript[W, 3,4,5]),Subscript[W, 2,3,5]/Subscript[W, 3,4,5],-(Subscript[W, 2,3,4]/Subscript[W, 3,4,5])}}};

(* this can be taken as data, worked out in various other places *)
PentSolutionsScalingsFid::usage = "A paired list of the config and the scalings for that config {\!\(\*SubscriptBox[\(\[Alpha]\), \(i\)]\), \!\(\*SubscriptBox[\(\[Beta]\), \(i\)]\), \!\(\*SubscriptBox[\(\[Gamma]\), \(i\)]\)} in terms of the primary scalings {\!\(\*SubscriptBox[\(\[Alpha]\), \(1\)]\), \!\(\*SubscriptBox[\(\[Beta]\), \(1\)]\), \!\(\*SubscriptBox[\(\[Gamma]\), \(1\)]\)} (from the 54 config)"
PentSolutionsScalingsFid={{{5,4},{Subscript[\[Alpha], 1],Subscript[\[Beta], 1],Subscript[\[Gamma], 1]}},{{5,3},{Subscript[\[Alpha], 1]/Subscript[\[Gamma], 1],Subscript[\[Beta], 1]/Subscript[\[Gamma], 1],1/Subscript[\[Gamma], 1]}},{{5,2},{Subscript[\[Alpha], 1]/Subscript[\[Beta], 1],Subscript[\[Gamma], 1]/Subscript[\[Beta], 1],1/Subscript[\[Beta], 1]}},{{5,1},{Subscript[\[Beta], 1]/Subscript[\[Alpha], 1],Subscript[\[Gamma], 1]/Subscript[\[Alpha], 1],1/Subscript[\[Alpha], 1]}},{{4,5},{1-Subscript[\[Alpha], 1],1-Subscript[\[Beta], 1],1-Subscript[\[Gamma], 1]}},{{4,3},{(-1+Subscript[\[Alpha], 1])/(-1+Subscript[\[Gamma], 1]),(-1+Subscript[\[Beta], 1])/(-1+Subscript[\[Gamma], 1]),1/(1-Subscript[\[Gamma], 1])}},{{4,2},{(-1+Subscript[\[Alpha], 1])/(-1+Subscript[\[Beta], 1]),(-1+Subscript[\[Gamma], 1])/(-1+Subscript[\[Beta], 1]),1/(1-Subscript[\[Beta], 1])}},{{4,1},{(-1+Subscript[\[Beta], 1])/(-1+Subscript[\[Alpha], 1]),(-1+Subscript[\[Gamma], 1])/(-1+Subscript[\[Alpha], 1]),1/(1-Subscript[\[Alpha], 1])}},{{3,5},{1-Subscript[\[Alpha], 1]/Subscript[\[Gamma], 1],1-Subscript[\[Beta], 1]/Subscript[\[Gamma], 1],1-1/Subscript[\[Gamma], 1]}},{{3,4},{(-Subscript[\[Alpha], 1]+Subscript[\[Gamma], 1])/(-1+Subscript[\[Gamma], 1]),(-Subscript[\[Beta], 1]+Subscript[\[Gamma], 1])/(-1+Subscript[\[Gamma], 1]),Subscript[\[Gamma], 1]/(-1+Subscript[\[Gamma], 1])}},{{3,2},{(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1])/(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1]),(-1+Subscript[\[Gamma], 1])/(-Subscript[\[Beta], 1]+Subscript[\[Gamma], 1]),Subscript[\[Gamma], 1]/(-Subscript[\[Beta], 1]+Subscript[\[Gamma], 1])}},{{3,1},{(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1]),(-1+Subscript[\[Gamma], 1])/(-Subscript[\[Alpha], 1]+Subscript[\[Gamma], 1]),-(Subscript[\[Gamma], 1]/(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1]))}},{{2,5},{1-Subscript[\[Alpha], 1]/Subscript[\[Beta], 1],1-Subscript[\[Gamma], 1]/Subscript[\[Beta], 1],1-1/Subscript[\[Beta], 1]}},{{2,4},{(-Subscript[\[Alpha], 1]+Subscript[\[Beta], 1])/(-1+Subscript[\[Beta], 1]),(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1])/(-1+Subscript[\[Beta], 1]),Subscript[\[Beta], 1]/(-1+Subscript[\[Beta], 1])}},{{2,3},{(-Subscript[\[Alpha], 1]+Subscript[\[Beta], 1])/(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1]),(-1+Subscript[\[Beta], 1])/(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1]),Subscript[\[Beta], 1]/(Subscript[\[Beta], 1]-Subscript[\[Gamma], 1])}},{{2,1},{(-Subscript[\[Beta], 1]+Subscript[\[Gamma], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1]),(-1+Subscript[\[Beta], 1])/(-Subscript[\[Alpha], 1]+Subscript[\[Beta], 1]),Subscript[\[Beta], 1]/(-Subscript[\[Alpha], 1]+Subscript[\[Beta], 1])}},{{1,5},{1-Subscript[\[Beta], 1]/Subscript[\[Alpha], 1],1-Subscript[\[Gamma], 1]/Subscript[\[Alpha], 1],1-1/Subscript[\[Alpha], 1]}},{{1,4},{(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1])/(-1+Subscript[\[Alpha], 1]),(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1])/(-1+Subscript[\[Alpha], 1]),Subscript[\[Alpha], 1]/(-1+Subscript[\[Alpha], 1])}},{{1,3},{(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1]),(-1+Subscript[\[Alpha], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1]),Subscript[\[Alpha], 1]/(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1])}},{{1,2},{(Subscript[\[Alpha], 1]-Subscript[\[Gamma], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1]),(-1+Subscript[\[Alpha], 1])/(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1]),Subscript[\[Alpha], 1]/(Subscript[\[Alpha], 1]-Subscript[\[Beta], 1])}}};

PentFidSolve::usage = "A list of mappings between the \!\(\*SubscriptBox[\(W\), \(i, j, k\)]\) and the primary scalings, where the {5,4} config was taken as fiducial"
PentFidSolve = {Subscript[W, 1,2,3]->1,Subscript[W, 1,2,4]->-Subscript[\[Gamma], 1],Subscript[W, 1,2,5]->-1+Subscript[\[Gamma], 1],Subscript[W, 1,3,4]->Subscript[\[Beta], 1],Subscript[W, 1,3,5]->1-Subscript[\[Beta], 1],Subscript[W, 1,4,5]->Subscript[\[Beta], 1]-Subscript[\[Gamma], 1],Subscript[W, 2,3,4]->-Subscript[\[Alpha], 1],Subscript[W, 2,3,5]->-1+Subscript[\[Alpha], 1],Subscript[W, 2,4,5]->-Subscript[\[Alpha], 1]+Subscript[\[Gamma], 1],Subscript[W, 3,4,5]->Subscript[\[Alpha], 1]-Subscript[\[Beta], 1]};

(* for a given config (sorted in the same order as PentSolutionsFid) these are the common denominators which therefore also determine the scaling term *) 
PentDenomWList::usage = "A list of the denominators for each config, sorted in the same order as PentSolutionsWList etc"
PentDenomWList={Subscript[W, 1,2,3],Subscript[W, 1,2,4],Subscript[W, 1,3,4],Subscript[W, 2,3,4],Subscript[W, 1,2,3],Subscript[W, 1,2,5],Subscript[W, 1,3,5],Subscript[W, 2,3,5],Subscript[W, 1,2,4],Subscript[W, 1,2,5],Subscript[W, 1,4,5],Subscript[W, 2,4,5],Subscript[W, 1,3,4],Subscript[W, 1,3,5],Subscript[W, 1,4,5],Subscript[W, 3,4,5],Subscript[W, 2,3,4],Subscript[W, 2,3,5],Subscript[W, 2,4,5],Subscript[W, 3,4,5]};

Wijk::usage = "Wijk[spins, i, j, k], Returns \!\(\*SubscriptBox[\(W\), \(i, j, k\)]\) = \!\(\*SubscriptBox[\(J\), \(i\)]\).\!\(\*SubscriptBox[\(J\), \(j\)]\)\[Cross]\!\(\*SubscriptBox[\(J\), \(k\)]\), where the J are elements of the spin list"
ScalingsFromSpins::usage = "ScalingsFromSpins[spins], Returns {\[Alpha], \[Beta], \[Gamma], \!\(\*SubscriptBox[\(W\), \(123\)]\)} computed from the spin list"



GetVolPent::usage = "GetVolePent[configIndex], returns the pent volume as a formula in the \!\(\*SubscriptBox[\(W\), \(ijk\)]\), given the config index from 1..20"
GetEomPent::usage = "GetEomPent[spinCpt, ham], returns the RHS of the eom (the vector field) for the given spin component, i.e \!\(\*SubscriptBox[\(J\), \(3, 1\)]\), given a ham in Wform"
GetEomListPent::usage = "GenEomListPent[ham], returns a list of the ROS fo the eom for all Spin cpts"

ToSpinCpt::usage = "expands all instances of \!\(\*SubscriptBox[\(W\), \(i, j, k\)]\) in thing to their full spin component form \[IndentingNewLine]\!\(\*SubscriptBox[\(W\), \(\(i\)\(,\)\(j\)\(,\)\(k\)\(\\\ \)\)]\)\[Rule] \!\(\*SubscriptBox[\(J\), \(i\)]\).\!\(\*SubscriptBox[\(J\), \(j\)]\)\[Cross]\!\(\*SubscriptBox[\(J\), \(k\)]\) \[Rule] fully expanded interms of the components of \!\(\*SubscriptBox[\(J\), \(i\)]\) which are labelled in the following convention \[IndentingNewLine]\!\(\*SubscriptBox[\(J\), \(\(i\)\(\\\ \)\)]\)= (\!\(\*SubscriptBox[\(J\), \(i, 1\)]\),\!\(\*SubscriptBox[\(J\), \(i, 2\)]\), \!\(\*SubscriptBox[\(J\), \(i, 3\)]\))"

EvalPentN::usage = "EvalPentN[thing, spinsFlat] evaluate the provided *thing* by inserting \!\(\*SubscriptBox[\(J\), \(1, 1\)]\)\[Rule]spinsFlat[1], this should return numerical values"
ToExportForm::usage = "ToExportForm[thing_] convert pent Jlist spins into an ordering compatible with a flat array J = [ \!\(\*SubscriptBox[\(J\), \(1, 1\)]\), \!\(\*SubscriptBox[\(J\), \(1, 2\)]\), ... , \!\(\*SubscriptBox[\(J\), \(4, 1\)]\), \!\(\*SubscriptBox[\(J\), \(4, 2\)]\),\!\(\*SubscriptBox[\(J\), \(4, 3\)]\)]"
ConvertSpinClose::usage = "ConvertSpinClose[thing], replaces \!\(\*SubscriptBox[\(J\), \(5\)]\) with the closure relation"

(** config functions*)

FindConfigFromScales::usage = "FindConfigFromScales[scalings], returns the config index (in the 1..20 ordering) for a given set of scalings"
HamFromScales::usage = "HamFromScales[scalings, wv], return the volume from {a,b,c} and {wvol},  uses FindConfigFromScales to figure out which ham to us"

(** general helper functions *)

EvalPentN[thing_, spinsFlat_]:= (* evaluate the provided *thing* by inserting Subscript[J, 1,1]\[Rule]spinsFlat[1] etc 
 this should provide numerical values, k is inserted to approximate Abs'[x] = Sgn[x] = Tanh[kx] *)
	Block[{jlist},
	jlist = Table[Subscript[J, i,j], {i, 1, 4}, {j,1,3}];
	thing /. MapThread[#1->#2&,{(Flatten@jlist), spinsFlat}] /. k->10000
]

ToSpinCpt[thing_]:= 
(* expand all instances of Subscript[W, i,j,k] in thing to their full spin component form 
Subscript[W, i,j,k ]\[Rule] Subscript[J, i].Subscript[J, j]\[Cross]Subscript[J, k] \[Rule] fully expanded interms of the components of Subscript[J, i] which are labelled in the following convention 
Subscript[J, i ]= (Subscript[J, i,1],Subscript[J, i,2], Subscript[J, i,3])
*)
 thing /. {Subscript[W, i_, j_, k_] -> Subscript[J, i].Cross[Subscript[J, j], Subscript[J, k]]} /. Subscript[J, i_]->{Subscript[J, i,1],Subscript[J, i,2],Subscript[J, i,3]}

ToExportForm[thing_]:= thing /.  {Subscript[J, i_, j_]->Subscript[J, (i-1)*3+j]}   /. {Subscript[J, i_]->J[[i]]}
ConvertSpinCloseDep[thing_]:= thing /. {Subscript[J, 5,i_ ]->-Subscript[J, 1,i]-Subscript[J, 2,i]-Subscript[J, 3,i]-Subscript[J, 4,i]}

ineqToExportForm[thing_]:= thing /. Subscript[x_, 1]->x /. {\[Alpha]->alpha, \[Beta]->beta, \[Gamma]->gamma}
ineqTabFull = Table[GenIneqsFull[PentSolutionsScalingsFid[[i]][[2]]], {i, 1, 20}];


Begin["`Private`"]

Wijk[spins_, i_, j_, k_]:= spins[[i]].Cross[spins[[j]], spins[[k]]];

ScalingsFromSpins[spins_]:= Block[{a,b,c, denom},
	(* this is only for the 54 config, needs to be generalized *)
	denom = Wijk[spins, 1,2,3];
	a = -1*Wijk[spins,2,3,4]/denom;
	b = Wijk[spins, 1,3,4]/denom;
	c =-1* Wijk[spins, 1,2,4]/denom;
	{a,b,c,denom}]

(* don't expose this *)
VolPent::usage = "VolPent[config, Wvol], Returns the pent volume. Config is the appropriate second element from PentSolutionsScalingsFid,Wvol is the apprpopriate overall scale."
VolPent[config_, Wvol_]:=Block[{a, b,c}, 
	{a,b,c}=config;
	(Sqrt[2]/3)*(Sqrt[Abs[a*b*c]]-Sqrt[Abs[(a-1)*(b-1)*(c-1)]])*Sqrt[Abs[Wvol]]
	(*(Sqrt[2]/3)*(Sqrt[a*b*c]-Sqrt[(a-1)*(b-1)*(c-1)])*Sqrt[Wvol]*)
]

GetVolPent[configIndex_]:= (* labelling the configs in the order they are in PentSolutionsFid,
this returns the pent volume (i think) for a given config index, in W form *)
VolPent[PentSolutionsScalingsFid[[configIndex]][[2]], PentDenomWList[[configIndex]]] /.MapThread[#1->#2&, {{Subscript[\[Alpha], 1 ],Subscript[\[Beta], 1], Subscript[\[Gamma], 1]}, PentSolutionsWList[[1]][[2]]}] 

GetEomPent[spinCpt_, ham_]:= 
	(* given a hamiltonian in spin component form (i.e interms of the Subscript[J, 1,3] etc) compute the equation of motion for the provided spinCpt (i.e Subscript[J, 1,3]) *)
	Module[{gradtab, Jlist}, 
	gradtab = MakeGradTabPent[ham];
	Jlist = Table[Subscript[J, r,i], {r, 1, 4}, {i, 1, 4}];
	Total@Flatten@Table[D[spinCpt, Jlist[[r]][[j]]]*gradtab[[(r-1)*3+kk]]*Jlist[[r]][[i]]*LeviCivitaTensor[3][[i, j, kk]], {i, 1, 3}, {j, 1, 3}, {kk, 1, 3}, {r,1,4}]
]

(* compute the whole list of EOM's *)
GetEomListPent[ham_] := Map[GetEomPent[#, ham]&, Flatten@Table[Subscript[J, i,j],{i, 1, 4}, {j, 1, 3}]]

MakeGradTabPent[hamPent_]:= 
(* if you know the right ham (in spin-cpt form) this func will return a flattened table of derivatives with respect to each spin component *) 
	Flatten@ Table[D[hamPent, Subscript[J, i,j]] /. Abs'[x_]-> Tanh[k*x] , {i, 1, 4}, {j, 1, 3}]

(* finding the config *)
cfns = {\[Gamma]>=(\[Alpha]*\[Beta])/(\[Alpha]+\[Beta]-1), \[Gamma]<=(\[Alpha](1-\[Beta]))/(\[Alpha]-\[Beta]), \[Gamma]<=((\[Alpha]-1)\[Beta])/(\[Alpha]-\[Beta])}; 

GenIneqsFull[config_]:= Block[{f1,f2,fin1, fin2},
	f1 = Map[FullSimplify@(# /. MapThread[#1->#2&, {{\[Alpha],\[Beta],\[Gamma]}, config}])&, cfns] ;
	f2 =And@@ Map[#/.x_->x>=1&, config];
	fin1 = Join[f2, f1[[1]]&&(f1[[2]]||f1[[3]])]
]



FindConfigFromScales[scalings_]:=Module[{ineqs},
	{a,b,c,wv} = scalings;
	ineqs =ineqTabFull /.{Subscript[\[Alpha], 1]->a, Subscript[\[Beta], 1]->b, Subscript[\[Gamma], 1]->c};
	configIndex = First@First@Position[ineqs, True]
]


HamFromScales[scalings_, wv_] := Module[{index, ham},
	index = FindConfigFromScales[Join[scalings, {wv}]];
	ham = VolPent[PentSolutionsScalingsFid[[index]][[2]], PentDenomWList[[index]]*wv];
	ham /.PentFidSolve/. MapThread[#1->#2&, {{Subscript[\[Alpha], 1], Subscript[\[Beta], 1], Subscript[\[Gamma], 1]}, scalings}]
]

	
End[ ]


EndPackage[ ]



