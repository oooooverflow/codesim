make:codesim.cpp
	g++ codesim.cpp -lclang -o codesim
test:codesim
	./codesim test.cpp test1.cpp
clean:
	rm codesim