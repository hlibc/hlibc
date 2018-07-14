#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	// these tests are derived from the dietlibc and glibc ones --cmg
	char *c;
	char *s;

	if(strtoll(s="123",&c,0)==123 && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s="123" ,&c,0)==123)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s="+123",&c,0)==123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s="+123",&c,0)==123)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s="  123",&c,0)==123 && c==s+5)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s=" 123 ",&c,0)==123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtoll(s="   -17",&c,0)==-17 && c==s+6)printf("worked\n");else printf("failed\n"); 

	if(strtol(s="0123",&c,0)==0123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0123a",&c,0)==0123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="01239",&c,0)==0123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x123",&c,0)==0x123 && c==s+5)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="-0x123",&c,0)==-0x123 && c==s+6)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x0xc",&c,0)==0 && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtol(s=" +0x123fg",&c,0)==0x123f && c==s+8)printf("worked\n");else printf("failed\n"); 

	if(strtol(s="123",&c,16)==0x123 && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x123",&c,16)==0x123 && c==s+5)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="123",&c,8)==0123 && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0123",&c,8)==0123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0123",&c,10)==123 && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x123",&c,10)==0 && c==s+1)printf("worked\n");else printf("failed\n"); 
printf("half\n");
	if(strtol(s="abcd",&c,16)==0xabcd && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="AbCd",&c,16)==0xabcd && c==s+4)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0xABCD",&c,16)==0xabcd && c==s+6)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0Xabcd",&c,16)==0xabcd && c==s+6)printf("worked\n");else printf("failed\n"); 

	if(strtol(s="0xyz",&c,35)==33*35+34 && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="yz!",&c,36)==34*36+35 && c==s+2)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="-yz",&c,36)==-(34*36 + 35) && c==s+3)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="GhI4",&c,20)==((16*20 + 17)*20 + 18)*20 + 4 && c==s+4)printf("worked\n");else printf("failed\n"); 

#if LONG_MAX == 0x7fffffff
	if(strtol(s="2147483647",&c,0)==2147483647 && c==s+10 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="2147483648",&c,0)==2147483647 && c==s+10 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="214748364888",&c,0)==2147483647 && c==s+12 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="2147483650",&c,0)==2147483647 && c==s+10 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	/* glibc will actually fail this because they don't set errno to 0
	 * when returning 0x8000000 in non-failure cases. */
	if(strtol(s="-2147483648",&c,0)==0x80000000 && c==s+11 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="-2147483649",&c,0)==0x80000000 && c==s+11 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x1122334455z",&c,16)==2147483647 && c==s+12 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
#else
	if(strtol(s="9223372036854775807",&c,0)==9223372036854775807 && c==s+19 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="9223372036854775808",&c,0)==9223372036854775807 && c==s+19 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="922337203685477580777",&c,0)==9223372036854775807 && c==s+21 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="9223372036854775810",&c,0)==9223372036854775807 && c==s+19 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 




	if(strtol(s="-9223372036854775808",&c,0)==0x8000000000000000 && c==s+20 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="-9223372036854775809",&c,0)==0x8000000000000000 && c==s+20 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0x112233445566778899z",&c,0)==9223372036854775807 && c==s+20 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtol(s="0xFFFFFFFFFFFF00FF",&c,0)==9223372036854775807 && c==s+18 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
#endif
printf("strtoul\n");
	if(strtoul(s="  0",&c,0)==0 && c==s+3)printf("worked\n");else printf("failed\n"); 
 
#if LONG_MAX == 0x7fffffff
	if(strtoul(s="-0xfedcba98",&c,0)==0x01234568 && c==s+11 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtoul(s="0xf1f2f3f4f5",&c,0)==0xffffffff && c==s+12 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtoul(s="-0x123456789",&c,0)==0xffffffff && c==s+12 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
#else
	if(strtoul(s="0xffffffffffffffffg",&c,0)==0xffffffffffffffff && c==s+18 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtoul(s="-0xfedcba987654321",&c,0)==0xf0123456789abcdf && c==s+18 && errno==0)printf("worked\n");else printf("failed\n"); 
	if(strtoul(s="0xf1f2f3f4f5f6f7f8f9",&c,0)==0xffffffffffffffff && c==s+20 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
	if(strtoul(s="-0x123456789abcdef01",&c,0)==0xffffffffffffffff && c==s+20 && errno==ERANGE)printf("worked\n");else printf("failed\n"); 
#endif

	if(strtoul(s="0x,",&c,0)==0 && c==s+1)printf("worked\n");else printf("failed\n"); 

	return 0;
}
