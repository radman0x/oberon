/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2014                                                      **
***********************************************************************************************************************/

#ifndef RANDOMISE_HPP
#define RANDOMISE_HPP

#include "oberon/Subcommand.hpp"
#include "oberon/OptionCollection.hpp"

namespace basic
{
//**********************************************************************************************************************
  /** You will note that this is very similar to the Remove command with only the unique options different, this is by
   *  design and is aimed at making it easy to specify and organise subcommands.
   */
  class Randomise : public oberon::Subcommand
  {
  public: // statics
    /** Helper function to get a random character based upon the parsed arguments from the command line
     */
    static char getRandomChar(const boost::program_options::variables_map& vm);

  public: // interface
    Randomise(oberon::OptionCollection sharedOptions) :
      oberon::Subcommand("randomise", "randomise a character from the provided string", sharedOptions)
    {
      /** **/
    }

    boost::program_options::options_description uniqueOptions(bool includeHidden, bool enableRestrictions) const
    {
      /** Several options for specifying inclusion of different character to be put in the random pool for the
       *  replacement. See how nasty this would be without subcommand separation?
       */
      boost::program_options::options_description returnOptions;
      returnOptions.add_options()
        ("with-lowerchar,c", "Include lower case characters in the selection for random replacement")
        ("with-upperchar,C", "Include upper case characters in the selection for random replacement")
        ("with-numbers,n", "Include numbers in the selection for random replacement")
        ("with-symbols,s", "Include symbols in the selection for random replacement");

      return returnOptions;
    }

    boost::program_options::positional_options_description positionalOptions() const
    {
      boost::program_options::positional_options_description positional;
      positional.add("targetChar", 1);
      positional.add("inputString", 1);
      return positional;
    }

    /** This is a new addition, see the documentation for the method for a detailed description
     */
    void checkOptionConsistency(boost::program_options::variables_map vm) const;

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // RANDOMISE_HPP
