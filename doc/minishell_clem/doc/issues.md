
#           ISSUES

>       help

# //////////////////////// ATHIRION

echo    \n hola
""''echo hola""'''' que""'' tal""''
echo \$HOME
echo $UID
echo $USER$var\$USER$USER\$USERtest$USER

export ""
export HO$?LA=bonjour ; env
export HOLA=$HOME

<<<<<<< Updated upstream
export HOLA="bonjour         "
export HOLA="  -n bonjour   "

export HOLA="s -la" ; l$HOLA
export HOL=A=""

export HOLA=p ; export BYE=w ;$""HOLA"$"BYE"d

SHLVL = 2

exit 9223372036854775808

ls | exit 42

export HOLA=hey ; echo bonjour > $HOLA ; echo $HOLA

echo hola > > bonjour

# //////////////////////// CVIDON

> echo '' ''salut
> echo ''''salut

# //////////////////////// ???

-  Fix make sani

- Fix status code
> `<C-C>` then `|` then `echo $?`

- Check substr
> Check substr (strlen **-1**)

- Normify
> Norm

##  Wtf

- Backslash is a character
> `rm \\  <-`

- Maybe remove tokpos

- Fix errmsg
> `/`, `//`, `///` etc. Should print `Is a directory` not `Permission denied`

- Exec signals
> `cat | cat` + SIGINT/SIGQUIT not handled.
> Should be same as `cat` + SIGINT/SIGQUIT.

- Fix << STOP cat << HELL cat >
> should display 'cat: cat: No such file or directory'
> error code should be 1 and not 0

- Add bonus errmsg management:
> `~` should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar` should print: `bash: $notavar: ambiguous redirect`
