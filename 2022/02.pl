#!/usr/bin/perl

use strict;
use warnings;

use constant INPUT_FILE => "input_files/day02_input.txt";

my %RPC_results = (
	LOSS => 0,
	DRAW => 3,
	WIN  => 6,
	X    => 0,
	Y    => 3,
	Z    => 6,
);

my %RPC_values = (
	A => 1,
	B => 2,
	C => 3,
	X => 1,
	Y => 2,
	Z => 3,
);

my %RPC_loss_draw_win_index = ( X => 0, Y => 1, Z => 2,);
my %RPC_loss_draw_win = (
	A => ['Z', 'X', 'Y'],
	B => ['X', 'Y', 'Z'],
	C => ['Y', 'Z', 'X'],
);

sub RPC_game {
	my ($hand1, $hand2) = @_;
	return $RPC_results{"DRAW"} if ($RPC_values{$hand1} == $RPC_values{$hand2});
	return $RPC_results{"WIN"} if (($RPC_values{$hand2} - $RPC_values{$hand1} == 1) || ($RPC_values{$hand2} - $RPC_values{$hand1} == -2));
	return $RPC_results{"LOSS"};
}

sub day02_1 {
	my $score = 0;
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		my @play = split(/ /);
		$score = $score + $RPC_values{$play[1]} + RPC_game(@play);
	}
	close($FI);
	return $score;
}

sub day02_2 {
	# X should be LOSS, Y should be DRAW, Z should be WIN
	my $score = 0;
	open(my $FI, "< ", INPUT_FILE) or die "Unable to open file ".INPUT_FILE.": $!.\n";
	while (<$FI>) {
		chomp;
		my @play = split(/ /);
		$score = $score + $RPC_values{$RPC_loss_draw_win{$play[0]}[$RPC_loss_draw_win_index{$play[1]}]} + $RPC_results{$play[1]};
	}
	return $score;
}

print "Rock Paper Scissors 2_1 score is: ".day02_1().".\n";
print "Rock Paper Scissors 2_2 score is: ".day02_2().".\n";
