/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INDENT_WIDTH 2

int _n_;
char *buf_;
int cur_;
int buf_size;

/* You may wish to change the renderC functions */
void renderC(Char c)
{
  if (c == '{')
  {
     bufAppendC('\n');
     indent();
     bufAppendC(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppendC('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppendC(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppendC(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for(t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppendC(c);
     bufAppendC(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppendC(' ');
     bufAppendC(c);
     bufAppendC(' ');
  }
}
void renderS(String s)
{
  if(strlen(s) > 0)
  {
    bufAppendS(s);
    bufAppendC(' ');
  }
}
void indent(void)
{
  int n = _n_;
  while (n > 0)
  {
    bufAppendC(' ');
    n--;
  }
}
void backup(void)
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
char *printProgram(Program p)
{
  _n_ = 0;
  bufReset();
  ppProgram(p, 0);
  return buf_;
}
char *printListStm(ListStm p)
{
  _n_ = 0;
  bufReset();
  ppListStm(p, 0);
  return buf_;
}
char *printStm(Stm p)
{
  _n_ = 0;
  bufReset();
  ppStm(p, 0);
  return buf_;
}
char *printRow(Row p)
{
  _n_ = 0;
  bufReset();
  ppRow(p, 0);
  return buf_;
}
char *printListExp(ListExp p)
{
  _n_ = 0;
  bufReset();
  ppListExp(p, 0);
  return buf_;
}
char *printListRow(ListRow p)
{
  _n_ = 0;
  bufReset();
  ppListRow(p, 0);
  return buf_;
}
char *printExp(Exp p)
{
  _n_ = 0;
  bufReset();
  ppExp(p, 0);
  return buf_;
}
char *showProgram(Program p)
{
  _n_ = 0;
  bufReset();
  shProgram(p);
  return buf_;
}
char *showListStm(ListStm p)
{
  _n_ = 0;
  bufReset();
  shListStm(p);
  return buf_;
}
char *showStm(Stm p)
{
  _n_ = 0;
  bufReset();
  shStm(p);
  return buf_;
}
char *showRow(Row p)
{
  _n_ = 0;
  bufReset();
  shRow(p);
  return buf_;
}
char *showListExp(ListExp p)
{
  _n_ = 0;
  bufReset();
  shListExp(p);
  return buf_;
}
char *showListRow(ListRow p)
{
  _n_ = 0;
  bufReset();
  shListRow(p);
  return buf_;
}
char *showExp(Exp p)
{
  _n_ = 0;
  bufReset();
  shExp(p);
  return buf_;
}
void ppProgram(Program _p_, int _i_)
{
  switch(_p_->kind)
  {
  case is_Prog:
    if (_i_ > 0) renderC(_L_PAREN);
    ppListStm(_p_->u.prog_.liststm_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Program!\n");
    exit(1);
  }
}

void ppListStm(ListStm liststm, int i)
{
  while(liststm != 0)
  {
    if (liststm->liststm_ == 0)
    {
      ppStm(liststm->stm_, i);
      renderC(';');
      liststm = 0;
    }
    else
    {
      ppStm(liststm->stm_, i);
      renderC(';');
      liststm = liststm->liststm_;
    }
  }
}

void ppStm(Stm _p_, int _i_)
{
  switch(_p_->kind)
  {
  case is_InitTex:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("create");
    ppString(_p_->u.inittex_.string_1, 0);
    renderS("titled");
    ppString(_p_->u.inittex_.string_2, 0);
    renderS("for");
    ppString(_p_->u.inittex_.string_3, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_OutTex:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.outtex_.ident_, 0);
    renderS("=>");
    renderS("tex");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_SOutTex:
    if (_i_ > 0) renderC(_L_PAREN);
    ppString(_p_->u.souttex_.string_, 0);
    renderS("=>");
    renderS("tex");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CloseTex:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("close");
    renderS("tex");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Redirect:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("out");
    renderS("=>");
    renderS("tex");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Print:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.print_.ident_, 0);
    renderS("=>");
    renderS("out");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_SPrint:
    if (_i_ > 0) renderC(_L_PAREN);
    ppString(_p_->u.sprint_.string_, 0);
    renderS("=>");
    renderS("out");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RPrint:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.rprint_.row_, 0);
    renderS("=>");
    renderS("out");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_PMat:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.pmat_.ident_, 0);
    renderS("::=");
    ppListRow(_p_->u.pmat_.listrow_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RSwp:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.rswp_.row_1, 0);
    renderS("<->");
    ppRow(_p_->u.rswp_.row_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RSet:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.rset_.row_1, 0);
    renderS("->");
    ppRow(_p_->u.rset_.row_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RAss:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.rass_.row_1, 0);
    renderC('=');
    ppRow(_p_->u.rass_.row_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Rref:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.rref_.ident_, 0);
    renderS("=>");
    renderS("rref");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Ref:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.ref_.ident_, 0);
    renderS("=>");
    renderS("ref");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_AVar:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.avar_.ident_, 0);
    renderC('=');
    ppExp(_p_->u.avar_.exp_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CDoub:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.cdoub_.ident_, 0);
    renderS("=>");
    renderS("double");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CInt:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(_p_->u.cint_.ident_, 0);
    renderS("=>");
    renderS("int");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Pause:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("pause");

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Stm!\n");
    exit(1);
  }
}

