#include <stdio.h>
#include <stdarg.h>

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
	FILE *fp = fopen(file, "r+");
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
	double ftest = 3123.21317892345;
	double ftest2 = 0.202309823709099;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld==%f==%lf\n";
	

	if ( argc == 2 ) 
		simplecat(argv[1]); 
	else if ( argc == 3) 
		simple_copy(argv[1], argv[2]); 
	else {

		fprintf(stdout, "decimal value of 987654         %d\n", 987654);
		fprintf(stdout, "octal value of 987654           %o\n", 987654);
		fprintf(stdout, "hexadecimal value of 987654     %x\n", 987654);
		fprintf(stdout, "The string literal \"987654\"     %s\n", "987654");
		fprintf(stdout, "decimal value of -987654        %d\n", -987654);

		
		dprintf(1, "decimal value of 987654         %d\n", 987654);
		dprintf(1, "octal value of 987654           %o\n", 987654);
		dprintf(1, "hexadecimal value of 987654     %x\n", 987654);
		dprintf(1, "The string literal \"987654\"     %s\n", "987654");
		dprintf(1, "decimal value of -987654        %d\n", -987654);


		//gprintf("gfprintf:\n");
		//gfprintf(gstderr, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		//gprintf("gdprintf:\n");
		//gdprintf(2, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		printf("gprintf:\n");
		printf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		printf("gsprintf:\n");
		sprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		printf("gvprintf:\n");
		testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);


	
		printf("%f\n", 43.6565123987324987132479183478173408712409710471249999);
		printf("%f\n", 21.111111111111111111111111111111111111111111111111111111);

		printf("%f\n", 3.1);
		//gprintf("%s\n", "a");

		printf("P\n");

		double two = 2;
		printf("%f\n", two);

		//printf("%ld\n", 10);
		//printf("%d\n", 0);
		//printf("%zu\n", 11);

	}
	return 0;
}





