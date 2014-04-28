(* ::Package:: *)

BeginPackage["PolyGeometry`"]
(* ccs
 * general functions that are super useful for investigating 
 * the Hamiltonian Volume flow of the pentagonal wedge (and tets) 
 *) 

SignedAngle::usage = "SignedAngle[va, vb, ref] gives the signed angle between vectors Va and Vb with the sign computed
 according to the reference direction ref"
GenJList::usage = "GenJList[nspin] return a list of spins {{\!\(\*SubscriptBox[\(J\), \(1, 1\)]\), \!\(\*SubscriptBox[\(J\), \(1, 2\)]\), \!\(\*SubscriptBox[\(J\), \(1, 3\)]\)}, ... , {\!\(\*SubscriptBox[\(J\), \(n, 1\)]\)...}}"


PhaseSpaceFromSpinsTet::usage = "PhaseSpaceFromSpinsTet[spins] Returns the KM phase space variables (q1, p1) from a set of tet spins"
GetNormsTet::usage = "GetNormsTet[q1, p1, A] Find a set of equifacial norms associated with a given p1, q1 and area A"
VolTet::usage = "VolTet[spins] Return the tet volume Vol = \!\(\*SubscriptBox[\(W\), \(\(123\)\(\\\ \)\)]\)= \!\(\*SubscriptBox[\(J\), \(1\)]\).\!\(\*SubscriptBox[\(J\), \(2\)]\)\[Cross]\!\(\*SubscriptBox[\(J\), \(3\)]\)"
PoissonBracketTet::usage = "PoissonBracketTet[f, g] compute the PB in the spin coordinates of f and g, where f and g are functions of \!\(\*SubscriptBox[\(J\), \(\(i\)\(,\)\(j\)\(\\\ \)\)]\)etc"


TetVertsDefault::usage="The default config for the tet used to extend into a pent"
MakeVertsPent::usage="MakePentVerts[TetVertList,\[Lambda],\[Mu],\[Nu]], Creates a set of pent verts by scaling the edges of a given set of tet verts"
GenSpinsFromVertsPent::usage="GenSpinsFromVertsPent[VertList], creates a set of spins from the given set of pent verts"
PhaseSpaceFromSpinsPent::usage = "PhaseSpaceFromSpinsPent[spins] Returns the KM variables (q1, q2, p1, p2) from a list of pent spins"

(* a set of default initial pent spins *)
ninitPent=GenSpinsFromVertsPent@MakeVertsPent[TetVertsDefault,.61,0.65,.62]

GenJList[nspin_]:= Table[Subscript[J, r,i], {r, 1, nspin}, {i, 1, 3}];

Begin["`Private`"]

(* general helper functions *)

SignedAngle[va_,vb_, ref_]:=
	Module[{sina,cosa,sign,angle},
	sina=Norm[Cross[va,vb]]/(Norm[va]*Norm[vb]);
	cosa=va.vb/(Norm[va]*Norm[vb]);
	angle=ArcTan[cosa, sina];
	sign=ref.Cross[va,vb];
	If[sign < 0, angle=2\[Pi]-angle];
	angle]



(* tet functions  *)

PhaseSpaceFromSpinsTet[norms_]:=
	Module[{p1vec,p2vec,p0vec,n1,n2,n3,n4,p1,q1,Avec,Bvec},
		{n1,n2,n3} = norms[[1;;3]];
	p0vec=n1;
	p1vec=p0vec+n2;
	p2vec=p1vec+n3;
	p1=Norm[p1vec];
	Avec=Cross[p0vec,p1vec]/Norm[Cross[p0vec,p1vec]];
	Bvec=Cross[p1vec,p2vec]/Norm[Cross[p1vec,p2vec]];
	q1=SignedAngle[Avec, Bvec, p1vec];
	{q1,p1}]

(* get the equations defining tet normals, given the quad indexs, index, i1, i2
 * should not be exposed for direct usage
 * note that the areas are fixed *)
FindNormsTetHelper[index_, i1_,i2_]:=
	Module[{n1,n2,n3,n4, n2x,n2z, n3x, n3y, n3z, P1Vec,AV,BV,Y,X, p1eqn, p1eqn2,q1eqn},
	A1=A2=A3=A4=A;
	n1={0,0,-1};
	n2={0, n2x, n2z};
	n3={n3x,n3y,n3z};
	n4 = (-1/A4)*(A1*n1 + A2*n2 + A3*n3);
	P1Vec=A1*n1+A2*n2;
	AV=Cross[A1*n1, P1Vec];
	BV=Cross[P1Vec, A3*n3];
	Y=Norm[Cross[AV,BV]];
	X=AV.BV;
	p1eqn=p1==Norm[P1Vec];
	p1eqn2=p1==Sqrt[A3^2+A4^2+2*A3*A4*n3.n4];
	q1eqn=q1==2*ArcTan[(Sqrt[X^2+Y^2]-X)/Y];
	norm2eqn=1==Norm[n2];
	norm3eqn=1==Norm[n3];
	soln2x=Solve[norm2eqn, n2x];
	soln3x=Solve[norm3eqn, n3x];
	sysTet={p1eqn, p1eqn2, q1eqn}/.soln2x[[i1]] /. soln3x[[i2]];
	roots=Solve[sysTet, {n2z,n3y, n3z}];
	{n1,n2,n3,n4}/.soln2x[[i1]] /. soln3x[[i2]]/.roots[[index]]]

