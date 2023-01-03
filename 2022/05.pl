#!/usr/bin/perl

use strict;
use warnings;

use constant INPUT_FILE => "input_files/day05_input.txt";

sub day05_1 {
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open ".INPUT_FILE.": $!.\n";
	my @stacks = ([], [], [], []);
	while (<$FI>) {
		chomp;
		last if (m/ 1   2   3   4   5   6   7   8   9 /);
		my @elements = split //;
		unshift (@{$stacks[1]}, $elements[1]) if ($elements[1] ne " ");
		unshift (@{$stacks[2]}, $elements[5]) if ($elements[5] ne " ");
		unshift (@{$stacks[3]}, $elements[9]) if ($elements[9] ne " ");
		unshift (@{$stacks[4]}, $elements[13]) if ($elements[13] ne " ");
		unshift (@{$stacks[5]}, $elements[17]) if ($elements[17] ne " ");
		unshift (@{$stacks[6]}, $elements[21]) if ($elements[21] ne " ");
		unshift (@{$stacks[7]}, $elements[25]) if ($elements[25] ne " ");
		unshift (@{$stacks[8]}, $elements[29]) if ($elements[29] ne " ");
		unshift (@{$stacks[9]}, $elements[33]) if ($elements[33] ne " ");
	}
	while (<$FI>) {
		chomp;
		next if (/^$/);
		/^move (\d+) from (\d+) to (\d+)$/;
		for (my $i=0 ; $i<$1 ; $i++) {
			push @{$stacks[$3]}, pop @{$stacks[$2]};
		}
	}
	close($FI);
	my $top_crates = "";
	for (my $i=1 ; $i<10 ; $i++) {
		my $tmp = pop @{$stacks[$i]};
		$top_crates = $top_crates.$tmp;
	}
	print "top_crates day 5_1: $top_crates.\n";
}

sub day05_2 {
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open ".INPUT_FILE.": $!.\n";
	my @stacks = ([], [], [], []);
	while (<$FI>) {
		chomp;
		last if (m/ 1   2   3   4   5   6   7   8   9 /);
		my @elements = split //;
		unshift (@{$stacks[1]}, $elements[1]) if ($elements[1] ne " ");
		unshift (@{$stacks[2]}, $elements[5]) if ($elements[5] ne " ");
		unshift (@{$stacks[3]}, $elements[9]) if ($elements[9] ne " ");
		unshift (@{$stacks[4]}, $elements[13]) if ($elements[13] ne " ");
		unshift (@{$stacks[5]}, $elements[17]) if ($elements[17] ne " ");
		unshift (@{$stacks[6]}, $elements[21]) if ($elements[21] ne " ");
		unshift (@{$stacks[7]}, $elements[25]) if ($elements[25] ne " ");
		unshift (@{$stacks[8]}, $elements[29]) if ($elements[29] ne " ");
		unshift (@{$stacks[9]}, $elements[33]) if ($elements[33] ne " ");
	}
	while (<$FI>) {
		chomp;
		next if (/^$/);
		my @tmp_array = ();
		/^move (\d+) from (\d+) to (\d+)$/;
		for (my $i=0 ; $i<$1 ; $i++) {
			push @tmp_array, pop @{$stacks[$2]};
		}
		for (my $i=0 ; $i<$1 ; $i++) {
			push @{$stacks[$3]}, pop @tmp_array;
		}
	}
	close($FI);
	my $top_crates = "";
	for (my $i=1 ; $i<10 ; $i++) {
		my $tmp = pop @{$stacks[$i]};
		$top_crates = $top_crates.$tmp;
	}
	print "top_crates day 5_2: $top_crates.\n";
}

day05_1();
day05_2();
