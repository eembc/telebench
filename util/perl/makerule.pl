# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

# Future development notes, standard packages.
#use File::Find;
##use dirtool; todo, replace with file::find

use subs qw /enum_dir dir_count add_tslash c_cppcmt_parse generate_rule scan_dep usage protect_quotes unprotect_quotes print_outputheader /;

=pod

=head1 NAME

makerule.pl - generates make file rules (dependency info) for C,C++, and 
              assembly language files with # comments.

=head1 SYNOPSIS

makerule <switches> <file specs>

    -?                    Dump usage help then exit ( -help also works)
    -I    <directory>     adds a directory to MAKERULE's include path
    -ix                   clear's (empties) MAKERULE's include path
    -p    <env variable>  Adds the contents of an environment variable
                          to MAKERULE's include path.  For example, when using
                          Microsoft compilers, the INCLUDE environment
                          variable contains the include path used by the
                          compiler.  Just use the -p switch to use it.
    -v                    Turns on the verbose flag. Turn verbose mode on
                          enabled on all kinds of messages.  Just try it.
                          Also, turning on the vebose flag turns the
                          quiet flag off.
    -v-                   Turns verbose mode off
    -q                    Enables quiet mode.  When being quiet, MAKERULE
                          only prints errors to STDERR.  Turning quiet mode
                          on implies that the verbose mode is turned off
    -q-                   Turns the quiet mode off
    -s                    Enables the processing of '#include <stdlib.h>'
                          include statements.  Normaly, MAKERULE ignores
                          'angle' include statements.
    -s-                   Turns off processing angle-bracket include statments
    -cq                   Places double quotes around obj or exe output files.
    -cq-                  Disables quoting.
    -co <obj output>      Enables generation of object file output statememts
                          in the rule generation. Used for compilers that do not support
                          $* directives. The obj output string is used to identify the output.
                          It is usually -o, but for VC++ it is -Fo. If using VC++ from gnu make,
                          the quoted string option should also be enabled -q.
    -cox                  Disables generation of object file output statements.
    -ce <exe output>      Enables generation of executable file output statememts
                          in the rule generation. Used for compilers that do not support
                          $* directives. The obj output string is used to identify the output.
                          It is usually -o. If using VC++ from gnu make,
                          the quoted string option should also be enabled -q.
    -cex                  Disables generation of executable file output statements.
    -r <recipe>           Sets the recipe to be placed after each rule.
                          NOTE: the recipe will have the dependant file appended, so
                          $* extensions are not needed.
    -rx                   Clears the current recipe.
    -tr <recipe>          Sets the recipe to be placed after each target rule.
                          NOTE: the recipe will have the dependant file appended, so
                          $^ extensions are not needed.
    -trx                  Clears the current target recipe.
    -ta <dependency)       Adds additional dependency to target. For example,
                          $(THOBJS) so that harness is built with benchmark.
    -tax                  clears the additional dependency targets.
    -a <dependency)       Adds additional dependency to the end of the
                          object.  For example, iterations.mak so that benchmarks 
                          are re-built when iterations change.                          benchmark.
    -ax                   clears the additional object dependencies.
    -ta <dependency)      Adds additional dependency to target. For example,
                          $(THOBJS) so that harness is built with benchmark.
    -tax                  clears the additional target dependencies.
    -ta <dependency)      Adds additional dependency to the end of the
                          target.  For example, $(THOBJS) so that harness is built with
                          benchmark.
    -tax                  clears the additional dependency targets.
    -te <library)         Adds additional dependency library to the end of the
                          target rule.  For example, $(THLIB) so that harness is linked as
                          a library, with $(THOBJS) as a dependency list.
    -tex                  clears the additional dependency library.
    -b <extension>        Sets the file extension of the target file
                          in the generated rules.  For example '-b .obj'
                          or '-b .o'.  The default is '.obj'
    -tb <extension>       Sets the file extension of the target executable file
                          in the generated rules.  For example '-tb .exe'
                          or '-tb .lib'.  The default is ''.
    -o <directory>        Sets the target directory used to generate each
                          rule.  For example, on NT systems it is common
                          to put objects in a 'debug' or 'release'
                          subdirectory.  Using '-o debug' cause targets such
                          as 'debug/foo.obj : foo.c' to be generated.  The
                          default is an empty string.
    -ox                   Clears the current target directory
    -to <directory>       Sets the target executable directory used to generate each
                          rule.  For example, it is common
                          to put executables in a bin directory
                          Using '-to bin' cause targets such
                          as 'bin/foos.exe : foos.o' to be generated.  The
                          default is an empty string.
    -tox                  Clears the current target executable directory
    -g <file name>        Ignore the specified include, or source file.  If 
                          MAKERULE see's this file, it will be ignored.
                          You can have as many -g switches as you like.
                          MAKERULE keeps a list of files to ignore.
    -g- <file name>       Remove the file name from the ignore list
    -gx                   Clear the entire ignore file list
    -j <regular expression> Ignore the specified incldue file. If MAKERULE
                          see's this include file, it will be ignored.
                          You can have as many -j switches as you like.
                          MAKERULE keeps a list of include files to ignore
    -j- <regular expression> Remove the regular expression from the ignore list
    -jx                   Clear the entire ignore regular expression file list.
    -w  <directory>       Ignore the specified include directory.  MAKERULE
                          will NOT search this directory for include files.
                          You can have as many -w switches as you like.
                          MAKERULE keeps a list of directories to ignore
    -w- <directory>       Removes the directory from the ignore list.
    -wx                   Clears the ignore directories list.
    -m <number>           Sets the right hand margin.  This defaults to
                          80 but you can set it is small as 60 (which is
                          the minimum).
    -s                    Turns the STRICT flag on.  When STRICT is set, then
                          MAKERULE exits with an error if it can't find
                          an include file, or if a directory on the
                          include path does not exist.
    -s-                   Turns strict mode OFF.
    -t                    Sets the current target.  If there is a current
                          target, then all object file's are associated with
                          only that target
    -t-                   Clears the current target
    -tx                   Clears the target list
    -td                   Dumps the object file list for the current target
                          and clears the current target.
    -tdx                  Dumps the object file list for the current target
                          and clears the ALL targets. (used to handle duplicate
                          target names in the harness).
    -tf <filename>        Dumps the current target to the specified file.
    -tfx                  Resets the output file name to STDOUT.
    -cmd <cmdfile>        Gets more command line arguments from the 'cmdfile'
                          Command files can be nested

    -debug                Turns on DEBUG mode.  This also turns on verbose
                          mode.  If you have problems figuring out what
                          MAKERULE is doing, then turn on the debug mode.
                          You may wan't to redirect stderr to a file so you
                          can read all of it.  Under the korn shell this is
                          done like this 'makerule 2> err >makerule.dep'
                          The rules go to the file 'makerule.dep' and all the
                          output to STDERR goes to the file 'err'.


