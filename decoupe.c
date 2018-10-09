#include <stdio.h>            /* C input/output                       */
#include <stdlib.h>           /* C standard library                   */
#include <glpk.h>             /* GNU GLPK linear/mixed integer solver */


int main(void)
{
  /* declare variables */
  glp_prob *lp;
  int ia[1+1000], ja[1+1000];
  double ar[1+1000], z, x1, x2, x3,x4;

  /* create problem */
  lp = glp_create_prob();
  glp_set_prob_name(lp, "decoupe");
  glp_set_obj_dir(lp, GLP_MIN);

  /* fill problem */
  glp_add_rows(lp, 4);
  glp_set_row_name(lp, 1, "p1");
  glp_set_row_bnds(lp, 1, GLP_FX, 97.0, 97.0);
  glp_set_row_name(lp, 2, "p2");
  glp_set_row_bnds(lp, 2, GLP_FX, 610.0, 610.0);
  glp_set_row_name(lp, 3, "p3");
  glp_set_row_bnds(lp, 3, GLP_FX, 395.0, 395.0);
  glp_set_row_name(lp, 4, "p4");
  glp_set_row_bnds(lp, 4, GLP_FX, 211.0, 211.0);
  glp_add_cols(lp, 4);
  glp_set_col_name(lp, 1, "x1");
  glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 1, 1.0);
  glp_set_col_name(lp, 2, "x2");
  glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 2, 1.0);
glp_set_col_name(lp, 3, "x3");
  glp_set_col_bnds(lp,3, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 3, 1.0);
glp_set_col_name(lp, 4, "x4");
  glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);
  glp_set_obj_coef(lp, 4, 1.0);

  ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */
  ia[2] = 1, ja[2] = 2, ar[2] = 0.0; /* a[1,2] = 2 */
  ia[3] = 1, ja[3] = 3, ar[3] = 0.0; /* a[2,1] = 3 */
  ia[4] = 1, ja[4] = 4, ar[4] = 0.0; /* a[2,2] = 1 */

  ia[5] = 2, ja[5] = 1, ar[5] = 0.0; /* a[1,1] = 1 */
  ia[6] = 2, ja[6] = 2, ar[6] = 1.0; /* a[1,2] = 2 */
  ia[7] = 2, ja[7] = 3, ar[7] = 0.0; /* a[2,1] = 3 */
  ia[8] = 2, ja[8] = 4, ar[8] = 0.0; /* a[2,2] = 1 */

  ia[9] = 3, ja[9] = 1, ar[9] = 0.0; /* a[1,1] = 1 */
  ia[10] =3, ja[10] = 2, ar[10] = 0.0; /* a[1,2] = 2 */
  ia[11] =3, ja[11] = 3, ar[11] = 1.0; /* a[2,1] = 3 */
  ia[12] = 3, ja[12] = 4, ar[12] = 0.0; /* a[2,2] = 1 */

  ia[13] = 4, ja[13] = 1, ar[13] = 0.0; /* a[1,1] = 1 */
  ia[14] = 4, ja[14] = 2, ar[14] = 0.0; /* a[1,2] = 2 */
  ia[15] = 4, ja[15] = 3, ar[15] = 0.0; /* a[2,1] = 3 */
  ia[16] = 4, ja[16] = 4, ar[16] = 1.0; /* a[2,2] = 1 */

  glp_load_matrix(lp, 16, ia, ja, ar);
  /* solve problem */

  glp_simplex(lp, NULL);
  /* recover and display results */
  z = glp_get_obj_val(lp);
  /*x1 = glp_get_col_prim(lp, 1);
  x2 = glp_get_col_prim(lp, 2);
  x3 = glp_get_col_prim(lp, 3);
  x4 = glp_get_col_prim(lp, 4);*/

  x1=glp_get_row_dual(lp,1);
  x2=glp_get_row_dual(lp,2);
  x3=glp_get_row_dual(lp,3);
  x4=glp_get_row_dual(lp,4);

 /* branch and cut*/
	glp_set_obj_dir(lp, GLP_MAX); 
int y;	
y=(x1*97+x2*610+x3*375+x4*211);
  printf("Sac a dos = %d\n",y);
  printf("z = %g; x1 = %g; x2 = %g;x3 = %g;x4 = %g\n", z, x1, x2, x3,x4);
glp_intopt(lp, NULL);
  /* housekeeping */
  glp_delete_prob(lp);
  glp_free_env();

  return 0;
}
