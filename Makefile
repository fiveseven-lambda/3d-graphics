a: a.cpp
#	if [ ! -e bmp.c ] ; then wget coconut.sys.eng.shizuoka.ac.jp/bmp/bmp.c ; fi
#	if [ ! -e bmp.h ] ; then wget coconut.sys.eng.shizuoka.ac.jp/bmp/bmp.h ; fi
	g++ a.cpp bmp.cpp
clean:
	rm a.out *.bmp
