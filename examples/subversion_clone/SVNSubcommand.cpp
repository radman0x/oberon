/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "SVNSubcommand.hpp"

#include "oberon/OptionPrinter.hpp"

#include <sstream>


namespace
{
  namespace po = boost::program_options;

  const bool EXCLUDE_HIDDEN = false;

} // namespace


namespace svnclone
{
//----------------------------------------------------------------------------------------------------------------------
  SVNSubcommand::SVNSubcommand(const std::string& name,
                               const std::string& usageDescription,
                               const oberon::OptionCollection& sharedOptions,
                               const oberon::OptionCollection& globalOptions,
                               const std::vector<std::string>& sharedOptionsPresent) :
    /** shared options are stored in the base */
    Subcommand(name, usageDescription, sharedOptions),
    globalSVNOptions_(globalOptions),
    sharedOptionNames_(sharedOptionsPresent)
  {
    /** The programmer is responsible for passing in the right names */
    for ( auto option : sharedOptionNames_)
    {
      assert( (sharedOptions.exists(option)) && "Option specified does not exist in shared set" );
    }
  }

//----------------------------------------------------------------------------------------------------------------------
  std::string SVNSubcommand::usageDescription() const
  {
    std::ostringstream out;
    oberon::OptionPrinter allPrinter(allOptions(), positionalOptions());
    out << "Subcommand: " << name_ << std::endl << std::endl
        << commandUsageDescription_ << std::endl << std::endl
        << "USAGE: " << name_ << " " << allPrinter.usage() << std::endl;

    if ( uniqueOptions(false).options().size() > 0 || sharedOptionNames_.size() > 0)
    {
      out << std::endl << "Valid options: " << std::endl
          << uniqueOptions(EXCLUDE_HIDDEN)
          << sharedOptions_.getOptions(sharedOptionNames_);
    }

    if ( globalSVNOptions_.size() > 0 )
    {
      out << std::endl << "Global options: " << std::endl;
      out << globalSVNOptions_.allOptions() << std::endl;
    }

    return out.str();
  }

//----------------------------------------------------------------------------------------------------------------------
  boost::program_options::options_description SVNSubcommand::sharedOptions(bool enableRestrictions) const
  {
    return Subcommand::sharedOptions(enableRestrictions).add( globalSVNOptions_.allOptions(enableRestrictions) );
  }

//----------------------------------------------------------------------------------------------------------------------


} // namespace
