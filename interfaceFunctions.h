#ifndef INTERFACE_FUNCTIONS_H
#define INTERFACE_FUNCTIONS_H
#include <iostream>
using namespace std;
/**
 * @brief clearInput clears cin of all text and error for future use
 * 
 */
void clearInput();
/**
 * @brief multChoice accepts multiple choice user input and restricts them from entering anything else
 * 
 * @param title The title of the question being asked
 * @param choices An array of strings to represent options
 * @param choiceNum The number of entries in the above array, to prevent unessecary calculation
 * @return int The choice the user chose, index starting at 1 for readability
 */
int multChoice(string title, string choices [], int choiceNum);
/**
 * @brief VerifyExt checks if the extension of an entered filename matches the second argument, to prevent incorrect file manipulation
 * 
 * @param input The filename to be judged
 * @param ext The extension which must be matched
 * @return true If the filename has the desired extension
 * @return false If the filename does not have the desired extension
 */
bool verifyExt(string input, string ext);
/**
 * @brief openSIF renders the provided fileName, provided that file exists and is valid
 * 
 * @param fileName The name of the file to render
 */
void openSIF(string fileName);
/**
 * @brief convertPPM converts a PPM file to an SIF file with a chosen pixel size
 * 
 * @param ppmName The name of the PPM file to convert
 * @param sifName The name of the sif file to be created
 */
void convertPPM(string ppmName,string sifName);
/**
 * @brief openPPM renders the provided fileName, provided that file exists and is valid
 * 
 * @param fileName Name of file to be rendered
 */
void openPPM(string fileName);
/**
 * @brief convertSIF converts an SIF file to a PPM file. Takes awhile.
 * 
 * @param sifName Name of sif file to be converted
 * @param ppmName Name of target ppm file
 */
void convertSIF(string sifName, string ppmName);
#endif