=head1 DESCRIPTION

MAKERULE automagically generates dependency rules for C, C++ and
assembly language files using #include.  These rules can then be
included in a make file.

MAKERULE needs to basic pieces of information:

   #1 A list of source files to scan
   #2 A list of include directories in which to look for
      include files.

Given this simple information, MAKERULE will generate rules like this:

    obj/app.obj : ../xvutil/assert.h ../platform/am186/DEF186.H                    \
                  ../platform/am186/in186.h ../platform/am186/tmr186.h             \
                  ../platform/am186/am186leds.h ../platform/am186/am186ser.h       \
                  ../platform/pio.h ../common/compiler.h                           \
                  ../platform/am186/printf.h ../common/stdinc.h                    \
                  C:/MSVC/INCLUDE/stddef.h ../platform/am186/ptypes.h              \
                  ../common/serialx.h ../common/serial.H C:/MSVC/INCLUDE/stdarg.h  \
                  ../common/printfe.h
    obj/app.obj : ../app/app.c
            $(COM) ../app/app.c

	APP = \
		app.obj

    app:
    app.exe : app.obj
    	$(CC) -o $(APP) app.exe

    targets:: app

MAKERULE generates human readable output which can be directly included
in a make file.

=head2 Using MAKERULE

Makerule generates makerules for object files and executable targets. 
Multiple targets are supported.  The normal operation is to define a
target, and a set of source files.  At the end of each target, the
object files processed will be placed in a make variable, and an
execuaable line built.

At the end of processing, a list of the generated targets will be
placed in a target rule (target:: t1...tn).

MAKERULE must be run from the same directory that you run your make
file.  This is because MAKERULE puts full or relative path names in its
output.  If you don't run them from the same directory, then make won't
look in the right places.

#2 Makerule is controlled by command line arguments and switches.  All
'unswitched' arguments are taken to be either directories or file
names.  They can contain wild cards.  For example '*.c' or '*.cpp'.

Switches that require arguments may be followed by a space such as

    -I c:\msvc\include

or, you can stick the together like this:

    -Ic:\msvc\include.

Both the above examples add the 'c:\msvc\include' directory to MAKERULE's
include path.

Note that all command line arguments are I<NOT> case sensitive.  I hate
case sentitive command line switches.  So '-I' and '-i' are handled the
same way.

A simple makerule execution might look like this:

    makerule -I c:\msvc\include *.c > deps.mak


This simple command will generate a set of rules for all the C files
in the current directory.  Note that the output goes to STDOUT which,
in this case, is redirected to the file 'deps.mak'.

The key thing to remember about MAKERULE is that it processes the command
line in order from left to right.  So, put -I switches before file specs.

=head2 Important Notes

By default MAKERULE makes a best effort at findign all the include file
dependanices.  However, there are a few things you should know.

#1  By default, MAKERULE ignores #include <....> statements.  MAKERULE
    assumes that angle-bracket includes are only used for libraries such
    as the standard library, or other libraries.  e.g. they are used
    for code that you will NOT be changing during development.

    However, not all folks use angle-bracket includes this way.  So, if you
    want to have MAKERULE search for include files specified using
    angle-bracket includes, then use the '-s' switch.  Note that you can
    turn this back off using the '-s-' switch.

#2  By default, MAKERULE keeps going if it can't find an include file.  So,
    if you have an #include "foo.h" and 'foo.h' cannot be found in the
    source file's directory or in the include path, then MAKERULE just skips
    this file and goes on.  E.g. it is not incldued as a dependency in the
    rule for the source file which tried ot include it.

    This could happen for several reasons, most likely it will be an
    legitimate include path issue.  For example, you might want to use the
    '-s' switch to process angle-bracket include statements but you don't
    want to include stuff from your compiler's standard library.  So you
    will leave the compilers incldue directory (like 'C:\MSVC\INCLUDE' )
    out of the include path MAKERULE uses to generate its rules.  This is
    a perfectly fine thing to do.

    BUT! If you want to makes sure MAKERULE doesn't miss anything then
    turn on STRICT mode by using the '-s' switch.  WHen the stricit mode
    is set, then MAKERULE will exit with an error if it can't find a
    specified directory, source file or include file.

#3  Sometimes you I<want> MAKERULE to ignore header files, even if you
    have strict mode enabled.  The -g switch does this.  '-g <fn>' adds
    a file name to a list of files to ignore. '-g- <fn>' removes a file
    name from the ignore list.  '-gx' clears the entire ignore file list.

#3  Sometimes you I<want> MAKERULE to ignore certain directories in
    the include path.  For example, a setup shell script (or batch file)
    may setup an INCLUDE environment variable.  You would like to use it,
    but there is one directory in the compiler's path that you don't want
    to search.  The -w switch does this.  This switch can also be used
    to ignore directories that do not exist, thus by-passing the strict
    mode check for that include directory.  '-w <dn>' adds a directory
    to a list of include directories to ignore. '-w- <dn>' removes directory
    name from the ignore list.  '-wx' clears the entire ignore directory list.

=head2 Command Files

What would a utility be if it couldn't be run from a command file??? Of course
MAKERULE can read command line arguments from a command file.  Just put a
@<filename> on the makerule command line. There can be more than one and
command files can be nested.  There is no limit to the nesting level.

By convention, I name command files using a '.cml' extension.  MAKERULE
doesn't care though.

Command files can also contain comments.  These are comments just like in
a makfile.  Everything between a '#' and the end of the line is a comment.

