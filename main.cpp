/* CSCI 261: Final Project
 *
 * Author: Shane Gordon (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Referenced class notes to remember how to seed the random number generator
 *
 *  This program defines and provides the tools to work with a new image file format, SIF (Shane Image File)
 */
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include "interfaceFunctions.h"
using namespace std;
/*
Contained in int main: A switch statement depending on user input. While this is the 'beating heart' of the program, it is also just the entrance
to the program's interface

*/
int main(){
    //The random number generator is seeded at program launch for the purpose of the SIF class's randomization of pixel formats
    srand(time(NULL));
    //Most functions used here are defined in interfaceFunctions.cpp and interfaceFunctions.h
    string options [] = {"Open an SIF file", "Convert a PPM file to an SIF file", "Open a PPM file", "Convert an SIF file to a PPM file"};
    unsigned short int path = multChoice("Which action would you like to perform?",options,4);
    path--;
    //With the path chosen using multChoice, the user is directed to the below switch statement
    string fileName = "";
    string fileName2 = "";
    switch(path){
        case 0: //When the user chooses to open an SIF file
        cout << "Enter the address of an SIF file: ";
        cin >> fileName;
        //The pattern for these cases is similar, with if(verifyExt(fileName, "ext")) being employed as a guard against incorrect file
        //selection. If they pass this test, they are good to go into the individual functions of this program
        if(verifyExt(fileName,"sif")){
            cout << "File has correct extension. Attempting to open..." << endl;
            openSIF(fileName);
        }else{
            
            cout << "ERROR: File does not appear to have the correct extension. Exiting program..." << endl;
            return 0;
        }
        break;
        case 1: //When the user chooses to convert a PPM file to an SIF file

        cout << "Enter the address of the PPM file to convert: ";
        cin >> fileName;
        if(verifyExt(fileName,"ppm")){
            cout << "File has correct extension." << endl;
        }else{
            cout << "ERROR: File does not appear to have the correct extension. Exiting program..." << endl;
            return 0;
        }
        cout << "Enter the name of the desired file (Do not include any numbers): ";
        cin >> fileName2;
        
        convertPPM(fileName,fileName2);
        break;
        case 2://When the user chooses to open a PPM file
        cout << "Enter the address of a PPM file: ";
        cin >> fileName;
        if(verifyExt(fileName,"ppm")){
            cout << "File has correct extension. Attempting to open..." << endl;
            openPPM(fileName);
        }else{
            cout << "ERROR: File does not appear to have the correct extension. Exiting program..." << endl;
            return 0;
        }
        break;

        case 3: //When the user chooses to convert an SIF file to a PPM file

        cout << "Enter the address of the SIF file to convert: ";
        cin >> fileName;
        if(verifyExt(fileName,"sif")){
            cout << "File has correct extension." << endl;
        }else{
            cout << "ERROR: File does not appear to have the correct extension. Exiting program..." << endl;
            return 0;
        }
        cout << "Enter the desired name of the file (Do not include numbers): ";
        cin >> fileName2;
        convertSIF(fileName,fileName2);
        break;
    }
}