NormsTetNumHelper[Q1_,P1_, index_, i1_, i2_]:=
	FindNormsTetHelper[index, i1, i2]/.{p1->P1, q1->Q1,A->1};

GetNormsTet[Q1_,P1_, Area_]:=(Module[{index, i1, i2, q1red},
	If[Q1<=\[Pi]/2, index=2;i1=1;i2=1;q1red=Q1,
	If[Q1<=\[Pi], index=1; i1=1;i2=1;q1red=\[Pi]-Q1,
	If[Q1<(3\[Pi]/2), index=1; i1=1;i2=2;q1red=Q1-\[Pi],(* q1-\[Pi] is an important choice, doesn't work otherwise *)
	index=2;i1=1;i2=2;q1red=2\[Pi]-Q1]]];
	NormsTetNumHelper[q1red,P1, index, i1, i2]])

VolTet[spins_]:= spins[[1]].Cross[spins[[2]], spins[[3]]]

jListTet = GenJList[4];

PoissonBracketTet[fn1_, fn2_]:= Total@Flatten@Table[D[fn1, jListTet[[r]][[j]]]*D[fn2, jListTet[[r]][[k]]]*jListTet[[r]][[i]]*LeviCivitaTensor[3][[i, j, k]], {i, 1, 3}, {j, 1, 3}, {k, 1, 3}, {r,1,4}]

(* pent geometry fns *)

(* these from H.Haggard *)
MakeVertsPent[TetVertList_,\[Lambda]_,\[Mu]_,\[Nu]_]:= Module[{Vert1,Vert2,Vert3,Vert4,Vert5,Vert6},
Vert1=TetVertList[[1]];
Vert2=TetVertList[[2]];
Vert3=TetVertList[[3]];
Vert4=\[Lambda](TetVertList[[4]]-TetVertList[[1]]);
Vert5=\[Mu](TetVertList[[4]]-TetVertList[[2]])+(Vert2-Vert1);
Vert6=\[Nu](TetVertList[[4]]-TetVertList[[3]])+(Vert3-Vert1);
{Vert1,Vert2,Vert3,Vert4,Vert5,Vert6}]

GenSpinsFromVertsPent[VertList_]:= Module[{AVec1,AVec2,AVec3,AVec4,AVec5},
AVec1= 1/2 Cross[VertList[[4]]-VertList[[1]],VertList[[3]]-VertList[[1]]]+1/2 Cross[VertList[[3]]-VertList[[6]],VertList[[4]]-VertList[[6]]];
AVec2=1/2 Cross[VertList[[2]]-VertList[[1]], VertList[[4]]-VertList[[1]]]+1/2 Cross[VertList[[4]]-VertList[[5]],VertList[[2]]-VertList[[5]]];
AVec3= 1/2 Cross[VertList[[3]]-VertList[[2]],VertList[[5]]-VertList[[2]]]+1/2 Cross[VertList[[5]]-VertList[[6]],VertList[[3]]-VertList[[6]]];
AVec4=1/2 Cross[VertList[[3]]-VertList[[1]],VertList[[2]]-VertList[[1]]];
AVec5=1/2 Cross[VertList[[5]]-VertList[[4]],VertList[[6]]-VertList[[4]]];
Chop[{AVec1,AVec2,AVec3,AVec4,AVec5}]]

TetVertsDefault={{0,0,0}, {1,0,.1},{.5,1,0},{.3,.2, 1}}

PhaseSpaceFromSpinsPent[spins_]:=
Module[{p1vec,p2vec,p0vec,p3vec,n1,n2,n3,n4,n5,p1,p2,q1,q2,Avec,Bvec},
	{n1,n2,n3,n4} = spins[[1;;4]];
	p0vec=n1;
	p1vec=p0vec+n2;
	p2vec=p1vec+n3;
	p3vec=p2vec+n4;
	p1=Norm[p1vec];
	p2=Norm[p2vec];
	Avec=Cross[p0vec,p1vec]/Norm[Cross[p0vec,p1vec]];
	Bvec=Cross[p1vec,p2vec]/Norm[Cross[p1vec,p2vec]];
	q1=SignedAngle[Avec,Bvec,p1vec];	
	Avec=Cross[p1vec,p2vec]/Norm[Cross[p1vec,p2vec]];Bvec=Cross[p2vec,p3vec]/Norm[Cross[p2vec,p3vec]];
	q2=SignedAngle[Avec,Bvec,p2vec];
	{q1,q2,p1,p2}
]

End[ ]

EndPackage[ ] 



