

#           220419 - MINISHELL

#INDEX
------
##  Misc
##  Interactive Non-Login Shell Behavior:
##  Fonctions autorisées
##  Error management
##  Parsing
##  Termios
##  Tests
##  Valgrind check

##  Misc

    /*
     ** Security layer for 'ft_strjoin'.
     */

    char	*ft_strjoin_free_s2(char *s1, char *s2)
    {
        char	*temp;

        temp = s2;
        s2 = ft_strjoin(s1, s2);
        if (temp)
        {
            free(temp);
            temp = NULL;
        }
        return (s2);
    }

    /*
     ** Security layer for 'ft_strjoin'.
     */

    char	*ft_strjoin_free_s1(char *s1, char *s2)
    {
        char	*temp;

        temp = s1;
        s2 = ft_strjoin(s1, s2);
        if (temp)
        {
            free(temp);
            temp = NULL;
        }
        return (s2);
    }

    /*
     ** Security layer for 'ft_strjoin'.
     */

    char	*ft_strjoin_free(char *s1, char *s2)
    {
        char	*temp1;
        char	*temp2;
        char	*s3;

        temp1 = s1;
        temp2 = s2;
        s3 = ft_strjoin(s1, s2);
        if (temp1)
        {
            free(temp1);
            temp1 = NULL;
        }
        if (temp2)
        {
            free(temp2);
            temp2 = NULL;
        }
        return (s3);
    }

Builtins:
- cd        (rel || abs)
- pwd       (!opts)
- export    (!opts)
- unset     (!opts)
- env       (!opts && !args)
- exit      (!opts)

Invoke Bash in POSIX mode:
    $ bash --posix
Invoke last command matching pattern:
    $ <Esc>p<pattern>
Access readline params:
    $ <Esc>n<argument>

Display all the fds that are open by minishell:
    $ lsof | grep "minishell"

- Bash outputs the prompt to '/dev/tty' not '/dev/stdout' or '/dev/stdin'.

[Bash Variables](https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html)

