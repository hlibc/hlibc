#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <time.h>



char *generator(char *path, int lever)
{
        size_t i          = 0;
	int pathtab[4096];
        size_t npth       = 0;
	size_t k = 0;
	
	static char slash[2] = {'/', '\0'};
	static char dot[2] = {'.', '\0'};

        for (i = 0; path[i] != '\0' && i < 4096; i++, k++) {
                if (path[i] == '/') {
                       pathtab[npth++] = i;
			pathtab[npth] = 0;
                }
        }
	if (i == 0 )
		return dot;
	if ( npth == k && k > 1)
		return slash;
	if (i > 1){
	        for (; path[--i] == '/';--npth) {
      	        	path[i] = '\0';
        	}
	}
	if ((npth > 0 ) ) { 
                return path + pathtab[npth -1]  + 1;
        }
        else { 
                return path;
        }

}

char *mydirname(char *path)
{
        size_t i          = 0;
	int pathtab[4096];
        size_t npth       = 0;
	size_t k          = 0;
	
	static char slash[2] = {'/', '\0'};
	static char dot[2]   = {'.', '\0'};

        for (i = 0; path[i] != '\0' && i < 4096; i++, k++) {
                if (path[i] == '/') {
			pathtab[npth++] = i;
			pathtab[npth] = 0;
                }
        }

	if (i == 0 )
		return dot;
	if ( npth == k && k > 1)
		return slash;
	if (i)
		--i;
        for (;i &&  path[i] == '/';--i) {
        	path[i] = '\0';
       	} 
        for (; i && path[i] != '/';--i) { 
        	path[i] = '\0';
       	} 
        for (; i && path[i] == '/';--i) {
        	path[i] = '\0';
       	}

        return path; 
}

char *mybasename(char *path)
{
        size_t i          = 0;
	int pathtab[4096];
        size_t npth       = 0;
	size_t k = 0;
	
	static char slash[2] = {'/', '\0'};
	static char dot[2] = {'.', '\0'};

        for (i = 0; path[i] != '\0' && i < 4096; i++, k++) {
                if (path[i] == '/') {
                       pathtab[npth++] = i;
			pathtab[npth] = 0;
                }
        }
	if (i == 0 )
		return dot;
	if ( npth == k && k > 1)
		return slash;
	if (i > 1){
	        for (; path[--i] == '/';--npth) {
      	        	path[i] = '\0';
        	}
	}
	if ((npth > 0 ) ) { 
                return path + pathtab[npth -1]  + 1;
        }
        else { 
                return path;
        }

}

int main(int argc, char *argv[])
{
	char ss[1000];
	char tt[1000];
	char vv[1000];
	char *s = ss;
	char *t = tt;
	char *v = vv;

	strcpy(s, argv[1]);
	strcpy(t, argv[1]);
	strcpy(v, argv[1]);
	
	s = mybasename(s); 
	t = mydirname(t);
	v = dirname(v); 
	printf("mybasename %s\n", s); 
	printf("mydirname %s\n", t);
	printf("dirname %s\n", v);

	return 0;
}

