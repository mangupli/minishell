# minishell

This group project is all about creating a simple shell and working in a team.

**Mstoneho**: parser part;
**Mangupli(lizagap)**: processor part;

## How to use
```
make
./minishell
```
then opens up a prompt that will wait for your command:
```
superbash>
```
exit from minishell like from normal shell: print **exit** command


## Our minishell:

- doesn't interpret unclosed quotes or unspecified special characters like \ or;..
- has a working History.
- searches and launches the right executable (based on the PATH variable or by using
relative or absolute path)

- it implements the builtins:
1. echo with option -n
2. cd with only a relative or absolute path
3. pwd with no options
4. export with no options
5. unset with no options
6. env with no options or arguments
7. exit with no options

**The following works like in bash**

- double quotes and single quotes
- redirections
- pipes 
- environment variables
- $? 
- ctrl-C ctrl-D ctrl-\ 

**Additional files**

script.sh - for testing

CMakeLists.txt - for building cmake project in CLion
