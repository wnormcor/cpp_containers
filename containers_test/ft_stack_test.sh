#! /bin/sh

RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
ENDCOLOR="\x1b[0m"

if [ -d "logs" ]; then rm -fr logs; fi
if [ -d "exec" ]; then rm -fr exec; fi
mkdir logs
mkdir exec

if [ -e diff_stack.txt ]; then rm diff_stack.txt; fi

# --------------------- STACK TESTS
clang++ -Wall -Wextra -Werror ft_stack_test.cpp -o exec/ft_stack && 

./exec/ft_stack > logs/stack_user.output

echo -e "${BLUE}Tests for stack successfully complied! Log file has been created.${ENDCOLOR}\n"

cp ft_stack_test.cpp std_stack_test.cpp

sed 's/ft::stack/std::stack/g' std_stack_test.cpp > output.file; mv output.file std_stack_test.cpp

clang++ -Wall -Wextra -Werror std_stack_test.cpp -o exec/std_stack &&

./exec/std_stack > logs/std_stack.output

echo -e "${GREEN}std_tests successfully complied! Log file has been created.${ENDCOLOR}\n"

diff logs/stack_user.output logs/std_stack.output > logs/diff_stack.txt

if [[ -z $(grep '[^[:space:]]' logs/diff_stack.txt) ]]
then
	echo -e "${GREEN}No differences found. Good job!${ENDCOLOR}\n"
else
	echo -e "${RED}Poor you, some std funcs are not identical to yours, here is the diff: ${ENDCOLOR}\n"
	cat diff_stack.txt
fi

rm std_stack_test.cpp
