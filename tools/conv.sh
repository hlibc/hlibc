sed -i 's|GFILE|FILE|g' $1

sed -i 's|gprintf|printf|g' $1

sed -i 's|gsprintf|sprintf|g' $1

sed -i 's|gfprintf|vprintf|g' $1

sed -i 's|gputs|puts|g' $1

sed -i 's|gputc|putc|g' $1

sed -i 's|gfgets|fgets|g' $1

sed -i 's|gfwrite|fwrite|g' $1

sed -i 's|gfread|fread|g' $1

sed -i 's|gdprintf|dprintf|g' $1




