echo "$USER$HOME$SHELL"
echo "User: $USER, Path: $PATH, PWD='$PWD'"
echo "$USER'$HOME'"
echo "$USER\"$HOME\""
echo "'$USER$HOME'"
echo "$UNSETVAR"
echo "$USER$"
echo "Text before$USERtext after"
echo "$USER$?$USER"
echo "Empty:$EMPTY:"
echo "$USER"world
echo "$USER""$HOME"
echo "$USER ""$HOME"
echo "$USER 'inside' $HOME"
echo "User='$USER' Home='$HOME'"
echo "Hello 'world'"
echo 'Hello "world"'
echo "'Single' "Double""
echo "unclosed
echo 'unclosed
echo "nested 'quotes' here"
echo 'nested "quotes" here'
echo "'mix\"ed' quotes"
echo "escape quote: \""
echo "complex 'mi\"x' here"
echo a > b > c > d
echo a >>> b
echo a > > b
echo a < < c
echo a | | b
echo a || b
echo a && b
echo "a | b" | cat
echo ">|<" > out.txt
echo hello >file1>>file2
echo ">" ">>" "<" "|" "||" "&&"
echo "a > b" "c | d"
echo "> > >"
echo "   leading spaces"
echo trailing spaces    
echo	"tab	test"
echo "multi	 tab"
echo ""	""
echo "a	b	c"
echo " | | | "
echo ";;"
echo "&& || | &"
echo "[$USER	$HOME]"
echo "a$USER b$HOME c$SHELL"
echo $(echo $USER)
echo "`echo $HOME`"
echo "`echo '$USER'`"
echo "$(echo "$USER")"
echo "`echo \"$HOME\"`"
|
||
|||
&&
&&&
|&
&|
;|
|;|
echo a ||| echo b
echo a >>> b
echo a &&& b
echo a <|> b
echo a | | b
echo "Mix '$USER' $HOME" 'NoExp $USER' $PATH | grep bin > out.txt
echo "$USER" "$?" "$PWD" "$SHELL" "$RANDOM" "$?"
echo "$USER$USER$USER$USER$USER$USER"
echo "$USER$HOME" '$USER$HOME' "$USER'$HOME'"
echo "$USER" | cat | grep "$HOME"
echo "$USER" && echo "$HOME" || echo "fail"
echo "Pre$USER$HOME$SHELL" > tmp && cat tmp
echo "abc\"
echo 'abc\'
echo "abc\\"
echo 'abc\\'
echo "\$USER"
echo '\$USER'
echo "$USER\ $HOME"
echo "$USER\\$HOME"
echo "End\$"
echo "Double$USER$HOME$$"
echo "A$USER'B'$HOME"C"
echo '$USER'$HOME
echo "$USER"'$HOME'
echo "$USER"'$HOME'"$SHELL"
echo ">$USER<|$HOME|&$SHELL&"
echo "Begin "$USER" middle '$HOME' end"
echo "'a'$USER'b'"
echo "1$USER2$HOME3$SHELL"
echo '"$USER" inside'
echo "multi
line"
echo 'multi
line'
echo "line1\
line2"
echo 'line1\
line2'
echo "tab->	<-here"
echo $USER | grep "rga"
echo "$USER" > "file with spaces.txt"
