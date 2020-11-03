#include "codesim.hpp"

struct Node {
    int kind;
    bool mark;
};
struct sub_str {
    int begin1;
    int begin2;
    int length;
};
vector<Node> vec1, vec2;

int main(int argc, char *argv[]) {
    bool verbose = false;
    if(argc == 2 && (strcmp(argv[1], "--help")==0 || strcmp(argv[1], "-h")==0)) {
        cout << "usage: codesim [-v|--verbose] [-h|--help] code1 code2" << endl;
        return 0;
    }
    else if(argc == 4 && (strcmp(argv[1], "--verbose")==0 || strcmp(argv[1], "-v")==0)) {
        // cout << "verbose!" << endl;
        verbose = true;
        // return 0;
    }
    else if(argc != 3) {
        cerr << "type codesim [-h|--help] for help" << endl;
        exit(-1);
    }
     
    Codesim *codesim = new Codesim(verbose);
    // cout << argv[1] << " " << argv[2] << endl;
    if(argc == 3) {
        codesim->parse_file(argv[1], argv[2]);
    }
    else {
        codesim->parse_file(argv[2], argv[3]);
    }
    codesim->gst();
    codesim->cal_sim();
    return 0;
}

Codesim::Codesim(bool verbose) {
    this->verbose = verbose;
}

void Codesim::parse_file(char *filename_1, char *filename_2) {
    file1 = filename_1;
    file2 = filename_2;
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(index, filename_1, nullptr, 0, nullptr, 0, CXTranslationUnit_None);
    if (unit == nullptr) {
        cerr << "Unable to parse files" << filename_1 <<" !" << endl;
        exit(-1);
    }
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, 
    [](CXCursor c, CXCursor parent, CXClientData client_data)
    {
        // cout << clang_getCursorKind(c) << " " << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '" << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
        Node temp;
        temp.kind = clang_getCursorKind(c);
        temp.mark = false;
        vec1.push_back(temp);
        return CXChildVisit_Recurse;
    },
    nullptr);

    index = clang_createIndex(0, 0);
    unit = clang_parseTranslationUnit(index, filename_2, nullptr, 0, nullptr, 0, CXTranslationUnit_None);
    if (unit == nullptr) {
        cerr << "Unable to parse files" << filename_2 <<" !" << endl;
        exit(-1);
    }
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
    cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, 
    [](CXCursor c, CXCursor parent, CXClientData client_data)
    {
        // cout << clang_getCursorKind(c) << " " << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '" << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
        Node temp;
        temp.kind = clang_getCursorKind(c);
        temp.mark = false;
        vec2.push_back(temp);
        return CXChildVisit_Recurse;
    },
    nullptr);
    // cout << "Success !" << endl;
}

void Codesim::gst() {
    int min_match = 2;
    long int max_match = min_match;
    long int count = 0;
    vector<sub_str> matches;
    while(true) {
        for(int i = 0; i < vec1.size(); i++) {
            if(vec1[i].mark ==true) {
                continue;
            }
            int j = 0;
            for(; j < vec2.size(); j++) {
            if(vec2[j].mark == true) {
                continue;
            }
            if(j == vec2.size()) {
                break;
            }
            count = 0;
            while(vec1[i].mark == false && vec2[j].mark == false && vec1[i+count].kind == vec2[j+count].kind) {
                count++;
            }
            if(count >= max_match) {
                if(count > max_match) {
                    matches.clear();
                    max_match = count;
                }
                sub_str temp;
                temp.begin1 = i;
                temp.begin2 = j;
                temp.length = count;
                matches.push_back(temp);
            }
            }
        }
        if(max_match == min_match) {
            break;
        }
        for(int i = 0; i < matches.size(); i++) {
            for(int j = 0; j < matches[i].length; j++) {
                vec1[matches[i].begin1+j].mark = true;
                vec2[matches[i].begin2+j].mark = true;
            }
        }
        matches.clear();
        max_match = min_match;
        count = 0;
    }
}

void Codesim::cal_sim() {
    long int length1 = 0, length2 = 0;
    if(verbose) {
        cout << file1 << ": ";
    }
    for(int i = 0; i < vec1.size(); i++) {
        if(verbose) {
            cout << "kind: " << vec1[i].kind << " mark: " << vec1[i].mark << " ";
        }
        if(vec1[i].mark) {
            length1++;
        }
    }
    if(verbose) {
        cout << endl << file2 << ": ";
    }
    for(int i = 0; i < vec2.size(); i++) {
        if(verbose) {
            cout << "kind: " << vec2[i].kind << " mark: " << vec2[i].mark << " ";
        }
        if(vec2[i].mark) {
            length2++;
        }
    }
    if(verbose) {
        cout << endl;
    }
    // float res = (length1*1.0)/vec1.size() > (length2*1.0)/vec2.size() ? (length1*1.0)/vec1.size() : (length2*1.0)/vec2.size();
    float res = (length1*1.0+length2*1.0)/(vec1.size()+vec2.size());
    // cout << file1 << ":" << (length1*1.0)/vec1.size() << endl;
    // cout << file1 << ":" << (length2*1.0)/vec2.size() << endl;
    cout << res << endl;
}