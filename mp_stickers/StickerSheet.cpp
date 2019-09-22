#include "StickerSheet.h"
#include <iostream>
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    // std::cout << "Ctor" << std::endl;
    basePic = new Image(picture);
    //std::cout << "start" << std::endl;
    unsigned curNum = 0;
    max_ = max; //The maximum number of stickers (Images) on this StickerSheet
    stickers = new Image*[max]; //Store the stickers in an array.
    unsigned countLayer = 0; //Count the current layer.
    xCor = new unsigned[max_]; //Stores the x of stickers
    yCor = new unsigned[max_]; //Stores the y of stickers
    //int countAdd = 0;
}
StickerSheet::~StickerSheet(){
    _helpDe();
}
StickerSheet::StickerSheet(const StickerSheet &other) {
    _copy(other);
}
void StickerSheet::_helpDe() {
    delete basePic;
    if (curNum != 0) {
        for (unsigned i = 0; i < curNum; i++) {
            Image *toDelete = stickers[i];
            delete toDelete;
        }
    }
    //std::cout << "done looping" << std::endl;
    delete[] stickers;//array of pointers. still need to delete array[i]. still a pointer exists
    stickers = nullptr;
    delete[] xCor;
    xCor = nullptr;
    delete[] yCor;
    yCor = nullptr;
}
void StickerSheet::_copy(const StickerSheet &other) {
    //std::cout << "helpCtor" << std::endl;
    basePic = new Image(*(other.basePic));
    curNum = other.curNum;
    max_ = other.max_;
    countLayer = other.countLayer;
    xCor = new unsigned[other.max_];
    yCor = new unsigned[other.max_];
    stickers = new Image*[other.max_];
    for (unsigned i = 0; i < other.curNum; i++) {
        xCor[i] = other.xCor[i];
        yCor[i] = other.yCor[i];
        stickers[i] = new Image(*(other.stickers[i]));
    }
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
        _helpDe();
        _copy(other);
        return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    if(curNum < max) {
        Image **newStiArr = new Image*[max];
        unsigned *newXCor = new unsigned[max];
        unsigned *newYCor = new unsigned[max];
        for (unsigned i = 0; i < max; i++) {
            if (i <= curNum) {
                newStiArr[i] = stickers[i];
                newXCor[i] = xCor[i];
                newYCor[i] = yCor[i];
            } 
        }
        stickers = newStiArr;
        xCor = newXCor;
        yCor = newYCor;
    } else {
        Image **newStickers = new Image*[max];
        unsigned *newXCor = new unsigned[max];
        unsigned *newYCor = new unsigned[max];
        for (unsigned i = 0; i < max; i++) {
            newStickers[i] = new Image(*stickers[i]);
            newXCor[i] = xCor[i];
            newYCor[i] = yCor[i];
        }
        for (unsigned j = max; j < curNum; j++) {
            Image *to_lost = stickers[j];
            delete to_lost;
            curNum--;
        }
        stickers = newStickers;
        xCor = newXCor;
        yCor = newYCor;
    }
    
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    curNum = 0;
        if (curNum <= max_) {
            stickers[curNum] = new Image(sticker);
            xCor[curNum] = x;
            yCor[curNum] = y;
            curNum++;
            countLayer = curNum -1;
            return countLayer;
        }
        return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index <= countLayer && stickers[index] != NULL) {
        xCor[index] = x;
        yCor[index] = y;
        return true;
    }
    return false;
}
void StickerSheet::removeSticker(unsigned index) {
    if (index >= 0 && index < curNum) { // only delete when possible
        Image * to_delete = stickers[index];
        delete to_delete;
        curNum--;
        for (unsigned i = 0; i < curNum; i++) {
            if (i < index) {
                stickers[i] = stickers[i];
                xCor[i] = xCor[i];
                yCor[i] = yCor[i];
            } else {
                stickers[i] = stickers[i+1];
                xCor[i] = xCor[i+1];
                yCor[i] = yCor[i+1];
            } 
        }
    }

}
Image* StickerSheet::getSticker(unsigned index) {
    if (index > curNum - 1) {
      return NULL;
    }
    return stickers[index];
}
Image StickerSheet::render() const {
    Image deepBase(*basePic);
    for (unsigned i = 0; i < curNum; i++) { 
        deepBase = helper(*stickers[i]);
    }
    return deepBase;
}
Image StickerSheet::helper(Image sticker) const {
    Image deepBase(*basePic);
    unsigned newWid = deepBase.width();
    unsigned newHei = deepBase.height(); 
    for (unsigned j = 0; j < curNum; j++) {
        if ((xCor[j] + (*stickers[j]).width()) > newWid) {
            newWid = xCor[j] + (*stickers[j]).width();
        }
        if (yCor[j] + (*stickers[j]).height() > newHei) {
            newHei = yCor[j] + (*stickers[j]).height();
        }
    }
    deepBase.resize(newWid, newHei);
    for (unsigned i = 0; i < newWid; i++) {
        for (unsigned j = 0; j < newHei; j++) {
        if (xCor[i] == i && yCor[i] == j) {
            for (unsigned m = 0; m < sticker.width(); m++) {
            for (unsigned n = 0; n < sticker.height(); n++) {
                deepBase.getPixel(i,j) = sticker.getPixel(m,n);
                }
            }
        }
        }
    }
    return deepBase;
 }
