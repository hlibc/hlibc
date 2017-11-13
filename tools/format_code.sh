#!/usr/bin/env sh

# README
# ======
#
# This script formats all .{c,h} files according to the
# style configuration defined in .clang-format at the root
# of the project. In order to run this, you need to have
# the utility 'clang-format' installed.
#
# Some versions of 'clang-format' may support more recent
# directives described in the configuration file, but they
# have been commented out for compatibility reasons.
#
# One additional feature of this utility is that it can
# apply more advanced "checks" (and/or formatting rules)
# that are available in the 'clang-tidy' tool. TODO.

# CONFIG
# ======

HERE=$(dirname $0) # consistent relative paths
ROOT="$HERE/.."    # project root (relative is fine)
DIRS="$ROOT/hlibc" # space-separated list of directories to format

# CHECKS
# ======

command -v clang-format >/dev/null 2>&1 || { \
	echo >&2 "ERROR: 'clang-format' not found."; \
	exit 1;
}

[ -f $ROOT/.clang-format ] || { \
	echo >&2 "ERROR: '$ROOT/.clang-format' not found."; \
	exit 1;
}

# FORMAT
# ======

for f in $DIRS; do
	echo "Processing '$f'..."
	find $f -type f -name "*.h" | xargs clang-format -i;
	find $f -type f -name "*.c" | xargs clang-format -i;
done;
