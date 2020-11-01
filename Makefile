make:codesim.cpp
	g++ codesim.cpp -lclang -o codesim
test:codesim
	./codesim
clean:
	rm codesim