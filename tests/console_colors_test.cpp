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

#include <iostream>
#include <iomanip>
#include <boost/filesystem.hpp>
#include "console_colors/console_colors.hpp"

using namespace std;
using namespace boost::filesystem;
using namespace console_colors;

int main( int argc, char **argv )
{

    //const std::string br_bg_balck = "\e[40;1m";
    //const std::string br_bg_red = "\e[41;1m";
    //const std::string br_bg_green = "\e[42;1m";
    //const std::string br_bg_yellow = "\e[43;1m";
    //const std::string br_bg_blue = "\e[44;1m";
    //const std::string br_bg_magenta = "\e[45;1m";
    //const std::string br_bg_cyan = "\e[46;1m";
    //const std::string br_bg_white = "\e[47;1m";

    //const std::string reset = "\e[0m";

    int padding = 15;
    cout << "\ntext colors:\n\n" << balck
        << std::left << std::setw(padding) << " balck " // << reset
        << red << std::left << std::setw(padding) << " red"
        << green << std::left << std::setw(padding) << " green "
        << yellow << std::left << std::setw(padding) << " yellow "
        << blue << std::left << std::setw(padding) << " blue "
        << magenta << std::left << std::setw(padding) << " magenta "
        << cyan << std::left << std::setw(padding) << " cyan "
        << white << std::left << std::setw(padding) << " white " << "\n"
        << br_black << std::left << std::setw(padding) << " br_black "
        << br_red << std::left << std::setw(padding) << " br_red "
        << br_green << std::left << std::setw(padding) << " br_green "
        << br_yellow << std::left << std::setw(padding) << " br_yellow "
        << br_blue << std::left << std::setw(padding) << " br_blue "
        << br_magenta << std::left << std::setw(padding) << " br_magenta "
        << br_cyan << std::left << std::setw(padding) << " br_cyan "
        << br_white << std::left << std::setw(padding) << " br_white " << "\n" << reset
        << "\n\nback ground colors:\n\n"// << br_white
        << bg_black << std::left << std::setw(padding) << " bg_balck "
        << bg_red << std::left << std::setw(padding) << " bg_red "
        << bg_green << std::left << std::setw(padding) << " bg_green "
        << bg_yellow << std::left << std::setw(padding) << " bg_yellow "
        << bg_blue << std::left << std::setw(padding) << " bg_blue "
        << bg_magenta << std::left << std::setw(padding) << " bg_magenta "
        << bg_cyan << std::left << std::setw(padding) << " bg_cyan "
        << bg_white << std::left << std::setw(padding) << " bg_white " // << reset << "\n" << bg_black
        //<< br_bg_balck << std::left << std::setw(padding) << " br_bg_balck "
        //<< br_bg_red << std::left << std::setw(padding) << " br_bg_red "
        //<< br_bg_green << std::left << std::setw(padding) << " br_bg_green "
        //<< br_bg_yellow << std::left << std::setw(padding) << " br_bg_yellow "
        //<< br_bg_blue << std::left << std::setw(padding) << " br_bg_blue "
        //<< br_bg_magenta << std::left << std::setw(padding) << " br_bg_magenta "
        //<< br_bg_cyan << std::left << std::setw(padding) << " br_bg_cyan "
        //<< br_bg_white << std::left << std::setw(padding) << " br_bg_white "
        << reset << "\n" << endl;

    //std::cout << "\e[97;93maaaaa\e[0m" << std::endl;
    //path p = ".";
    //recursive_directory_iterator it(p);
    ////std::cout << it.lenght() << std::endl;
    ////for ( ; it != end(it); it++) {
    //unsigned int count = 0;
    //for (auto& entry : it) {
    //std::cout << entry << ", " << it.level() << std::endl;
    //++count;
    //}

    //std::cout << count << " files." << std::endl;
    return 0;
}
