/**
 * \file Dory.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms dory fish in aquarium
 */
#pragma once
#include "Item.h"
#include<memory>
 /**
 * Class that forms dory fish in aquarium
 */
class CDory :
    public CItem
{
public:
    CDory(CAquarium* aquarium);
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
    CDory() = delete;

    /// Copy constructor (disabled)
    CDory(const CDory&) = delete;
private:
    /// image for dory
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

