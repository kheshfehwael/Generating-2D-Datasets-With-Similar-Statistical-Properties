#include "compute_pi.h"

double pi_with_numerical_integration(const int num_steps) {
  const double width = 1.0 / double(num_steps); // width of a rectangle
  double sum = 0.0; // for summing up all heights of rectangles

#pragma omp parallel for simd reduction(+ : sum)
  for (int i = 0; i < num_steps; i++) {
    double x = (i + 0.5) * width; // midpoint
    sum = sum + (1.0 / (1.0 + x * x)); // add new height of a rectangle
  }

  return sum * 4 * width; // compute pi
}
