/**
 * \file Nemo.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms nemo fish in aquarium
 */
#pragma once
#include "Item.h"
#include<memory>
 /**
 * Class that forms nemo fish in aquarium
 */
class CNemo :
    public CItem
{
public:
    CNemo(CAquarium* aquarium);
    /// draws fish
    virtual void Draw(Gdiplus::Graphics* graphics) override;
    /// checks if fish clicked
    /// \param x x-coord
    /// \param y y-coord
    /// \return true if clicked
    bool HitTest(int x, int y);
    /// checks if fish can catch others
    /// \return false
    bool CanCatch();
    /// Default constructor (disabled)
    CNemo() = delete;

    /// Copy constructor (disabled)
    CNemo(const CNemo&) = delete;
private:
    /// image for nemo
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

