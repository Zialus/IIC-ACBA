#include "pearson.h"

double pearson(double x[], double y[], int n) {
  double xx[n], yy[n];

  double sum_y = 0, sum_yy = 0, sum_xy = 0, sum_x = 0, sum_xx = 0;

  for (int i = 0; i < n; i++) {
    xx[i] = x[i] * x[i];
    yy[i] = y[i] * y[i];
  }

  for (int i = 0; i < n; i++) {
    sum_x += x[i];
    sum_y += y[i];
    sum_xx += xx[i];
    sum_yy += yy[i];
    sum_xy += x[i] * y[i];
  }

  double nr = (n * sum_xy) - (sum_x * sum_y);
  double sum_x2 = sum_x * sum_x;
  double sum_y2 = sum_y * sum_y;
  double dr_1 = (n * sum_xx) - sum_x2;
  double dr_2 = (n * sum_yy) - sum_y2;
  double dr_3 = dr_1 * dr_2;
  double dr = sqrt(dr_3);
  double r = (nr / dr);

  return r;
}