void ppRow(Row _p_, int _i_)
{
  switch(_p_->kind)
  {
  case is_PRow:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('[');
    ppListExp(_p_->u.prow_.listexp_, 0);
    renderC(']');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RAdd:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.radd_.row_1, 0);
    renderC('+');
    ppRow(_p_->u.radd_.row_2, 1);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RSub:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRow(_p_->u.rsub_.row_1, 0);
    renderC('-');
    ppRow(_p_->u.rsub_.row_2, 1);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_RMul:
    if (_i_ > 1) renderC(_L_PAREN);
    ppExp(_p_->u.rmul_.exp_, 2);
    renderC('*');
    ppRow(_p_->u.rmul_.row_, 2);

    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_RDiv:
    if (_i_ > 1) renderC(_L_PAREN);
    ppRow(_p_->u.rdiv_.row_, 2);
    renderC('/');
    ppExp(_p_->u.rdiv_.exp_, 2);

    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_RMul2:
    if (_i_ > 1) renderC(_L_PAREN);
    ppRow(_p_->u.rmul_.row_, 1);
    renderC('*');
    ppExp(_p_->u.rmul_.exp_, 2);

    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_SMat:
    if (_i_ > 2) renderC(_L_PAREN);
    ppIdent(_p_->u.smat_.ident_, 0);
    renderC('[');
    ppExp(_p_->u.smat_.exp_, 0);
    renderC(']');

    if (_i_ > 2) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Row!\n");
    exit(1);
  }
}

void ppListExp(ListExp listexp, int i)
{
  while(listexp != 0)
  {
    if (listexp->listexp_ == 0)
    {
      ppExp(listexp->exp_, i);
      renderS("");
      listexp = 0;
    }
    else
    {
      ppExp(listexp->exp_, i);
      renderS("");
      listexp = listexp->listexp_;
    }
  }
}

void ppListRow(ListRow listrow, int i)
{
  while(listrow != 0)
  {
    if (listrow->listrow_ == 0)
    {
      ppRow(listrow->row_, i);
      renderS("");
      listrow = 0;
    }
    else
    {
      ppRow(listrow->row_, i);
      renderS("");
      listrow = listrow->listrow_;
    }
  }
}

