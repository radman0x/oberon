/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#ifndef SVNCLONE_SVNADD_HPP
#define SVNCLONE_SVNADD_HPP

#include "SVNSubcommand.hpp"

#include "boost/program_options.hpp"

#include <vector>
#include <string>

namespace svnclone
{
//**********************************************************************************************************************
  class SVNAdd : public SVNSubcommand
  {
  public: // static interface
    static const std::string NAME;

  public: // interface
    SVNAdd(const oberon::OptionCollection& sharedSVNOptions,
           const oberon::OptionCollection& globalSVNOptions);

    /** @name Inherited from Subcommand
     */
    //@{
      boost::program_options::options_description uniqueOptions(bool includeHidden, bool enableRestrictions) const override;
      boost::program_options::positional_options_description positionalOptions()                             const override;

      /** add can accept either positional paths or the --targets option, so we need to check for this meta dependency */
      void checkOptionConsistency(boost::program_options::variables_map vm) const override;
    //@}

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // SVNCLONE_SVNADD_HPP
