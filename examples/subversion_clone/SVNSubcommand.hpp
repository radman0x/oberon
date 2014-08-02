/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2013                                                      **
***********************************************************************************************************************/

#ifndef SVNCLONE_SVNSUBCOMMAND_HPP
#define SVNCLONE_SVNSUBCOMMAND_HPP

#include "oberon/Subcommand.hpp"
#include "oberon/OptionCollection.hpp"

#include "boost/shared_ptr.hpp"

#include <vector>
#include <string>

namespace svnclone
{
//**********************************************************************************************************************
  /** Class that defines how to implement an SVN style subcommand
   *
   * The main addition of functionality that this provides is handling for global options
   */
  class SVNSubcommand : public oberon::Subcommand
  {
  public: // interface
    SVNSubcommand(const std::string& name,
                  const std::string& usageDescription,
                  const oberon::OptionCollection& sharedOptions,
                  const oberon::OptionCollection& globalOptions,
                  const std::vector<std::string>& sharedOptionsPresent);

    /** @name Inherited from Subcommand
     */
    //@{
      /** Custom printing so we can look very close to the real subversion application */
      std::string usageDescription() const override;

      /** Need to override this so can make sure that the global options are included when extracting shared options */
      boost::program_options::options_description sharedOptions(bool enableRestrictions) const override;
    //@}

  protected: // data;
    /** Commands that appear in every svn subcommand */
    oberon::OptionCollection globalSVNOptions_;

    /** All subversion commands are given the pool of shared options from which they can then select the ones that they
     *  use. Take the names in the constructor and store them here so the correct options can be extracted whenever desired
     */
    std::vector<std::string> sharedOptionNames_;

  }; // class

//**********************************************************************************************************************

} // namespace

#endif // SVNCLONE_SVNSUBCOMMAND_HPP
