#include "boundary-fns.h"
#include <math.h>
#include "mdefs.h"

void boundary_fn_1(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[1]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[1]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[1]][[3]]] *> ;
}
void boundary_fn_2(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[2]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[2]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[2]][[3]]] *> ;
}
void boundary_fn_3(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[3]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[3]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[3]][[3]]] *> ;
}
void boundary_fn_4(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[4]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[4]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[4]][[3]]] *> ;
}
void boundary_fn_5(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[5]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[5]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[5]][[3]]] *> ;
}
void boundary_fn_6(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[6]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[6]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[6]][[3]]] *> ;
}
void boundary_fn_7(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[7]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[7]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[7]][[3]]] *> ;
}
void boundary_fn_8(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[8]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[8]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[8]][[3]]] *> ;
}
void boundary_fn_9(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[9]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[9]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[9]][[3]]] *> ;
}
void boundary_fn_10(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[10]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[10]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[10]][[3]]] *> ;
}

void boundary_fn_11(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[11]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[11]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[11]][[3]]] *> ;
}
void boundary_fn_12(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[12]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[12]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[12]][[3]]] *> ;
}
void boundary_fn_13(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[13]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[13]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[13]][[3]]] *> ;
}
void boundary_fn_14(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[14]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[14]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[14]][[3]]] *> ;
}
void boundary_fn_15(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[15]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[15]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[15]][[3]]] *> ;
}
void boundary_fn_16(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[16]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[16]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[16]][[3]]] *> ;
}
void boundary_fn_17(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[17]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[17]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[17]][[3]]] *> ;
}
void boundary_fn_18(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[18]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[18]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[18]][[3]]] *> ;
}
void boundary_fn_19(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[19]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[19]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[19]][[3]]] *> ;
}
void boundary_fn_20(double *J, double *b1, double* b2, double* b3)
{
  *b1 = <* ToExportForm[boundaryFnList[[20]][[1]]] *> ;
  *b2 = <* ToExportForm[boundaryFnList[[20]][[2]]] *> ;
  *b3 = <* ToExportForm[boundaryFnList[[20]][[3]]] *> ;
}
