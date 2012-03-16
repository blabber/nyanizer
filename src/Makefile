PROG=		nyanizer

WARNS?=		5
CC?=		clang

CFLAGS=		-I/usr/local/include/ImageMagick
LDFLAGS=	-L/usr/local/lib 
LDADD=		-lMagickWand -lMagickCore

NO_MAN=		YES

.include <bsd.prog.mk>
