## A Project to learn more about compilers.

I'm trying to make a compiler using the "Let's Build a Compiler, by Jack Crenshaw" tutorial. It's a really old tutorial (from the 90s), but I'm hoping it will somewhat simpler and impart fundamental concepts better. He has built his compiler with Turbo Pascal 4.0 to output 68000 assembly. I'm using C++23 to output arm64 assembly. My main goal with this project is to learn more about how compilers work and become comfortable with C++. 

### Build

I'm building with:
'g++ cradle.cpp -o cradle'

and running with:
'./cradle'

### Usage

Right now it accepts basic math:
- single digit integers
- addition, subtract, division, and multiplication operations
- precedence via parenthesis

For example a valid input may be:
'5+3*(8/4)-2'

### Tutorial

Here's a link to the tutorial I'm using:
<https://compilers.iecc.com/crenshaw/>