[Sigaction](https://www.i-programmer.info/programming/cc/13528-applying-c-signals.html?start=1)

##  Interactive Non-Login Shell Behavior:

    Input
    ↓
    Lexical Analysis + Parsing
    ↓
    Expansions → Command Execution → Exit Status
    ↓        ↑
    1. Brace Expansion
    2. Tilde Expansion
    3. Variable and Parameter, Expansion, Command, Process, Arithmetic Substitution
    4. Word Splitting
    5. Filename Generation

[Interactive Shell Behavior](https://www.gnu.org/software/bash/manual/html_node/Interactive-Shell-Behavior.html)


 README

 'sigaction()'
 	https://www.i-programmer.info/programming/cc/13528-applying-c-signals.html

 'rl_on_new_line()'
 	Tell the update functions that we have moved onto a new (empty) line,
 	usually after outputting a newline.

 'rl_replace_line()'
		Replace the contents of rl_line_buffer with text. The point and mark
 	are preserved, if possible. If clear_undo is non-zero, the undo list
		associated with the current line is cleared.

 'rl_redisplay()'
		Change what's displayed on the screen to reflect the current contents
		of rl_line_buffer.



1. *Startup* file `~/.bashrc` is read and executed.

2. *Job Control* is (enabled by default) in effect, Bash ignores the
keyboard-generated job control *signals*: `SIGTTIN`, `SIGTTOU` and `SIGTSTP`.

3. Bash expands and displays `$PS1` before reading the 1st
*command-line* or expands and displays. `$PS2` before reading the 2nd
and subsequent lines of a *multi-line command*. `$PS0` after it reads
a command but before executing it.
[Controlling the Prompt](https://www.gnu.org/software/bash/manual/html_node/Controlling-the-Prompt.html)

4. Bash executes the values set elements of the `$PROMPT_COMMAND`
array as commands before printing the primary prompt `$PS1`.

5. *Readline* is used to read commands from the user's terminal.

6. Bash inspects the value of the `ignoreeof` option to set -o instead
of exiting immediatley when it receives an *EOF* on its standard input
when reading a command.

7. Command history and *history* expansion are enabled by default. Bash
will save the command history to the file named by `$HISTFILE` when a
shell with history enabled exists.
[Command History](https://www.gnu.org/software/bash/manual/html_node/Bash-History-Facilities.html)
[History Expansion](https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html)

8. *Alias* expansion is performed by default.

9. Bash ignores `SIGTERM` (so the `kill 0` doesnt kill an interactive
shell).

10. `SIGINT` is caught and handled (`SIGINT` will interrupt some shell
builtins).

11. An interactive login shell sends a `SIGHUP` to all jobs on exit if
the `huponexit` shell option has been enabled.

12. The -n (read commands but do not execute them) invocation option
is ignored, and `set -n` has no effect.

13. Bash will check for mail periodically, depending on the values of
the `MAIL`, `MAILPATH`, and `MAILCHECK` shell variables.

14. Expansion errors due to references to unbound shell variables
after `set -u` has been enabled will not cause the shell to exit.

15. The shell will not exit on expansion errors cause by `var` being
unset or null in `${var:?word}` expansions.
[Shell Parameter Expansion](https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html)

16. Redirection errors encountered by shell builtins will not cause
the shell to exit.

17. When running in POSIX mode, a special builtin returning an error
status will not cause the shell to exit

18. A failed `exec` will no cause the shell to exit.

19. Parser syntax errors will not cause the shell to exit.

20. Simple spelling correction for directory arguments to the 'cd'
builtin is enabled by default (cdspell option to shopt builtin)

21. The shell will check the value of the TMOUT variable and exit if a
command is not read within the specified number of seconds after
printing $PS1

##  Fonctions autorisées

exit            : known
free            : known
malloc          : known
printf          : known

strerror        : return pointer string that describes the error code passed in arg
perror          : produces message on stderr describing the last encounterd error

open            : open the file specified by 'pathname'
read            : read bytes from fd into a buffer
write           : write bytes from a buf to a fd
close           : close a fd
dup             : duplicate an existing fd
dup2            : dup an existing fd
    let us to choose this value
    (if the choosen value is already taken it will be closed and open to our target)
kill            : send a signal to a process
fork            : create a child process
pipe            : create a pair of fd for interprocess communication
*wait*            : wait for a process termination signal
waitpid         : wait for a specific process
access          : check the accessibility
unlink          : remove directory entry
execve          : execute an executable file
    char *argList[] = { "ls", "-l", NULL };
    dprintf(2, "%i\n", execve("/bin/ls", argList, NULL));

add_history     : readline history
stat            : return info about a file pointed to by 'pathname' (like ls)
fstat           : same as stat but return info about a file pointed to by a fd
lstat           : return info about a file (or a symlink itself if 'pathname' is a symlink)
getcwd          : return the cwd abs path (size max = PATH_MAX)
chdir           : change working directory
getenv          : take an env key and return its value or NULL
opendir         : open a directory and return a pointer to it
readdir         : ***???*** lit l'entrée suivante dans le fd du dossier
readline        : read a line from the terminal and return it prefixed with the given 'prompt'
    vi mode possible

rl_clear_history:
rl_on_new_line  : tell the update functions that we have moved onto a new (empty) line, usually after outputting a new line.
rl_replace_line : repl the contents of rl_line_buffer with text
rl_redisplay    : change what's displayed on the screen to reflect the current content of rl_line_buffer
sigaction       : used to change the action taken by a process on receipt of a spec signal
sigaddset       : manipulate POSIX signal set
sigemptyset     : manipulate POSIX signal set
signal          : handle signals by running arbitrary function


* Terminal options:

tcgetattr       : gets params associated with the object referred by fd and stores them in the termios structure referenced by termios_p.
tcsetattr       : sets params associated with the terminal from the termios structure referred to by termios_p. (opts spec when changes take effect)
tgetent         :
tgetstr         :
tgetnum         :
tgetflag        :
tgoto           :
tputs           :

ioctl           : open an fd to a device ***???***
isatty          : tests whether fd is an open fd referring to a terminal
ttyname         : take a fd and returns a pointer to the 'pathname' of the open term device
ttyslot         : return the index of the current user's entry in some file

'builtin' commands can be executed by the minishell.
'external' commands need a *fork process*.

##  Error management

1       Catchall for general errors impermissible operations
2       Misuse of shell builtins
126     Command invoked cannot execute (permission problem or not an executable)
127     Command not found
128     Invalid argument to exit
128+n   Error signal n
130     Script terminated by Control-C
255     Exit status out of range

##  Parsing

[AST French Explanation](https://github.com/LucieLeBriquer/minishell)

https://www.grymoire.com/Unix/Quote.html
https://www.gnu.org/software/bash/manual/bash.html#Double-Quotes
https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html

##  Termios

https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios/

- tty: terminal (physical)

- pty: pseudo-terminal (virtual), a pair of endpoints ('master'
  connected to the terminal emulator for input and 'slave' connected to the
  running program for output) that provide bidirectional communication channel.

     IN ------------------------------------------------------>
    (console)===(master pty)===(termios)===(slave pty)===(shell)
     <----------------------------------------------------- OUT

##  Tests

**Commandline:**

    [ ] tofix
    [X] fixed

* Parsing:
    [X] echo ""
    [X] echo "$NOP"
    [X] echo "something"
    [X] echo "$USER"
    [X] echo $UU $USER
* Parsing (variable expansion):
    [X] echo 1. "$t=TEST" 2. $USER=USER 3. $USERR 4. $USER= 5. $=42 6. $100 7. $0tray
    [X] $U$USER
    [X] echo -nnnnnnnn
    [X] echo -nnn -nnnn -nnn
    [X] echo -nSalut
    [ ] echo "$TEST$TEST=lol$TEST"
    [ ] echo $TEST$TEST=lol$TEST""lol
    [ ] echo "$=TEST"
    [ ] echo "$1TEST"
    [ ] echo ciao ;|
    [ ] echo ciao |;
    [ ] echo ciao ||||;
    [ ] echo ciao <<<<
    [ ] echo ciao >>>
    [ ] echo ciao >>>>>
    [ ] echo ciao <<<;

* Path:
    [ ] mkdir a; cd a; rmdir a; unset PWD; pwd

    [x] chmod 000 /home; cd -
    [ ] cat;ls puis ctrl-c, le ls ne dois pas s'exécuter.
    [ ] export +=
    [ ] export var="cat Makefile | grep p" puis $var
    [ ] SHLVL augmente à chaque couche de minishell
    [ ] echo bonjour > $var
    [ ] Export var=" f1 f2 "

    [ ] mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd

    [ ] export A=a; echo $A;

    [ ] export ffff="   "; ffff; "    "

* Redir:
    [ ] < Makefile > out | echo salut > out
    [ ] < Makefile cat > out | echo salut > out
    [ ] < Makefile cat > out | wc -l > out
    [ ] < Makefile cat > out | wc -l >> out
    [ ] << STOP cat > out | wc -l >> out
    [ ] < Makefile wc -l > out | < Makefile grep CC >> out


**Behavior:**

Should not write 'salut' while 'yes' command is running:
    $ yes<CR>
    $ salut<CR>
    $ <C-C>

##  Valgrind check

valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell


valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell
