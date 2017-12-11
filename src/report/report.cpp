#include "report/report.h"
#include "parsers/parsers.h"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace boost::filesystem;
using namespace dreport;

Report::Report()
:files_n(0),
dir_n(0),
cpp_n(0), // number of cpp files
h_n(0), // header
other_n(0),

total_code_lines(0),
total_empty_lines(0),
total_comment_lines(0)
{
}

void Report::run(const boost::filesystem::path &p) {
  boost::filesystem::recursive_directory_iterator it(p);
  // std::cout << "running tests -- " << p << '\n'; // ====

  for (auto& entry : it) {

    if (entry.path().string()[p.size() + 1] == '.') {
      continue;
    }

    if (!is_directory(entry)) {
      ++files_n;
    }
    else {
      ++dir_n;
      continue;
    }

    if (entry.path().extension() == ".cpp" || entry.path().extension() == ".c"
    || entry.path().extension() == ".cc") {
      ++cpp_n;
      print_file_metrics(entry.path().string());
    }
    else if (entry.path().extension() == ".h" || entry.path().extension() == ".hpp") {
      print_file_metrics(entry.path().string());
      ++h_n;
    }
    else {
      ++other_n;
    }
  }

  std::cout
  << dir_n << " directories.\n"
  << files_n << " files.\n"
  << cpp_n << " source files.\n"
  << h_n << " header files.\n"
  << other_n << " other files.\n"
  << "\ntotal number of code lines: " << total_code_lines << '\n'
  << "total number of empty lines: " << total_empty_lines << '\n'
  << "total number of comment lines: " << total_comment_lines << '\n'
  << std::endl;
}

void Report::print_file_metrics(const std::string &entry) {

  CppLexer lex{entry};

  unique_ptr<Token> tk = lex.next_token();

  while (tk->tag() != Tag::T_EOF) {
    tk = lex.next_token();
  }
  lex.next_token();

  total_code_lines += lex.lineno();
  total_empty_lines += lex.empty_lines();
  total_comment_lines += lex.comment_lines();

  std::cout << "file: " << entry  << "\n  "
  << lex.lineno()
  << " lines" << "\n  "
  << lex.empty_lines()
  << " empty lines" << "\n  "
  << lex.comment_lines()
  << " comment lines.\n" << std::endl;

}
