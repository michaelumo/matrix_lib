all: install
	cd sample;make

clean:
	$(RM) *~ *.o;
	cd sample; make clean

install:
	cp matrix.h $(HOME)/include/matrix.h
	cp sparsematrix.h $(HOME)/include/sparsematrix.h

uninstall:
	rm $(HOME)/include/matrix.h
	rm $(HOME)/include/sparsematrix.h


