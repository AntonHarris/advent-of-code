#!/usr/bin/perl

use strict;
use warnings;

use constant INPUT_FILE => "input_files/day04_input.txt";

sub fully_contains {
	my ($i1_s, $i1_e, $i2_s, $i2_e) = @_;
	return (($i1_s <= $i2_s && $i1_e >= $i2_e) || ($i1_s>= $i2_s && $i1_e <= $i2_e))
}

sub room_overlaps {
	my ($i1_s, $i1_e, $i2_s, $i2_e) = @_;
	return ($i1_s <= $i2_e && $i1_e >= $i2_s);
}

sub day04_1 {
	my $count_fully_contains = 0;
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		my @rooms = split /,/;
		$count_fully_contains++ if (fully_contains(split(/-/, $rooms[0]), split(/-/, $rooms[1])));
	}
	print "count_fully_contains: $count_fully_contains.\n";
	close($FI);
}

sub day04_2 {
	my $rooms_overlapping = 0;
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		my @rooms = split /,/;
		$rooms_overlapping++ if (room_overlaps(split(/-/, $rooms[0]), split(/-/, $rooms[1])));
	}
	print "count_overlaps: $rooms_overlapping.\n";
	close($FI);
}

day04_1();
day04_2();
