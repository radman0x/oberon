/***********************************************************************************************************************
**         __________              ___                              ________                                          **
**         \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______        **
**          |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/        **
**          |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \         **
**          |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \        **
**                 \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/         **
**                                                         2014                                                       **
***********************************************************************************************************************/

#include "GenericHelpSubcommand.hpp"

namespace
{
  namespace po = boost::program_options;

} // namespace

namespace std
{
  std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& sv)
  {
    auto first = true;
    for (const auto& s : sv)
    {
      out << first ? " " + s : s;
      first = false;
    }
    return out;

  }

} // namespace

namespace oberon {

//----------------------------------------------------------------------------------------------------------------------
  GenericHelpSubcommand::GenericHelpSubcommand(const std::vector<std::string>& availableTopics) :
    Subcommand("help", "display help for other subcommand(s)"),
    helpTopics_(availableTopics)
  {

  }

//----------------------------------------------------------------------------------------------------------------------
  po::options_description GenericHelpSubcommand::uniqueOptions(bool includeHidden, bool enableRestrictions) const
  {
    po::options_description returnOptions;

    if ( includeHidden )
    {
      returnOptions.add_options()
        ("topic", getOptionValue<std::vector<std::string>>(enableRestrictions), "Topic to display help for, can be "
                                                                                "specified multiple times");
    }

    return returnOptions;
  }

//----------------------------------------------------------------------------------------------------------------------
  po::positional_options_description GenericHelpSubcommand::positionalOptions() const
  {
    po::positional_options_description positional;
    positional.add("topic", -1);
    return positional;

  }

//----------------------------------------------------------------------------------------------------------------------
  std::string GenericHelpSubcommand::usageDescription() const
  {
    std::ostringstream temp;
    temp << Subcommand::usageDescription();
    temp << "Available Topics:" << std::endl;
    for (auto subcommandName : helpTopics_)
    {
      temp << "\t" << subcommandName << std::endl;
    }

    return temp.str();
  }

//----------------------------------------------------------------------------------------------------------------------

} // namespace
