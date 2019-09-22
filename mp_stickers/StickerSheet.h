/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
class StickerSheet {
    public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;

    
    private:
    Image* basePic;
    unsigned curNum; //current number of stickers
    unsigned *xCor; //Store the x coordinate of the sticker
    unsigned *yCor; //Store the y coordinate of the sticker
    unsigned max_; //The new value for the maximum number of Images in the StickerSheet.
    Image** stickers;
    unsigned countLayer;
    Image helper(Image sticker) const;
    void _copy(const StickerSheet &other);
    void _helpDe();
    // unsigned baseWidth;
    // unsigned baseHeight;
    //int countAdd;
};
