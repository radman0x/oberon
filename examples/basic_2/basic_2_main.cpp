/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2014                                                      **
***********************************************************************************************************************/

#include "Remove.hpp"
#include "Randomise.hpp"

#include "oberon/Subcommand.hpp"
#include "oberon/SubcommandCollection.hpp"
#include "oberon/SubcommandCLI.hpp"
#include "oberon/Utils.hpp"

#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"


namespace
{
  namespace po = boost::program_options;

  const int SUCCESS = 0;
  const int FAILURE = 1;

  const std::string APPLICATION_USAGE = "Application that can manipulate one character in a string in a couple of ways";

} // namespace

/** NOTE: This example builds upon basic_1, if you don't understand some parts refer to the first part for clarification */

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
  /** Now that we have more than one subcommand it makes sense to share the options that are duplicated between them.
   *  The options are defined here and then referenced inside the subcommand if they are positional
   */
  oberon::OptionCollection sharedOptions;
  sharedOptions.addArgOption<std::string>("inputString", "String for the application to operate on", true);
  sharedOptions.addArgOption<char>("targetChar", "Character type to operate on within the string", true);

  oberon::SubcommandCollection subcommands;
  subcommands.add( "remove",    [=]() { return std::unique_ptr<basic::Remove>( new basic::Remove(sharedOptions) ); } );
  subcommands.add( "randomise", [=]() { return std::unique_ptr<basic::Randomise>( new basic::Randomise(sharedOptions) ); } );
  subcommands.finaliseRegistrations();

  /** Application level options are being added now as well, just an ultra basic version option
   */
  po::options_description mainDesc;
  mainDesc.add_options()
      ("version", "Display the version information for the application");

  oberon::SubcommandCLI subcommandApp = oberon::SubcommandCLI("CharManipulator",
                                                              APPLICATION_USAGE,
                                                              subcommands,
                                                              mainDesc); // pass the app level options

  try
  {
    oberon::SubcommandCLI::ParseOutput parseOutput = subcommandApp.parseCommandLine(argc, argv);
    po::variables_map parsedVars = parseOutput.vm();

    if ( boost::optional<std::string> subcommandNameOptional = parseOutput.subcommandUsed() )
    {
      std::string subcommandName = subcommandNameOptional.get();

      if ( subcommandName == "remove" )
      {
        std::string modified = parsedVars["inputString"].as<std::string>();
        char removeChar = parsedVars["targetChar"].as<char>();
        std::string replaceWith = parsedVars.count("no-collapse") ? " " : "";

        boost::algorithm::replace_all(modified, std::string(1, removeChar), replaceWith);
        std::cout << modified << std::endl;

      }
      else if ( subcommandName == "randomise" ) // processing for the randomise subcommand
      {
        std::string modified = parsedVars["inputString"].as<std::string>();
        char removeChar = parsedVars["targetChar"].as<char>();
        char replacementChar = basic::Randomise::getRandomChar(parsedVars);

        boost::algorithm::replace_all(modified, std::string(1, removeChar), std::string(1, replacementChar));
        std::cout << modified << std::endl;
      }
      else if ( subcommandName == "help" )
      {
        subcommandApp.displayHelp(parsedVars.count("topic") ?
                                     parsedVars["topic"].as< std::vector<std::string> >() :
                                        std::vector<std::string>(),
                                  std::cout);
      }
      else
      {
        assert(false && "Unrecognised subcommand used and it somehow got through parsing");
      }
    }
    else
    {
      if ( parsedVars.count("version") ) // act on the version option
      {
        std::cout << "Application Version: 0.1.0 - demo" << std::endl;
      }
      else
      {
        subcommandApp.displayHelp(boost::none, std::cout);
      }
    }

  }
  catch(oberon::CommandLineParsingError& e)
  {
    subcommandApp.displayParsingError(e, std::cout, std::cerr);
    return FAILURE;

  }

  return SUCCESS;

} // main

//----------------------------------------------------------------------------------------------------------------------
