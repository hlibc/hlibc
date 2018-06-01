#include "../internal/internal.h"
#include<stdlib.h>
#include<stdarg.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);

struct stream {
	char *buf;
	char *pos;
	FILE *fp;
};

int safe_read(struct stream* stream)
{
	if (stream->fp == NULL) return 0;
	stream->pos = stream->buf;
	return fread(stream->buf, 1, BUFSIZ, stream->fp);
}

int read_int(struct stream* stream, int *x)
{
	if (*stream->pos == '\0') return 0;

	char *old_pos = stream->pos;

	int distance = 0;

 	int x_;
	int log10;

	*x = strtoll(stream->pos, &stream->pos, 10);

	distance += stream->pos - old_pos;
	if (*stream->pos == '\0') {
		safe_read(stream);

		log10 = read_int(stream, &x_);
		distance += log10;
		for (; log10 > 0; --log10) *x *= 10;

		x += x_;
	}

	return distance;
}

int _scanf_inter(FILE *fp, char *str, size_t lim, int flag, const char *fmt, va_list ap)
{
	char buffer[BUFSIZ + 1];
	buffer[BUFSIZ] = '\0';

	const char *p = NULL;

	struct stream stream;
	stream.buf = (str != NULL) ? str : buffer;
	stream.pos = 0;
	stream.fp = fp;
	safe_read(&stream);

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
}