void ppExp(Exp _p_, int _i_)
{
  switch(_p_->kind)
  {
  case is_EAdd:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExp(_p_->u.eadd_.exp_1, 0);
    renderC('+');
    ppExp(_p_->u.eadd_.exp_2, 1);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_ESub:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExp(_p_->u.esub_.exp_1, 0);
    renderC('-');
    ppExp(_p_->u.esub_.exp_2, 1);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_EMul:
    if (_i_ > 1) renderC(_L_PAREN);
    ppExp(_p_->u.emul_.exp_1, 1);
    renderC('*');
    ppExp(_p_->u.emul_.exp_2, 2);

    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_EDiv:
    if (_i_ > 1) renderC(_L_PAREN);
    ppExp(_p_->u.ediv_.exp_1, 1);
    renderC('/');
    ppExp(_p_->u.ediv_.exp_2, 2);

    if (_i_ > 1) renderC(_R_PAREN);
    break;

  case is_ESInt:
    if (_i_ > 2) renderC(_L_PAREN);
    ppIdent(_p_->u.esint_.sinteger_, 0);

    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EDob:
    if (_i_ > 2) renderC(_L_PAREN);
    ppDouble(_p_->u.edob_.double_, 0);

    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_EIden:
    if (_i_ > 2) renderC(_L_PAREN);
    ppIdent(_p_->u.eiden_.ident_, 0);

    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_ConstE:
    if (_i_ > 2) renderC(_L_PAREN);
    renderC('e');

    if (_i_ > 2) renderC(_R_PAREN);
    break;

  case is_ConstPI:
    if (_i_ > 2) renderC(_L_PAREN);
    renderS("pi");

    if (_i_ > 2) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Exp!\n");
    exit(1);
  }
}

void ppInteger(Integer n, int i)
{
  char tmp[16];
  sprintf(tmp, "%d", n);
  bufAppendS(tmp);
}
void ppDouble(Double d, int i)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppendS(tmp);
}
void ppChar(Char c, int i)
{
  bufAppendC('\'');
  bufAppendC(c);
  bufAppendC('\'');
}
void ppString(String s, int i)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}
void ppIdent(String s, int i)
{
  renderS(s);
}

void ppSInteger(String s, int i)
{
  renderS(s);
}


