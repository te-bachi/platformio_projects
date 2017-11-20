/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "SdCard.h"


const int    SdCard::SD_CHIP_SELECT_PIN         = 38;
const int    SdCard::LOG_FILE_INDEX_MAX         = 1024;
const char  *SdCard::LOG_FILE_PREFIX_TEACH      = "T_0";
const char  *SdCard::LOG_FILE_PREFIX_EXERCISE   = "E_";
const char  *SdCard::LOG_FILE_PREFIX_RESULT     = "R_";
const char  *SdCard::LOG_FILE_SUFFIX            = ".txt";


SdCard::SdCard()
: init(false)
{
    //
}

SdCard::~SdCard()
{
    //
}


bool
SdCard::begin()
{

    if (!SD.begin(SD_CHIP_SELECT_PIN)) {
        SerialUSB.println("SD.begin(SD_CHIP_SELECT_PIN) failed!");
        return false;
    }

    if (!card.init(SPI_HALF_SPEED, SD_CHIP_SELECT_PIN)) {
        SerialUSB.println("card.init(SPI_HALF_SPEED, SD_CHIP_SELECT_PIN) failed!");
      return false;
    }

    if (!volume.init(card)) {
        SerialUSB.println("volume.init(card) failed!");
      return false;
    }

    init = true;

    return true;
}

bool
SdCard::isInitialized()
{
    return init;
}

void
SdCard::openRoot()
{
    root = SD.open("/");
}

void
SdCard::rewindRoot()
{
    root.rewindDirectory();
}

void
SdCard::closeRoot()
{
    root.close();
}

