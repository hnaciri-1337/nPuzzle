#include "nPuzzle.hpp"

int	main(int ac, char **av) {
	nPuzzle puzzle;
	

	if (ac != 2)
		fatal_error("Usage: ./n_puzzle [file]");
	puzzle.readPuzzle(av[1]);
	if (puzzle.isSolvable() == false)
		fatal_error("Error: puzzle is not solvable");
	puzzle.readOptions();
	puzzle.solvePuzzle();
	puzzle.printSolution();
	return 0;
}
