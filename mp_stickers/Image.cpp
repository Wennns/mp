#include "Image.h"
#include <iostream>
#include <cmath>
void Image::lighten() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l + 0.1 > 1) {
                pixel.l = 1;
            } else {
                pixel.l = pixel.l + 0.1;
            }
        }
    } 
}
void Image::lighten(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l + amount > 1) {
                pixel.l = 1;
            } else {
                pixel.l = pixel.l + amount;
            }
        }
    }
}
void Image::darken() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l - 0.1 < 0) {
                pixel.l = 0;
            } else {
                pixel.l = pixel.l - 0.1;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.l - amount < 0) {
                pixel.l = 0;
            } else {
                pixel.l = pixel.l - amount;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.s - 0.1 < 0) {
                pixel.s = 0;
            } else {
                pixel.s = pixel.s - 0.1;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.s - amount < 0) {
                pixel.s = 0;
            } else {
                pixel.s = pixel.s - amount;
            }
        }
    }
}
void Image::grayscale() {
    //uninitilized problem
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = 0;
        }
    }
}
void Image::illinify() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel &pixel = this->getPixel(x,y);
            if (pixel.h <= 114 || 293 <= pixel.h) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.s + 0.1 > 1) {
                pixel.s = 1;
            } else {
                pixel.s = pixel.s + 0.1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            if (pixel.s + amount > 1) {
                pixel.s = 1;
            } else {
                pixel.s = pixel.s + amount;
            }
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            pixel.h = fmod(pixel.h + degrees, 360);
            if (pixel.h < 0) {
                pixel.h += 360;
            }
            //pixel.h = fmod(pixel.h+degrees,360.0);
            // if (pixel.h + degrees > 360) {
            //     pixel.h = fmod(pixel.h + degrees, 360.0);
            // } 
            // if (pixel.h + degrees < 0) {
            //     pixel.h = 360 + fmod(pixel.h + degrees, 360.0);
            // } else {
            //     pixel.h = pixel.h + degrees;
            // }
            // pixel.h = pixel.h + degrees360;
            // if (pixel.h + degrees % 360 > 360) {
            //     pixel.h = pixel.h + degrees % 360 - 360;
            // } 
            // if (pixel.h + (degrees) % 360 < 0) {
            //     pixel.h = pixel.h + (degrees) % 360 + 360;
            // }
            // if (pixel.h + degrees >= 360) {
            //     pixel.h = (pixel.h + degrees) % 360.0;
            // }
            // if (pixel.h + degrees < 0) {
            //     pixel.h = (pixel.h + degrees) % 360.0 + 360;            
            // } else {
            //     pixel.h = pixel.h + degrees;
            // }
            // if (degrees > 0) {
            //     if (pixel.h + degrees <= 360) {
            //         pixel.h = pixel.h + degrees;
            //     } else {
            //         pixel.h = remainder(pixel.h + degrees, 360);
            //     }
            // } else {
            //     if (pixel.h + degrees >= 0) {
            //         pixel.h = pixel.h + degrees;
            //     } else {
            //         //unsigned interger = 360 - remainder(pixel.h + degrees, 360);
            //         pixel.h = remainder(pixel.h + degrees, 360);
            //     }
            // }
        }
    }
}
void Image::scale(double factor) {
    Image image;
    unsigned widthNew = this->width() * factor;
    unsigned heightNew = this->height() * factor;
    //create a newImage with widthNew,heightNew 
    //for loop 
    image.resize(widthNew,heightNew);
    for (unsigned i = 0; i < widthNew; i++) {
        for (unsigned j = 0; j < heightNew; j++) {
            image.getPixel(i,j) = this->getPixel(i/factor, j/factor);
        }
    }
    *this = image;
}
void Image::scale(unsigned w, unsigned h) {
    double widthFactor = (double) w/width();
    double heightFactor =(double) h/height();
    if (widthFactor > heightFactor) {
        this -> scale(heightFactor);
    } else {
        this -> scale(widthFactor);
    }
}