includes()
{
	sed -i 's|gstdio.h|stdio.h|g' $@
	sed -i 's|gstdout|stdout|g' $@
	sed -i 's|gstdin|stdin|g' $@

}
includes $@




to()
{
	sed -i 's|GFILE|FILE|g' $1
  sed -i 's|gdprintf|dprintf|g' $@
  sed -i 's|gfclose|fclose|g' $@
  sed -i 's|gfeof|feof|g' $@
  sed -i 's|gferror|ferror|g' $@
  sed -i 's|gfflush|fflush|g' $@
  sed -i 's|gfgetc|fgetc|g' $@
  sed -i 's|gfgets|fgets|g' $@
  sed -i 's|gfileno|fileno|g' $@
#  sed -i 's|g_fillbuf|_fillbuf|g' $@
#  sed -i 's|g_flushbuf|_flushbuf|g' $@
  sed -i 's|gfopen|fopen|g' $@
  sed -i 's|gfprintf|fprintf|g' $@
  sed -i 's|gfputc|fputc|g' $@
  sed -i 's|gfputs|fputs|g' $@
  sed -i 's|gfread|fread|g' $@
  sed -i 's|gfseek|fseek|g' $@
  sed -i 's|gfwrite|fwrite|g' $@
#  sed -i 's|ggetc|getc|g' $@
  sed -i 's|ggetchar|getchar|g' $@
  sed -i 's|ggetdelim|getdelim|g' $@
  sed -i 's|ggetline|getline|g' $@
  sed -i 's|gpclos|pclose|g' $@
  sed -i 's|gpopen|popen|g' $@
  sed -i 's|gprintf|printf|g' $@
  sed -i 's|gputchar|putchar|g' $@
  sed -i 's|gsetbuf|setbuf|g' $@
  sed -i 's|gsetlinebuf|setlinebuf|g' $@
  sed -i 's|gsetvbuf|setvbuf|g' $@
  sed -i 's|gsnprintf|snprintf|g' $@
  sed -i 's|gsprintf|sprintf|g' $@
  sed -i 's|gvdprintf|vdprintf|g' $@
  sed -i 's|gvfprintf|vfprintf|g' $@
  sed -i 's|gvprintf|vprintf|g' $@
  sed -i 's|gvsnprintf|vsnprintf|g' $@
  sed -i 's|gvsprintf|vsprintf|g' $@
}

#to $@

from()
{
dprintf
fclose
feof
ferror
fflush
fgetc
fgets
fileno
_fillbuf
_flushbuf
fopen
fprintf
fputc
fputs
fread
fseek
fwrite
getc
getchar
getdelim
getline 
pclose
popen
printf 
putchar 
setbuf
setlinebuf
setvbuf
snprintf
sprintf
vdprintf
vfprintf
vprintf
vsnprintf
vsprintf
}
