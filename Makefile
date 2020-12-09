make:src/codesim.cpp
	g++ src/codesim.cpp -lclang -o src/codesim
test:src/codesim
	./src/codesim testcases/test1.cpp testcases/test2.cpp
clean:
	rm src/codesim