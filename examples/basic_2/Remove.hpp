/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2014                                                      **
***********************************************************************************************************************/

#ifndef REMOVE_HPP
#define REMOVE_HPP

#include "oberon/Subcommand.hpp"
#include "oberon/OptionCollection.hpp"

namespace basic
{
//**********************************************************************************************************************
  /** Create a derived class of Subcommand and fill in the relevant pieces
   *
   * Only 1-2 methods need to be defined here for a basic setup and they are basically just setting up blocks of
   * Boost.Program_options descriptions and returning them.
   */
  class Remove : public oberon::Subcommand
  {
  public: // interface
    Remove(oberon::OptionCollection sharedOptions) :
      oberon::Subcommand("remove", "remove a character from the provided string", sharedOptions)
    {
      /** **/
    }

    boost::program_options::options_description uniqueOptions(bool includeHidden, bool enableRestrictions) const
    {
      boost::program_options::options_description returnOptions;
      returnOptions.add_options()
          ("no-collapse,N", "The character is removed but a space is left where it was in the string");

      return returnOptions;
    }

    boost::program_options::positional_options_description positionalOptions() const
    {
      /** Now that we have share positional options it is necessary to specify where they should appear in the command
       *  line for this subcommand. Note here that you as the programmer 'know' the names of the shared options that
       *  will be present for this subcommand. This in not the best but works just fine in practice.
       */
      boost::program_options::positional_options_description positional;
      positional.add("targetChar", 1);
      positional.add("inputString", 1);
      return positional;
    }

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // REMOVE_HPP
