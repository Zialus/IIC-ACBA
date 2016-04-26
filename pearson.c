#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double pearson(double x[], double y[], int n) {
  int i;

  double r, xx[n], yy[n], nr = 0, dr_1 = 0, dr_2 = 0, dr_3 = 0, dr = 0;

  double sum_y = 0, sum_yy = 0, sum_xy = 0, sum_x = 0, sum_xx = 0;

  for (i = 0; i < n; i++) {
    xx[i] = x[i] * x[i];
    yy[i] = y[i] * y[i];
  }

  for (i = 0; i < n; i++) {
    sum_x += x[i];
    sum_y += y[i];
    sum_xx += xx[i];
    sum_yy += yy[i];
    sum_xy += x[i] * y[i];
  }

  nr = (n * sum_xy) - (sum_x * sum_y);
  double sum_x2 = sum_x * sum_x;
  double sum_y2 = sum_y * sum_y;
  dr_1 = (n * sum_xx) - sum_x2;
  dr_2 = (n * sum_yy) - sum_y2;
  dr_3 = dr_1 * dr_2;
  dr = sqrt(dr_3);
  r = (nr / dr);

  return r;
}