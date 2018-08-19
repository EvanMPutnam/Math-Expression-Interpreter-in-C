# Math-Expression-Interpreter
A Math Expression Interpreter in C

This is a basic interpreter for a mathematical language.  I named it Romance, after the movie True Romance.  Everything needs a name...  

# Language Features

  ## Assignment
    LET x = someExpression
  ## Display
    Type into the console the name of the variable or an expression
  ## Math Operations
    +, -, /, *
    SIN() COS(), TAN(), ABS(), SQRT()
  ## Helpful Functions
    - HELP() displays all this information about language
    - VARS() displays information about all set variables
    - EXIT() cleans up memory and exits the interpreter
  ## Usage Example
![alt tag](http://evanputnam.com/wp-content/uploads/2018/01/Screen-Shot-2018-01-04-at-3.34.47-AM.png "Description goes here")
 


# Description
This was an experiment in making a simple interpreter in the C language(And in turn appreciate how much of a pain it is compared to say Java).
The biggest difficulties I found ironically were not related to dynamic storage but instead string manipulation.
A lot of the string manipulation stuff is a pain in C where in JAVA where you have very nice functions like split or
strip with regular expressions to help out.  It was also a challenge doing a lot of this without classes because, while
structs are great and provide a lot of functionality, lack of encapsulation, inheritance, and polymorphism are things that I am just so used to now.  However, now after taking a class on compiler/interpreter design I realized I could have made this a lot better by adding some sort of lexer/parser and making abstract syntax trees to evaluate expressions.  Maybe in the future I will come back to this project.

# Data Structures
I creaded a number of my own data structures for this particular project.
- Stack
- Queue
- Hash Table - adapted from a version I wrote for my mechanics class

They gave me a lot of functionality and they were needed for things like variable storage or
handling the shunting yard algorithm.



