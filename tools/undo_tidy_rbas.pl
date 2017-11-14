#!/usr/bin/env perl

#---------------------------------------------------------------------
#                          file information
#---------------------------------------------------------------------

# Filename : undo_tidy_rbas.pl
# Authors  : Robert Kiraly, Zach van Rijn
# License  : MIT/X
# Revision : 171114

#---------------------------------------------------------------------
#                           important note
#---------------------------------------------------------------------

# This software is provided on an  AS IS basis with ABSOLUTELY NO WAR-
# RANTY.  The  entire risk as to the  quality and  performance of  the
# software is with you.  Should the software prove defective,  you as-
# sume the cost of all necessary  servicing, repair or correction.  In
# no event will any of the developers,  or any other party, be  liable
# to anyone for damages arising out of use of the software, or inabil-
# ity to use the software.

#---------------------------------------------------------------------
#                              overview
#---------------------------------------------------------------------

                                # Label must be single-quoted here
my $USAGE_TEXT = << 'END_OF_USAGE_TEXT';
Usage: $PROGNAME --run file.log

The 'clang-tidy' tool may be used for formatting code as in the follo-
wing usage:

    clang-tidy -checks="readability-braces-around-statements" \
        -fix-errors file.c

However it may perform undesired substitutions,  in which case it will
emit the string 'did you mean' along with some other information about
the changes that it made. If the '-fix-errors' flag is replaced simply
by '-fix' then the  'clang-tidy'  tool will abort  prematurely without
makin any of the desired corrections.

This is a  single  use-case script that performs a set of  "undo"-type
edits to modified  ".c" and/or ".h"  files  that are listed in  "file.
log".

"file.log" needs to be in a highly specific format that is to be docu-
mented elsewhere.

Warning #1: This script doesn't presently  back-up  the files  that it
modifies.  The files should be  backed up manually  before this script
is executed.

Warning #2: The ".c" and/or ".h" files involved must not be edited be-
tween the time that "file.log" is created and this script is executed.
Even a detab operation will lead to data corruption.

Warning #3: Corruption  will  also occur  if  this script  is executed
twice with the same input.
END_OF_USAGE_TEXT

#---------------------------------------------------------------------
#                             usage notes
#---------------------------------------------------------------------

# (1) The 'clang-tidy' output log specifes absolute paths,  so we need
#     not worry about  calling this script from  within the same root.
#
# (2) This script is  intended to  be called by  the  'format_code.sh'
#     script. It may also be used directly.

#---------------------------------------------------------------------
#                            module setup
#---------------------------------------------------------------------

require 5.16.1;
use strict;
use Carp;
use warnings;
                                # Trap warnings
$SIG{__WARN__} = sub { die @_; };

#---------------------------------------------------------------------
#                           basic constants
#---------------------------------------------------------------------

use constant ZERO  => 0;        # Zero
use constant ONE   => 1;        # One
use constant TWO   => 2;        # Two

use constant FALSE => 0;        # Boolean FALSE
use constant TRUE  => 1;        # Boolean TRUE

#---------------------------------------------------------------------
#                         program parameters
#---------------------------------------------------------------------

my $PURPOSE  = 'Fixes "did you mean?" assumptions made by clang-tidy';
my $REVISION = '171114';
my $USE_LESS = FALSE;           # Flag: Use "less" for usage text

#---------------------------------------------------------------------
#                          global variables
#---------------------------------------------------------------------

my $PROGNAME;                   # Program name (without path)
   $PROGNAME =  $0;
   $PROGNAME =~ s@.*/@@;

#---------------------------------------------------------------------
#                          support routines
#---------------------------------------------------------------------

# "UsageError" prints  usage text for the current program,  then term-
# inates the program with exit status one.

#---------------------------------------------------------------------

sub UsageError
{
    $USAGE_TEXT =~ s@^\s+@@s;
    $USAGE_TEXT =~ s@\$PROGNAME@$PROGNAME@g;

    $USAGE_TEXT = << "END";     # "END" must be double-quoted here
$PROGNAME $REVISION - $PURPOSE

$USAGE_TEXT
END
    $USAGE_TEXT =~ s@\s*\z@\n@s;

    if ($USE_LESS && (-t STDOUT) && open (OFD, "|/usr/bin/less"))
    {
                                # "END" must be double-quoted here
        $USAGE_TEXT = << "END";
To exit this "help" text, press "q" or "Q".  To scroll up or down, use
PGUP, PGDN, or the arrow keys.

$USAGE_TEXT
END
        print OFD $USAGE_TEXT;
        close OFD;
    }
    else
    {
        print "\n", $USAGE_TEXT, "\n";
    }

    exit ONE;
}

#---------------------------------------------------------------------
#                            main routine
#---------------------------------------------------------------------