void
SdCard::write(File &file, Quaternion &upperArmQ, Position &upperArmPos, Quaternion &lowerArmQ, Position &lowerArmPos)
{
    String line;

    line   = String("[ ");
    line  += String(millis());
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(upperArmQ.getW(), 4) + ", ";
    line  += String(upperArmQ.getX(), 4) + ", ";
    line  += String(upperArmQ.getY(), 4) + ", ";
    line  += String(upperArmQ.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(upperArmPos.getX(), 4) + ", ";
    line  += String(upperArmPos.getY(), 4) + ", ";
    line  += String(upperArmPos.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(lowerArmQ.getW(), 4) + ", ";
    line  += String(lowerArmQ.getX(), 4) + ", ";
    line  += String(lowerArmQ.getY(), 4) + ", ";
    line  += String(lowerArmQ.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(lowerArmPos.getX(), 4) + ", ";
    line  += String(lowerArmPos.getY(), 4) + ", ";
    line  += String(lowerArmPos.getZ(), 4);
    line  += String(" ] ");

    file.println(line);

}


/******************************************************************************
 * Teach file
 */
File
SdCard::replaceTeachFile(DateTime &t)
{
    String filename;

    filename  = String(LOG_FILE_PREFIX_TEACH);
    filename += String(LOG_FILE_SUFFIX);

    if (SD.exists(filename)) {
        SD.remove(filename);
    }

    SerialUSB.print("open: ");
    SerialUSB.print(filename);
    File file = SD.open(filename, FILE_WRITE);
    if (file) {
        SerialUSB.println(" <success>");
        file.println(getDateString(t));
    } else {
        SerialUSB.println(" <fail>");
    }

    return file;
}

File
SdCard::openNextTeachFile()
{
    String pattern = String(LOG_FILE_PREFIX_TEACH);
    return findFile(pattern);
}

void
SdCard::closeTeachFile(File &file, DateTime &t)
{
    file.println(getDateString(t));
    file.close();
}

/******************************************************************************
 * Exercise file
 */
File
SdCard::openExerciseFile(DateTime &t)
{
    String filename;

    /* Create new file */
    filename  = getNextExerciseFilename();

    SerialUSB.print("open: ");
    SerialUSB.print(filename);
    File file = SD.open(filename, FILE_WRITE);

    if (file) {
        SerialUSB.println(" <success>");
        file.println(getDateString(t));
    } else {
        SerialUSB.println(" <fail>");
    }

    return file;
}

File
SdCard::openNextExerciseFile()
{
    String pattern = LOG_FILE_PREFIX_EXERCISE;
    return findFile(pattern);
}

void
SdCard::deleteExerciseFiles()
{
    String pattern = LOG_FILE_PREFIX_EXERCISE;
    deleteFiles(pattern);
}

void
SdCard::closeExerciseFile(File &file, DateTime &t)
{
    file.println(getDateString(t));
    file.close();
}

/******************************************************************************
 * Result file
 */
File
SdCard::openResultFile(DateTime &t)
{
    String filename;

    /* Create new file */
    filename  = getNextResultFilename();

    SerialUSB.print("open: ");
    SerialUSB.print(filename);
    File file = SD.open(filename, FILE_WRITE);

    if (file) {
        SerialUSB.println(" <success>");
        file.println(getDateString(t));
    } else {
        SerialUSB.println(" <fail>");
    }

    return file;
}

File
SdCard::openNextResultFile()
{
    String pattern = LOG_FILE_PREFIX_RESULT;
    return findFile(pattern);
}

void
SdCard::deleteResultFiles()
{
    String pattern = LOG_FILE_PREFIX_RESULT;
    deleteFiles(pattern);
}

void
SdCard::closeResultFile(File &file, DateTime &t)
{
    file.println(getDateString(t));
    file.close();
}

/*
void
SdCard::readLine(File &file, char *buffer, int *len)
{
    int     i;
    char    ch = 1;

    SerialUSB.print("readLine ");
    for (i = 0; file.available(); i++) {
        ch = file.read();
        if (ch > 0 && ch != '\n') {
            buffer[i] = ch;
        } else {
            SerialUSB.println("done!");
            break;
        }
    }
    *len = i;
}
*/


/******************************************************************************
 * Download
 */


void
SdCard::downloadTeachFiles()
{
    File file;

    openRoot();
    rewindRoot();

    while (true) {

        file = openNextTeachFile();

        if (!file) {
            break;
        }

        downloadFile(file);
    }

    closeRoot();
}

void
SdCard::downloadExerciseFiles()
{
    File file;

    openRoot();
    rewindRoot();

    while (true) {
        file = openNextExerciseFile();

        if (!file) {
            break;
        }

        downloadFile(file);
    }

    closeRoot();
}

void
SdCard::downloadResultFiles()
{
    File file;

    openRoot();
    rewindRoot();

    while (true) {
        file = openNextResultFile();

        if (!file) {
            break;
        }

        downloadFile(file);
    }

    closeRoot();
}

void
SdCard::downloadFile(File &file)
{
    String line;

    SerialUSB.println(">>>");
    SerialUSB.println(file.name());
    while (true) {
        line = file.readStringUntil('\n');
        if (line.length() == 0) {
            break;
        }
        SerialUSB.println(line);
        delay(5);
    }
    SerialUSB.println("<<<");
    file.close();
}


/******************************************************************************
 * Date/time functions
 */

String
SdCard::getDateFileSuffix(DateTime &t)
{
    char buf[32];

    sprintf(buf, "%04d_%02d_%02d_%02d_%02d_%02d", t.year(), t.month(),  t.day(),
                                                  t.hour(), t.minute(), t.second());

    return String(buf);
}

String
SdCard::getDateString(DateTime &t)
{
    char buf[32];

    sprintf(buf, "%02d.%02d.%04d %02d:%02d:%02d", t.day(), t.month(), t.year(),
                                                  t.hour(), t.minute(), t.second());

    return String(buf);
}

/******************************************************************************
 * Private methods
 */


void
SdCard::deleteFiles(String &pattern)
{
    File    entry;
    bool    removeFile;
    String  filename;

    openRoot();
    root.rewindDirectory();

    SerialUSB.print("Delete files with pattern \"");
    SerialUSB.print(pattern);
    SerialUSB.println("\"");

    while (true) {
        removeFile = false;
        entry      = root.openNextFile(FILE_READ);

        /* EOF */
        if (!entry) {
            break;
        }

        /* Is directory */
        if (entry.isDirectory()) {
            // no nothing

        /* Is regular file */
        } else {
            filename = entry.name();

            if (filename.startsWith(pattern)) {
                removeFile = true;
            }
        }

        entry.close();

        /* Remove permanently */
        if (removeFile) {
            SerialUSB.println(filename);
            SD.remove(filename);
        }
    }

    closeRoot();
}

File
SdCard::findFile(String &pattern)
{
    File    entry;
    String  filename;

    while (true) {
        entry  = root.openNextFile(FILE_READ);

        /* EOF */
        if (!entry) {
            break;
        }

        /* Is directory */
        if (entry.isDirectory()) {
            // no nothing

        /* Is regular file */
        } else {
            filename = entry.name();
            if (filename.startsWith(pattern)) {

                /* Return opened file */
                return entry;
            }
        }

        entry.close();
    }

    return File();
}

String
SdCard::getNextTeachFilename()
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename  = String(LOG_FILE_PREFIX_TEACH);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            return filename;
        }
    }

    return "";
}

String
SdCard::getNextExerciseFilename()
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename  = String(LOG_FILE_PREFIX_EXERCISE);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            return filename;
        }
    }

    return "";
}

/**
 * Find the next available log file. Or return a null string
 * if we've reached the maximum file limit.
 */
String
SdCard::getNextResultFilename()
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename  = String(LOG_FILE_PREFIX_RESULT);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            return filename;
        }
    }

    return "";
}
