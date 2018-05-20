#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[ ])
{
/*
cmd -ao arg path path
cmd -a -o arg path path
cmd -o arg -a path path
cmd -a -o arg -- path path
cmd -a -oarg path path
cmd -aoarg path path
*/
	int c;
	int bflg = 0, aflg = 0, errflg = 0;
	char *ifile = NULL;
	char *ofile = NULL;
	//. . .
	while ((c = getopt(argc, argv, ":abf:o:")) != -1) {
		switch(c) {
		case 'a':
			if (bflg)
				errflg++;
			else
				aflg++;
			break;
		case 'b':
			if (aflg)
				errflg++;
			else
				bflg++;
			break;
		case 'f':
			ifile = optarg;
			break;
		case 'o':
			ofile = optarg;
			break;
		case ':':	   /* -f or -o without operand */
			fprintf(stderr,
				"Option -%c requires an operand\n", optopt);
			errflg++;
			break;
		case '?':
			fprintf(stderr,
				"Unrecognized option: '-%c'\n", optopt);
			errflg++;
		}
	}
	if (errflg) {
		fprintf(stderr, "usage: . . . ");
		exit(2);
	}
	for ( ; optind < argc; optind++) {
		printf("%s\n", argv[optind]);
		//if (access(argv[optind], R_OK)) {
		//}
	}
	if (ofile)
		printf("%s\n", ofile);
	if (ifile)
		printf("%s\n", ifile);
}
