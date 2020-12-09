#include <iostream>
#include <clang-c/Index.h>
#include <vector>
#include <cstring>

using namespace std;

class Codesim {
    private:
        long int min_match = 5;
        string file1, file2;
        bool verbose;

    public:
        Codesim(bool verbose);
        void parse_file(char *filename_1, char *filename_2);
        void gst();
        void cal_sim();
};