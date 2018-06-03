#include "../internal/internal.h"
#include<stdlib.h>
#include<stdarg.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);

struct stream {
	char unget;
	char *pos;
	FILE *fp;
};

int safe_getc(struct stream* stream)
{
	char unget;
	if (stream->fp == NULL) return *(stream->pos++);
	if (unget == '\0') return getchar(stream->fp);
	
	unget = stream->unget;
	stream->unget = '\0';
	return unget;
}

void safe_ungetc(char c, struct stream *stream)
{
	if (stream->fp == NULL) *(--stream->pos) = c;
	else stream->unget = c;
}

int read_int(struct stream *stream, int *x)
{
	char buf[BUFSIZ];
	char *pos = buf;

	while (isdigit(*pos++ = safe_getc(stream)));
	safe_ungetc(*--pos, stream);

	*x = strtoll(buf, NULL, 10);

	return pos - buf;
}

int _scanf_inter(FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{
	const char *p = NULL;

	struct stream stream;
	stream.unget = '\0';
	stream.pos = str;
	stream.fp = fp;

	for (p = fmt; *p; ++p) {
		if (*p != '%') continue;

		++p;
		do { // Allocate a new loop-block in order to allow re-entry to the switch-case using `continue`
			switch (*p) {
			case 'd':
				read_int(&stream, va_arg(ap, int *));
				break;
			}
			break;
		} while (1);
	}

	if (fp && stream.unget != '\0') --fp->rp;
}
