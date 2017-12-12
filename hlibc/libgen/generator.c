#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <time.h>

char *_generator(char *path, int lever)
{
        size_t i          = 0;
	int pathtab[4096];
        size_t npth       = 0;
	size_t k          = 0;
	
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
	if (lever) /* basename */
	{
		if (i > 1){
		        for (; path[--i] == '/';--npth) {
      		        	path[i] = '\0';
	        	}
		}
		if ((npth > 0 ) ) { 
	                return path + pathtab[npth -1]  + 1;
	        } 
	}else { /* dirname */
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
	}
        return path; 

}

char *dirname(char *path)
{
	return _generator(path, 0);
}

char *basename(char *path)
{
	return _generator(path, 1);
}
