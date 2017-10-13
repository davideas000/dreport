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

#include "parsers/parsers.h"

#include <iostream>
#include <iomanip>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace dreport;

int main( int argc, char **argv )
{


    path p = ".";
    if (argc > 1) {
        p = argv[1];
    }

    recursive_directory_iterator it(p);

    unsigned int files_n = 0;
    unsigned int dir_n = 0;
    unsigned int cpp_n = 0; // number of cpp files
    unsigned int h_n = 0; // header
    unsigned int py_n = 0;
    unsigned int makefile_n = 0;
    unsigned int tupfile_n = 0;

    unsigned int total_lines = 0;
    unsigned int total_empty_lines = 0;
    unsigned int total_comment_lines = 0;

    std::cout << "path: " << p << "size: " << p.size() << std::endl;

    vector< tuple<string, int, int, int> > file_metrics; /*comment not a commet line*/

    for (auto& entry : it) {

        std::cout << entry.path().filename() << std::endl;

        if (entry.path().string()[p.size() + 1] == '.') {
            continue;
        }
        //if (it.level() == 10 || entry.path().string()[0] == '.') {
        //it.pop();
        //}


        //std::cout << entry << std::endl; // ====

        if (!is_directory(entry)) {
            ++files_n;
        }
        else {
            //std::cout << "directory " << entry << " level: " << it.level() << std::endl; // ====
            ++dir_n;
            continue;
        }

        if (entry.path().extension() == ".cpp" || entry.path().extension() == ".c"
                || entry.path().extension() == ".cc") {
            ++cpp_n;

            CppLexer lex{entry.path().string()};
            //std::cout << entry << std::endl; // ====
            //std::cout << "new LEXER" << std::endl; // ====

            unique_ptr<Token> tk = lex.next_token(); // ====

            //std::cout << tk.get() << std::endl; // ====

            while (tk->tag() != Tag::T_EOF) {
                tk = lex.next_token();
            }
            lex.next_token();

            auto files_metrics = make_tuple(entry, lex.lineno(), lex.empty_lines(), 
                    lex.comment_lines());

            total_lines += lex.lineno();
            total_empty_lines += lex.empty_lines();
            total_comment_lines += lex.comment_lines();

            std::cout << "file: " << entry  << ", "
                << lex.lineno() 
                << " lines" << ", "
                << lex.empty_lines()
                << " empty lines" << ", "
                << lex.comment_lines()
                << " comment lines.\n"
                ;
            //<< std::endl;

            //std::cout << "main===============" << std::endl; // ====
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

    std::cout << '\n'
        << dir_n << " directories.\n" 
        << files_n << " files.\n" 
        << cpp_n << " source files.\n" 
        << h_n << " header files.\n"
        << py_n << " python files.\n"
        << tupfile_n << " Tupfile files.\n"
        << "total number of lines of code: " << total_lines << '\n'
        << "total number of empty lines: " << total_empty_lines << '\n'
        << "total number of comment lines: " << total_comment_lines << '\n'
        << std::endl;

    return 0;
}

