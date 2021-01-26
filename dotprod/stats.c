//
#include <math.h>

//
void sort(double *a, unsigned n)
{
  //
  for (unsigned i = 0; i < n; i++)
    for (unsigned j = i + 1; j < n; j++)
      if (a[i] > a[j])
	{
	  double tmp = a[i];

	  a[i] = a[j];
	  a[j] = tmp;
	}
}

//
double mean(double *a, unsigned n)
{
  //
  double m = 0.0;

  //
  for (unsigned i = 0; i < n; i++)
    m += a[i];

  //
  return m / (double)n;
}

//
double stddev(double *a, unsigned n)
{
  //
  double d = 0.0;
  double m = mean(a, n);
  
  //
  for (unsigned i = 0; i < n; i++)
    d += (a[i] - m) * (a[i] - m);

  //
  d /= (double)(n - 1);
  
  //
  return sqrt(d);
}