Here is an example MAKERULE command file:

      # MAKERULE Command File
      #
      # This entire file is tokenized and logically inserted into the command
      # line where the @ character is

      -s             # include #include <...> statements
      -o obj/        # targets go in the obj directory

      # use this include directories.
      #
      -I C:/rogue/workspaces/WINNT4/MSVC50/8s
      -I c:/coding/am186tpl/common
      -I c:/coding/am186tpl/xvkernel

      -P INCLUDE       # also include the INCLUDE path in the environment

      -r "$(COM)"      # C files are built with this recipe

      source\*.c       # build all the files in the source directory

      -ix              # clear the include path
      -i source        # asm files don't need a fancy include path
      -r "$(ASM) "     # use this recipe to build ASM files
      source/*.asm     # build all the ASM files MAKERULE can find

=head1 RATIONALE

March, 2002:	Rick Foos.
After reviewing makedeps, gcc -M, and autoconf the dependency generation
was not adequate for the range of tool chains to be supported.

Makerule was enhanced to perform this function.

August, 1998:

I wrote MAKERULE to help me maintain make files.  I like GUI development
environments like Microsoft's Visual C++ and Borland's (now Inprise) C++.
I use them almost every day.  They keep track of the header files (and
other files) which each C or C++ file includes.

However, I do a lot of embedded systems programming.  These tools and
projects are often best built using a make file executed from the command
line.  I just got sick to death of maintaining rules like:

   tcpip.obj : tcpip.c tcpip.h udp.h arp.h

So, there you have it.

=head1 AUTHOR

Rick Foos rickf@ebenchmarks.com

Richard G Russell richard.russell@amd.com

=head1 TODO

* Use File::Find to locate files.

* Use GetLongOptions to parse. Will need to replace streaming the cml file in
  through ARGV to do it.

* Use a better C comment parser, or -M option in modern compilers.

* allow multi-line recipes to be placed in MAKERULE command files.  I'll
  probably use something like 'here' documents.

=cut


#===============================================================================

my $version = '$Revision: 1.22 $ $Date: 2002/07/18 19:00:12 $';

$verbose            = 0;            # -v assume FALSE
$debug              = 0;            # -debug assume FALSE
$quiet              = 0;            # -q assume FALSE
$strict             = 0;            # -s assume FALSE
$look_for_angles    = 0;            # -s assume FALSE
$outfile			= "STDOUT";		# -tf assume standard out
$cmdfile			= "STDIN";		# -cmd set by command line argument 

$tgt_ext            = ".obj";       # -b assume a .obj target extension
$ttgt_ext           = "";           # -tb assume no target executable extension
$main_ext           = "";           # -zb assume no main file suffix string
$obj_prefix         = '';           # -o assume no object path
$tobj_prefix        = '';           # -to assume no executable path
$margin             = 72;           # -m 72 is the default right hand margin
$obj_output			= "";			# -co assume no object ouput (recipe $*)
$exe_output			= "";			# -ce assume no executable output (recipe $*)
$quote              = 0;            # -cq assume object output files are not quoted.

@include_path       = ( "" );       # -i the include path maintained by MAKERULE

@ccobjs             = ();           # list of object files
@ctobjs             = ();           # list of current target object fles

$objs               = \@ccobjs;     # current object file list

$ctarget            = '';           # -t  there is no current target
@ctargets           = ();           # -t  list of current targets
$atarget            = '';           # -ta there is no additional target
@atargets           = ();           # -ta list of additional targets
$otarget            = '';           # -a  there is no additional target
@otargets           = ();           # -a  list of additional targets
$etarget            = '';           # -te there is no additional target library
@etargets           = ();           # -te list of additional target libraries

%ignore_files       = ();           # -g ignore file list starts out empty
%ignore_paths       = ();           # -w ignore path list starts out empty
@ignore_regex       = ();           # -j ignore any include thing that matches
%main_files			= ();			# -z main file list starts out empty

$recipe             = '';			# -r object file recipe
$trecipe            = '';			# -tr executable file recipe

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# 1'st pass through the command line
#
# This processes any command files found

for ( $i = 0; $i < @ARGV; $i++ )
   {
   my $iml;
   my @newstuff;
   my $code;

   @newstuff = ();

   # Gotta look for the debug flag here...

   if ( $ARGV[$i] =~ /^-debug$/ )
     {
     $debug = 1; $quiet = 0; $verbose = 1;
     print STDERR "DEBUG: ON\n";
     }

   print STDERR "ARG-A : '$ARGV[$i]'\n" if $debug;

   if ( $ARGV[ $i ] =~ /^-cmd$/ )
      {
      $i++;
      $cmdfile = $ARGV[ $i ];
      unless( -r $cmdfile)
         {
         print STDERR "\nERRROR : Command file '$cmdfile' does not exist\n";
         exit 3;
         }

      print STDERR "CMD FILE : '$cmdfile'\n" if $debug;

      open CMDFILE, $cmdfile || die "\nERROR : Cannot open '$cmdfile' $!\n";

      while ( $code = <CMDFILE> )
         {
         chomp $code;
         $code =~ s/(.*?)#.*$/$1/;      # Remove comments
         $code =~ s/^\s*(.*?)\s*$/$1/;  # remove leading/trailing spaces

         $code = protect_quotes( $code );

         @tmp = split /\s+/, $code;     # split it up into pieces

         foreach $e (@tmp)
            {
            $e = unprotect_quotes( $e );
            print STDERR "ARG-J : '$e'\n" if $debug;
            push @newstuff, $e;
            }
         }

      splice @ARGV, $i, 1, @newstuff;    # insert new arguments into @ARGV

      $i --;  # step back one to properly process the first argument
              # in the command file
      }
   }

# for $e (@ARGV) { print STDERR "ARG-X : '$e'\n"; } exit 0;

print_outputheader;


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# 2'd pass through the command line

ARGS: while ( $e=shift( @ARGV ) )
    {
    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # some debug stuff...
    #
    print STDERR "ARG          : '$e'\n" if $debug;

    if ( $e =~ /^-/ )  # is it a command line switch??
       {
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # The Help Switch
       #
       # -? or -help (or any switch with the word 'help' in it
       #
       if ( $e =~ /^-\?/ || $e =~ /^-.*help/)
          {
          usage();
          exit 1;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -v Verbose
       #
       if ( $e =~ /^-v([-+]?)/i )
          {
          if ( $1 eq '-' )  # turn it off
             { $verbose = 0 }
          else
             {
             $verbose = 1;
             $quiet = 0;
             }

          print STDERR "VERBOSE : ". ( $verbose ? "ON" : "OFF" ) . "\n" if $debug;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -q quiet
       #
       if ( $e =~ /^-q([-+]?)/i )
          {
          print STDERR "\nQUIET : ON" if $debug;

          if ( $1 eq '-' )  # turn it off
             { $quiet = 0 }
          else
             {
             $verbose = 0;
             $quiet   = 1;
             }

          print STDERR "QUIET : ". ( $quiet ? "ON" : "OFF" )  . "\n" if $debug;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -s Strict
       #
       if ( $e =~ /^-s([-+]?)/i )
          {
          if ( $1 eq '-' )  # turn it off
             { $strict = 0 }
          else
             { $strict = 1 }

          print STDERR "STRICT MODE : ". ( $strict ? "ON" : "OFF" ) . "\n" if $debug;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -s  Allow Processing of #include <...> statements
       #
       if ( $e =~ /^-s([+-])?$/i )
          {
          $look_for_angles = ( $1 eq '-' ) ? 0 : 1;
          print STDERR "ANGLES : ". ( $look_for_angles ? "ON" : "OFF" ) . "\n" if $debug;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -I Add to include path
       #
       if ( $e =~ /^-ix$/i )
          { @include_path = ( "" ) } # reset include path
       elsif ( $e =~ /^-i(.*)/i )
          {
          my $e;
          if ( $1 ) { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No Include path after -I switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;

          if ( $strict && (! -d $e) )
             {
             print STDERR "\n** ERROR: Can't find specified include path '$e'\n";
             exit 2;
             }

          $e =  add_tslash( $e );

          push @include_path, $e;

          print STDERR "INCLUDE PATH : '$e'\n" if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -g Ignore file
       #

       if ( $e =~ /^-gx$/i )
          { 
          %ignore_files = ();
          print STDERR "CLEAR IGNORE FILES\n" if $verbose;
          } 
       elsif ( $e =~ /^-g(-?)(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No file name after -g switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;

          if ( $1 eq '-' )
             {
             delete $ignore_files{ uc $e };
             print STDERR "DELETE IGNORE FILE : '$e'\n" if $verbose;
             }
          else
             {
             $ignore_files{ uc $e } = $e;
             print STDERR "ADD IGNORE FILE : '$e'\n" if $verbose;
             }
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -a additional object dependency
       #

       if ( $e =~ /^-ax$/i )
          { 
          @otargets = ();
          $otarget = '';
          print STDERR "CLEAR OBJECT DEPENDENCIES\n" if $verbose;
          } 
       elsif ( $e =~ /^-a(-?)(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No dependency after -a switch\n";
             usage();
             exit 2;
             }

            $otarget = $e;
        	push @otargets, $e;

          print STDERR "ADD ADDITIONAL OBJECT DEPENDENCY : '$e'\n";# if $verbose;

          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -z Main File section
       #

       # -zx: make main file list empty
       if ( $e =~ /^-zx$/i )
          { @main_files = () }

       # -zb: Set the target extension

       elsif ( $e =~ /^-zbx$/i )
          { $main_ext = '' }
       elsif ( $e =~ /^-zb(.*)/i )
          {
          my $e;

          if ( $1 )
             { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             $main_ext = $e;
             print STDERR "MAIN FILE SUFFIX STRING: '$e'\n" if $verbose;
             }
          else
             {
             print STDERR "\nERROR: No filename suffix after -zb switch\n";
             usage();
             exit 2;
             }

          }
       elsif ( $e =~ /^-z(-?)(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No file name after -z switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;

          if ( $1 eq '-' )
             {
             delete $main_files{ uc $e };
             print STDERR "DELETE MAIN FILE : '$e'\n" if $verbose;
             }
          else
             {
             $main_files{ uc $e } = $e;
             print STDERR "ADD MAIN FILE : '$e'\n" if $verbose;
             }
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -j Ignore Reg-ex
       #

       if ( $e =~ /^-jx$/i )
          { @ignore_regex = () }# make ignore file list empty!
       elsif ( $e =~ /^-j(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No file name after -j switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;

          $ignore_regex{ $e } = $e;
          print STDERR "ADD IGNORE REGEX : '$e'\n" if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -cq, -co, -ce
       #

       if ( $e =~ /^-cq([+-])?$/i )
          {
          $quote = ( $1 eq '-' ) ? 0 : 1;
          print STDERR "ANGLES : ". ( $quote ? "ON" : "OFF" ) . "\n" if $debug;
          }
       elsif ( $e =~ /^-cox$/i )
          { 
          $obj_output = ''; # clear compiler object output
          print STDERR "CLEAR COMPILER OBJECT OUTPUT\n";
          }
       elsif ( $e =~ /^-co(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No compiler obj output after -co switch!\n";
             usage();
             exit 2;
             }

          $obj_output = $e;
          print STDERR "SET COMPILER OBJECT OUTPUT : '$e'\n";# if $verbose;
          }
       elsif ( $e =~ /^-cex$/i )
          { 
          $exe_output = ''; # clear exe output
          print STDERR "CLEAR COMPILER EXECUTABLE OUTPUT\n" if $verbose;
          }
       elsif ( $e =~ /^-ce(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No compiler executable output after -ce switch!\n";
             usage();
             exit 2;
             }

          $exe_output = $e;
          print STDERR "SET COMPILER EXECUTABLE OUTPUT : '$e'\n" if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # BEGIN -T OPTIONS
       # -t Set/Clear Target Object File Lset
       #

       if ( $e =~ /^-tx$/i )
          {
          dump_objs();
          $ctarget = '';
          @ctargets = ();
          print STDERR "TARGET LIST EMPTIED\n" if $verbose;
          $objs = \@ccobjs;     # use the current object file list
          @ctobjs = ();         # emtpy the current target obj list
          }
       elsif ( $e =~ /^-td$/i )
          {
          dump_objs();
          $ctarget = '';
          print STDERR "NO TARGET\n" if $verbose;
          $objs = \@ccobjs;     # use the current object file list
          @ctobjs = ();         # emtpy the current target obj list
          }
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -ta Set/Clear Additional target dependancies
       #

       elsif ( $e =~ /^-tax$/i )
          { $atarget = '';
            @atargets = (); # make additional targets list empty!
            print STDERR "CLEAR ADDITIONAL TARGET LIST\n" if $verbose; 
          }
       elsif ( $e =~ /^-ta(.*)$/i )
          {
          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No target after -ta switch\n";
             usage();
             exit 2;
             }

            $atarget = $e;
        	push @atargets, $e;

          print STDERR "ADD ADDITIONAL TARGET : '$e'\n" if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -te Set/Clear Additional target library file
       #

       elsif ( $e =~ /^-tex$/i )
          { $etarget = '';
            @etargets = (); # make additional targets list empty!
            print STDERR "CLEAR ADDITIONAL TARGET LIBRARY LIST\n";# if $verbose; 
          }
       elsif ( $e =~ /^-te(.*)$/i )
          {
          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No target library after -te switch\n";
             usage();
             exit 2;
             }

            $etarget = $e;
        	push @etargets, $e;

          print STDERR "ADD ADDITIONAL TARGET LIBRARY: '$e'\n";# if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -to Set the executable target directory
       #

       elsif ( $e =~ /^-tox$/i )
          {
          $tobj_prefix = '';
          }
       elsif ( $e =~ /^-to(.*)/i )
          {
          if ( $1 )
             { $tobj_prefix = $1 }
          elsif ( $tobj_prefix = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No target directory after -to switch!\n";
             usage();
             exit 2;
             }

          $tobj_prefix = add_tslash( $tobj_prefix );
          print STDERR "SET BIN PATH : '$tobj_prefix'\n" if $verbose;
          }
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -tf Set output file
       #

       elsif ( $e =~ /^-tfx$/i )
          {
          $outfile = "STDOUT";
          print STDERR "RESET OUTPUT FILE : '$outfile'\n";
          print_outputheader;
          }
       elsif ( $e =~ /^-tf(.*)/i )
          {
          if ( $1 )
             { $outfile = $1 }
          elsif ( $outfile = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No output file after -tf switch!\n";
             usage();
             exit 2;
             }

          print STDERR "SET OUTPUT FILE : '$outfile'\n";
          open(OFILE, ">$outfile" ) or die "\nERROR : Cannot open $outfile \n";
          print_outputheader;
          }
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -tb Set the target extension
       #

       elsif ( $e =~ /^-tbx$/i )
          { $ttgt_ext = '' }
       elsif ( $e =~ /^-tb(.*)/i )
          {
          my $e;

          if ( $1 )
             { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             # make sure target extension has a '.' in front of it
             }
          else
             {
             print STDERR "\nERROR: No target extension after -tb switch!\n";
             usage();
             exit 2;
             }

          if ( $e !~ /^./ )
             { $ttgt_ext = ".$e"; }
          else
             { $ttgt_ext = $e; }
          }
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -tr Set the Recipe
       #

       elsif ( $e =~ /^-trx$/i )
          { $trecipe = '';  }
       elsif ( $e =~ /^-tr(.*)/i )
          {
          my $e;

          if ( $1 )
             { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No Include environment after -tr switch!\n";
             usage();
             exit 2;
             }

          $trecipe = $e;
          print STDERR "RECIPE : $trecipe\n" if $verbose;
          }

# add new -t options onto previous elsif's, or they become targets
       elsif ( $e =~ /^-t(-?)(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2; }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No text after -t switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;

          if ( $1 eq '-' )
             {
             $ctarget = '';
             print STDERR "NO TARGET\n" if $verbose;
             $objs = \@ccobjs;     # use the current object file list
             @ctobjs = ();         # emtpy the current target obj list
             }
          else
             {
             $ctarget = $e;
        	 push @ctargets, $e;

             print STDERR "NEW TARGET : '$ctarget'\n" if $verbose;
             @ctobjs = ();         # emtpy the current target obj list
             $objs = \@ctobjs;     # use the target object file list
             }
          }
       # END -T OPTIONS

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -w Ignore Paths
       #

       if ( $e =~ /^-wx$/i )
          {  
          %ignore_paths = ();   # make ignore path list empty!
          print STDERR "CLEAR IGNORE PATHS\n" if $verbose;
          }

       elsif ( $e =~ /^-w(-?)(.*)$/i )
          {
          my $e;

          if ( $2 ) { $e = $2 }
          elsif ( ! ($e = shift( @ARGV )) )
             {
             print STDERR "\nERROR: No file name after -w switch!\n";
             usage();
             exit 2;
             }

          $e =~ tr!\\!\/!;
          $e =  add_tslash( $e );

          if ( $1 eq '-' )
             {
             delete $ignore_paths{ uc $e };
             print STDERR "DELETE IGNORE PATH : '$e'\n" if $verbose;
             }
          else
             {
             $ignore_paths{ uc $e } = $e;
             print STDERR "ADD IGNORE PATH : '$e'\n" if $verbose;
             }
          }


       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -p Add to include path from environment variable
       #
       if ( $e =~ /^-p(.*)/i )
          {
          # get the include path from an environment variable.
          my $e;

          if ( $1 ) { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             my @tmp = split /;/, $ENV{$e} ;

             print STDERR    "USE ENV      : '$e'\n" if $verbose;

             foreach $e ( @tmp )
                {
                $e =  add_tslash( $e );
                $e =~ tr!\\!\/!;
                push @include_path, $e;
                print STDERR "INCLUDE PATH : '$e'\n" if $verbose;
                }
             }
          else
             {
             print STDERR "\nERROR: No Include environment after -p switch!\n";
             usage();
             exit 2;
             }
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -r Set the Recipe
       #

       if ( $e =~ /^-rx$/i )
          { $recipe = '';  }
       elsif ( $e =~ /^-r(.*)/i )
          {
          my $e;

          if ( $1 )
             { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No Include environment after -r switch!\n";
             usage();
             exit 2;
             }

          $recipe = $e;
          print STDERR "RECIPE : $recipe\n" if $verbose;
          }


       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -m Set the Margins
       #

       if ( $e =~ /^-m(\d*)/i )
          {
          my $e;

          if ( $1 )
             { $margin = $1 }
          elsif ( $e = shift( @ARGV ) )
             { $margin = $e }
          else
             {
             print STDERR "\nERROR: No Include environment after -r switch!\n";
             usage();
             exit 2;
             }

          $margin = ($margin < 60) ? 60 : $margin;

          print STDERR "MARGIN : $margin\n" if $verbose;
          }

       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -b Set the target extension
       #

       if ( $e =~ /^-bx$/i )
          { $tgt_ext = '' }
       elsif ( $e =~ /^-b(.*)/i )
          {
          my $e;

          if ( $1 )
             { $e = $1 }
          elsif ( $e = shift( @ARGV ) )
             {
             # make sure target extension has a '.' in front of it
             }
          else
             {
             print STDERR "\nERROR: No target extension after -b switch!\n";
             usage();
             exit 2;
             }

          if ( $e !~ /^./ )
             { $tgt_ext = ".$e"; }
          else
             { $tgt_ext = $e; }
          }


       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # -o Set the object target directory
       #

       if ( $e =~ /^-ox$/i )
          {
          $obj_prefix = '';
          }
       elsif ( $e =~ /^-o(.*)/i )
          {
          if ( $1 )
             { $obj_prefix = $1 }
          elsif ( $obj_prefix = shift( @ARGV ) )
             {
             }
          else
             {
             print STDERR "\nERROR: No target directory after -o switch!\n";
             usage();
             exit 2;
             }

          $obj_prefix = add_tslash( $obj_prefix );
          print STDERR "SET OBJ PATH : '$obj_prefix'\n" if $verbose;
          }
       }
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # more help stuf
       #
    elsif ( $e eq '/?' || $e eq '?' )
       {
       usage();
       exit 1;
       }
    else
       {
       # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       # Ok... the argument will be treated as a file name of some sort
       #
       print STDERR "WORK ON : '$e'\n" if $debug;

       $e =~ tr!\\!\/!;  # make sure directory separators are right...

       $e =~ /([a-zA-Z]:)?(.*\/)?(.*)/;  # parse the file spec

       $include_path[0] = add_tslash( "$1$2" );  # first thing in include
                                                 # path is the lcoation of
       my @files;

       if ( -f $e )
          { @files = ( $e ) }
       else
          {
          print STDERR "GLOBBING : '$e'\n";
          @files = glob( $e );     # glob an wild cards...
          if ( $debug ) { foreach $e ( @files ) { print STDERR "\nGLOBED : '$e'\n" } }
          }

       if ( @files )
          {
          for $e ( @files )
             {
             $fname = $e;
             $e =~ /([a-zA-Z]:)?(.*\/)?(.*)/;  # parse the file name
             if (exists $ignore_files{ uc $3 })
             {
             print STDERR "IGNORE FILE : '$e'\n" if $debug;
             }
             else 
             {
             print STDERR "PROCESS FILE : '$e'\n" if $verbose;
             $depth = 0;   # scan_dep() level is zero
             @ilist = ();  # empty the include list
             %found = ();
             scan_dep( $e );
             # Now, we have the list of include files, generate the rule
             generate_rule( $e );
             }
             }
          }
       else
          {
          print STDERR "** No files found for '$e'!\n";
          }
       }
    }

dump_objs();

print OFILE "\n";  # newline at the end or make isn't happy

exit 0;   # Fin!

#-------------------------------------------------------------------------------

sub generate_rule

   {
   my $depf = $_[0];
   my $rule_len;
   my $rule;
   my $line_len;
   my $fn;
   my $filename;
   my $objname;

   $depf =~ /([a-zA-Z0-9]:)?(.*\/)?(.*)?(\..*)/;  # parse the file name

	printf STDERR "$1, $2, $3, $4, $depf\n" if $debug;
   $fn = $3;
   $filename ="$3$4";

   if (exists $main_files{uc $filename})
   {
   $fn = "$fn$main_ext";
   $depf = "$2$3$main_ext$4";
   print STDERR "MAIN FILE FOUND: $fn, $depf\n" if $verbose;
   }
	
   $objname = "$obj_prefix$fn$tgt_ext";

   push @$objs, $objname;

   if ( @ilist > 0 )
      {
      $rule = "$objname :";
      $line_len = $rule_len = length $rule;

      print OFILE "$rule";

      if ( $rule_len > 20 )
         {
         $rule_len = length($objname) + 2;
         print OFILE ' ' x ($margin - $line_len - 2) . ' \\';
         print OFILE "\n" . (' ' x $rule_len);
         $line_len = $rule_len;
         }

      foreach $e ( @ilist )
         {
         if ( ($line_len + length(" $e")) >= $margin-1 )
            {
            print OFILE ' ' x (($margin - $line_len) - 2) . " \\\n";
            print OFILE ' ' x $rule_len . ' ' . $e;
            $line_len = $rule_len + length( $e ) + 1;
            }
         else
            {
            $line_len += length( " $e" );
            print OFILE " $e";
            }
         }
      }

   $rule = "$objname : $depf";
   print OFILE "\n$rule";
   
   $line_len = length("$rule");
   foreach $e (@otargets) {
         if ( ($line_len + length(" $e")) >= $margin-1 )
            {
            print OFILE ' ' x (($margin - $line_len) - 2) . " \\\n";
            print OFILE ' ' x $rule_len . ' ' . $e;
            $line_len = $rule_len + length( $e ) + 1;
            }
         else
            {
            $line_len += length( " $e" );
            print OFILE " $e";
            }
   }

   if ( $recipe )
	{print OFILE "\n\t$recipe ";
		if ($obj_output)
		{
		if ($quote) {print OFILE "$obj_output\"$objname\" $depf";}
		else		{print OFILE "$obj_output$objname $depf";}
		}
	}

   print OFILE "\n\n";
   }

#-------------------------------------------------------------------------------

sub dump_objs

   {
   my $line_len = 0;
   my $tag_len  = 0;
   my $tag;

# dumping executable targets
   if ( (@ctobjs, @ccobjs) == 0 )
      {
      if (@ctobjs){
      $utarget = $ctarget;
      $exename = "$tobj_prefix$ctarget$ttgt_ext";
      $utarget =~ tr/a-z/A-Z/;
      print OFILE "$utarget = ";
      foreach $e (@ctobjs) {print OFILE "\\\n    $e ";}
      print OFILE "\n\n";
      print OFILE "$tobj_prefix$ctarget$ttgt_ext:  \$\($utarget\) ";
      foreach $e (@atargets) {print OFILE "$e ";}
      print OFILE "\n";

	  if ( $trecipe )
		{print OFILE "\t$trecipe ";
			if ($exe_output)
			{
			if ($quote) {print OFILE "$exe_output\"$exename\"";}
			else		{print OFILE "$exe_output $exename";}
			}
		}
      print OFILE " \$($utarget) ";
      if (@etargets) {
      foreach $e (@etargets) {print OFILE "$e ";}
      } else {foreach $e (@atargets) {print OFILE "$e ";}}
      print OFILE " \n\n\n";

      } else {
      print OFILE "targets:: ";
      foreach $e (@ctargets) {print OFILE "\\\n\t$tobj_prefix$e$ttgt_ext ";}
      print OFILE "\n\n";
      print STDERR "Nothing more to do! (I need some file names...)\n";
      }
      return;
      }

   if ($ctarget)
      {
      $tag = $ctarget . "_OBJS = ";
      }
   else
      {
      $tag = "OBJS = ";
      }

   print OFILE $tag;

   $line_len = $tag_len = length $tag;

   foreach $e ( (@ctobjs, @ccobjs) )
      {
      if ( ($line_len + length(" $e")) >= $margin-1 )
         {
         print OFILE ' ' x (($margin - $line_len) - 2) . " \\\n";
         print OFILE ' ' x $tag_len . ' ' . $e;
         $line_len = $tag_len + length( $e ) + 1;
         }
      else
         {
         $line_len += length( " $e" );
         print OFILE " $e";
         }
      }

   print OFILE "\n\n";
   }


#-------------------------------------------------------------------------------
# FUNC   : scan_dep
#
# DESC   : Scans source files for include files
#
#          This is the work horse function that actually does all the work.
#          All the other junk is just support for this function.
# ------------------------------------------------------------------------------

sub scan_dep

   {
   my @new;
   my $e;
   my $line;
   my $type;
   my $iname;
   my $iml = 0;
   my $code;
   my $comment;
   my $isasm;
   my $skip_it;
   my $first;

   $depth++;

   # Ok, is it an INTEL Assembly Language file?  If so, then we need
   # a different include regex.

   unless ( $_[0] =~ /.asm/i )
      {
      # include match pattern for C and C++ files
      $ipat = '^\s*#\s*include\s*(["<])\s*(\S*)\s*[">]';
      }
   else
      {
      # include match pattern for ASM files
      $ipat = '(INCLUDE)\s*(\S*)';
      $isasm = 1;
      }

   print STDERR "OPEN $depth  : $_[0]\n" if $debug;

   if ( open( SFILE, $_[0] ) == 0 )
      {
      print STDERR "\n** ERROR: Can't Open source file '$_[0]' $!\n";

      if ( $strict )
         {
         exit 1;
         }
      return;
      }

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   # Scan through all the lines in the source file looking for include
   # directives...

   FILES: while( $line = <SFILE> )
      {
      unless ( $isasm )
         { ( $iml, $code, $comment ) = c_cppcmt_parse( $line, $iml ); }
      else
         {
         $code  = $line;
         $code =~ s/(.*?);.*$/$1/;      # Remove comments
         }

      if ( $code =~ $ipat )
         {
         # Ahh! We found an include file!  Now, do we make it a dependency
         # on the original source file????

         $type    = $1;  # include file type
         $iname   = $2;  # include file name
         $first   =  1;  # first time throught the loop
         $skip_it =  0;  # don't skip the include path

         $iname =~ tr!\\!\/!;  # make sure separater is correct

         if ( $type eq '<' && !$look_for_angles )
            {
            # Not looking for files in angle brakets.... so just continue
            print STDERR "SKIP ANGLE INCLUDES : $iname\n" if $debug;
            next FILES;
            }

         if ( exists $ignore_files{ uc $iname } )
            {
            print STDERR "IGNORE FILE : $iname\n" if $debug;
            next FILES;
            }

         print STDERR "INCLUDE : '$iname' type='$type'\n" if $debug;

         # Ok, we found a included file name and we don't need to skip it
         # so see if we can find it on the include path

         PATHS: foreach $i (@include_path )
            {
            if ( exists $ignore_paths{ uc $i } )
               {
               print STDERR "IGNORE PATH : $iname\n" if $debug;
               next PATHS;
               }

            $skip_it = ($type eq '<' && $first );

            # ok, serch throug the list of ignore regular expressions
            # If we have a match, then set the skip flag
            #
            if ( !skip_it && @ignore_regex )
               {
               foreach $e ( @ignore_regex )
                  {
                  if ("$i$iname" =~ $e)
                     {
                     $skip_it = 1;
                     last;          # don't need to look any more
                     }
                  }
               }

            $first = 0;

            print STDERR "LOOKFOR  : $i$iname\n" if $debug && !$skip_it;
            print STDERR "SKIPPING : $i$iname\n" if $debug &&  $skip_it;

            if ( !$skip_it && (-f "$i$iname") )
               {
               print STDERR "FOUND   ! $i$iname " if $debug;

               if ( !exists $found{ uc "$i$iname" } )
                  {
                  $found{ uc "$i$iname" } = "$i$iname";
                  push @ilist, "$i$iname";
                  push @new,   "$i$iname";
                  print STDERR " (added)" if $debug;
                  }
               else
                  {
                  print STDERR " (got it already)" if $debug;
                  }
               print STDERR "\n" if $debug;
               next FILES;
               }
            }

         if ( !$skip_it )
            {
            print STDERR "** Can't Find include file '$iname' from '$_[0]'\n" if (!$quiet || $strict);
            exit 1 if $strict;
            }
         }
      }

   close SFILE;

   my $cnt = @new ? @new : 0 ; # count the files add to the rule

   print STDERR "CLOSE   $cnt\n" if $debug;

   if ( $cnt )
      {
      for $e ( @new )
         {
         print STDERR "RECURSE :\n" if $debug;
         scan_dep( $e );
         }
      }

   print STDERR "DONE $depth  :\n" if $debug;

   $depth--;
   }

#-------------------------------------------------------------------------------

sub usage
   {
   $version =~ s/\$//g;  # Remove the '$' charactes

   printf  <<EOF;

Usage: makerule <switches> <file spec> [switches] [file spec]

Version $version

makerule generates dependency rules for makefiles.

Switches:
    -?                    Dump some help then exit ( -help also works)
    -I    <directory>     adds a directory to MAKERULE's include path
    -ix                   clear's (empties) MAKERULE's include path
    -p    <env variable>  Use include path from environment variable
    -v                    Turns on the verbose mode. (implies -q-)
    -v-                   Turns verbose mode off
    -q                    Turns on quiet mode.  (implies -v-)
    -q-                   Turns the quiet mode off
    -s                    Enables processing of '#include <...>' statments
    -s-                   Turns off processing angle-bracket incldue statments
    -r <recipe>           Sets the recipe to be placed after each rule.
    -rx                   Clears the current recipe.
    -b <extension>        Sets the file extension of the target file in rules
    -o <directory>        Sets the target directory for rules
    -a <dependency>		  Adds additional object dependency.
    -ox                   Clears the current target directory
    -m <number>           Sets the right hand margin.  (default = 80)
    -g  <file name>       Ignore include file (multiple -g's supported)
    -g- <file name>       Oposite of -g
    -gx                   Clears the entire ignore file list
    -w  <directory>       Ignore include directory (multiple -w's supported)
    -w- <directory>       Oposite of -w
    -wx                   Clears the entire ignore diretory list
    -s                    Turns the STRICT mode on.
    -s-                   Turns strict mode OFF.
    -t                    Sets the current target
    -t-                   Clears the current target
    -cmd <cmdfile>        Gets more command line arguments from the 'cmdfile'
    -debug                Turns on DEBUG mode.  This also turns on verbose

EOF
   }

#-------------------------------------------------------------------------------

sub protect_quotes
   {
   if ( $_[0] !~ /"/ )
      { return $_[0]; }

   $_[0] =~ /(.*?)(\".*?\")(.*)/;

#  print OFILE "-- '$_[0]' => '$1' '$2' '$3' --\n";

   my $s1 = $1;
   my $s2 = $2;
   my $s3 = $3;

   $s2 =~ tr/ /\001/;

   return $s1.$s2.$s3;
   }

sub unprotect_quotes
   {
   my $s;

   if ( $_[0] !~ /"/ )
      { return $_[0]; }

   $_[0] =~ /(.*?)(\".*?\")(.*)/;

#  print OFILE "== '$_[0]' -> '$1' '$2' '$3' ->";

   $s = $1.$2.$3;
   $s =~ tr/\001/ /;   # undo the space zapper
   $s =~ s/"//g;       # remove the quotes

   return $s;
   }

sub print_outputheader
	{
	# print any header information here.
	print OFILE "# File generated by Makerule.pl - DO NOT EDIT\n";

	if ($cmdfile) {print OFILE "# Edit $cmdfile to change\n";}
	else {print OFILE "\n";}

	print OFILE "\# $version\n";
	}
# dirtool.pm
## to be replaced with File::Find
##package dirtool;
#require Exporter;
#@ISA=(Exporter);
#@EXPORT=qw(enum_dir dir_count add_tslash);

#------------------------------------------------------------------------------
# SUB    : enum_dir
#
# DESC   : enumerates a directory
#
#          0 => the directory to enumerate
#          1 => an array reference which receives a list of sub directories
#               in the
#------------------------------------------------------------------------------

sub enum_dir
   {
   my $the_dir = add_tslash( $_[0] );

   opendir THEDIR, $_[0] or die "Cannot open dir: $!";

   while ( $entry = readdir THEDIR )
      {
	  if ( -d $the_dir.$entry )
         {
         if ( defined $_[1] )
         	{
         	push @{$_[1]}, $entry;
         	}
         }
	   else
         {
         if ( defined $_[2] )
         	{
         	push @{$_[2]}, $entry;
         	}
          }
	  }

   closedir THEDIR;

   return $the_dir;
   }

sub tslash
   {
   if ( $_[0] !~ /\\$/ )
      { $_[0] .= '\\'; }

   return $_[0];
   }

#-------------------------------------------------------------------------------
# SUB    : dir_count
#
# DESC   : Counts the number of directories in a directory
#
#          This function is much more efficient than calling
#------------------------------------------------------------------------------

sub dir_count
   {
   my $cnt     = 0;
   my $the_dir = add_tslash( $_[0] );

   opendir THEDIR, $_[0] or die "Cannot open dir: $!";

   while ( $entry = readdir THEDIR )
      {
	  if ( ($entry ne '.') && ($entry ne '..') && (-d $the_dir.$entry) )
         { $cnt++; }
	  }

   closedir THEDIR;

   return $cnt;
   }

#-------------------------------------------------------------------------------
# SUB    : add_tslash
#
# DESC   : adds a trailing slash to a string (if there isn't one)
#------------------------------------------------------------------------------

sub add_tslash
   {
   if ( @_ == 0 || !defined($_[0]) )
	  { return undef; }

   my $dirn = $_[0];

   if ( defined($_[1]) && $_[1] == '/' )
	  {
      if ( $dirn !~ /\\$/ )
         { $dirn .= '\\'; }
	  }
   else
      {
      if ( $dirn !~ m!\/$! )
         { $dirn .= '/'; }
	  }

   return $dirn;
   }

#-------------------------------------------------------------------------------
# ENDOF   : dirtool.pm
#-------------------------------------------------------------------------------

# cmt.pm
## find a better comment parser
#package cmt;

#use Exporter;
#@ISA=(Exporter);
#@EXPORT=qw(c_cppcmt_parse);

#-------------------------------------------------------------------------------
# FILE   : cmt.pl
#
# DESC   : Stuff for handling C and C++ style comments
#-------------------------------------------------------------------------------

sub c_cppcmt_parse
   {
   my $line          = $_[0];
   my $in_multi_line = $_[1];

   my $gap           = 0;
   my $comment       = '';
   my $code          = $line;
   my $indicate      = '';

   LINE: while( 1 )
      {
      if ( !$in_multi_line )
         {
         $cpp_cmt_start = index( $code, '//' );
         $c_cmt_start   = index( $code, '/*' );

         while ( $cpp_cmt_start != -1 || $c_cmt_start != -1 )
            {
            # We have some kind of comment...., first, lets adjust
			# the c comment start to someting easier to work with

            if ( $c_cmt_start == -1 ) { $c_cmt_start = 999999; }

			# First, see if a C++ comment is ahead of a C comment
			# on the line
            if ( $cpp_cmt_start >= 0 && ($cpp_cmt_start < $c_cmt_start ))
               {
               # Ok, a '//' is in front of a '/*' .OR. there is
               # only a '//' on the line.  So, everyting past it is a
               # comment and there can be no C style comments on the line

               $cmt_len = length($code) - $cpp_cmt_start;

               $indicate .= '%' x ($cpp_cmt_start - $gap) . '@' x $cmt_len;

               # get the comment from the code line
               $comment = (' ' x $cpp_cmt_start) . substr( $code, $cpp_cmt_start, $cmt_len);

               # replace the comment with spaces
               substr( $code, $cpp_cmt_start, $cmt_len) = ' ' x $cmt_len;

               # done with the comment scanning loop
               last LINE;
               }
            elsif ( $code =~ m!\/\*.*?\*\/! )
               {
               # ok, its a entire 'C' style comment.

               $indicate .= '%' x (length($`) - $gap) . '@' x length($&);
               $comment .= ' ' x (length($`) - $gap) . $&;

               # replace comment with spaces
               substr( $code, length($`), length($&) ) = ' ' x length($&);

               $gap += (length($`)-$gap) + length($&);
               }
            elsif ( $code =~ m!\/\*.*$! )
               {
               # Its a C style comment that continues on the next line

               $indicate .= '%' x (length($`) - $gap) . '@' x length($&);
               $comment  .= ' ' x (length($`) - $gap) . $&;

               # replace comment with spaces
               substr( $code, length($`), length($&) ) = ' ' x length($&);

               # oopss.. we gotta start looking for a end of comment
               $in_multi_line = 1;

               # done with the comment scanning loop
               last LINE;
               }

            $cpp_cmt_start = index( $code, '//' );
            $c_cmt_start   = index( $code, '/*' );
            }

         if ( length($code) > length($comment) )
            {
            $code_tail_len = length($code) - length($comment);
            $indicate .= '%' x $code_tail_len;
            $comment  .= ' ' x $code_tail_len;
            }

         last LINE;
         }
      else
         {
         # ok, there was a trailing C style start of comment, gotta
         # look for a end of comment at the front of a line

         if ( $line =~ m!^.*?\*\/! )
            {
            # cool, we found the end of a multi-line C style comment

            # what we matched is the comment
            $indicate = '@' x length($&);
            $comment  = $&;

            # replace comment with spaces
            substr( $code, 0, length($&) ) = ' ' x length($&);

            $gap += length($&);

            # Not in a multi-line C comment any more
            $in_multi_line = 0;

            # note, we continue at the top of the 'LINE' loop
            }
         else
            {
            # the whole line is all comment!
            $comment   = $line;
            $code      = ' ' x length( $line );
            $indicate  = '@' x length( $line );

            last LINE;
            }
         }
      }

   return ( $in_multi_line, $code, $comment, $indicate );
   }

#-------------------------------------------------------------------------------
# ENDOF   : cmt.pl
#-------------------------------------------------------------------------------










