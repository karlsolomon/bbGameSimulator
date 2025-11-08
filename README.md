# bbGameSimulator
bbGameSimulator is a C++23 project that simulates a given number of baseball games using Monte-Carlo simulations. This generates statistical averages for runs scored and at-bats per game (ignoring plate attempts). This can be used to identify the expected runs (xRuns) and expected at-bats (xBats) for a team's given lineup.

## Requirements

* A C++23 compatible compiler (e.g., GCC 13+, Clang 16+)
* CMake (version 3.30 or higher)
* Ninja (recommended build system)
* Boost libraries (specifically `program_options`)

## Building

To build the project, run the following commands from the root directory:

```bash
# Create a build directory and configure CMake
# Replace <compiler> with your C++23 compiler (e.g., g++, clang++)
cmake -D CMAKE_CXX_COMPILER=<compiler> src/ -G Ninja -B build

# Compile the project
ninja -C build
```

### Example with g++:
```
cmake -D CMAKE_CXX_COMPILER=g++ src/ -G Ninja -B build
ninja -C build
```

## Usage

After building you can run the simulator from the root directory with
`./build/baseball -f <path_to_csv_file> -n <number_of_games>`

### Arguments
* -f, --file: (Required) Path to a CSV file containing the team's player stats sorted by batting position
* -n, --numGames: (Required) Number of games to simulate
* -h, --help: Show help message

### Example
```
# Run 10,000 simulations using the astros.csv data file
./build/baseball -f ./examples/astros.csv -n 10000
```

## Input File Format
The simulator requires a csv file with a header row followed by player data. The simulation will use the first 9 players listed in the file as the batting lineup.
The expected columns are: `Player, AtBats, Singles, Doubles, Triples, HomeRuns, Walks, Outs`. Unless specified otherwise, all values are each batter's cumulative stats over an entire season. It is generally recommended to use the most recent (mostly healthy) season.
**Note**: The simulator does not currently opposing pitchers or pitchers' stats.
**Note**: The simulator assumes that `AtBats` is the sum of `Singles, Doubles, Triples, HomeRuns, Walks, and Outs`. In other words it dows not consider POs (Plate Opportunities) or PA (Plate Appearances).

## Output Interpretation
The program will print the simulation results to the console.

### Example Output:
```
Testing with 10000 game simulations
astros.csv
Runs: 4.0792 +/- 3.06: med 4
AB  : 40.8967 +/- 4.56: med 41
```

## License
This project is released under the MIT license. See the `LICENSE` file for details.

Copyright (c) 2024 Karl Solomon
