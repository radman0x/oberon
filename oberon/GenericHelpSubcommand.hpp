/***********************************************************************************************************************
**         __________              ___                              ________                                          **
**         \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______        **
**          |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/        **
**          |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \         **
**          |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \        **
**                 \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/         **
**                                                         2014                                                       **
***********************************************************************************************************************/

#ifndef OBERON_GENERICHELPSUBCOMMAND_HPP
#define OBERON_GENERICHELPSUBCOMMAND_HPP

#include "Subcommand.hpp"

#include <vector>
#include <string>

namespace oberon {

//**********************************************************************************************************************
  class GenericHelpSubcommand : public Subcommand
  {
  public: // interface
    GenericHelpSubcommand(const std::vector<std::string>& availableTopics);

    /** @name Inherited from Subcommand
     */
    //@{
      boost::program_options::options_description uniqueOptions(bool includeHidden, bool enableRestrictions) const override;
      boost::program_options::positional_options_description positionalOptions() const override;
      std::string usageDescription() const override;
    //@}

   private: // data
    std::vector<std::string> helpTopics_;

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // OBERON_GENERICHELPSUBCOMMAND_HPP
