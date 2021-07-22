#! /bin/sh

RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
ENDCOLOR="\x1b[0m"

if [ -d "logs" ]; then rm -fr logs; fi
if [ -d "exec" ]; then rm -fr exec; fi
mkdir logs
mkdir exec

if [ -e diff_map.txt ]; then rm diff_map.txt; fi

# --------------------- MAP TESTS
clang++ -Wall -Wextra -Werror ft_map_test.cpp -o exec/ft_map && 

./exec/ft_map > logs/map_user.output

echo -e "${BLUE}Tests for map successfully complied! Log file has been created.${ENDCOLOR}\n"

cp ft_map_test.cpp std_map_test.cpp

sed 's/ft::map/std::map/g' std_map_test.cpp > output.file; mv output.file std_map_test.cpp

clang++ -Wall -Wextra -Werror std_map_test.cpp -o exec/std_map &&

./exec/std_map > logs/std_map.output

echo -e "${GREEN}std_tests successfully complied! Log file has been created.${ENDCOLOR}\n"

diff logs/map_user.output logs/std_map.output > logs/diff_map.txt

if [[ -z $(grep '[^[:space:]]' logs/diff_map.txt) ]]
then
   echo -e "${GREEN}No differences found. Good job!${ENDCOLOR}\n"
else
   echo -e "${RED}Poor you, some std funcs are not identical to yours, here is the diff: ${ENDCOLOR}\n"
   cat diff_map.txt
fi

rm std_map_test.cpp