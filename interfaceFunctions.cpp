/* CSCI 261: Final Project
 *
 * Author: Shane Gordon (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // Previous projects provided ClearInput and MultChoice, for instance.
 *
 * This file contains all interface functions that branch off of main.cpp
 */
#include <iostream>
#include "interfaceFunctions.h"
#include <fstream>
#include "SIF.hpp"
#include "PPM.hpp"
using namespace std;
/**
 * @note clearInput does not appear in the header file, as it is only employed within this file
 * 
 */
void clearInput(){
    //Clear cin of errors
    cin.clear();
    char badChar;
    //Continue assigning cin items until they are all gone
    do { badChar = cin.get(); } while( badChar != '\n' );
    return;
}
int multChoice(string title, string choices [], int choiceNum){
    //Pose the question
    cout << title << endl;
    while(1){//Keep providing options until valid response is given
        for(int i=0; i<choiceNum;i++){//Print all options in a formatted option
            cout << i+1 <<": "<<choices[i] << endl;
        }
        int choice = 0;
        cout << "Your selection: ";
        cin >> choice;
        if(cin.fail()){//If its not even a number, clear input and continue loop
            cout << "That input is not an integer, please try again." << endl;
            clearInput();
            continue;
        }
        if(choice > choiceNum||choice < 1){//If it is not a provided option, clear input and contiue loop
            cout << "That input is not an option, please try again." << endl;
            clearInput();
            continue;
        }
        //If the choice made it this far, it is valid. Clear input and return their choice
        clearInput();
        return choice;
    }
}
bool verifyExt(string input, string ext){
    //Check if input is even long enough to have an extension
    if(input.length()<5) return false;
    //Check if the last characters match the extension
    return input.substr(input.length()-3,-1)==ext;
}
void openSIF(string fileName){
    cout << "Opening " << fileName << "..." << endl;
    ifstream file;
    file.open(fileName);
    if(file.fail()){//Every one of the four core functions has this check to ensure that the file the user is trying to access exists
        cout << "That file does not exist. Exiting program" << endl;
        return;
    }
    SIF s(file);
    using namespace sf;
    //They also have similar rending oeprations, different by how the window is sized.
    //With SIF objects, the window is sized based on size AND pixel size, whereas PPM objects are always just width x height.
    //The object is only displayed once, as it is not animated
    RenderWindow window( VideoMode(s.getWidth()*s.getPixelSize(), s.getHeight()*s.getPixelSize()), "SIF file" );
    window.clear();
    s.render(window);
    window.display();
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                cout << "Window closing..." << endl;
                window.close();
                break;
            }
        }
    }
};

void convertPPM(string ppmName,string sifName){
    ifstream inputFile;
    inputFile.open(ppmName);
    if(inputFile.fail()){//Test is file exists
        cout << "PPM file does not exist. Exiting program" << endl;
        return;
    }
    PPM ppm(inputFile);//Construct PPM object from ppm file
    int pixelSize = 1;
    clearInput();
    cout << "Please enter your desired size of each pixel in the SIF file (1 < size < 51): ";
    do{//Take user input on pixel size until the size falls within the bounds and is an integer
        cin >> pixelSize;
        if(cin.fail()||pixelSize<1||pixelSize>50){
            cout << "That input is invalid" << endl;
            clearInput();
            continue;
        }else{
            break;
        }
    }while(1);
    cout << "Converting..." << endl;
    SIF sif(ppm);//Construct an SIF object using the PPM object
    sif.setPixelSize(pixelSize);
    cout << "Saving new file..." << endl;
    sif.save(sifName+".sif");//Add extension to name and save
}
void openPPM(string fileName){
    //Open and validate file
    cout << "Opening " << fileName << "..." << endl;
    ifstream file;
    file.open(fileName);
    if(file.fail()){
        cout << "That file does not exist. Exiting program" << endl;
        return;
    }
    //Construct ppm object
    PPM p(file);
    using namespace sf;
    //Render ppm object to a window
    RenderWindow window( VideoMode(p.getWidth(), p.getHeight()), "PPM file" );
    window.clear();
    p.render(window);
    window.display();
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                cout << "Window closing..." << endl;
                window.close();
                break;
            }
        }
    }
}
void convertSIF(string sifName, string ppmName){//This function works similarly to openSIF, but is somewhat simpler as PPM files do not have a pixel size
    ifstream inputFile;
    inputFile.open(sifName);
    if(inputFile.fail()){
        cout << "SIF file does not exist. Exiting program" << endl;
        return;
    }
    cout << "Converting..." << endl;
    SIF sif(inputFile);
    //The ppm constructor is different as it cannot rely on an understanding of the SIF class. Thus every value is fed piece by piece
    PPM ppm(sif.getPixelSize(),sif.getWidth(),sif.getHeight(),sif.getPixels());
    cout << "Saving new file..." << endl;
    ppm.save(ppmName+".ppm");

}