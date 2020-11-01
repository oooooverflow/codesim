#include "codesim.hpp"


// ostream& operator<<(ostream& stream, const CXString& str)
// {
//   stream << clang_getCString(str);
//   clang_disposeString(str);
//   return stream;
// }

vector<int> vec1, vec2;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Please input 2 filename which will be detedted !" << endl;
    exit(-1);
  }
  
  if(parse_file(argv[1], argv[2])) {
    cout << "success !" << endl;
  }
  else {
    cerr << "Unable to parse translation unit. Quitting." << endl;
    exit(-1);
  }
  // for(vector<int>::iterator iter=vec1.begin(); iter!=vec1.end(); iter++) {
  //   cout << *iter << endl;
  // }
  string str1, str2;
  for(vector<int>::iterator iter=vec1.begin(); iter!=vec1.end(); iter++) {
    if(iter != vec1.begin()) {
      str1 += ' ';
    }
    str1 += to_string(*iter);
  }
  for(vector<int>::iterator iter=vec2.begin(); iter!=vec2.end(); iter++) {
    if(iter != vec2.begin()) {
      str2 += ' ';
    }
    str2 += to_string(*iter);
  }
  cout << str1 << endl;
  cout << str2 << endl;


}

bool parse_file(char *filename_1, char *filename_2) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(index, filename_1, nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (unit == nullptr) {
    return false;
  }
  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
  CXCursor cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(cursor, 
  [](CXCursor c, CXCursor parent, CXClientData client_data)
  {
    // cout << clang_getCursorKind(c) << " " << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '" << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
    vec1.push_back(clang_getCursorKind(c));
    return CXChildVisit_Recurse;
  },
  nullptr);

  index = clang_createIndex(0, 0);
  unit = clang_parseTranslationUnit(index, filename_2, nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (unit == nullptr) {
    return false;
  }
  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
  cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(cursor, 
  [](CXCursor c, CXCursor parent, CXClientData client_data)
  {
    // cout << clang_getCursorKind(c) << " " << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '" << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
    vec2.push_back(clang_getCursorKind(c));
    return CXChildVisit_Recurse;
  },
  nullptr);
  return true;
}

float gst() {
  
}