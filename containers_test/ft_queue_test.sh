#! /bin/sh

RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
ENDCOLOR="\x1b[0m"

if [ -d "logs" ]; then rm -fr logs; fi
if [ -d "exec" ]; then rm -fr exec; fi
mkdir logs
mkdir exec

if [ -e diff_queue.txt ]; then rm diff_queue.txt; fi

# --------------------- QUEUE TESTS

clang++ -Wall -Wextra -Werror ft_queue_test.cpp -o exec/ft_queue && 

./exec/ft_queue > logs/queue_user.output

echo -e "${BLUE}Tests for queue successfully complied! Log file has been created.${ENDCOLOR}\n"

cp ft_queue_test.cpp std_queue_test.cpp

sed 's/ft::queue/std::queue/g' std_queue_test.cpp > output.file; mv output.file std_queue_test.cpp

clang++ -Wall -Wextra -Werror std_queue_test.cpp -o exec/std_queue &&

./exec/std_queue > logs/std_queue.output

echo -e "${GREEN}std_tests successfully complied! Log file has been created.${ENDCOLOR}\n"

diff logs/queue_user.output logs/std_queue.output > logs/diff_queue.txt

if [[ -z $(grep '[^[:space:]]' logs/diff_queue.txt) ]]
then
   echo -e "${GREEN}No differences found. Good job!${ENDCOLOR}\n"
else
   echo -e "${RED}Poor you, some std funcs are not identical to yours, here is the diff: ${ENDCOLOR}\n"
   cat diff_queue.txt
fi

rm std_queue_test.cpp
