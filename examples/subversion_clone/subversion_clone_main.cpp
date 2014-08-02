/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "AllSubversionSubcommands.hpp"

#include "oberon/SubcommandCollection.hpp"
#include "oberon/SubcommandCLI.hpp"
#include "oberon/Utils.hpp"

#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/range/algorithm/copy.hpp"

#include <iostream>
#include <string>
#include <algorithm>


namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

  namespace po = boost::program_options;

  const std::string descriptionString = "Subversion command-line imitator.\n"
                                        "Type 'svn_mimic help <subcommand>' for help on a specific subcommand.\n"
                                        "Type 'svn_mimic --version' to see the program version and RA modules\n"
                                        "  or 'svn_mimic --version --quiet' to see just the version number.\n"
                                        "\n"
                                        "Most subcommands take file and/or directory arguments, recursing\n"
                                        "on the directories.  If no arguments are supplied to such a\n"
                                        "command, it recurses on the current directory (inclusive) by default.\n";

  using namespace svnclone;
  template <typename T_SubcommandType>
  oberon::SubcommandCollection::SubcommandPtr getSVNSubcommand(const oberon::OptionCollection& sharedOptions,
                                                               const oberon::OptionCollection& globalOptions)
  {
    return oberon::SubcommandCollection::SubcommandPtr(new T_SubcommandType(sharedOptions, globalOptions));
  }

} // namespace

