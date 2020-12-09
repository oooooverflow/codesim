make:src/codesim.cpp
	g++ src/codesim.cpp -lclang -o src/codesim
test:src/codesim
	./src/codesim test/test1.cpp test/test2.cpp
clean:
	rm src/codesim