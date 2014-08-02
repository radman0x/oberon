/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "SVNAdd.hpp"

#include "oberon/Utils.hpp"


namespace
{
  namespace po = boost::program_options;

} // namespace


namespace svnclone
{
  const std::string SVNAdd::NAME = "add";

//----------------------------------------------------------------------------------------------------------------------
  SVNAdd::SVNAdd(const oberon::OptionCollection& sharedSVNOptions,
                 const oberon::OptionCollection& globalSVNOptions) :
    SVNSubcommand(SVNAdd::NAME,
                  "add: Put files and directories under version control, scheduling\n"
                  "them for addition to repository.  They will be added in next commit.",
                  sharedSVNOptions,
                  globalSVNOptions,
                  {"targets", "depth", "quiet", "non-recursive", "force", "no-ignore", "auto-props", "no-auto-props"})
  {

  }

//----------------------------------------------------------------------------------------------------------------------
  po::options_description SVNAdd::uniqueOptions(bool includeHidden, bool enableRestrictions) const
  {
    po::options_description returnOptions;
    returnOptions.add_options()
      ("parents", "Add intermediate parents");

    if ( includeHidden )
    {
      returnOptions.add_options()
        // not required because --targets (from the shared options) can be passed instead
        ("paths", po::value<std::vector<std::string> >(), "Paths indicating files to be added");
    }

    return returnOptions;

  }

//----------------------------------------------------------------------------------------------------------------------
  po::positional_options_description SVNAdd::positionalOptions() const
  {
    po::positional_options_description positional;
    positional.add("paths", -1);
    return positional;

  }

//----------------------------------------------------------------------------------------------------------------------
  void SVNAdd::checkOptionConsistency(boost::program_options::variables_map vm) const
  {
    if ( ! vm.count("paths") && ! vm.count("targets") )
    {
      throw oberon::CommandLineParsingError("svn: E205001: Not enough arguments provided, need paths or --targets",
                                            SVNAdd::NAME);
    }
    else if ( vm.count("paths") && vm.count("targets") )
    {
      throw oberon::CommandLineParsingError("Only one of either paths or --targets may be specified",
                                            SVNAdd::NAME);
    }
  }

//----------------------------------------------------------------------------------------------------------------------

} // namespace


