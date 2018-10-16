LIBS = -lm
a: a.c
	if [ ! -e bmp.c ] ; then wget coconut.sys.eng.shizuoka.ac.jp/bmp/bmp.c ; fi
	if [ ! -e bmp.h ] ; then wget coconut.sys.eng.shizuoka.ac.jp/bmp/bmp.h ; fi
	gcc a.c bmp.c $(LIBS)
