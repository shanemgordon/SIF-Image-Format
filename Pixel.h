#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>
#include "conversionFunctions.h"
//Include only Color.hpp because it needs no other features of Graphics
#include <SFML/Graphics/Color.hpp>
using namespace std;
/**
 * @brief The Pixel class is made to store in an SIF class. It can have any of the three formats, and contains a string pertaining to content
 * 
 * 
 */
struct Pixel{
    unsigned int format;
    string content;
    //0 = hex
    //1 = binary
    //2 = RGB
    /**
     * @brief Construct a new Pixel object with white color and hexadecimal format
     * 
     */
    Pixel(){
        format = 0;
        content = "#FFFFFF";
    }
    /**
     * @brief Construct a new Pixel object with a given format and text content
     * 
     * @param format 
     * @param content 
     */
    Pixel(unsigned int format, string content){
        this->content = content;
        this->format = format;
    }
    /**
     * @brief Construct a new Pixel object with a given format and SFML Color object.
     * 
     * @param format 
     * @param value 
     */
    Pixel(unsigned int format, sf::Color value){
        this->format = format;
        switch(format){//These conversion functions are stored in conversionFunctions.h and conversionFunctions.cpps
            case 0:
                content = colorToHex(value);
            break;

            case 1:
                content = colorToBinary(value);
            break;

            case 2:
                content = colorToRGB(value);
            break;
        }
    }
};
#endif