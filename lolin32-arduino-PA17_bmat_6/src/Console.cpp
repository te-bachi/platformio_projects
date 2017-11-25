/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "Console.h"

#include <Arduino.h>
#include <FS.h>

#include "SPIFFS.h"
#include "FlashFileSystem.h"

void
printArgs(Shell &shell, int argc, const ShellArguments &argv)
{
    Serial.println("Arguments:");
    for (int i = 0; i < argc; i++) {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(argv[i]);
    }
}

void
cmdList(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("No direcory");
        return;
    }
    listDir(SPIFFS, argv[1], 0);
}

void
cmdMkdir(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("No direcory");
        return;
    }
    createDir(SPIFFS, argv[1]);
}

void
cmdRmdir(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("No directory");
        return;
    }
    removeDir(SPIFFS, argv[1]);
}

void
cmdWrite(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 3) {
        Serial.println("write <file> <numbytes>");
        return;
    }
    printArgs(shell, argc, argv);
}

void
cmdWriteLn(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("writeln <file>");
        return;
    }

    //std::ostringstream buffer;

    File file = SPIFFS.open(argv[1], FILE_WRITE);
    if (file) {
        int key;
        while (true) {
            key = shell.readKey();
            if (key == -1) {
                delay(10);
                continue;
            }
            if (key == KEY_RETURN) {
                break;
            }
            Serial.write(key);
            file.write(key);
            //buffer << key;
        }
    }
    //printArgs(shell, argc, argv);
}

void
cmdAppend(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 3) {
        Serial.println("append <file> <numbytes>");
        return;
    }
    printArgs(shell, argc, argv);
}

void
cmdAppendLn(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("appendln <file>");
        return;
    }
    printArgs(shell, argc, argv);
}

void
cmdRead(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("append <file>");
        return;
    }
    printArgs(shell, argc, argv);
}

void
cmdRename(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 3) {
        Serial.println("rename <old file> <new file>");
        return;
    }
    printArgs(shell, argc, argv);
}

void
cmdRemove(Shell &shell, int argc, const ShellArguments &argv)
{
    if (argc < 2) {
        Serial.println("remove <file>");
        return;
    }
    deleteFile(SPIFFS, argv[1]);
}
