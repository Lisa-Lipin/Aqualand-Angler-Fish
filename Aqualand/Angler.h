/**
 * \file Angler.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms angler fish in aquarium
 */
#pragma once
#include "Item.h"
#include<memory>
 /**
 * Class that forms angler fish in aquarium
 */
class CAngler :
    public CItem
{
public:
    CAngler(CAquarium* aquarium);
    /// draws fish
    virtual void Draw(Gdiplus::Graphics* graphics) override;
    /// checks if fish clicked
    /// \param x x-coord
    /// \param y y-coord
    /// \return true if clicked
    bool HitTest(int x, int y);

    /// Default constructor (disabled)
    CAngler() = delete;

    /// Copy constructor (disabled)
    CAngler(const CAngler&) = delete;
    /// checks if fish can catch others
    /// \return true
    bool CanCatch();
    /// allows angler to catch fish
    /// \param item fish to catch if possible
    /// \return whether a fish was caught
    bool CatchFish(std::weak_ptr<CItem> item);
    void PreMoved(double changeX, double changeY);
    /// Checks if a certain fish was caught for testing purposes
    /// 
    /// \param item the fish we are checking whether we caught
    /// \return whether that fish was caught
    bool IsCaughtFish(std::weak_ptr<CItem> item) { return mCaughtFish.lock() == item.lock(); }
private:
    /// image for angler
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
    /// fish caught by angler
    std::weak_ptr<CItem> mCaughtFish;

};

