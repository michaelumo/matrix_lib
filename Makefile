all: install
	cd sample;make

clean:
	$(RM) *~ *.o;
	cd sample; make clean

install:
	cp matrix.h $(HOME)/include/matrix.h

uninstall:
	rm $(HOME)/include/matrix.h

