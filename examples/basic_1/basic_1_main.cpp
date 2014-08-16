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

#include "oberon/Subcommand.hpp"
#include "oberon/SubcommandCollection.hpp"
#include "oberon/SubcommandCLI.hpp"
#include "oberon/Utils.hpp"

#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"

#include <iostream>

namespace
{
  namespace po = boost::program_options;

  const int SUCCESS = 0;
  const int FAILURE = 1;

  const std::string APPLICATION_USAGE = "Application that can manipulate one character in a string in a couple of ways";

} // namespace


//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
  /** The first necessary step is to define the subcommands that will be used in the application. It is necessary for
   *  there to have been derived classes of oberon::Subcommand created with the relevent options previously so that can
   *  be added. for description of how to create a new subcommand check out Remove.hpp.
   */
  oberon::SubcommandCollection subcommands;
  subcommands.add( "remove", []() { return std::unique_ptr<basic::Remove>( new basic::Remove() ); } );
  subcommands.finaliseRegistrations(); // this adds a default help subcommand and is a pre condition before the collection
                                       // can be given to the SubcommandCLI

  /** create the subcommand based command line interface, just give it the desired subcommands and it's ready to go */
  oberon::SubcommandCLI subcommandApp = oberon::SubcommandCLI("CharManipulator", APPLICATION_USAGE, subcommands);

  /** From this point on the command line is being parsed and there is the risk of it not succeeding for various
   *  reasons. There is an exception type defined for oberon and this whole block is wrapped in a try to catch any errors
   */
  try
  {
    /** Do the initial parse of the command line */
    oberon::SubcommandCLI::ParseOutput parseOutput = subcommandApp.parseCommandLine(argc, argv);

    if ( boost::optional<std::string> subcommandNameOptional = parseOutput.subcommandUsed() )
    {
      po::variables_map parsedVars = parseOutput.vm(); // this is a second parsing step
      std::string subcommandName = subcommandNameOptional.get();

      if ( subcommandName == "remove" )
      {
        /** parsing succeeded and we know which subcommand we are dealing with. At this point you will have a
         *  boost.Program_options variables_map corresponding to the options specified in the Subcommand class. From
         *  here it is necessary to reference that option specification to know the names of the desired vars.
         */
        std::string modified = parsedVars["input"].as<std::string>();
        char removeChar = parsedVars["removeChar"].as<char>();
        std::string replaceWith = parsedVars.count("no-collapse") ? " " : "";

        boost::algorithm::replace_all(modified, std::string(1, removeChar), replaceWith);
        std::cout << modified << std::endl;

      }
      else if ( subcommandName == "help" )
      {
        /** If you look at the GenericHelpSubcommand you will see it takes infinite positional options for topic and
         *  this is given as a vector of strings. These are given to a helper function for display
         */
        subcommandApp.displayHelp(parsedVars.count("topic") ?
                                     parsedVars["topic"].as< std::vector<std::string> >() :
                                        std::vector<std::string>(),
                                  std::cout);
      }
      else
      {
        /** this is like the default case in a switch, basically we shouldn't be able to reach this point if everything
         *  was written correctly.
         */
        assert(false && "Unrecognised subcommand used and it somehow got through parsing");
      }
    }
    else
    {
      /** Use the same helper function as above but don't specify any topics to have the root level application usage
       *  description displayed
       */
      subcommandApp.displayHelp(boost::none, std::cout);
    }

  }
  catch(oberon::CommandLineParsingError& e)
  {
    /** Again a nice helper function for displaying the error along with usage for the subcommand or if one wasn't
     *  specified then the root level usage information
     */
    subcommandApp.displayParsingError(e, std::cout, std::cerr);
    return FAILURE;

  }

  return SUCCESS;

} // main

//----------------------------------------------------------------------------------------------------------------------
