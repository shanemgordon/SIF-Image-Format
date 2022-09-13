#ifndef PPM_HPP
#define PPM_HPP
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstring>
#include <iostream>
#include "SIF.hpp"
#include "conversionFunctions.h"
#include "Pixel.h"
using namespace std;
class PPM{
    private:

        unsigned int width, height, maxColor;
        sf::Color** pixels;
        /**
         * @brief readHeadersFromFile scans a ppm file for its headers.
         * @note These functions are kept private in the PPM and SIF classes because they are easily misused elsewhere
         * 
         * @param file ifstream file object to be read
         */
        void readHeadersFromFile(ifstream &file){

            string thisLine;

            do{//The purpose of these brackets is to skip through any comments which are not to be included in any SIF file and which are not
            //needed in the rendering process
                file >> thisLine;
            }while(thisLine[0]=='#'||!isNum(thisLine[0]));

            width = stoi(thisLine);

            do{
                file >> thisLine;
            }while(thisLine[0]=='#'||!isNum(thisLine[0]));
            height = stoi(thisLine);

            do{
                file >> thisLine;
            }while(thisLine[0]=='#'||!isNum(thisLine[0]));
            maxColor = stoi(thisLine);

            pixels = new sf::Color*[height];
            for(int i=0; i<height; i++){
                pixels[i] = new sf::Color[width];
            }
        }
        /**
         * @brief readPixelsFromFile reads all color values from the given ppm file and stores them in the object's pixels array
         * 
         * @param file ifstream file object to be read
         */
        void readPixelsFromFile(ifstream &file){
            unsigned int row = 0;
            unsigned int column = 0;
            string thisLine;
            while(!file.eof()){
                int r, g, b;
                do{//Clear comments out of the way
                    file >> thisLine;
                }while(thisLine[0]=='#');
                //Collect a pixel
                r = stoi(thisLine) * 255 / maxColor;
                do{//Clear comments out of the way
                    file >> thisLine;
                }while(thisLine[0]=='#');
                //Collect a pixel
                g = stoi(thisLine) * 255 / maxColor;
                do{//Clear comments out of the way
                    file >> thisLine;
                }while(thisLine[0]=='#');
                //Collect a pixel
                b = stoi(thisLine) * 255 / maxColor;
                //Create and store a color
                sf::Color c(r,g,b);
                pixels[row][column] = c;
                column++;
                if(column == width){
                    column = 0;
                    row++;
                }
            }
        }

    public:
        /**
         * @brief Get the Pixels object
         * 
         * @return sf::Color** 
         */
        sf::Color** getPixels() const{
            return pixels;
        }
        /**
         * @brief Get the Width object
         * 
         * @return unsigned int 
         */
        unsigned int getWidth() const{
            return width;
        }
        /**
         * @brief Get the Height object
         * 
         * @return unsigned int 
         */
        unsigned int getHeight() const{
            return height;
        }
        /**
         * @brief Get the Max Color object
         * 
         * @return unsigned int 
         */
        unsigned int getMaxColor() const{
            return maxColor;
        }
        /**
         * @brief Construct a new PPM object with no width or height, and with a maxColor of 255
         * 
         */
        PPM(){
            width = 0;
            height = 0;
            maxColor = 255;
        }
        /**
         * @brief Construct a new PPM object with a given file. Calls readHeadersFromFile and readPixelsFromFile in sequence
         * 
         * 
         * @param file ifstream file object to be read
         */
        PPM(ifstream &file){
            readHeadersFromFile(file);
            readPixelsFromFile(file);
        }
        /**
         * @brief Construct a new PPM object using information from an SIF object
         * 
         * @param pixelSize Size of each pixel in the SIF object
         * @param width of the SIF's pixel grid
         * @param height of the SIF's pixel grid
         * @param src contents of the SIF object's pixel grid
         */
        PPM(unsigned int pixelSize, unsigned int width, unsigned int height, Pixel** src){
            //Copy header informatin
            cout << "Creating a ppm..." << endl;
            pixels = new sf::Color* [height*pixelSize];
            this->width = width*pixelSize;
            this->height = height*pixelSize;
            this->maxColor = 255;
            //Allocate pixel array for SIF's information. Must be larger by a magnitude of pixelsize as PPM files do not have this metric
            for(int row=0; row<height*pixelSize; row++){
                pixels[row] = new sf::Color [width*pixelSize];
            }
            //These are to show the user the function's progress. I found that this is the most intense function, so its probably nessecary
            float progress = 0;
            float increment = 100/(float)((float)height*(float)pixelSize);
            for(int row=0; row<height*pixelSize; row++){
                
                progress+=increment;
                cout << "Progress: " << to_string(progress).substr(0,5) << "%" << endl;
                for(int column = 0; column < width*pixelSize; column++){
                    //Several pixels in the PPM file will often correspond to one in the SIF object, divided into a grid where each square is
                    //the width and height of the SIF's pixelsize
                    Pixel thisPixel = src[row/pixelSize][column/pixelSize];
                    unsigned int format = thisPixel.format;
                    switch(format){//These conversions can be found in conversionFunctions.h and conversionFunctions.cpp
                        //Hexidecimal
                        case 0:
                            pixels[row][column] = hexToColor(thisPixel.content);
                        break;
                        //Binary
                        case 1:
                            pixels[row][column] = binaryToColor(thisPixel.content);
                        break;
                        //RGB
                        case 2:
                            pixels[row][column] = RGBToColor(thisPixel.content);
                        break;
                        default:
                        break;
                    }//End switch
                }//End column
            }//End row
        }//End constructor
        /**
         * @brief Destroy the PPM object and its pixel arrays
         * 
         */
        ~PPM(){
            cout << "Deleting a PPM" << endl;
            for(int i=0;i<height;i++){
                delete[] pixels[i];
            }
            delete[] pixels;
        }
        /**
         * @brief Saves the header and pixel data of the PPM object to a file
         * 
         * @param address 
         */
        void save(string address){
            cout << "Saving PPM file" << endl;
            ofstream outputFile;
            outputFile.open(address);
            //Header
            outputFile << "P3" << endl;
            outputFile << width << " " << height << endl;
            outputFile << maxColor << endl;
            for(int row = 0; row < height; row++){
                for(int column = 0; column < width; column++){//This is quite a bit simpler than SIF, since all pixels have the same format
                    sf::Color c = pixels[row][column];
                    outputFile << to_string((int)c.r) << " " << to_string((int)c.g) << " " << to_string((int)c.b) << "    ";
                }
                outputFile << endl;
            }
            outputFile.close();
        }
        /**
         * @brief Draws all pixels to a rendering window
         * 
         * @param window 
         */
        void render(sf::RenderTarget &window){
            cout << "rendering" << endl;
            using namespace sf;
            VertexArray va;
            for(int row=0;row<height;row++){
                for(int column=0; column<width; column++){
                    Vertex thisVert;
                    thisVert.position = Vector2f(column,row);//Place the vertex in the right spot
                    thisVert.color = pixels[row][column];//Color it according to its corresponding pixel in the pixels array
                    va.append(thisVert);//Add it to the vertex array
                }
            }
            window.draw(va);//Draw the whole array of vertices
            cout << "Done rendering" << endl;
        }
};
#endif