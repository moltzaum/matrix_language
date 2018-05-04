/* This is an example of bnfc using: http://bnfc.digitalgrammars.com/tutorial.html
 * 
 * This is my first time defining a list of statements (assignments), instead of 
 * evaluating a simple expression. This program is an interpreter.
 *
 * For simplicity, this interpreter only has * and + operators, without any
 * operator precedence stated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interp/Skeleton.h"
#include "bnfc/Parser.h"
#include "bnfc/Printer.h"
#include "bnfc/Absyn.h"

int main (int argc, char** argv) {
    FILE *input;
    char *filename = argv[1];
        
    if (filename) {
        if (argc == 0) {
            printf ("Give the name of an input file please.\n");
            exit(1);
        }
        input = fopen (filename, "r");
    } else input = stdin;
    
    Program parse_tree = pProgram (input);
    if (parse_tree) {
        visitProgram(parse_tree);
    }
}

