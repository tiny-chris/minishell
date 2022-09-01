
#           ISSUES

>       help

# //////////////////////// BEWARE

		Invalid read of size 1:
>		< file cmd '$USER' '' | youhou << dd << dd | " $    'youpi"

		Conditional jump or move depends on uninitialised value(s)
	+	Invalid read of size 1:
>		< file cmd '$USER' '' | youhou << dd << dd | $

		--> si $ tout seul, si "$"
		--> OK si '$', "$ ", $USER, $youpi...
		--> OK si "<" ou ">"

>		CHECK pour "enter"
		si ca existe ?
		--> si non on sort --> si pas une string avec une vraie adresse
		--> si oui, on regarde si la len vaut 0 --> renvoie le prompt (probablement readline enlève le \n)

# //////////////////////// LENA


# //////////////////////// CHRISTEL

# //////////////////////// TO DO

>		create a function to init t_data
>		create function(s) to free all mallocs (garbage collector?)
>		reset the compilator to 'clang' !! (modified to gcc for valgrind use)
>		a re-tester avec les $ et espaces : $USER $$USER $'coucou' $$$$$$$$$'USER' "$$  "
>		free clean_cmd_no_redir; token; tok_redir in ft_free_cmd


##  WTF


