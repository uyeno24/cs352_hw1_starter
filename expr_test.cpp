#include "expr.hpp"

#include <iostream>
#include <string>
#include <utility>

/// wrapper function for addition
int plus(int a, int b) { return a + b; }

/// wrapper function for equality
bool equals(int a, int b) { return a == b; }

/// wrapper function for multiplication
bool mult(int a, int b) {return a * b;}

/// wrapper function for subtraction
bool sub(int a, int b) {return a - b;}

int main() {
    // constant expressions
    auto two = new const_expr<int>(2);
    std::cout << *two << " = " << two->eval() << std::endl;

    // binary operators
    // note that because the expr nodes take ownership of their 
    // constructor arguments I can create these concisely in-place
    auto cond = new bin_op_expr<bool, int, int>(
        equals, "==",
        new bin_op_expr<int, int, int>(
            plus, "+",
            two,
            two->clone()
        ),
        new const_expr<int>(4)
    );
    std::cout << *cond << " = " << (cond->eval() ? "true" : "false") << std::endl;

    // more complex if-expression
    // note that this top-level expression is stack-allocated, so we don't 
    // need to delete it when we're done with it, and root's destructor will 
    // delete all the other expressions we've created so far.
    if_expr<std::string> root = {
        cond,
        new const_expr<std::string>("correct"),
        new const_expr<std::string>("incorrect")
    };
    std::cout << root << "\n = " << root.eval() << std::endl;

    // TODO: write your own expression containing at least 6 expression nodes, 
    // and build the expression object and print it below, similar to the 
    // `root` example above. You may nest the subexpressions or put them in 
    // separate variables, as you will
    // auto my_expr = {
    //     cond,
    //     new const_expr<std::string>("correct"),
    //     new const_expr<std::string>("incorrect")
    // };
    auto eight = new const_expr<int>(8);
    auto five = new const_expr<int>(5);

    auto my_expr = new bin_op_expr<bool, int, int>(
        equals, "==",
        new bin_op_expr<int, int, int>(
            mult, "*",
            eight,
            five
        ),
        new const_expr<int>(40)
    );
    
    if_expr<std::string>* my_expr_two = new if_expr<std::string> {
        my_expr,
        new const_expr<std::string>("correct"),
        new const_expr<std::string>("incorrect")
    };

    std::cout << *my_expr << "\n = " << my_expr->eval() << std::endl;
    std::cout << *my_expr_two << "\n = " << my_expr_two->eval() << std::endl;
    delete my_expr_two;
}