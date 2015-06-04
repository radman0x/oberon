/***********************************************************************************************************************
**         __________              ___                              ________                                          **
**         \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______        **
**          |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/        **
**          |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \         **
**          |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \        **
**                 \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/         **
**                                                         2014                                                       **
***********************************************************************************************************************/

#include "ExceptionTranslater.hpp"

namespace
{
  namespace po = boost::program_options;

} // namespace


namespace oberon {

//----------------------------------------------------------------------------------------------------------------------
  boost::optional<CustomOptionDescription> locateOption(const std::string& optionName,
                                                        const po::options_description& options)
  {
    for ( auto option : options.options() )
    {
      CustomOptionDescription parsedOption(option);
      if ( parsedOption.requiredExceptionName_ == optionName )
      {
        return parsedOption;
      }
    }

    return boost::none;
  }

//----------------------------------------------------------------------------------------------------------------------

} // namespace
