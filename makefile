PREFIX=
DESTDIR=/usr
CC=gcc
CFLAGS+= -shared
LIB_NAME=$(shell pwd | rev | cut -d'/' -f1 | rev )

help:
	@echo "available cmd are make help|install|uninstall|clean"
	@echo "available args:"
	@echo "    LIB_NAME current \"${LIB_NAME}\""
	@echo "    CC current \"${CC}\""
	@echo "    DESTDIR current \"${DESTDIR}\""
	@echo "    PREFIX current \"${PREFIX}\""

lib%.so: %.c
	${CC} -o $@ $^ ${CFLAGS}

install: lib${LIB_NAME}.so
	install ${LIB_NAME}.h ${DESTDIR}/${PREFIX}/include
	install lib${LIB_NAME}.so ${DESTDIR}/${PREFIX}/lib

uninstall:
	rm -f ${DESTDIR}/${PREFIX}/include/${LIB_NAME}.h
	rm -f ${DESTDIR}/${PREFIX}/lib/lib${LIB_NAME}.so

clean:
	rm lib${LIB_NAME}.so
