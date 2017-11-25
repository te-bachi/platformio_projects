/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Shell.h"

void cmdList(Shell &shell, int argc, const ShellArguments &argv);
void cmdMkdir(Shell &shell, int argc, const ShellArguments &argv);
void cmdRmdir(Shell &shell, int argc, const ShellArguments &argv);
void cmdWrite(Shell &shell, int argc, const ShellArguments &argv);
void cmdWriteLn(Shell &shell, int argc, const ShellArguments &argv);
void cmdAppend(Shell &shell, int argc, const ShellArguments &argv);
void cmdAppendLn(Shell &shell, int argc, const ShellArguments &argv);
void cmdRead(Shell &shell, int argc, const ShellArguments &argv);
void cmdRename(Shell &shell, int argc, const ShellArguments &argv);
void cmdRemove(Shell &shell, int argc, const ShellArguments &argv);

ShellCommand(list,      "1",  cmdList);
ShellCommand(mkdir,     "2",  cmdMkdir);
ShellCommand(rmdir,     "3",  cmdRmdir);
ShellCommand(write,     "a",  cmdWrite);
ShellCommand(writeln,   "aa", cmdWriteLn);
ShellCommand(append,    "b",  cmdAppend);
ShellCommand(appendln,  "bb", cmdAppendLn);
ShellCommand(read,      "c",  cmdRead);
ShellCommand(rename,    "d",  cmdRename);
ShellCommand(remove,    "e",  cmdRemove);

extern Shell shell;

#endif
