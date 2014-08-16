/***********************************************************************************************************************
**          __________              ___                              ________                                         **
**          \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**           |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**           |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**           |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                  \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                          2014                                                      **
***********************************************************************************************************************/

#include "Randomise.hpp"

#include "oberon/Utils.hpp"

#include "boost/random.hpp"

namespace
{
  void pushAll(const std::string& source, std::vector<char>& destination)
  {
    for (char character : source)
    {
      destination.push_back(character);
    }
  }
}

namespace basic
{
  const std::string NUMBERS = "0123456789";
  const std::string LOWER_CHARS = "abcdefghijklmnopqrstuvwxyz";
  const std::string UPPER_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const std::string SYMBOLS = "&[{}(=*)+]!#@$~"; // not all symbols but enough for the example

//----------------------------------------------------------------------------------------------------------------------
  char Randomise::getRandomChar(const boost::program_options::variables_map& vm)
  {
    assert(vm.count("with-lowerchar") || vm.count("with-upperchar") ||
           vm.count("with-numbers") || vm.count("with-symbols"));

    std::vector<char> randomSet;
    if ( vm.count("with-lowerchar") ) { pushAll(LOWER_CHARS, randomSet); }
    if ( vm.count("with-upperchar") ) { pushAll(UPPER_CHARS, randomSet); }
    if ( vm.count("with-numbers") )   { pushAll(NUMBERS, randomSet); }
    if ( vm.count("with-symbols") )   { pushAll(SYMBOLS, randomSet); }

    typedef boost::uniform_int<> UniformDist;
    UniformDist distribution(0, randomSet.size()-1);
    typedef boost::mt19937 BaseRandomNumberGenerator;
    BaseRandomNumberGenerator generator;

    boost::variate_generator<BaseRandomNumberGenerator&,UniformDist> numberGenerator(generator, distribution);
    generator.seed( static_cast<uint32_t>(time(nullptr)) );

    return randomSet[ numberGenerator() ];
  }

//----------------------------------------------------------------------------------------------------------------------
  void Randomise::checkOptionConsistency(boost::program_options::variables_map vm) const
  {
    /** Here we just want to check if any characters were included for random generation, it is required that there be
     *  at least one. This type of verification is impossible with boost.Program_options so this facility was included.
     */
    if ( vm.count("with-lowerchar") || vm.count("with-upperchar") || vm.count("with-numbers") || vm.count("with-symbols") )
    {
      return; // all is well
    }
    else
    {
      throw oberon::CommandLineParsingError("No random replacement set selected! Must specify at least one of -Ccns",
                                            std::string("randomise") );
    }
  }

//----------------------------------------------------------------------------------------------------------------------

}
