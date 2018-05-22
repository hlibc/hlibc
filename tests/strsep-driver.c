#include <string.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char ** argv)
{
    char	*token,	*string, *tofree;

    tofree = string = strdup("abc,def,ghi");
    assert(string != NULL);

    while ((token = strsep(&string, ",")) != NULL)
        printf("%s\n", token);

    free(tofree);

    return 0;
}
