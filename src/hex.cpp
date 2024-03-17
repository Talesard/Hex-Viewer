#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

bool ReadFile (const std::string &theFilePath, std::vector<unsigned char> &theBuffer)
{
    std::ifstream anInputStream (theFilePath, std::ios::binary);
    if (!anInputStream) return false;
    std::vector <unsigned char> aBuffer (std::istreambuf_iterator<char> (anInputStream), {});
    theBuffer = aBuffer;
    anInputStream.close();
    return true;
}

void PrintAdrr16 (size_t theValue, std::ostringstream& theStream) {
    unsigned char* aBytes = reinterpret_cast <unsigned char*> (&theValue);
    int aSetwValues[4] = {1, 2, 2, 3};
    for (int i = 3; i > -1; i--) {
        theStream << std::setfill('0') << std::setw (aSetwValues[i]) << std::hex << (0xff & aBytes[i]);
    }
    theStream << " | ";
}

void PrintDumpLine (std::vector<unsigned char> &theBuffer, size_t theCurrentPos, size_t theColsCount, std::ostringstream& theStream)
{
    if (theColsCount < 16) {
        for (int i = 0; i < 15 - theColsCount; i++) theStream << "   ";
        theStream << "  ";
    }
    theStream << " | ";
    for (size_t i = theCurrentPos - theColsCount + 1; i < theCurrentPos + 1; i++) {
        if (isprint (theBuffer[i])) {
            theStream << std::setw (sizeof (char)) << std::dec << theBuffer[i];
        } else {
            theStream << std::setw (sizeof (char)) << std::dec << '.';
        }
    }
}

void PrintBuffer (std::vector<unsigned char> &theBuffer)
{
    const size_t aColsCount = 16;
    std::ostringstream aResultOutStream;
    aResultOutStream << "Address  | 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f | Characters" << std::endl;
    aResultOutStream << "---------+-------------------------------------------------+-----------------" << std::endl;
    PrintAdrr16 (0, aResultOutStream);

    for (size_t i = 0; i < theBuffer.size(); i++) {
        aResultOutStream << std::setfill ('0') << std::setw (2) << std::hex << (0xff & theBuffer[i]);
        if ((i+1) % aColsCount == 0 && i != 0) {
            PrintDumpLine (theBuffer, i, aColsCount, aResultOutStream);
            aResultOutStream << std::endl;
            PrintAdrr16 ((i+1) * aColsCount, aResultOutStream);
        } else aResultOutStream << " ";
    }
    PrintDumpLine (theBuffer, theBuffer.size()-1, theBuffer.size() % 16, aResultOutStream);
    aResultOutStream << std::endl << "---------+-------------------------------------------------+-----------------" << std::endl;
    aResultOutStream << std::dec << std::setw (sizeof (size_t)) << "Total    | " << theBuffer.size() << " bytes" << std::endl;
    std::cout << aResultOutStream.str();
}

void Help (char const *theArgv[]) {
    std::cout << "Hex Viewer" << std::endl;
    std::cout << "Usage: " << theArgv[0] << " <file>" << std::endl;
}

int main (int theArgc, char const *theArgv[])
{
    std::string aFilePath;
    std::vector <unsigned char> aBuffer;

    if (theArgc > 1) {
        aFilePath = theArgv[1];
        if (ReadFile (aFilePath, aBuffer)) {
            PrintBuffer (aBuffer);
        } else {
            std::cout << "The file does not exist" << std::endl;
            return 1;
        }
    } else {
        Help (theArgv);
    }

    return 0;
}
