
#include "parsers/parsers.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <regex>
#include <cstdlib>
//#include <unistd.h>
#include <cassert>

using namespace std;
using namespace dreport;

int main(int argc, char const* argv[])
{

    //char buff[300];
    //auto r = getcwd(buff, 300);
    //char reslp[300];
    //auto r2 = realpath(__FILE__, reslp);

    //std::cout 
    //<< __FILE__  << '\n'
    //<< r << '\n'        
    //<< r2 << '\n'        
    //<< std::endl;
    //assert(r2 != NULL);

    regex re{R"((.*?/)\w+$)"};
    smatch m;

    std::cout 
        << boolalpha << regex_match(string(argv[0]), m, re)
        << "\nsize: " << m.size()
        << "\nresult: " << m[1]
        << std::endl;

    string entry = m[1].str() + "files/file_1.cpp";
    CppLexer lex{entry};
    unique_ptr<Token> tk = lex.next_token();
    while (tk->tag() != Tag::T_EOF) {
        tk = lex.next_token();
    }

    lex.next_token();
    std::cout << "file: " << entry  << ", "
        << lex.lineno() 
        << " lines" << ", "
        << lex.empty_lines()
        << " empty lines" << ", "
        << lex.comment_lines()
        << " comment lines."
        << std::endl;

    return 0;
}
