#!/bin/sh

set -xe

sed_minus_i()
{
	# sed -i is not in posix, so emulate it for conveniece
	TMPFILE=temp
	cp $2 "$TMPFILE"
	sed "$1" "$TMPFILE" > $2
	rm "$TMPFILE"
}


text2htmlsh()
{
	FILE=$1
	printf '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"> <pre>\n' > ${FILE}.html
	cat $FILE >> ${FILE}.html
	printf '</pre>\n' >> ${FILE}.html
	# mark up directories
	sed_minus_i 's/\([a-Z,0-9,/,-,.,_]*\/\)$/<a href="&">&<\/a>/g' ${FILE}.html
	# mark up hyper links
	sed_minus_i 's/\(http.*\)/<a href="&">&<\/a>/g' ${FILE}.html
	# mark up mailing links
	sed_minus_i 's/\([a-Z,0-9,.,-]*@.*\)/<a href="mailto:&">&<\/a>/g' ${FILE}.html
	# If the title occurs on the first line then make it attr strong
	sed_minus_i 's/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl><strong>&<\/strong><\/dl><pre>/' ${FILE}.html
	# mark up anything that does not begin with a tab
	sed_minus_i 's/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl>&<\/dl><pre>/g' ${FILE}.html
	# mark up underlines
	sed_minus_i 's/\(^[^\t]-.*\)/<\/pre><dd><hr\/><\/dd><pre>/g' ${FILE}.html
	# mark up images
	sed_minus_i 's/\([a-Z,0-9,\/,.,-]*.png\)/<\/pre><dl><img src="&" style="float:left;height:15em;margin-right:1em"><\/img><pre><\/dl>/g' ${FILE}.html
}


text2htmlsh $1


