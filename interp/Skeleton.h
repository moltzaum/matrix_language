#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "../bnfc/Absyn.h"

void visitProgram(Program p);
void visitListStm(ListStm p);
void visitStm(Stm p);
void visitRow(Row p);
void visitListExp(ListExp p);
void visitListRow(ListRow p);
void visitExp(Exp p);

void visitSInteger(SInteger p);
void visitIdent(Ident i);
void visitInteger(Integer i);
void visitDouble(Double d);
void visitChar(Char c);
void visitString(String s);

#endif