sub Main
{
    my $ifname;                 # Input (i.e., log) file name
    my $OptRun;                 # Flag: "--run" option

#---------------------------------------------------------------------
# Initial setup.

    select STDERR; $| = ONE;    # Force STDERR flush on write
    select STDOUT; $| = ONE;    # Force STDOUT flush on write

    for my $arg (@ARGV)
    {
        if ($arg =~ m@^-+run\z@i)
        {
            $OptRun = TRUE;
        }
        elsif ($arg =~ m@^-\z@i)
        {
            die "Invalid argument: $arg\n";
        }
        else
        {
            die "Error: Inaccessible or not a regular file: $arg\n"
                unless -f $arg;
            die "Error: Missing read permissions: $arg\n"
                unless -r $arg;
            die "Error: Can only specify one input file\n"
                if defined $ifname;
            die "Error: Input file shouldn't be .c or .h type\n"
                if $arg =~ m@\.[ch]\z@;
            $ifname = $arg;
        }
    }
                                # Final checks
    &UsageError() unless $OptRun && defined ($ifname);

#---------------------------------------------------------------------
# Read entire input file.

    open (IFD, "<$ifname") ||
        die "Error: Can't read input file: $!: $ifname\n";
    binmode (IFD);
    undef $/;
    my $data =  <IFD>;
       $data =  "" unless defined $data;
       $data =~ s@\015?\012@\n@gs;
    close IFD;

#---------------------------------------------------------------------
# Split the data into appropriate pieces.

    my $pat = '/\S+?\.[ch]:\d+:\d+:.*';

    $data =  "\n" . $data;
    $data =~ s@\001\002@@gs;

    if ($data !~ s@(\n)($pat)@${1}\001\002${2}@gi)
    {
        die "Error: File isn't formatted as expected: $ifname\n";
    }

    my @pieces = split (m@\001\002@, $data);

#---------------------------------------------------------------------
# Main loop.

    for my $piece (@pieces)     # Process all  pieces
    {                           # Process next piece

#---------------------------------------------------------------------
# Look for relevant pieces.

                                # Note: No "s" flag here
        next unless $piece =~ m@^.*did you mean@i;
        next unless $piece =~ m@^(/\S+?\.[ch]):(\d+):(\d+):@;

        # $cfname = Source-file pathname
        # $n1     = Line      number in file (1+)
        # $n2     = Character number in line (1+)
        # Note: Tab counts as one character!

        my ($cfname, $n1, $n2) = ($1, $2, $3);

#---------------------------------------------------------------------
# Check the current piece.

        if ($piece =~ m@\t@)
        {
            die << "END";
Error:  The input file shouldn't contain tabs. Warning: Do *not* detab
the file to correct this. Modify the program which creates the file to
begin with.
END
        }

        die "Error: ^ part isn't formatted as expected:\n$piece\n"
            unless $piece =~ m@^.*\n( *)\^\s*\n\s*(\S+)\s*\z@s;
        my $n3 = length ($1);

        die "Error: 2nd line isn't formatted as expected:\n$piece\n"
            unless $piece =~ m@^.*\n.{$n3}(\w+)@;
        my $fixit = $1;

#---------------------------------------------------------------------
# Check the referenced file.

        my $reffile = 'Referenced file';

        die "Error: $reffile is missing or inaccessible: $cfname\n"
            unless -f $cfname;
        die "Error: $reffile isn't readable: $cfname\n"
            unless -r $cfname;
        die "Error: $reffile isn't writable: $cfname\n"
            unless -w $cfname;

#---------------------------------------------------------------------
# Read entire referenced file into memory.

        open (IFD, "<$cfname") ||
            die "Error: Can't read referenced file: $!: $cfname\n";
        binmode (IFD);
        undef $/;
        my $xdata =  <IFD>;
           $xdata =  "" unless defined $xdata;
           $xdata =~ s@\015?\012@\n@gs;
        close IFD;

#---------------------------------------------------------------------
# Make specified edit in memory.

        my @xdata = split (/\n/, $xdata);
        $n1 -= ONE;
        $n2 -= ONE;

        $xdata [$n1] =~ s@^(.{$n2})\w+@${1}$fixit@;
        $xdata =  join "\n", @xdata;
        $xdata =~ s@\s*\z@\n@s;

#---------------------------------------------------------------------
# Write edited text back to file.

        open (OFD, ">$cfname") ||
            die "Error: Can't create output file: $!: $cfname\n";
        binmode (OFD);
        print OFD $xdata;
        close OFD;

        print "Edited $cfname\n";
    }

    undef;
}

#---------------------------------------------------------------------
#                            main program
#---------------------------------------------------------------------

&Main();                        # Call the main routine
exit ZERO;                      # Normal exit
