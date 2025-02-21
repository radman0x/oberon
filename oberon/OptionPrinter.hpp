/***********************************************************************************************************************
**         __________              ___                              ________                                          **
**         \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______        **
**          |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/        **
**          |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \         **
**          |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \        **
**                 \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/         **
**                                                         2012                                                       **
***********************************************************************************************************************/

#ifndef OBERON_OPTIONPRINTER_HPP
#define OBERON_OPTIONPRINTER_HPP

#include "CustomOptionDescription.hpp"

namespace oberon {

//**********************************************************************************************************************
  /** Utility class that accepts program options descriptions and allows printing of nicely formatted information
   */
  class OptionPrinter
  {    
  public: // static
    static void printStandardAppDesc(const std::string& appName,
                                     std::ostream& out,
                                     boost::program_options::options_description desc,
                                     boost::program_options::positional_options_description positionalDesc=boost::program_options::positional_options_description());

    static void printSingleLineUsageDescription(const std::string& appName,
                                                std::ostream& out,
                                                boost::program_options::options_description desc,
                                                boost::program_options::positional_options_description positionalDesc=boost::program_options::positional_options_description());

    static void formatRequiredOptionError(boost::program_options::required_option& error);

  public: // interface
    OptionPrinter() = default;
    OptionPrinter(boost::program_options::options_description desc,
                  boost::program_options::positional_options_description positionalDesc=boost::program_options::positional_options_description());


    /** Print the single line application usage description */
    std::string usage();

    std::string positionalOptionDetails();
    std::string optionDetails();

  private: // data
    void addOption(const CustomOptionDescription& optionDesc);

    std::vector<CustomOptionDescription> options_;
    std::vector<CustomOptionDescription> positionalOptions_;

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // OBERON_OPTIONPRINTER_HPP
