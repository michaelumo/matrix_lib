current = sparsematrix.cpp

all:
	g++ -g3 -o sample main.cpp -I$(HOME)/include -std=gnu++11
	g++ -g3 -o quaternionSample quaternion.cpp -I$(HOME)/include -I../ -std=gnu++11
	g++ -g3 -o sparsematrix sparsematrix.cpp -I$(HOME)/include -I../ -std=gnu++11

clean:
	$(RM) sample *.o *~

e:
	vi $(current)

