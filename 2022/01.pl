#!/usr/bin/perl

use strict;
use warnings;

sub day01_1 {
	my ($max_calories, $current_calorie_count) = (0);
	open(my $FI, "< ", "input_files/day01_input.txt") or die "Unable to open file day01_input.txt: $!.\n";
	while (<$FI>) {
		chomp;
		if (/^$/) {
			$max_calories=$current_calorie_count if ($current_calorie_count > $max_calories);
			$current_calorie_count = 0;
		} else {
			$current_calorie_count += $_;
		}
	}
	close ($FI);	
	print "Day 1_1: Max calorie count = $max_calories.\n";
}

sub day01_2 {
	my @max_calories_array = ();
	my $current_calorie_count = 0;
	open(my $FI, "< ", "input_files/day01_input.txt") or die "Unable to open file day01_input.txt: $!.\n";
	while (<$FI>) {
		chomp;
		if (/^$/) {
			push @max_calories_array, $current_calorie_count;
			$current_calorie_count = 0;
		} else {
			$current_calorie_count += $_;
		}
	}
	close ($FI);
	my @max_calories_array_sorted = reverse sort { $a <=> $b } @max_calories_array;
	print "Day 1_2: Sum top 3 calorie count = ", $max_calories_array_sorted[0]+$max_calories_array_sorted[1]+$max_calories_array_sorted[2], ".\n";
}

day01_1();
day01_2();
