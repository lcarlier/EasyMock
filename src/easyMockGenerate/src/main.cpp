#include <CodeGeneratorCTemplate.h>
#include "CodeParserCLang.h"
#include "MainCodeGenerator.h"
#include "Function.h"
#include <LLVMParser.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  LLVMParser of;
  of.setFlags("-I/usr/include/ -I/usr/include/linux");
  CodeGeneratorCTemplate cg;
  MainCodeGenerator cp("/usr/include/stdio.h", of, cg);
  cp.generateCode("/tmp");

  return 0;
}
