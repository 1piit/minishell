minishell :
//       EOF avec pipe derrière -> comportement inattendu par rapport au bash
    X    pouvoir lancer minishell sans environnement (avec variables de base)
    Y    leaks
    Y    gérer plusieurs heredoc (go crazy fiche d’évaluation) 
    Y    le heredoc il doit être fork ça évite le problème des 2 heredoc
    Y    pour toutes commandes bloquantes comme cat, heredoc, grep il faut gérer les signaux dans l’enfant et non dans le parent comme ctrl   c ctrl   d ca doit tuer l’enfant et pas minishell (à ajouter dans l’enfant pid = 0 redirehier les signaux la dedans)
    Y    expand dans les putain de heredocs
