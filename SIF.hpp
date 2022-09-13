#ifndef SIF_HPP
#define SIF_HPP
#include <SFML/Graphics.hpp>
#include <cstring>
#include <fstream>
#include "Pixel.h"
#include <random>
#include "PPM.hpp"
using namespace std;

/**
 * @brief The SIF class stores and manipulates the data present in an SIF file. Can also be used to create an SIF file
 * 
 */
class SIF{
    private:
        unsigned int width,height,pixelSize;
        /**
         * @brief readHeadersFromFile scans an sif file for its headers.
         * @note These functions are kept private in the PPM and SIF classes because they are easily misused elsewhere
         * 
         * @param file ifstream file object to be read
         */
        void readHeadersFromFile(ifstream &file){
            string thisLine = "";
            file >> thisLine;
            file >> width;
            file >> height;
            file >> pixelSize;
            file >> thisLine;
            pixels = new Pixel*[height];
            for(int row = 0; row<height; row++){
                pixels[row] = new Pixel [width];
            }
}
        /**
         * @brief readPixelsFromFile reads all color values from the given sif file and stores them in the object's pixels array
         * 
         * @param file ifstream file object to be read
         */
        void readPixelsFromFile(ifstream &file){
            unsigned int row = 0;
            unsigned int column = 0;
            while(!file.eof()&&row!=height){
                string thisLine = "";
                file >> thisLine;
                //Unique to SIF, each pixel has an unknown format that must be derived to properly make a Pixel object
                unsigned short int thisFormat = detectFormat(thisLine);
                if(thisFormat == 1){
                    //When the format is binary, three blocks must be read at once
                    string thisLine2, thisLine3;
                    file >> thisLine2;
                    file >> thisLine3;
                    thisLine = thisLine + " " + thisLine2 + " " + thisLine3;
                }
                pixels[row][column] = Pixel(thisFormat,thisLine);
                column++;
                if(column==width){
                    column = 0;
                    row++;
                }
            }
        }
    public:

        
        Pixel** pixels;
        /**
         * @brief Destroy the SIF object and its pixel array
         * 
         */
        ~SIF(){
            cout << "Deleting an SIF object" << endl;
            for(int i=0; i<height; i++){
                delete[] pixels[i];
            }
            delete[] pixels;
        }
        /**
         * @brief Used in debugging. Prints all pixel data
         * 
         */
        void printRaw(){
            cout << "Printing raw with width " << width << " and height " << height << endl; 
            for(int row = 0; row < height; row++){
                for(int column = 0; column < width; column++){
                    cout << "Content: " << pixels[row][column].content << endl;
                }
            }
        }
        /**
         * @brief Construct a new SIF object with no width nor height and a pixel size of 3
         * 
         */
        SIF(){
            width = 0;
            height = 0;
            pixelSize = 3;
        }
        /**
         * @brief Construct a new SIF object from a file. Calls readHeaders and readPixels in sequence
         * 
         * @param file 
         */
        SIF(ifstream &file){
            readHeadersFromFile(file);
            readPixelsFromFile(file);
        }
        /**
         * @brief Construct a new SIF object using a PPM object
         * 
         * @param src source PPM object
         */
        SIF(const PPM &src){
            width = src.getWidth();
            height = src.getHeight();
            pixelSize = 3;
            pixels = new Pixel* [height];
            //Allocate pixel array
            for(int i=0; i<height;i++){
                pixels[i] = new Pixel [width];
            }
            sf::Color** pColors = src.getPixels();
            for(int row=0; row<src.getHeight();row++){
                for(int column=0; column<src.getWidth(); column++){
                    //All ppm pixels are RGB, they must be scrambled to make it a true SIF file
                    short unsigned int format = rand() % 3;
                    sf::Color thisColor = pColors[row][column];
                    Pixel pix(format,thisColor);
                    pixels[row][column] = pix;
                }
            }
        };
        

        /**
         * @brief Get the Pixels object
         * 
         * @return Pixel** 
         */
        Pixel** getPixels() const{
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
         * @brief Get the Pixel Size object
         * 
         * @return unsigned int 
         */
        unsigned int getPixelSize() const{
            return pixelSize;
        }
        /**
         * @brief Set the Pixel Size object
         * 
         * @param pixelSize 
         */
        void setPixelSize(const unsigned int pixelSize){
            this->pixelSize = pixelSize;
        }
        /**
         * @brief Save the SIF object to an SIF file
         * 
         * @param location 
         */
        void save(string location){
            //Declare the file
            ofstream outFile;
            outFile.open(location);
            //Fill in header information
            outFile << "SIF" << endl;
            outFile << to_string(width) + " " + to_string(height) << " " << pixelSize << endl;
            outFile << "255" << endl;
            for(int row=0; row < height; row++){//Index through each row
                for(int column=0; column < height; column++){//Insert every pixel in row seperated by four spaces
                    outFile << pixels[row][column].content << "    ";
                }
                //Indent for next row
                outFile << endl;
            }
            //CLose the file
            outFile.close();
        }
        /**
         * @brief Render the SIF image to a window
         * 
         * @param window the window to render the image to
         */
        void render(sf::RenderTarget &window){
            cout << "Rendering..." << endl;
            using namespace sf;
            for(int row=0;row<height;row++){
                for(int column=0; column<width; column++){
                    //Deriving SFML color from given format and content
                    Color c;
                    string content = pixels[row][column].content;
                    unsigned int format = pixels[row][column].format;
                    switch(format){
                        case 0:
                            c = hexToColor(content);
                        break;
                        case 1:
                            c = binaryToColor(content);
                        break;
                        case 2:
                            c = RGBToColor(content);
                        break;
                    }
                    //Create the rectangle object and modify it to match SIF file
                    RectangleShape thisRect;
                    //SIF files are rendered with rectangles since their pixels can be different sizes
                    thisRect.setPosition(Vector2f(column*pixelSize,row*pixelSize));
                    thisRect.setSize(Vector2f(pixelSize,pixelSize));
                    thisRect.setFillColor(c);
                    window.draw(thisRect);
                }
            }
            
            cout << "Done rendering" << endl;
            
        }
};
#endif