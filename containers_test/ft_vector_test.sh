#! /bin/sh

RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
ENDCOLOR="\x1b[0m"

if [ -d "logs" ]; then rm -fr logs; fi
if [ -d "exec" ]; then rm -fr exec; fi
mkdir logs
mkdir exec

if [ -e diff_vector.txt ]; then rm diff_vector.txt; fi

# --------------------- VECTOR TESTS
clang++ -Wall -Wextra -Werror ft_vector_test.cpp -o exec/ft_vector && 

./exec/ft_vector > logs/vector_user.output

echo -e "${BLUE} Tests for vector successfully complied! Log file has been created.${ENDCOLOR}\n"

cp ft_vector_test.cpp std_vector_test.cpp

sed 's/ft::vector/std::vector/g' std_vector_test.cpp > output.file; mv output.file std_vector_test.cpp

clang++ -Wall -Wextra -Werror std_vector_test.cpp -o exec/std_vector &&

./exec/std_vector > logs/std_vector.output

echo -e "${GREEN}std_tests successfully complied! Log file has been created.${ENDCOLOR}\n"

diff logs/vector_user.output logs/std_vector.output > logs/diff_vector.txt

if [[ -z $(grep '[^[:space:]]' logs/diff_vector.txt) ]]
then
   echo -e "${GREEN}Vector test successfully passed. Good job!${ENDCOLOR}\n"
else
   echo -e "${RED}Poor you, some std funcs are not identical to yours, here is the diff: ${ENDCOLOR}\n"
   cat diff_vector.txt
fi

rm std_vector_test.cpp
