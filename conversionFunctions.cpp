/* CSCI 261: Final Project conversion functions
 *
 * Author: Shane Gordon
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Online number converters to verify results
 *
 * XXXXXXXX (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <cstring>
//Regrettably 'string' is a part of iostream and thus it must be included
#include <iostream>
#include "conversionFunctions.h"
using namespace std;
string numToBinary(unsigned int num, unsigned int bits){
    string output = "";
    do{
        output = to_string(num%2)+output;
        num/=2;
    }while(num>=1);
    while(output.length() < bits){
        output = "0" + output;
    }
    return output;
}
unsigned int binaryToNum(string bin){
    unsigned int num = 0;
    for(int i=0; i<bin.length();i++){
        if(bin[i]=='1'){
            num+=(pow(2,bin.length()-i-1));
        } 
    }
    return num;
}
string numToHex(int num,bool addTag = true){
    string output = "";
    while(num>=1){
        int thisPlace = num%16;
        char thisChar = 'Z';
        if(thisPlace<10){
            thisChar = to_string(thisPlace)[0];
        }else{
            thisChar = (char)(55+thisPlace);
        }
        output = thisChar + output;
        num/=16;
    }
    while(output.length()<2) output = "0" + output;
    if(addTag) output = "#" + output;
    return output;
}
int hexToNum(string hex){
    unsigned int num = 0;
    if(hex[0]=='#') hex = hex.substr(1,-1);
    for(int i=0; i<hex.length();i++){
        int thisValue = 0;
        if(hex[i]-65<0){
            thisValue = stoi(hex.substr(i,1));
        }else{
            thisValue = hex[i]-55;
        }
        num += thisValue * pow(16,hex.length()-i-1);
    }
    return num;
}
string colorToBinary(sf::Color c){
    return numToBinary(c.r,8) + " " + numToBinary(c.g,8)+" "+numToBinary(c.b,8);
}
sf::Color binaryToColor(string s){
    sf::Color output;
    string bin = s.substr(0,8);
    output.r = binaryToNum(bin);
    bin = s.substr(9,8);
    output.g = binaryToNum(bin);
    bin = s.substr(18,8);
    output.b = binaryToNum(bin);
    return output;
}
string colorToHex(sf::Color c){
    string output = "";
    output.append(numToHex(c.r,true));
    output.append(numToHex(c.g,false));
    output.append(numToHex(c.b,false));
    return output;
}
sf::Color hexToColor(string hex){
    sf::Color output;
    if(hex[0]=='#') hex = hex.substr(1,-1);
    output.r = hexToNum(hex.substr(0,2));
    output.g = hexToNum(hex.substr(2,2));
    output.b = hexToNum(hex.substr(4,2));
    return output;
}
string colorToRGB(sf::Color c){
    string red = to_string((int)c.r);
    string green = to_string((int)c.g);
    string blue = to_string((int)c.b);
    return "(" + red + "," + green + "," + blue + ")";
};
sf::Color RGBToColor(string s){
    //Because the lengths of the numbers in RGB are uncertain, special care must be taken in selecting substrings
    sf::Color output;
    //Red
    int place1 = 1;
    int place2 = s.find(',');
    output.r = stoi(s.substr(place1,place2-place1));
    //Green
    place1 = place2 + 1;
    place2 = s.find(',',place2+1);
    output.g = stoi(s.substr(place1,place2-place1));
    //Blue
    place1 = place2 + 1;
    place2 = s.find(')');
    output.b = stoi(s.substr(place1, place2-place1));
    return output;
}
unsigned int detectFormat(string s){
    if(s[0]=='#') return 0;
    if(s[0]=='(') return 2;
    return 1;
}
bool isNum(char c){
    return c-65 < 0;
}