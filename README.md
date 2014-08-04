

# README #

## Oberon - A Subcommand Program Options Library ##

Subcommands are an effective way of making a complex command line application easier to use. The essential idea is that the high level capabilities of the application are separated, each having their own distinct options and focussed purpose. Once an application reaches a certain amount of complexity it becomes exceedingly difficult to use without this separation.  Probably the most well known application to utilise this technique is Subversion (svn).

Oberon is built on top of Boost.Program_options, is available under the same MIT license as boost and is written in modern C++. I named it Oberon after a type of __sub__marine.

### Version ###


#### 0.7.0 ####

* First released version


## How to build? ##

Building of Oberon should be straightforward as it has only 1 external dependency and there are no complicated configuration steps. In order to build you will need to have a copy of [boost](http://www.boost.org) and I would recommend 1.55.0, although I would expect it to work with others. 

Generally when integrating a library into a project you already have a build tool that is being leveraged; make, cmake, premake, VisualStudio etc. If you are in this position then all you need to do is add the Oberon source code to your project and link and include the boost libraries through the mechanisms your build system provides. With this said I have included [premake](http://industriousone.com/what-premake) build files for easy building of the example code. To use it you will need to [download it](http://sourceforge.net/projects/premake/). See the wiki for further details... !need a link here!

## Contribution guidelines ##

Participation in the development of Oberon is encouraged and appreciated. The source code repository is curated by Conrad "radman" Mercer and additions will be reviewed before they appear in the public version of the code. Once other knowledgeable contributors are established this workload will be shared and the responsibility distributed.

## Who do I talk to? ##

There are a few sources of information available for Oberon:

+ [The Issue Tracker](https://bitbucket.org/radman/oberon/issues?status=new&status=open)
+ [The Wiki](https://bitbucket.org/radman/oberon/wiki/Home)
+ [www.radmangames.com](http://www.radmangames.com/oberon)
+ email: radman\[at\]radmangames.com
