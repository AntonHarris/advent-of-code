#!/usr/bin/perl

use strict;
use warnings;

my $INPUT_FILE = $ARGV[0] if @ARGV>0 or die "No input file specified.\n";

sub day08_1 {
    my @data = @_;
    my $data_len = scalar(@data);
    my $element_len = scalar(@{$data[0]});
    my @seen_array = ();
    for my $i (0..$data_len-1) {
        push(@seen_array, [(0)x($element_len-1)]);
    }

    # left to right, right to left
    for my $row (0..$data_len-1) {
        my ($tallest_tree_left, $tallest_tree_right) = (-1, -1);
        for my $col (0..$element_len-1) {
            if ($data[$row][$col] > $tallest_tree_left) {
                $seen_array[$row][$col] = 1;
                $tallest_tree_left = $data[$row][$col];
            }
            if ($data[$row][$element_len-1-$col] > $tallest_tree_right) {
                $seen_array[$row][$element_len-1-$col] = 1;
                $tallest_tree_right = $data[$row][$element_len-1-$col];
            }
        }
    }
    # top to bottom, bottom to top
    for my $col (0..$element_len-1) {
        my ($tallest_tree_top, $tallest_tree_bottom) = (-1, -1);
        for my $row (0..$data_len-1) {
            if ($data[$row][$col] > $tallest_tree_top) {
                $seen_array[$row][$col] = 1;
                $tallest_tree_top = $data[$row][$col];
            }
            if ($data[$data_len-1-$row][$col] > $tallest_tree_bottom) {
                $seen_array[$data_len-1-$row][$col] = 1;
                $tallest_tree_bottom = $data[$data_len-1-$row][$col]
            }
        }
    }
    # Count seen from seen_array
    my $count_seen = 0;
    for my $line (@seen_array) {
        $count_seen += scalar(grep { $_ == 1 } @$line );
    }
    print "Number of trees seen: $count_seen.\n";
}

sub day08_2 {
    my @data = @_;
    my $data_len = scalar(@data);
    my $element_len = scalar(@{$data[0]});
    my $top_scenic_score = 0;
    for my $row (1..$data_len-2) {
        for my $col (1..$element_len-2) {
            my ($top_score, $right_score, $bottom_score, $left_score, $scenic_score) = (0, 0, 0, 0, 0);
            my $curr_tree_height = $data[$row][$col];
            # top
            for (my $i=$row-1 ; $i >= 0 ; $i--) {
                $top_score++;
                last if ($data[$i][$col] >= $curr_tree_height);
            }
            # right
            for (my $i = $col+1 ; $i <= $element_len-1  ; $i++) {
                $right_score++;
                last if ($data[$row][$i] >= $curr_tree_height);
            }
            # bottom
            for (my $i=$row+1 ; $i <= $data_len-1 ; $i++) {
                $bottom_score++;
                last if ($data[$i][$col] >= $curr_tree_height);
            }
            # left
            for (my $i = $col-1 ; $i >= 0  ; $i--) {
                $left_score++;
                last if ($data[$row][$i] >= $curr_tree_height);
            }
            $scenic_score = $top_score*$right_score*$bottom_score*$left_score;
            $top_scenic_score = $scenic_score if ($scenic_score > $top_scenic_score);
        }
    }
    print "Top scenic score: $top_scenic_score.\n";
}

my @data = ();
open my $fh, "< ", $INPUT_FILE or die "$INPUT_FILE: $!";
while (<$fh>) {
    chomp;
    push(@data, [split(//, $_)]);
}
close ($fh);

day08_1(@data);
day08_2(@data);
