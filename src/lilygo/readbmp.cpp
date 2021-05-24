#include "readbmp.hpp"
#include "epd_driver.h"

#define SD_BUFFER_PIXELS 20


int drawBitmap_SD(const char *filename, int x, int y,uint8_t *framebuffer){
    bool flip = true; // bitmap is stored bottom-to-top
    uint8_t buffer[3 * SD_BUFFER_PIXELS];
    uint32_t pos = 0;
    //epd_fill_circle( x,  y, 10, 0, framebuffer);

    File file = SPIFFS.open(filename);
    if(!file){
        Serial.println("Failed to open file for reading");
        return -1;
    }

    // Parse BMP header
    if (read16(file) == 0x4D42){ // BMP signature
        //Serial.println("BMP file");
        uint32_t fileSize = read32(file);
        uint16_t creatorBytes1 = read16(file);
        uint16_t creatorBytes2 = read16(file);
        uint32_t imageOffset = read32(file); // Start of image data
        uint32_t headerSize = read32(file);
        uint32_t width  = read32(file);
        uint32_t height = read32(file);
        uint16_t planes = read16(file);
        uint16_t depth = read16(file); // bits per pixel
        uint32_t format = read32(file);  //metodo de compresion
        if ((planes == 1) && (format == 0)){ // uncompressed is handled
/*             Serial.printf("File size: %d\n",fileSize); 
            Serial.printf("Image Offset: %d\n",imageOffset); 
            Serial.printf("Creator: %d :: %d\n",creatorBytes1,creatorBytes2); 
            Serial.printf("Header size: %d\n",headerSize); 
            Serial.printf("Bit Depth: %d\n",depth); 
            Serial.printf("Image size: %d x %d\n",width,height); */
            // BMP rows are padded (if needed) to 4-byte boundary
            uint32_t rowSize = (width * depth / 8 + 3) & ~3;
            if (height < 0){
                height = -height;
                flip = false;
            }
            uint16_t w = width;
            uint16_t h = height;

            size_t buffidx = sizeof(buffer); // force buffer load
            for (uint16_t row = 0; row < h; row++) { // for each line
                if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                    pos = imageOffset + (height - 1 - row) * rowSize;
                else     // Bitmap is stored top-to-bottom
                    pos = imageOffset + row * rowSize;
                if (file.position() != pos)
                { // Need seek?
                    file.seek(pos);
                    buffidx = sizeof(buffer); // force buffer reload
                }
                uint8_t bits=0;
                        for (uint16_t col = 0; col < w; col++) { // for each pixel
                            // Time to read more pixel data?
                            if (buffidx >= sizeof(buffer)){
                                file.read(buffer, sizeof(buffer));
                                buffidx = 0; // Set index to beginning
                            }
                            switch (depth){
                                case 1: {// one bit per pixel b/w format
                                    if (0 == col % 8){
                                        bits = buffer[buffidx++];
                                    }
                                    uint16_t bw_color = bits & 0x80 ?  0 : 255;
                                    //display.drawPixel(col+x, row+y, bw_color);
                                    epd_draw_pixel(col+x, row+y, bw_color, framebuffer);
                                    bits <<= 1;
                                }
                                break;
                                case 24: {// standard BMP format
                                    uint16_t b = buffer[buffidx++];
                                    uint16_t g = buffer[buffidx++];
                                    uint16_t r = buffer[buffidx++];
                                    uint16_t bw_color = (r + g + b) / 3;
                                    //display.drawPixel(col+x, row+y, bw_color);
                                    epd_draw_pixel(col+x, row+y, bw_color, framebuffer);
                                }
                                break;
                            }
                        } // end pixel


            }// end line
        }
        }else{
            Serial.println("No es BMP");
        }


  file.close();
return 0;

}



uint16_t read16(File f)
{
  // BMP data is stored little-endian, same as Arduino.
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f)
{
  // BMP data is stored little-endian, same as Arduino.
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

