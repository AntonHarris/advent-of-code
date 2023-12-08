#!/usr/bin/perl

use strict;
use warnings;

my $INPUT_FILE = $ARGV[0] if @ARGV>0 or die "No input file specified.\n";

sub day17_1 {
}

sub day17_2 {
}

open my $fh, "< ", $INPUT_FILE or die "$INPUT_FILE: $!";
chomp(my @data = <$fh>);
close ($fh);

day17_1();
day17_2();