/** NOTE: This example builds upon basic_1 and basic_2, if you don't understand some parts refer to these for clarification */

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
  /** Subversion has a plethora of option of which there are a number of global options (present on every subcommand) and
   *  a pool of options that are used by one, two or more subcommands. Below we specify option sets for these.
   */
  oberon::OptionCollection sharedSubversionOptions;
  sharedSubversionOptions.addArgOption<std::string>("targets", "pass contents of file ARG as additional args");
  sharedSubversionOptions.addArgOption<std::string>("depth", "limit operation by depth ARG ('empty', 'files', 'immediates', or"
                                                    " 'infinity')");
  sharedSubversionOptions.addBasicOption("quiet", "print nothing, or only summary information", false, 'q');
  sharedSubversionOptions.addArgOption<std::string>("editor-cmd", "use ARG as external editor");
  sharedSubversionOptions.addArgOption<std::string>("with-revprop", "set revision property ARG in new revision "
                                                           "using the name[=value] format");
  sharedSubversionOptions.addArgOption<std::string>("changelist", "operate only on members of changelist ARG");
  sharedSubversionOptions.addBasicOption("non-recursive", "obsolete; try --depth=files or --depth=immediates", false, 'N');
  sharedSubversionOptions.addBasicOption("force", "force operation to run");
  sharedSubversionOptions.addBasicOption("auto-props", "enable automatic properties");
  sharedSubversionOptions.addBasicOption("no-auto-props", "disable automatic properties");
  sharedSubversionOptions.addBasicOption("no-ignore", "disregard default and svn:ignore property ignores");

  oberon::OptionCollection globalSubversionOptions;
  globalSubversionOptions.addArgOption<std::string>("username", "specify a username ARG");
  globalSubversionOptions.addArgOption<std::string>("password", "specify a password ARG");
  globalSubversionOptions.addArgOption<std::string>("config-dir", "read user configuration files from directory ARG");
  globalSubversionOptions.addArgOption<std::string>("config-option", "set user configuration option in the format:\n"
                                                                     "  FILE:SECTION:OPTION=[VALUE]\n"
                                                                     "For example:\n"
                                                                     "servers:global:http-library=serf");

  globalSubversionOptions.addBasicOption("no-auth-cache", "do not cache authentication tokens");
  globalSubversionOptions.addBasicOption("non-interactive", "do no interactive prompting");
  globalSubversionOptions.addBasicOption("trust-server-cert", "accept SSL server certificates from unknown\n"
                                                              "certificate authorities without prompting (but only\n"
                                                              "with '--non-interactive')");

  /** Here the subcommands implemented for this example are added to the collection, note that the default help is not
   *  used in favour of a custom help command. This is mainly to avoid the custom printing included with the default.
   *
   * Another interesting thing here is that the subcommands being added subclass SVNSubcommand instead of Subcommand
   * directly. This is so that the common special handling is handled without duplication. The additional implementation
   * in that base is mainly to help printing in a custom manner and handling the addition of a separate concept of
   * global options.
   */
  oberon::SubcommandCollection subversionSubcommands;
  subversionSubcommands.add( SVNAdd::NAME,    [=]() { return getSVNSubcommand<SVNAdd>   (sharedSubversionOptions, globalSubversionOptions); } );
  subversionSubcommands.add( SVNCommit::NAME, [=]() { return getSVNSubcommand<SVNCommit>(sharedSubversionOptions, globalSubversionOptions); } );
  subversionSubcommands.add( SVNHelp::NAME,   [=]() { return getSVNSubcommand<SVNHelp>  (sharedSubversionOptions, globalSubversionOptions); } );

  /** main options for the clone mirroring what is present in the real subversion application */
  po::options_description mainDesc;
  mainDesc.add_options()
      ("version", "Display the version information for the application")
      ("quiet",   "sub option for --version, just see the version number");

  /** Below is the (now familiar) standard parsing of the options and detection of subcommand to excute */
  oberon::SubcommandCLI svnCommandLineApp("subversion", descriptionString, subversionSubcommands, mainDesc);
  try
  {
    oberon::SubcommandCLI::ParseOutput parseOutput = svnCommandLineApp.parseCommandLine(argc, argv);
    if ( parseOutput.subcommandUsed() )
    {
      std::string subcommandName = parseOutput.subcommandUsed().get();
      std::cout << "Subcommand used = " << subcommandName << std::endl << std::endl;
      if      ( subcommandName == SVNAdd::NAME )
      {
        po::variables_map addParameters = parseOutput.vm();
        for ( auto val : addParameters )
        {
          std::cout << "Option Set -> " << val.first << std::endl;
        }
        std::cout << "Adding:" << std::endl;
        if ( addParameters.count("paths") )
        {
          for ( auto path : addParameters["paths"].as<std::vector<std::string> >() )
          {
            std::cout << path << std::endl;
          }
        }
        else // must have --targets
        {
          std::cout << "Contents of Targets File: " << addParameters["targets"].as<std::string>() << std::endl;
        }

      }
      else if ( subcommandName == SVNCommit::NAME )
      {
        po::variables_map addParameters = parseOutput.vm();
        for ( auto val : addParameters )
        {
          std::cout << "Option Set -> " << val.first << std::endl;
          std::cout << "Committing:" << std::endl;
          if ( addParameters.count("paths") )
          {
            for ( auto path : addParameters["paths"].as<std::vector<std::string> >() )
            {
              std::cout << path << std::endl;
            }
          }
          else // must have --targets
          {
            std::cout << "Contents of Targets File: " << addParameters["targets"].as<std::string>() << std::endl;
          }
        }

      }
      else if ( subcommandName == SVNHelp::NAME )
      {
        po::variables_map vm = parseOutput.vm();
        if ( vm.count("topic") )
        {
          svnCommandLineApp.displayHelp(vm.count("topic") ?
                                           vm["topic"].as< std::vector<std::string> >() :
                                              std::vector<std::string>(),
                                        std::cout);

        }
        else
        {
          std::cout << svnCommandLineApp.applicationUsage() << std::endl;
        }

      }

    }
    else
    {
      po::variables_map vm;
      po::store( po::parse_command_line(argc, argv, mainDesc), vm );
      po::notify(vm);

      if ( vm.count("version") )
      {
        if ( vm.count("quiet") )
        {
          std::cout << "1.7.5" << std::endl;
        }
        else
        {
          std::cout << "svn, version 1.7.5 (r1336830)\n"
                       "compiled Jun 21 2013, 22:18:20" << std::endl;
        }

      }
      else if ( vm.count("quiet") )
      {
        std::cout << "Subcommand argument required\n"
                     "Type 'svn help' for usage." << std::endl;
      }
      else
      {
        std::cout << "Type 'svn help' for usage." << std::endl;
      }

    }

  }
  catch(oberon::CommandLineParsingError& e)
  {
    svnCommandLineApp.displayParsingError(e, std::cout, std::cerr);
    return ERROR_IN_COMMAND_LINE;

  }

  return SUCCESS;

} // main

//----------------------------------------------------------------------------------------------------------------------
