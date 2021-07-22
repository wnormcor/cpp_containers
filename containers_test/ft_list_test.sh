#! /bin/sh

# скрипт для сравнения разницы отработки тестового мейна с нашим контенером и контейнером от STD

RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
ENDCOLOR="\x1b[0m"

if [ -d "logs" ]; then rm -fr logs; fi
if [ -d "exec" ]; then rm -fr exec; fi
mkdir logs
mkdir exec

if [ -e diff_list.txt ]; then rm diff_list.txt; fi

# --------------------- LIST TESTS
# компилируем тестовик
clang++ -Wall -Wextra -Werror ft_list_test.cpp -o exec/ft_list 

# запускаем и отдаем в list_user для сравнения
./exec/ft_list > logs/list_user.output

# успешная компляция и создания вывода
echo -e "${BLUE}Tests fot list successfully complied! Log file has been created.${ENDCOLOR}\n"

# заменяем все вызовы ft::list в std::list (через вывод седа с стд, потом этот файл подменяем в std_list_test.cpp)
sed 's/ft::list/std::list/g' ft_list_test.cpp > std_list_test.cpp

# компилируем тестовик с вызовами std::list для проверки
clang++ -Wall -Wextra -Werror std_list_test.cpp -o exec/std_list

# копируем в вывод std_list.output
./exec/std_list > logs/std_list.output

# успешная компиляция и сохранение вывода с std::list вызовами
echo -e "${GREEN}std_tests successfully complied! Log file has been created.${ENDCOLOR}\n"

# вызываем дифф для проверки результатов двух выводов
diff logs/list_user.output logs/std_list.output > logs/diff_list.txt

# если есть разница то показываем - если нет - радуемся!
if [[ -z $(grep '[^[:space:]]' logs/diff_list.txt) ]]
then
   echo -e "${GREEN}No differences found. Good job!${ENDCOLOR}\n"
else
   echo -e "${RED}Poor you, some std funcs are not identical to yours, here is the diff: ${ENDCOLOR}\n"
   cat logs/diff_list.txt
fi

rm std_list_test.cpp