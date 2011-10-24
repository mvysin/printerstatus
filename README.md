PrinterStatus
=============

Seen those pictures around the web with printers asking for coins, moar
BBQ sauce, paper jams in non-existent locations, or plans for world domination?

This is a very simple C++ console application that will let you set the
message to whatever you want.  All you need is:

* A printer with a LCD message display (most HP business-class LaserJets have them)
* The IP address or hostname of the printer (sorry, USB printers won't cut it)
* An active imagination

Requirements
------------

This application is designed for Windows 2000 and above. It supports IPv4 and IPv6.

To compile this program you will need Visual Studio (a 2010 solution is included) or
other compatible Windows compiler.

Compiling
---------

Compile this application on Windows. I have included a Visual Studio 2010 project
to facilitate this process, it supports 32-bit and 64-bit configurations.  I have
also made this as self-contained as possible, so it should work with other compilers.

Minor changes would be necessary to get this to compile on Linux; if demand is there
I can make the code more portable.

Usage
-----

Invoke the program from the command line as follows:

    printerstatus [IP Address or Hostname] "Your Message"
    printerstatus 192.168.1.20 "INSERT COIN"
    printerstatus UpstairsBW "NEED MOAR BBQ SAUCE"

Test it first; the printers I have used have 2 rows of 20 characters each, the printer
will wrap lines for you.  For a multiple-line message, you'll have to manually align it
as follows:

    printerstatus 192.168.1.20 "REPLACE BBQ SAUCE   TO CONTINUE JOB"

Other Uses
----------

I have tried to write this program in a straightforward manner. If you are a Windows
programmer looking for basic "getting started" with WinSock, this program could be a
good beginning example.

Ideas
-----

Go have fun! Some ideas that were successful in the past include:

* REPLACE BBQ SAUCE
* REPLACE YELLOW TONER (on a B&W printer)
* PAPER JAM IN LEFT SIDE DOOR (on a printer with no left door)
* INSERT COIN

This is confirmed to work on HP LaserJet 9050 and HP LaserJet 4700 printers.

