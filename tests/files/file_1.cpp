#include <iostream>
#include <cstring>
#include <algorithm>
#include <regex>

using namespace std;

int main(int argc, char const* argv[])
{
    //regex re{R"((.*?/)\w+$)"};
    smatch m;

    std::cout 
        << boolalpha << regex_match(string(argv[0]), m, re)
        << "\nsize: " << m.size()
        << "\nresult: " << m[1]
    << std::endl;
    /*for (int i = strlen(argv[0]) - 1; i > 0; --i) {
    std::cout << argv[0][i] << std::endl;
    if (argv[0][i] == '/') {
    break;
    }
    }*/

    //return 0;
}

