
#           ISSUES

>       help

>	Attention dans le history
	Quand on a un echo -n (pas de retour à la ligne), lorsqu'on veut sélectionner de précédentes commandes, la prompt line 'minishell>' s'efface... (ou ne s'affiche plus)

>	** tests non concluants **


	/*********************/
	A TESTER QUAND HERE-DOC CODE
	/*********************/
	>	** à tester **
	$tutu $toto <youpla pwd $tut <<$$$$bou super $?
	-->
	> ""
	>
	> $bou
	> $$$bou
	> $$$$bou
	bash: youpla: No such file or directory
	/*********************/
	

# //////////////////////// BEWARE


>	tests corrigés - A RETESTER avant la fin



	/***********/
	FIXED !
	/***********/
	$tutu $toto <youplaboom pwd $tut super $? | wc
		--> OK - fonctionne (quand le file n'existe pas, pas de pwd)
	
	PAR CONTRE:
	$tutu $toto <youplaboom pwd $tut super $?
		--> PAS OK - NE fonctionne PAS:quand le file n'existe pas, affiche de pwd car une seule commande
	/***********/


	/***********/
	FIXED !
	/***********/
	toto | $tutu >outfile |echo -nnn -nnnn -nnnnnnnnnnnnnnn --n youpi
		--> bash:
				--n youpi
				Command 'toto' not found, but can be installed with:

				snap install toto

				Exception ignored in: <_io.TextIOWrapper name='<stdout>' mode='w' encoding='utf-8'>
				BrokenPipeError: [Errno 32] Broken pipe	
	=> on ne va pas àla ligne dans notre minishell --> s'explique... mais une ligne par commande ?
		en soi, c'est ok (test : si dans un outfile, on a bien la bonne info)
	/**********/


	/***********/
	FIXED !
	/***********/
		$tutu $toto <youpla pwd
			--> bash: youpla: No such file or directory
		=> PAS OK sur notre minishell

		!attention une variable expand qui ne donne rien passe la main à l'argument suivant pour la commande:
		Exemple:
			$UxSER blabla 'abcd $? eee'
	/**********/



>		check pour les clean token
		echo "-nnnn  -n coucou"
		vs.
		echo "-nnnn" " n" "coucou"

>	14/09/2022 :
	résultat de la commande à corriger (fonction : del_empty_token)
	$tutu $toto <youpla pwd
	$tutu $toto <youpla pwd $tut <<$$$$bou super $?



# //////////////////////// LENA


# //////////////////////// CHRISTEL

# //////////////////////// TO DO

>		create a function to init t_data
>		create function(s) to free all mallocs (garbage collector?)
>		reset the compilator to 'clang' !! (modified to gcc for valgrind use)
>		a re-tester avec les $ et espaces : $USER $$USER $'coucou' $$$$$$$$$'USER' "$$  "
>		free clean_cmd_no_redir; token; tok_redir in ft_free_cmd
>		bien penser modifier val exit dans data en cas d'erreurs de malloc
>		pour les redirections : 1ère étape de l'exec (avant execve) et mettre "ambiguous redirect" sans nécessairement faire référence au token concerné

##  WTF



##  OK

>	problemes d'espaces si on retire les redirections
	--> mieux vaut ne pas enlever les espaces lors de get_redir et nettoyer par la suite les espaces
	(car ce seront des espaces hors quotes et donc pas en négatif...)
	sinon, le risque est d'avoir 2 token collés (car plus de redir entre...)
	tests:
		"coucou">"tut""tot">>test 'abcd $? eee'
		"coucou" >'tut' >> test 'youpi'

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

>		***** Cas d'un $ suivi immédiatement d'un chiffre, le tout hors ' ' *****
			Dans DEL_QUOTES aussi :
			- faire une condition dans le cas où $ n'est pas entre ' ' mais est suivi d'un chiffre
				--> supprimer $2
				comme pour 	$"USER" --> USER : on supprime le $
							$24444	--> 4444 : on supprime $2

>		***** CAS DE "$" ou "$$$$$...$" *****
			Dans ce cas, on garde 1 seul $ et on le met en négatif (car on retire les " ")

>		***** CAS DE $? *****
		- si '$?' 		--> texte $? donc $ en négatif (déjà géré), type "WORD" ou "COMMAND"
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
