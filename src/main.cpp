
/**
 * \file
 *
 * \brief main function
 * \details inicialize the program
 * \author David Endrew
 * \version 1.0
 * \date Last modifiede: 2017 Jan 22
 * \pre First initialize the system.
 * \warning Improper use can crash your application
 * \copyright GNU Public License.
 */

#include "console_colors/console_colors.hpp"
#include "parsers/parsers.h"

#include <iostream>
#include <iomanip>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace console_colors;
using namespace dreport;

int main( int argc, char **argv )
{

    path p = ".";
    recursive_directory_iterator it(p);
    //std::cout << it.lenght() << std::endl;
    //for ( ; it != end(it); it++) {
    unsigned int count = 0;
    unsigned int cpp_n = 0; // number of cpp files
    unsigned int h_n = 0; // header
    unsigned int py_n = 0;
    unsigned int makefile_n = 0;
    unsigned int tupfile_n = 0;

    for (auto& entry : it) {

        if (it.level() == 10) {
            it.pop();
        }

        //std::cout << entry << ", " << it.level() 
        //<< ", extension: " << entry.path().extension() 
        //<< std::endl;
        ++count;

        if (entry.path().extension() == ".cpp" || entry.path().extension() == ".c"
                || entry.path().extension() == ".cc") {
            ++cpp_n;
            CppLexer lex{entry.path().string()};
            unique_ptr<Token> tk = lex.next_token();
            while (tk->tag() != Tag::T_EOF) {
                //std::cout << tk.get() << std::endl;
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
            std::cout << "main===============" << std::endl;
            break;
            //std::cout << blue << "source " << reset << entry.path().string() << std::endl;
        }
        else if (entry.path().extension() == ".h" || entry.path().extension() == ".hpp") {
            ++h_n;
            //std::cout << yellow << "header " << reset << entry << std::endl;
        }
        else if (entry.path().extension() == ".py") {
            ++py_n;
            //std::cout << yellow << "python " << reset << entry << std::endl;
        }
        else if (entry.path().filename() == "Makefile" || entry.path().filename() == "makefile") {
            ++makefile_n;
            //std::cout << yellow << "makefile " << reset << entry << std::endl;
        }
        else if (entry.path().filename() == "Tupfile") {
            ++tupfile_n;
            //std::cout << yellow << "makefile " << reset << entry << std::endl;
        }
    }

    std::cout << count << " files.\n" 
        << cpp_n << " source files.\n" 
        << h_n << " header files.\n"
        << py_n << " python files.\n"
        << tupfile_n << " Tupfile files.\n"
        << std::endl;

    return 0;
}
