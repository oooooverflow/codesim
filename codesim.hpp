#include <iostream>
#include <clang-c/Index.h>
#include <vector>
#include <cstring>

using namespace std;

class Codesim {
    private:
        // struct Node {
        //     int kind;
        //     bool mark;
        // };
        // struct sub_str {
        //     int begin1;
        //     int begin2;
        //     int length;
        // };
        // vector<Node> vec1, vec2;
        long int min_match = 2;
        string file1, file2;
        bool verbose;

    public:
        Codesim(bool verbose);
        void parse_file(char *filename_1, char *filename_2);
        void gst();
        void cal_sim();
};

// bool parse_file(char *filename_1, char *filename_2);
// void gst();