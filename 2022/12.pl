#!/usr/bin/perl

use strict;
use warnings;

my $INPUT_FILE = $ARGV[0] if @ARGV>0 or die "No input file specified.\n";

sub day12_1 {
}

sub day12_2 {
}

open my $fh, "< ", $INPUT_FILE or die "$INPUT_FILE: $!";
chomp(my @data = <$fh>);
close ($fh);

day12_1();
day12_2();
