#!/bin/sh

libtoolize --force \
	&& autoheader \
	&& aclocal \
	&& autoconf \
	&& automake --add-missing --foreign --copy \
	&& ./configure $@
