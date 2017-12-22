#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <float.h>

void simple_copy(char *src, char *dest)
{
	int c = 0;
	FILE *fpsrc = fopen(src, "r");
	FILE *fpdest = fopen(dest, "w");
	while ((c = getc(fpsrc)) != EOF) 
		putc(c, fpdest);
	fclose(fpsrc);
	fclose(fpdest);
}

void simplecat(char *file)
{
	int c = 0;
	FILE *fp = fopen(file, "r");
	while ((c = getc(fp)) != EOF)
		putc(c, stdout);
	fclose(fp);
}

void testgvprintf(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

int main(int argc, char *argv[])
{

	char string[10] = { 'h', 'e', 'l', 'l', 'o', '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871;
	char string1[1000] = { 0 };
	long ltest = 23459999;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld\n";
	if ( argc == 2 ) 
		simplecat(argv[1]); 
	else if ( argc == 3) 
		simple_copy(argv[1], argv[2]); 
	else {

		fprintf(stdout, "decimal value of 987654         %d\n", 987654);
		fprintf(stdout, "octal value of 987654           %o\n", 987654);
		fprintf(stdout, "The string literal \"987654\"     %s\n", "987654");
		fprintf(stdout, "decimal value of -987654        %d\n", -987654);
		dprintf(1, "decimal value of 987654         %d\n", 987654);
		dprintf(1, "octal value of 987654           %o\n", 987654);
		dprintf(1, "The string literal \"987654\"     %s\n", "987654");
		dprintf(1, "decimal value of -987654        %d\n", -987654);

		printf("gprintf:\n");
		printf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest);
		printf("gsprintf:\n");
		sprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest);

		printf("gvprintf:\n");
		testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest);

		printf("%f\n", 3.1);


		printf("P\n");

		double two = 2;
		printf("%f\n", two);



		printf("%zu\n", (size_t)-1);

		size_t t1[22] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

		printf("%zu %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n", t1[0], t1[1],t1[2],t1[3],t1[4],t1[5],t1[6],t1[7],t1[8],t1[9],t1[10]);
		printf("%zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n", t1[11], t1[12],t1[13],t1[14],t1[15],t1[16],t1[17],t1[18],t1[19],t1[20]);

		ssize_t t2[22] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
		ssize_t t3[22] = {-0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20 };


		printf("%zd %zd %zd %zd %zd %zd %zd %zd %zd %zd %zd\n", t2[0], t2[1],t2[2],t2[3],t2[4],t2[5],t2[6],t2[7],t2[8],t2[9],t2[10]);

		printf("start negatives\n");
		printf("%zd %zd %zd %zd %zd %zd %zd %zd %zd %zd %zd\n", t3[0], t3[1], t3[2],t3[3],t3[4],t3[5],t3[6],t3[7],t3[8],t3[9],t3[10]);
		printf("%zd %zd %zd %zd %zd %zd %zd %zd %zd %zd\n", t3[11], t3[12],t3[13],t3[14],t3[15],t3[16],t3[17],t3[18],t3[19],t3[20]);

	
		size_t hold = SIZE_MAX;
		printf("LONG_MAX %zd\n", LONG_MAX);
		printf("LONG_MIN %zd\n", LONG_MIN);
		//printf("-LONG_MAX %zd\n", -LONG_MAX);
		//printf("-LONG_MIN %zd\n", -LONG_MIN);
		printf("SIZE_MAX %zu\n", hold);
		printf("SSIZE_MAX %zd\n", SSIZE_MAX);
		printf("LLONG_MAX %lld\n", LLONG_MAX);
		printf("LLONG_MIN %lld\n", LLONG_MIN);

	}
	return 0;
}





