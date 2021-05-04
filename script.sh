#!/bin/bash
rm own_shell bash_shell

export to_test="echo         \'\"\\"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test=">fil$q\'1\' e$w\"ho\" s$i\"r\"ing f$r$u file1"
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

export to_test="echo hello '\' ';' "   '\' \" \" \" \"$PWD\\\"\~\;\"\; >> t1 \' \ \ \\"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test="ec\"ho;\";pwd"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

















