
#           ISSUES

>       help

>	Attention dans le history
	Quand on a un echo -n (pas de retour à la ligne), lorsqu'on veut sélectionner de précédentes commandes, la prompt line 'minishell>' s'efface... (ou ne s'affiche plus)

>>	** tests non concluants **


	/*******************************/
	FIXED
	/*******************************/

> 	commande :     cd //
		--> vérifier que c'est / ou // qui doit être retourné
		- test bash (chez moi): //
		- test minishell: /


	/*******************************/
	FIXED sauf MINISHELL dans MINISHELL
	/*******************************/

>	G-DOC : 85 tests (de 388 à 472) - voir mes commentaires colonne L
	cf. lignes :
		- l. 392, 393, 394, 395 --> non gérées, à gérer ??
		- l. 416 : valeur de retour à 1 (et non 2) --> CORRIGE (forcé dans cd)
		- l. 420 : valeur de retour à 1 (et non 2)
			/!\ path différent (Not such file or directory ou bien not a directory), cf. mes notes
		- l. 423 : vérifier le résultat sur bash à 42 : si // alors / ou // ??
		- l. 424 : idem 423
		- l. 428 : valeur de retour à 1 (et non 2) --> CORRIGE (forcé dans cd)
		- l. 433 : géré comme un texte (et pas une option, idem 431 et 432)
		- l. 438 : valeur de retour à 1 (et non 2) --> CORRIGE (forcé dans cd)
		- l. 446 : ?? (mais plus dans le sujet)
		- l. 450 : built-in cd :
				il faut gérer le cas de getcwd quand on ne peut plus aller qq part avec cd

				G-DOC ligne 450 :
					$> mkdir a
					$> mkdir a/b
					$> cd a/b
					$> rm -r ../../a
					($> pwd   --> optionnel, mais le résultat cd .. reste le même)
					$> cd ..

					- dans bash --> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
					- notre minishell --> on exite comme "malloc failure" (point discuté le 13.10)
		- l. 462 : ok pour minishell dans minishell
				MAIS erreurs de commandes (lien env_path)
				l'env est l'env path... (wrong)

		+ sur cd : revoir les éléments/tests pour valeur de retour (13, 20...)
				une partie a été modifiée mais s'assurer que tout OK
				!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/*******************************/
	PAS GRAVE
	/*******************************/

>	ordre des commandes (d'abord heredoc puis les autres redir)

	$tutu $toto <youpla pwd $tut <<$$$$bou super $?
	(puis $$$$bou)
	--> dans bash : d'abord here_doc puis la redir pas ok
	--> pour nous : d'abord redir pas ok, puis heredoc ==> à inverser ?

	sinon OK pour :
	> $tutu $toto <youpla pwd $tut <<$$$$bou super $?    --> quand youpla existe (d'abord heredoc puis pwd)
		ou
	> $tutu $toto >youpi pwd $tut <<$$$$bou super $?     --> pwd dans youpi après le heredoc




	/*******************************/
	TESTS DU G-DOC from ligne 640 : redir
	/*******************************/

	l. 640 :	echo hola > bonjour
		→ devrait mettre hola dans fichier 'bonjour', mais l'affiche dans le prompt
	... idem la suite

	ex:  echo hola > hello >> hello >> hello

	/*******************************/
	TESTS DU G-DOC lignes 224 à 381 : built-ins
	/*******************************/

	l. 230 :	env ./Makefile
		→ res minishell : ./Makefile: no such file or directory
		→ bash : env: ‘./Makefile’: Permission denied

	/*******************************/

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

	Retours de corrections minishell - à regarder !!!

	Probleme sur les fds (3 d'ouverts en plus), a export avec le _ au debut ou avec des chiffres dans le nom le += (pas obligatoire). Soucis d'expand : "$USER"$USER'$USER' , le echo avec -nnnnnt ne fonctionne pas correctement. Le chemin relatif ne fonctionne pas, si on enleve le path et qu'on est dans /usr/bin il faut que la commande fonctionne. Les redirections : ls < ok > ok cree ls alors que ca ne devrait pas. Probleme de heredoc cat << ok << salut doit afficher ce qu'on a place dans le heredoc. Probleme Pipe avec les leaks de fds (valgrind --track=fds=yes., Cat | cat | ls ne marche pas ainsi que yes | head, a cause d'un probleme au niveau des pipes. Du coup les variables d'env petit soucis a cause de l'expand (explique plus haut)

	echo ".../n...." exit ne retourne pas les valeurs ctrl-c avec bcp de texte : probleme d'affichage echo "..." > test : erreur (is a directory) Petites erreurs restantes a regler. bon courage pour le reste.

	Exit: Limite négative, - et + à gérer sur le premier caractère Valeur de retour: Command not found -> 127 et pas 13 CTRL + \: leave la commande bloquante + print message (optionnel) CTRL + C: pas oublier \n Redirection input: argv[0] = argv[1] Bon projet dans l'ensemble, dommage pour les petites erreurs par ci et par là, bon courage pour la suite

	Tres bon projet, super propre pour un 1er push! La defense est tres bonne. Un `unset` de `SHLVL` et un `./minishell` fait crash minishell. `cat << EOF >> log.txt` fait `exit`le programme de maniere involontaire. Le code est clean, les explications sont completes et le projet est compris. Gentilles, curieuses et interessees par la correction. Merci pour votre bonne humeur et bon courage par la suite!

	Bon proje ayant couvert beaucoup de cas. Pas de crash, de fuites de memoire ou de fd ouverts quel que soit l'exit via commande ou signal. Bravo pour ce dernier push qui est le bon.

# //////////////////////// BEWARE


>	tests corrigés - A RETESTER avant la fin

	/***********/
	FIXED
	/***********/
	l. 296 :
		$> export HOLA='"'
		$> echo " $HOLA " | cat -e
		→ bash :  " $
		→ res minishell : on n’ a pas le résultat attendu
	==> autres exemples :
		export test='"youpi'
		puis echo $test
		--> SOUCI DANS PARSING : csquotes token = "youpi" --> len = 6 vs. strlen = 7
	==> solution envisagee : si les expands sont des quotes -> les passer en negatif pour eviter qu'on la prenne pour une closing quote.


	/***********/
	FIXED
	/***********/
	si HOME unset --> et export HOME= (vide)
	gérer le cd ou cd $HOME qui ne fait rien dans bash...

	=> fixed : ajout d'une condition si data->home[0] = '\0' --> return (0)
	/***********/

	/***********/
	FIXED
	/***********/
	export $USER=pouet
		--> bash: dans env
				tinychris=pouet

	--> le '=' est un séparateur de expand...
		choisit-on de l'inclure comme séparateur
		OU bien choisit-on de le considérer comme un caractère quelconque - donc expand de $USER=toto est empty ??
	==> tous les caractères hors alpha, num et _ sont des séparateurs pour un nom de variable --> mise à jour le 26/09

	/***********/


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

	/***********/
	FIXED !
	/***********/
	$USER | $USTER | echo $?	--> OK quand le token vide est en 1er
								bash :	0
										tiny_chris: command not found

	$USdddER | $USTER | echo $?	--> PAS OK - pas d'affichage
								bash :	0
	/***********/

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
