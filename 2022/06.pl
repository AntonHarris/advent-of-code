#!/usr/bin/perl

use strict;
use warnings;

use constant INPUT_FILE => "input_files/day06_input.txt";

sub all_unique {
	my %elements = ();
	my $input_size = scalar @_;
	foreach (@_) {
		$elements{$_}++;
	}
	return $input_size == scalar keys %elements;
}

sub day06_X {
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	$_ = <$FI>;
	close ($FI);
	my @letters = split //;
	my @buffer = ();
	my $buffer_size = shift @_;
	for (my $i=0 ; $i<$buffer_size ; $i++) {
		push @buffer, shift @letters;
	}
	my $char_to_check = shift @letters;
	my $count_pos = $buffer_size;
	while (! all_unique(@buffer)) {
		shift @buffer;
		push @buffer, $char_to_check;
		$char_to_check = shift @letters;
		$count_pos++;
	}
	return $count_pos;
}

sub day06_1 {
	print "day06_1: ".day06_X(4).".\n";
}

sub day06_2 {
	print "day06_2: ".day06_X(14).".\n";
}

day06_1();
day06_2();
