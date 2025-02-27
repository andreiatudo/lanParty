# Requirements

A list will be created with the information from the file d.in (the list will be formed by adding elements at the beginning - O(1)).
Teams with the lowest team score will be removed from the previously created list so that only n teams remain (where n is the maximum possible power of 2). If multiple teams have the same score, the first team found in the list will be removed. After each removal, the list traversal will restart from the beginning.
The necessary data structures will be implemented to conduct the matches:
A queue will be created in which matches between teams will be placed.
Teams will form matches in the order they appear in the previous list, the first two teams forming the first match (and so on).
Two stacks will be created - one for losers and one for winners - containing teams that lost or won the previous match.
Teams will be added to the stack based on their results, and one point will be added to the team score of the winning teams.
In case of a match where both teams have the same score, the first team added to the match will be chosen.
Teams in the loser stack will be deleted (at the end of each stage; e.g., in a round with 8 teams, deletion occurs after all eliminations. In this case, after 4 teams have been eliminated, they will be deleted. In the next round, for this example, 2 teams will be added to the loser stack, which will then be cleared again).
Teams will be extracted from the winner stack and the match queue will be refilled, forming matches with consecutive teams (the first team removed from the stack will play against the second removed team in the first match).
The steps will be repeated until the top 8 teams are determined, which will be saved in another list. After identifying them, the matches will continue until the winning team is determined.
A ranking of the last 8 teams (saved in the previous step) will be created in the form of a BST (Binary Search Tree). It will be sorted by team score and displayed in descending order (if two teams have the same score, they will be sorted by name in descending order).
An AVL tree will be created with the last 8 teams (saved in step 3 but sorted as in step 4), and the teams on the second level of the tree will be displayed.

# Main

In main, the files were opened and checked if they opened correctly.
The task values were read to determine which tasks to perform.
The number of teams was read.
For each task, an if condition was used to check execution.

## Task 1

All teams were read using the add function in a loop.

## Task 2

The highest power of 2 less than or equal to the number of teams was calculated.
The team scores were calculated, and teams with the lowest score were removed.

The list was displayed.

## Task 3

The queue was created, and teams were added to it.
Winner and loser stacks were formed.
If the remaining number of teams was 8, a list was created with the last 8 remaining teams.
The loser list was cleared.
Winning teams were placed back into the queue.

## Task 4

The BST was created and then displayed in in-order traversal.

## Task 5

The AVL tree was created using the BST.
A function was used to display the nodes at the second level, from root to leaf (**depth, not height**).

# File: lanPartyLib.c

## player_read

Reads a player.

## add_player

Adds the player to the team.

## add_team

Creates the entire team by reading the number of players from the file, removing that number, leaving only the team name.

## display

Displays the list and removes the extra space from team names in the file.

## remove_team

Removes the team with the lowest score.

## team_points

Calculates the number of points.

## total_points_function

Assigns the total points to a team.

## delete

Finds the lowest score and removes the corresponding team.

## Copy

Copies a team into another team using deep copy.

## display_queue

Displays the team names in the queue exactly as required.
The fprintf function aligns the first team's name 33 spaces to the left, adds a hyphen, then aligns the second team's name to the right.

## createStacks

This function creates the winner and loser stacks.

## score_correction

At some point, discrepancies in scores were found in test cases. After verification, the scores did not match the result files, so this function was created.

## display_stack

This function displays the team name character by character, followed by the score.
This display approach was chosen because the previous one did not fit exactly in this case, so another idea was tried.

## create_list

This function creates the list of the top 8 teams.

## For creating the BST and AVL, only course functions were used (for queue, stack, and most of the program).

## inorder_selection

This function retrieves nodes in the correct order from the BST and places them in the AVL.

## print_nodes

A recursive function that displays all nodes at a given level, in our case, the second. This function keeps track of the current level, and if it matches the desired level, it prints the team name. It searches the right subtree first, then the left. This order is followed because it matches the result file.

## Next, several functions for memory deallocation follow.

# File: lanPartyLib.h

This file contains the libraries and declarations of all structures and subprograms.
