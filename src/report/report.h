#ifndef DREPORT_REPORT_H
#define DREPORT_REPORT_H

#include "parsers/parsers.h"
#include <boost/filesystem.hpp>

namespace dreport {
  class Report {

  public:
    Report();
    void run(const boost::filesystem::path &p);
    /*
    * \brief parse files and print metrics
    */
    void print_file_metrics(const std::string &entry);

  private:
    unsigned int files_n;
    unsigned int dir_n;
    unsigned int cpp_n; // number of cpp files
    unsigned int h_n; // number of header
    unsigned int other_n; // number of header

    unsigned int total_code_lines;
    unsigned int total_empty_lines;
    unsigned int total_comment_lines;
  };
} /* namespace dreport */

#endif
