//
#include <math.h>
#include <stdio.h>

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

//
void print_stats(double *data, unsigned n)
{
  //
  double min = 0.0, max = 0.0, amean = 0.0, dev = 0.0, devp = 0.0;
  
  //
  sort(data, n);

  min = data[0];
  max = data[n - 1];
  amean = mean(data, n);
  dev = stddev(data, n);
  devp = (dev * 100.0) / amean;
  
  printf("\n%.3lf, %.3lf, %.3lf, %.3lf, %.3lf %%\n",
	 min,
	 max,
	 amean,
	 dev,
	 devp);

  printf("\nDelta(min, max)   = %.3lf\n", max - min);
  printf("Delta(amean, min) = %.3lf\n", fabs(amean - min));
  printf("Delta(amean, max) = %.3lf\n", fabs(amean - max));

}
