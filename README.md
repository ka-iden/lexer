# lexer

Writing a simple lexer to learn how to tokenize code/statements.  
This is the first step not only towards learning how to write a programming language, but also towards tokenising a math expression for evaluation.

## Building

You can build this on Windows using the included Visual Studio 2022 solution.

## Running

You can either run this with no command arguments, in which the lexer will read from the default supplied code, or you can pass a file name as an argument, in which case the lexer will read from that file.  
The executable can be found in either the `x64/Debug/` or `x64/Debug/` folder, depending on how you built it.

## Example

Running the lexer with no arguments uses the default code:

```go <!-- using go because it highlights func and for no other reason. red herring. -->
func main() {
	int x = 5;
	return x + 5;
}
```

And will produce the following output:

```console
Line:   1, Column:   1 TOKEN_FUNC
Line:   1, Column:   6 TOKEN_IDENTIFIER(main)
Line:   1, Column:  10 TOKEN_LPAREN
Line:   1, Column:  11 TOKEN_RPAREN
Line:   1, Column:  13 TOKEN_LBRACE
Line:   2, Column:   2 TOKEN_IDENTIFIER(int)
Line:   2, Column:   6 TOKEN_IDENTIFIER(x)
Line:   2, Column:   8 TOKEN_EQUAL
Line:   2, Column:  10 TOKEN_NUMBER(5)
Line:   2, Column:  11 TOKEN_SEMICOLON
Line:   3, Column:   2 TOKEN_RETURN
Line:   3, Column:   9 TOKEN_IDENTIFIER(x)
Line:   3, Column:  11 TOKEN_PLUS
Line:   3, Column:  13 TOKEN_NUMBER(5)
Line:   3, Column:  14 TOKEN_SEMICOLON
Line:   4, Column:   1 TOKEN_RBRACE
Line:   4, Column:   2 TOKEN_EOF
```

## Learning Resources

[The Phi Compiler], video devlogs and source code. Used for a token list, and a nice printing scheme for the tokens.

## Licenses

This project is licensed under the [MIT License].

[The Phi Compiler]: https://github.com/wzid/phi

[MIT License]: LICENSE