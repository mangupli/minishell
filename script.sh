#!/bin/bash
rm own_shell bash_shell
export to_test="echo ~"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test="\'export\' \'q\'=e \"w\"=c e=\"h\" r=\'o\' \'t\'=\'x\' \"y\"=\"p\" u=r i=t"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

export to_test="\'e\'\"x\"p\'o\'r\'t\' \"t\"$q\'s\'$i=\'h\'\"e\"\'l\'l$r"
echo -e "\033[0;31mcommand=\"$to_test\"\033[0m"
./minishell > own_shell
echo $to_test | bash > bash_shell
diff own_shell bash_shell

















