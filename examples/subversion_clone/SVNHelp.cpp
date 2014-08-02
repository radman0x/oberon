/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "SVNHelp.hpp"

namespace
{
  namespace po = boost::program_options;

} // namespace


namespace svnclone
{
  const std::string SVNHelp::NAME = "help";

//----------------------------------------------------------------------------------------------------------------------
  SVNHelp::SVNHelp(const oberon::OptionCollection& sharedSVNOptions,
                   const oberon::OptionCollection& globalSVNOptions) :
    SVNSubcommand(SVNHelp::NAME,
                  "help (?, h): Describe the usage of this program or its subcommands.",
                  sharedSVNOptions,
                  globalSVNOptions,
                  std::vector<std::string>())
  {

  }

//----------------------------------------------------------------------------------------------------------------------
  po::options_description SVNHelp::uniqueOptions(bool includeHidden, bool enableRestrictions) const
  {
    po::options_description returnOptions;

    if ( includeHidden )
    {
      returnOptions.add_options()
        ("topic", po::value<std::vector<std::string> >(), "Topic to display help for");
    }

    return returnOptions;

  }

//----------------------------------------------------------------------------------------------------------------------
  po::positional_options_description SVNHelp::positionalOptions() const
  {
    po::positional_options_description positional;
    positional.add("topic", -1);
    return positional;

  }

//----------------------------------------------------------------------------------------------------------------------


} // namespace
