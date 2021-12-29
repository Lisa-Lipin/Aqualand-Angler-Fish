/**
 * \file FishBeta.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms beta fish in aquarium
 */
#pragma once
#include "Item.h"
#include<memory>
/**
* Class that forms beta fish in aquarium
*/
class CFishBeta :
    public CItem
{
public:
    CFishBeta(CAquarium* aquarium);
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
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;
private:
    /// image for beta
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

