#include <gstddef.h>
#include <gstdlib.h>
/* definitions */
#define	TOLER	.00001
#define	EULER	2.71828182846
#define PI	3.14159265358979323846264
#define MYNAN	-(0./0.) 

/* trig */ 
double gsin(double);
double gsinh(double); 
double gasin(double); 

double gtan(double);
double gtanh(double);
double gatan(double); 

double gcos(double);
double newcos(double);
double gcosh(double);
double gacos(double);

/* exp */
double gexp(double);

/* pow */
double gpow(double, double);

/* sqrt */
double gsqrt(double);

/* log */
double glog(double);


double gremainder(double, double);
double gjn(int, double);
double gj0(double);
double gj1(double);
double ggamma(double);

double gfabs(double);

double gfloor(double);

/* internal */
double _arg_reduction(double);
int _check_tolerance(double, double);
double aseries_func(double, int);
double series_func(double, int, int, int);

double series_func_driver(double, int);

double trigfunc(int, double);

