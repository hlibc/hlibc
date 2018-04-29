
const double __john_hart_table[] = { 
	0, /* unused so that the polynomial degrees start at 1 */
	0.99999999999925182,
	-0.49999999997024012,
	0.041666666473384543,
	-0.001388888418000423,
	0.0000248010406484558,
	-0.0000002752469638432,
	 0.0000000019907856854
};

double __h_cos(double x)
{
	/* 12.1 dec dig over [0, pi/2]. */
	const double *c = __john_hart_table;
	x *= x;
	return (c[1] + x*(c[2]+ x*(c[3] + x*(c[4] + x*(c[5] + x*(c[6] + c[7]*x))))));
}