void shProgram(Program _p_)
{
  switch(_p_->kind)
  {
  case is_Prog:
    bufAppendC('(');

    bufAppendS("Prog");

    bufAppendC(' ');

    shListStm(_p_->u.prog_.liststm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Program!\n");
    exit(1);
  }
}

void shListStm(ListStm liststm)
{
  bufAppendC('[');
  while(liststm != 0)
  {
    if (liststm->liststm_)
    {
      shStm(liststm->stm_);
      bufAppendS(", ");
      liststm = liststm->liststm_;
    }
    else
    {
      shStm(liststm->stm_);
      liststm = 0;
    }
  }
  bufAppendC(']');
}

void shStm(Stm _p_)
{
  switch(_p_->kind)
  {
  case is_InitTex:
    bufAppendC('(');

    bufAppendS("InitTex");

    bufAppendC(' ');

    shString(_p_->u.inittex_.string_1);
  bufAppendC(' ');
    shString(_p_->u.inittex_.string_2);
  bufAppendC(' ');
    shString(_p_->u.inittex_.string_3);

    bufAppendC(')');

    break;
  case is_OutTex:
    bufAppendC('(');

    bufAppendS("OutTex");

    bufAppendC(' ');

    shIdent(_p_->u.outtex_.ident_);

    bufAppendC(')');

    break;
  case is_SOutTex:
    bufAppendC('(');

    bufAppendS("SOutTex");

    bufAppendC(' ');

    shString(_p_->u.souttex_.string_);

    bufAppendC(')');

    break;
  case is_CloseTex:
  
    bufAppendS("CloseTex");

  

  
    break;
  case is_Redirect:
  
    bufAppendS("Redirect");

  

  
    break;
  case is_Print:
    bufAppendC('(');

    bufAppendS("Print");

    bufAppendC(' ');

    shIdent(_p_->u.print_.ident_);

    bufAppendC(')');

    break;
  case is_SPrint:
    bufAppendC('(');

    bufAppendS("SPrint");

    bufAppendC(' ');

    shString(_p_->u.sprint_.string_);

    bufAppendC(')');

    break;
  case is_RPrint:
    bufAppendC('(');

    bufAppendS("RPrint");

    bufAppendC(' ');

    shRow(_p_->u.rprint_.row_);

    bufAppendC(')');

    break;
  case is_PMat:
    bufAppendC('(');

    bufAppendS("PMat");

    bufAppendC(' ');

    shIdent(_p_->u.pmat_.ident_);
  bufAppendC(' ');
    shListRow(_p_->u.pmat_.listrow_);

    bufAppendC(')');

    break;
  case is_RSwp:
    bufAppendC('(');

    bufAppendS("RSwp");

    bufAppendC(' ');

    shRow(_p_->u.rswp_.row_1);
  bufAppendC(' ');
    shRow(_p_->u.rswp_.row_2);

    bufAppendC(')');

    break;
  case is_RSet:
    bufAppendC('(');

    bufAppendS("RSet");

    bufAppendC(' ');

    shRow(_p_->u.rset_.row_1);
  bufAppendC(' ');
    shRow(_p_->u.rset_.row_2);

    bufAppendC(')');

    break;
  case is_RAss:
    bufAppendC('(');

    bufAppendS("RAss");

    bufAppendC(' ');

    shRow(_p_->u.rass_.row_1);
  bufAppendC(' ');
    shRow(_p_->u.rass_.row_2);

    bufAppendC(')');

    break;
  case is_Rref:
    bufAppendC('(');

    bufAppendS("Rref");

    bufAppendC(' ');

    shIdent(_p_->u.rref_.ident_);

    bufAppendC(')');

    break;
  case is_Ref:
    bufAppendC('(');

    bufAppendS("Ref");

    bufAppendC(' ');

    shIdent(_p_->u.ref_.ident_);

    bufAppendC(')');

    break;
  case is_AVar:
    bufAppendC('(');

    bufAppendS("AVar");

    bufAppendC(' ');

    shIdent(_p_->u.avar_.ident_);
  bufAppendC(' ');
    shExp(_p_->u.avar_.exp_);

    bufAppendC(')');

    break;
  case is_CDoub:
    bufAppendC('(');

    bufAppendS("CDoub");

    bufAppendC(' ');

    shIdent(_p_->u.cdoub_.ident_);

    bufAppendC(')');

    break;
  case is_CInt:
    bufAppendC('(');

    bufAppendS("CInt");

    bufAppendC(' ');

    shIdent(_p_->u.cint_.ident_);

    bufAppendC(')');

    break;
  case is_Pause:
  
    bufAppendS("Pause");

  

  
    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Stm!\n");
    exit(1);
  }
}

void shRow(Row _p_)
{
  switch(_p_->kind)
  {
  case is_PRow:
    bufAppendC('(');

    bufAppendS("PRow");

    bufAppendC(' ');

    shListExp(_p_->u.prow_.listexp_);

    bufAppendC(')');

    break;
  case is_RAdd:
    bufAppendC('(');

    bufAppendS("RAdd");

    bufAppendC(' ');

    shRow(_p_->u.radd_.row_1);
  bufAppendC(' ');
    shRow(_p_->u.radd_.row_2);

    bufAppendC(')');

    break;
  case is_RSub:
    bufAppendC('(');

    bufAppendS("RSub");

    bufAppendC(' ');

    shRow(_p_->u.rsub_.row_1);
  bufAppendC(' ');
    shRow(_p_->u.rsub_.row_2);

    bufAppendC(')');

    break;
  case is_RMul:
    bufAppendC('(');

    bufAppendS("RMul");

    bufAppendC(' ');

    shExp(_p_->u.rmul_.exp_);
  bufAppendC(' ');
    shRow(_p_->u.rmul_.row_);

    bufAppendC(')');

    break;
  case is_RDiv:
    bufAppendC('(');

    bufAppendS("RDiv");

    bufAppendC(' ');

    shRow(_p_->u.rdiv_.row_);
  bufAppendC(' ');
    shExp(_p_->u.rdiv_.exp_);

    bufAppendC(')');

    break;
  case is_RMul2:
    bufAppendC('(');

    bufAppendS("RMul2");

    bufAppendC(' ');

    shRow(_p_->u.rmul_.row_);
  bufAppendC(' ');
    shExp(_p_->u.rmul_.exp_);

    bufAppendC(')');

    break;
  case is_SMat:
    bufAppendC('(');

    bufAppendS("SMat");

    bufAppendC(' ');

    shIdent(_p_->u.smat_.ident_);
  bufAppendC(' ');
    shExp(_p_->u.smat_.exp_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Row!\n");
    exit(1);
  }
}

void shListExp(ListExp listexp)
{
  bufAppendC('[');
  while(listexp != 0)
  {
    if (listexp->listexp_)
    {
      shExp(listexp->exp_);
      bufAppendS(", ");
      listexp = listexp->listexp_;
    }
    else
    {
      shExp(listexp->exp_);
      listexp = 0;
    }
  }
  bufAppendC(']');
}

void shListRow(ListRow listrow)
{
  bufAppendC('[');
  while(listrow != 0)
  {
    if (listrow->listrow_)
    {
      shRow(listrow->row_);
      bufAppendS(", ");
      listrow = listrow->listrow_;
    }
    else
    {
      shRow(listrow->row_);
      listrow = 0;
    }
  }
  bufAppendC(']');
}

void shExp(Exp _p_)
{
  switch(_p_->kind)
  {
  case is_EAdd:
    bufAppendC('(');

    bufAppendS("EAdd");

    bufAppendC(' ');

    shExp(_p_->u.eadd_.exp_1);
  bufAppendC(' ');
    shExp(_p_->u.eadd_.exp_2);

    bufAppendC(')');

    break;
  case is_ESub:
    bufAppendC('(');

    bufAppendS("ESub");

    bufAppendC(' ');

    shExp(_p_->u.esub_.exp_1);
  bufAppendC(' ');
    shExp(_p_->u.esub_.exp_2);

    bufAppendC(')');

    break;
  case is_EMul:
    bufAppendC('(');

    bufAppendS("EMul");

    bufAppendC(' ');

    shExp(_p_->u.emul_.exp_1);
  bufAppendC(' ');
    shExp(_p_->u.emul_.exp_2);

    bufAppendC(')');

    break;
  case is_EDiv:
    bufAppendC('(');

    bufAppendS("EDiv");

    bufAppendC(' ');

    shExp(_p_->u.ediv_.exp_1);
  bufAppendC(' ');
    shExp(_p_->u.ediv_.exp_2);

    bufAppendC(')');

    break;
  case is_ESInt:
    bufAppendC('(');

    bufAppendS("ESInt");

    bufAppendC(' ');

    shIdent(_p_->u.esint_.sinteger_);

    bufAppendC(')');

    break;
  case is_EDob:
    bufAppendC('(');

    bufAppendS("EDob");

    bufAppendC(' ');

    shDouble(_p_->u.edob_.double_);

    bufAppendC(')');

    break;
  case is_EIden:
    bufAppendC('(');

    bufAppendS("EIden");

    bufAppendC(' ');

    shIdent(_p_->u.eiden_.ident_);

    bufAppendC(')');

    break;
  case is_ConstE:
  
    bufAppendS("ConstE");

  

  
    break;
  case is_ConstPI:
  
    bufAppendS("ConstPI");

  

  
    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Exp!\n");
    exit(1);
  }
}

void shInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppendS(tmp);
}
void shDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppendS(tmp);
}
void shChar(Char c)
{
  bufAppendC('\'');
  bufAppendC(c);
  bufAppendC('\'');
}
void shString(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}
void shIdent(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}

void shSInteger(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void bufAppendS(const char *s)
{
  int len = strlen(s);
  int n;
  while (cur_ + len > buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  for(n = 0; n < len; n++)
  {
    buf_[cur_ + n] = s[n];
  }
  cur_ += len;
  buf_[cur_] = 0;
}
void bufAppendC(const char c)
{
  if (cur_ == buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  buf_[cur_] = c;
  cur_++;
  buf_[cur_] = 0;
}
void bufReset(void)
{
  cur_ = 0;
  buf_size = BUFFER_INITIAL;
  resizeBuffer();
  memset(buf_, 0, buf_size);
}
void resizeBuffer(void)
{
  char *temp = (char *) malloc(buf_size);
  if (!temp)
  {
    fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
    exit(1);
  }
  if (buf_)
  {
    strncpy(temp, buf_, buf_size); /* peteg: strlcpy is safer, but not POSIX/ISO C. */
    free(buf_);
  }
  buf_ = temp;
}
char *buf_;
int cur_, buf_size;

