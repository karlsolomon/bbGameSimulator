# bbGameSimulator
Simulate runs scored by a baseball team given at bats (ignores plate attempts)

build with command:  ```cmake -D CMAKE_CXX_COMPILER=<compiler> src/ -G Ninja -B build; ninja -C build```  
run with command:  ```./build/baseball -f <csv_file> -n <num_games_to_simulate>```  

