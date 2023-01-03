#!/usr/bin/perl

use strict;
use warnings;

use constant INPUT_FILE => "input_files/day03_input.txt";

sub find_common_letter {
	my $str1 = shift @_;
	my @str1_letters = split //, $str1;
	my @common_letters = ();
	while (scalar @_) {
		my $str_to_cmp = shift @_;
		@common_letters = grep(/[$str_to_cmp]/, @str1_letters);
		@str1_letters = @common_letters;
	}
	return $common_letters[0];
}

sub value_priority {
	my $priority_string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return index($priority_string, $_[0])+1;
}

sub day03_1 {
	my $sum_priorities = 0;
	open(my $FI, "<", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		$sum_priorities += value_priority(find_common_letter(substr($_, 0, length($_)/2), substr($_, length($_)/2)));
	}
	close($FI);
	print "sum_priorities 3_1 = $sum_priorities.\n";
}

sub day03_2 {
	my $sum_priorities = 0;
	my @groups_of_three = ();
	open(my $FI, "<", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		push @groups_of_three, $_;
		if (3 == scalar @groups_of_three) {
			$sum_priorities += value_priority(find_common_letter(@groups_of_three));
			@groups_of_three = ();
		}
	}
	close($FI);
	print "sum_priorities 3_2 = $sum_priorities.\n";
}

day03_1();
day03_2();
