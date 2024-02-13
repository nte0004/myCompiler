#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
const char TAB = '\t';
char look;

void getChar() {
    std::cin.get(look);
}

void error(const std::string& s) {
    std::cerr << std::endl << '\a' <<"Error: " << s << '.' << '\n';
}
void abort(const std::string& s) {
    error(s);
    std::exit(EXIT_FAILURE);
}
void expected(const std::string& s) {
    abort(s + " Expected");
}
void match(char x) {
    if (look == x) {
        getChar();
    }
    else {
        expected('\'' + std::string(1, x) + '\'');
    }
}
bool isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
}
bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool isAddOp(char c) {
    if (c == '+' || c == '-') {
        return true;
    }
    else {
        return false;
    }
}

char getName() {
    if (!isAlpha(look)) {
        expected("Name");
    }
    char result =  std::toupper(static_cast<unsigned char>(look));
    getChar();

    return result;
}
char getNum() {
    if (!isDigit(look)) {
        expected("Integer");
    }
    char result = look;
    getChar();

    return result;
}
void emit(const std::string& s) {
    std::cout << TAB << s;
}
void emitLn(const std::string& s) {
    emit(s);
    std::cout << '\n';
}

// Parse and Translate a Math Factor
void expression();
void factor() {
    if (look == '(') {
        match('(');
        expression();
        match(')');
    }
    else {
        std::string s = "MOV X0, #" + std::string(1, getNum()) + " //Put factor in X0." ;
        emitLn(s);
    }
}

void multiply() {
    match('*');
    factor();
    emitLn("MUL X0, [SP, #8], X0 // Multiply value at top of stack by X0, store in X0."); 
}

// Recognize and Translate a Divide
void divide() {
    match('/');
    factor();
    emitLn("UDIV X0, [SP, #8], X0 // Divide value at top of stack by X0, store in X0.");
}

// Parse and Translate a Math Term
void term() {
    factor();
    while(look == '*' || look == '/') {
        emitLn("MOV [SP, #-8], X0 // Push term.");
        switch(look) {
            case '*':
                multiply();
                break;
            case '/':
                divide();
                break;
            default:
                expected("Mulop");
                break;
        }
    }
}

// Recognize and Translate an Addition
void add() {
    match('+');
    term();
    emitLn("ADD X0, [SP, #8], X0 // Add value at top of stack to X0, store in X0."); 
}

// Recognize and Translate a Subtraction
void subtract() {
    match('-');
    term(); 
    emitLn("SUB X0, [SP, #8], X0 // Sub X0 from value at top of stack, store in X0.");
}

// Parse and Translate an Expression
void expression() {
    if (isAddOp(look)) {
        emitLn("MOV X0, #0 // Set X0 to zero.");
    }
    else {
        term();
    }
    while(isAddOp(look)) {
        emitLn("MOV [SP, #-8], X0 // Push expression.");
        switch(look) {
            case '+':
                add();
                break;
            case '-':
                subtract();
                break;
            default:
                expected("Addop");
                break;
        }
    }

}
void init() {
    getChar();
    expression();
}

int main() {
    init();
    return 0;
}
