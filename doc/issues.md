
#           ISSUES

>       help

# //////////////////////// BEWARE


>		***** Cas additionnel de $ entre double quotes avec texte qui n'est pas une variable *****
		check "$tata" --> must return "" (command not found)

		use empty token (check if empty token = only when "" or '')
		if empty token, maybe consider that it is "" or ''
		--> ET LES REMETTRE ????????????? (dans clean token)

			1. dans DEL_QUOTES:
				on checke si $ dans " " et au moins un caractère après $ qui n'est pas un $
				--> on passe les " " en negatif (on les conserve jusqu'au clean)
				ex : 	"$top", "$2"... --> " en négatif
						"$$$$" 			--> " pas en négatif
			2. expand
			3. clean :
			- si les " " en négatif sont vides, alors les mettre en positif et les conserver
			- sinon, supprimer les " "

		***** Cas d'un $ suivi immédiatement d'un chiffre, le tout hors ' ' *****
			Dans DEL_QUOTES aussi :
			- faire une condition dans le cas où $ n'est pas entre ' ' mais est suivi d'un chiffre
				--> supprimer $2
				comme pour 	$"USER" --> USER : on supprime le $
							$24444	--> 4444 : on supprime $2

>		***** CAS DE $? *****
		- si '$?' 		--> texte donc $ en négatif (déjà géré), type "WORD" ou "COMMAND"
		- si $? ou "$?" --> type special "ERR_STATUS" (à créer dans enum)
			et :
				- si pas echo avant --> doit faire apparaitre 0
				- si devant echo --> à traiter dans built-in
			/!\
			echo $?$? $?	--> affiche plusieurs fois le dernier error status (ex: 127127 127)
			echo coucou $?	--> affiche le dernier error status (ex: coucou 127)
			echo yo $? cou	--> affiche le dernier error status (ex: yo 127 cou)

			pour les token --> un seul word après echo et -n
			puis gérer les $? dans echo (exec part)
			ex:	echo $?coucou top $? youhou		--> 0coucou top 0 youhou





		Invalid read of size 1:
>		< file cmd '$USER' '' | "$youhou" << dd << dd | " $    'youpi"

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


