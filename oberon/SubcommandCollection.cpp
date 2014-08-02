/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#include "SubcommandCollection.hpp"

#include "GenericHelpSubcommand.hpp"

#include <cassert>

namespace
{
  namespace po = boost::program_options;

  const bool INCLUDE_HIDDEN = true;
  const bool DO_NOT_RESTRICT = false;

  const std::string HELP_SUBCOMMAND_KEY = "help";
} // namespace


namespace oberon {

//----------------------------------------------------------------------------------------------------------------------
  SubcommandCollection::SubcommandCollection() :
    registrationsFinalised_(false)
  {

  }

//----------------------------------------------------------------------------------------------------------------------
  void SubcommandCollection::finaliseRegistrations()
  {
    assert( ! registrationsFinalised_ && "Attempt to close registrations twice!");
    assert( ! subcommandFactory_.hasRegistration(HELP_SUBCOMMAND_KEY) && "Attempt to finalise with help already added!");
    std::vector<std::string> subcommandNames = subcommandFactory_.registeredIndexes();
    auto helpCreator = [subcommandNames]()
    {
      return SubcommandPtr( new GenericHelpSubcommand(subcommandNames) );
    }; // lambda

    subcommandFactory_.registerCreator(HELP_SUBCOMMAND_KEY, helpCreator);

    registrationsFinalised_ = true;
  }

//----------------------------------------------------------------------------------------------------------------------
  void SubcommandCollection::add(const std::string& key,
                                 SubcommandCollection::SubcommandCreator creatorMethod)
  {
    if ( registrationsFinalised_ )
    {
      throw std::runtime_error("Attempt to register subcommand: " + key + ", after registrations were closed");
    }

    subcommandFactory_.registerCreator(key, creatorMethod);
  }

//----------------------------------------------------------------------------------------------------------------------
  std::vector<SubcommandCollection::SubcommandPtr> SubcommandCollection::allSubcommands()
  {
    std::vector<SubcommandPtr> subcommands;
    for (auto index : subcommandFactory_.registeredIndexes())
    {
      subcommands.push_back( subcommandFactory_.get(index) );
    }
    return subcommands;
  }

//----------------------------------------------------------------------------------------------------------------------
  SubcommandCollection::SubcommandPtr SubcommandCollection::getSubcommand(const std::string& subcommandName)
  {
    return subcommandFactory_.get(subcommandName);
  }

//----------------------------------------------------------------------------------------------------------------------
  bool SubcommandCollection::exists(const std::string& subcommandName)
  {
    return subcommandFactory_.hasRegistration(subcommandName);
  }

//----------------------------------------------------------------------------------------------------------------------
  std::vector<std::string> SubcommandCollection::allSubcommandKeys()
  {
    return subcommandFactory_.registeredIndexes();
  }

//----------------------------------------------------------------------------------------------------------------------
  po::options_description SubcommandCollection::allUniqueOptions()
  {
    po::options_description allUniqueOptions;
    for (SubcommandPtr& subcommand : allSubcommands() )
    {
      allUniqueOptions.add(subcommand->uniqueOptions(INCLUDE_HIDDEN, DO_NOT_RESTRICT));

      /** Have to make a local here as program_options returns const&'s and the temporary explodes in a range based for */
      std::vector<boost::shared_ptr<po::option_description> > subcommandSharedOptions = subcommand->sharedOptions(DO_NOT_RESTRICT).options();
      for ( boost::shared_ptr<po::option_description> option : subcommandSharedOptions )
      {
        std::vector<boost::shared_ptr<po::option_description> > allRawOptions = allUniqueOptions.options();
        auto result = std::find_if(allRawOptions.begin(),
                                   allRawOptions.end(),
                                   [&option](boost::shared_ptr<po::option_description> o) {return o->long_name() == option->long_name();});
        if ( result == allRawOptions.end() )
        {
          allUniqueOptions.add(option);
        }
      }
    }

    return allUniqueOptions;
  }

//----------------------------------------------------------------------------------------------------------------------

} // namespace
