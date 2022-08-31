lexer(){
	if(ft_pipe() == 1)
		return (1);
	if(ft_quote() == 1)
		return (1);
	if (ft_redirection() == 1)
		return(1);
	return (0);
}

//-------------------------------

ft_lexer_pipe:

"" | "": bon
|: pas bon
fdsfds |: pas bon
| fsdfsdfds:pas bon
fsdfds || fdsfds: pas bon
fds | fsdfsd |: pas bon
syntax error near unexpected token '|'

//-------------------------------

ft_lexer_quote:

while(str[i])
{
	if (str[i] = double_quote ou single_quote)
	{
		if (str[i] = double_quote)
		{
			retrouver un double I++;
			si tarrive a la fin sans trouver le quote correspondant error
		}
		else if (str[i] = double_quote)
			retrouver un double I++;

	}
	i++;
}
syntax error near unexpected token '"'


//-------------------------------

ft_lexer_redirection()
<<<:faux
>>>:faux
><:faux
<>:faux
echo >:faux




nb de pipe + 1 sansa compter ceux dans les quote/double quote avec la fonction ft_quote

minishell(){

	while(1)
	{
		str= readline();
		if (ft_lexer(str) == 0)
		{
			subdiviser_en_commande();

			ft_parsing();

			ft_token();

			ft_exec();
		}
	}
}

//-------------------------------
subdiviser_en_commande();

exemple:

echo "bonjour $USER" "" | echo -fdsfds "|" '$USER' '''' | cat $USER$USER "''''"


compter le nombre de pipe et definir le nb de commande
s_command command = malloc(sizeof(s_command * nb de command))


s_minishell->command[0]->str_pas_clean = echo "bonjour $USER" ""
s_minishell->command[1]->str_pas_clean = echo -fdsfds "|" '$USER' ''''
s_minishell->command[2]->str_pas_clean = cat $USER$USER "''''"

//-------------------------------
ft_parsing(TRICKY DE OUF)

lobjectif cest de transformer ca:
s_minishell->command[0]->str_pas_clean = echo "bonjour $USER" "" > outfile1
s_minishell->command[1]->str_pas_clean = echo -fdsfds "|" '$USER' ''''
s_minishell->command[2]->str_pas_clean = cat $USER$USER "''''"

en ca (FLAT_TEXT)
s_minishell->command[0]->str_clean =echo bonjour cgaillag  > outfile1
s_minishell->command[1]->str_clean = echo -fdsfds | $USER
s_minishell->command[2]->str_clean = cat cgaillagcgaillag ''''


exmple:
str_pas_clean = echo "$USER$WEWEWEW lol ''" '$USER' = 26
str_pas_clean_sans_quote = echo $USER$WEWEWEW lol '' $USER
comment je sais quel expand etait dans quel quote
mettre les caractere entre simple quote en negatif (valeur ascii * -1)

str_pas_clean_sans_quote = echo $USER$WEWEWEW lol '' ($USER) (en negatif)

while (str[i] = "'")
{
	i++;
	if (str[i] = "'")
		break;
	str[i] = str[i] * -1;
}

str_ss_quote = malloc(sizeof(char) * (x + 1))
copier en passant les quotes exterieur


[...]

str_clean = malloc(sizeof(char) * (x + 1))
etablier le strlen avec expand

while(str[i])
{
	if (str[i] = '$') si le caractere sur lequel je suis a comme valeur ascii 36
		alors aller checker son equivalent dan lenv pour le remplacer
}

[...]

while (str[i])
{
	if (str[i] < 0 )
		str[i] = str[i] * -1;
}

puis copier avec presque les meme fonctions
on va regarder dans lenv a quoi correspond USER et WEWEWEW et ajouter au decompte le strlen du contenu si il existe on ajoute 0

//-----------

ft_token();
s_minishell->command[0]->str_clean =echo bonjour cgaillag > outfile1
nb de token = 5
minishell.command[0].token = malloc(sizeof(token) * 5)

le premier token qui nest pas une redirection est forcement la command (et yen a quune)
pour les redirection en fonction de loperator qui le precede on sait quel type de redirection

tout le role de cette fonction cest de typer en fonction de leur position/operator/contenu
echo





--------------------------------------------------------
lobjectif du taff ca va etre de rentrer des lignes de commande a parser de ouf (grave des quotes des expandes des pipes des truc tricky)

>minishell : echo "bonjour $USER" ""| cat >outfile

retour:
s_minishell->command[0]->str_pas_clean = echo "bonjour $USER" ""
minishell.command[0].token[0].token = echo
minishell.command[0].token[0].type = BUILTIN
minishell.command[0].token[1].token = bonjour cgaillag
minishell.command[0].token[1].type = WORD
minishell.command[0].token[2].token =
minishell.command[0].token[2].type = WORD

s_minishell->command[1]->str_pas_clean = cat >outfile
minishell.command[1].token[0].token = cat
minishell.command[1].token[0].type = COMMAND
minishell.command[1].token[1].token =

minishell.command[1].token[1].type =OPERATOR
minishell.command[1].token[2].token = outfile
minishell.command[1].token[2].type = OUTFILE





--------------------------------------------------------












MINISHELL.H

enum token {
COMMAND, //0
BUILTIN, //0bis
WORD, //1
WORD_N, //2
OPERATOR, //3
OUTFILE, //4
OUTFILE_APPEND, //5
INFILE, //6
HERE_DOC //7
} ;



STRUCTURE :

s_minishell

env *env;
s_command **command;
int nb_de_process;

env

char *cley;
char *contenue;
env *next;

command

char *str_pas_clean;
char *str_sans_quote;
char *str_clean;
t_token **token;

token
char *token;
int type;



