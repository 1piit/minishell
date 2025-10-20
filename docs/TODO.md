# Minishell — To-Do List

## PARSING

### 🔹 1. Lecture et gestion d’entrée
- [x] Lire la ligne de commande avec `readline()`
- [x] Gérer l’historique (`add_history`)
- [ ] Gérer les signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) pendant la lecture
- [ ] Nettoyer et libérer la mémoire de la ligne lue

---

### 🔹 2. Tokenisation
- [ ] Découper la ligne en **tokens** (mots, opérateurs, redirections, pipes, etc.)
- [ ] Gérer les **quotes** (`'` et `"`)
- [ ] Gérer les **espaces multiples** et tabulations
- [ ] Gérer les **caractères spéciaux** (`|`, `<`, `>`, `>>`, `<<`)
- [ ] Détecter les **tokens invalides** (`|||`, `><`, etc.)
- [ ] Gérer les **tokens vides** ou erreurs de syntaxe

---

### 🔹 3. Expansion
- [ ] Implémenter l’expansion des variables d’environnement (`$VAR`)
- [ ] Gérer `$?` (code de retour du dernier process)
- [ ] Gérer les quotes doubles (`"`) vs simples (`'`)
- [ ] Désactiver les expansions dans les `heredocs` si `<< 'EOF'`
- [ ] Créer une fonction `expand_env()`

---

### 🔹 4. Parsing syntaxique
- [ ] Créer les structures `t_command`, `t_redir`, etc.
- [ ] Parser les **redirections** (`<`, `>`, `>>`, `<<`)
- [ ] Parser les **pipes** (`|`)
- [ ] Vérifier la **syntaxe globale**
- [ ] Construire une **liste chaînée de commandes**
- [ ] Créer une fonction principale de parsing (`parse_line()`)

---

### 🔹 5. Gestion des erreurs et mémoire
- [ ] Messages d’erreur cohérents (`syntax error near unexpected token`)
- [ ] Libérer correctement la mémoire après parsing
- [ ] Créer des tests unitaires pour valider le parsing

---

## EXECUTION

### 🔹 1. Gestion des commandes simples
- [ ] Résoudre les chemins avec `PATH`
- [ ] Gérer les commandes absolues / relatives
- [ ] Gérer les erreurs “commande introuvable”
- [ ] Gérer les permissions
- [ ] `fork()` + `execve()`
- [ ] `waitpid()` pour attendre les enfants

---

### 🔹 2. Redirections
- [ ] Redirection **entrée** (`< fichier`)
- [ ] Redirection **sortie** (`> fichier`)
- [ ] Redirection **append** (`>> fichier`)
- [ ] Gestion des **heredocs** (`<< DELIM`)
- [ ] Fermer les fd inutiles dans les enfants

---

### 🔹 3. Pipes
- [ ] Créer les pipes entre commandes
- [ ] Rediriger `stdin` / `stdout` avant `execve`
- [ ] Fermer les pipes inutiles dans le parent
- [ ] Attendre tous les fils à la fin du pipeline

---

### 🔹 4. Builtins
- [ ] `echo` (avec `-n`)
- [ ] `cd`
- [ ] `pwd`
- [ ] `export`
- [ ] `unset`
- [ ] `env`
- [ ] `exit`
- [ ] Gérer les builtins sans `fork` (ex : `cd`, `exit`)

---

### 🔹 5. Gestion des signaux
- [ ] `SIGINT` (Ctrl+C) → interrompre le process fils
- [ ] `SIGQUIT` (Ctrl+\) → afficher `Quit (core dumped)` si nécessaire
- [ ] Ignorer `SIGTSTP` (Ctrl+Z)

---

### 🔹 6. Environnement et variables
- [ ] Copier l’environnement initial (`envp`)
- [ ] Gérer `export` / `unset`
- [ ] Gérer les expansions `$VAR`
- [ ] Synchroniser les changements entre shell et enfants

---

### 🔹 7. Exit status
- [ ] Retour correct de chaque commande
- [ ] Gérer `$?` pour les expansions
- [ ] Propager le bon code dans les pipes

---

### 🔹 8. Nettoyage & mémoire
- [ ] Libérer toutes les structures après exécution
- [ ] Fermer tous les descripteurs
- [ ] Supprimer les fichiers temporaires des `heredocs`
- [ ] Vérifier avec `valgrind`
