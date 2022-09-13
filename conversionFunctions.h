#ifndef CONVERSIONFUNCTIONS_H
#define CONVERSIONFUNCTIONS_H
#include <SFML/Graphics/Color.hpp>
#include <iostream>
using namespace std;
/**
 * @brief Converts a decimal number to binary
 * 
 * @param num decimal number
 * @param bits number of desired bits, if a minimum is required
 * @return string binary number
 */
string numToBinary(unsigned int num, unsigned int bits);
/**
 * @brief Converts a binary number to a decimal number
 * 
 * @param bin Binary to be converted
 * @return unsigned int decimal number
 */
unsigned int binaryToNum(string bin);
/**
 * @brief converts a decimal number to hex
 * 
 * @param num decimal number to be converted
 * @param addTag Whether or not to add the hashtag to the front
 * @return string Hex result
 */
string numToHex(int num,bool addTag);
/**
 * @brief Converts hexadecimal to a decimal number
 * 
 * @param hex Input hex number
 * @return int resulting decimal number
 */
int hexToNum(string hex);
/**
 * @brief Converts an SFML color to binary
 * 
 * @param c input SFMl color
 * @return string resulting binary
 */
string colorToBinary(sf::Color c);
/**
 * @brief converts a binary color to an SFMl color
 * 
 * @param s input binary color
 * @return sf::Color Resulting SFML color
 */
sf::Color binaryToColor(string s);
/**
 * @brief Converts an SFML color to a hexadecimal color
 * 
 * @param c Input SFMl color
 * @return string resulting hex color
 */
string colorToHex(sf::Color c);
/**
 * @brief Converts an SFMl color to a hex color
 * 
 * @param hex Input hex color
 * @return sf::Color Resulting SFML color
 */
sf::Color hexToColor(string hex);
/**
 * @brief Converets an SFML color to RGB
 * 
 * @param c Input SFML color
 * @return string Resulting RGB string
 */
string colorToRGB(sf::Color c);
/**
 * @brief Converts an RGB string to an SFML color
 * 
 * @param s 
 * @return sf::Color 
 */
sf::Color RGBToColor(string s);
/**
 * @brief Detects which color format a string contains
 * 
 * @param s String to be judged
 * @return unsigned int the format of the string
 */
unsigned int detectFormat(string s);
/**
 * @brief Tests if given character is a number
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool isNum(char c);
#endif