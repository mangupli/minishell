#!/bin/bash
rm own_shell bash_shell

export to_test="echo         \'\"\\"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test="echo '\'"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test="echo \hello \$PWD"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

















