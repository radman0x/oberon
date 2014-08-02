/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "SVNCommit.hpp"

#include "oberon/Utils.hpp"


namespace
{
  namespace po = boost::program_options;

} // namespace


namespace svnclone
{
  const std::string SVNCommit::NAME = "commit";

//----------------------------------------------------------------------------------------------------------------------
  SVNCommit::SVNCommit(const oberon::OptionCollection& sharedSVNOptions,
                       const oberon::OptionCollection& globalSVNOptions) :
    SVNSubcommand(SVNCommit::NAME,
                  "commit (ci): Send changes from your working copy to the repository.\n"
                  "\n"
                  "  A log message must be provided, but it can be empty.  If it is not\n"
                  "  given by a --message or --file option, an editor will be started.\n"
                  "  If any targets are (or contain) locked items, those will be\n"
                  "  unlocked after a successful commit.",
                  sharedSVNOptions,
                  globalSVNOptions,
                 {"targets", "depth", "quiet", "non-recursive", "editor-cmd", "with-revprop", "changelist"})
  {

  }

//----------------------------------------------------------------------------------------------------------------------
  po::options_description SVNCommit::uniqueOptions(bool includeHidden, bool enableRestrictions) const
  {
    po::options_description returnOptions;
    returnOptions.add_options()
      ("message,m", po::value<std::string>(), "specify log message ARG")
      ("file,F", po::value<std::string>(), "read log message from file ARG")
      ("no-unlock", "don't unlock the targets")
      ("force-log", "force validity of log message source")
      ("keep-changelists", "don't delete changelists after commit");


    if ( includeHidden )
    {
      returnOptions.add_options()
        // not required because --targets (from the shared options) can be passed instead
        ("paths", po::value<std::vector<std::string> >(), "Paths indicating files to be added");
    }

    return returnOptions;

  }

//----------------------------------------------------------------------------------------------------------------------
  po::positional_options_description SVNCommit::positionalOptions() const
  {
    po::positional_options_description positional;
    positional.add("paths", -1);
    return positional;

  }

//----------------------------------------------------------------------------------------------------------------------
  void SVNCommit::checkOptionConsistency(boost::program_options::variables_map vm) const
  {
    if ( ! vm.count("paths") && ! vm.count("targets") )
    {
      throw oberon::CommandLineParsingError("svn: E205001: Not enough arguments provided, need paths or --targets",
                                            SVNCommit::NAME);
    }
    else if ( vm.count("paths") && vm.count("targets") )
    {
      throw oberon::CommandLineParsingError("Only one of either paths or --targets may be specified",
                                            SVNCommit::NAME);
    }

  }

//----------------------------------------------------------------------------------------------------------------------
} // namespace
