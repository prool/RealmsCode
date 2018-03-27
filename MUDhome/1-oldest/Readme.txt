*** RoH - 2.47e ***

RoH is based off of Mordor (3.0/4.06/4.66/5.05). http://mordor.nazgul.com/

**********************************************
                 License
**********************************************
Please see License.txt for licence information.

***********************************************
               Setup/Install
***********************************************

You'll need at least the following libraries to compile
and run the mud.  I've listed package names as you'll find them on
debian/ubuntu but they should be available with some variation of the name
for any other linux/unix distribution.  The mud runs fine on both 32bit and
64bit systems and has in the past worked with Cygwin.  It compiles with a
few warnings, but no errors on gcc-4.7.2.  It may work with some tweaking on
macos.

Required Libraries:
libxml2-dev, zlib-dev, libaspell-dev, libpspell-dev, libboost-dev, 
libboost-python3-dev, python3-dev 

Other requirements:
You'll need a compiler that supports C++11 such as g++ 4.6 or 4.7. 
(Intel's icc compiler and clang will also work if you modify the compiler file)

1) Extract the archive to wherever you'd like it

2) Modify the Paths namespace (around line 672) in src-2.47e/config.cpp if desired, 
   otherwise they'll default to using relative paths.

3) Modify config/config.xml if so desired.

4) Modify/Add dms to the dmname struct in global.cpp, or use the default
"Admin".  Be sure the last item in the list is a NULL.

5) Install required libraries and compile the mud

6) run realms.exe

7) Login with "Admin/dm.pass1" or create your own DM - The default password
for creating a DM is in the config.xml

**********************************************
                    Other
**********************************************

If you have any problems, questions  or comments feel free to email me at bane /at/
rohonline.net or post on forums.rohonline.net under the non-game discussion
forum.  We haven't kept a running list of the features of the mud, it's on
the list of things to do!  Browse through the help, dmhelp, and bhelp folders 
for the helpfiles which, while slightly out of date, should give a more or less
accurate portrayal of what's going on.

The codebase originally started out in c, and has slowly been converted over
to c++.  As we update new things we've been moving them over, but there
still remains some straggling c code that we haven't had a chance to modify
yet.

Feel free to modify the login screen but please leave our credits
visible in some form. 

The latest changes to the codebase can be found at:
http://github.com/mitchej123/RealmsCode

We've included Oceancrest (from stock mordor) converted to be used with
roh's xml areas.

