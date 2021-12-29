/**
 * \file Angler.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Angler.h"
#include "Item.h"
#include "Aquarium.h"
#include <string>
using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring AnglerImageName = L"images/angler.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CAngler::CAngler(CAquarium* aquarium) : CItem(aquarium)
{
    mFishImage = unique_ptr<Bitmap>(Bitmap::FromFile(AnglerImageName.c_str()));
    if (mFishImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += AnglerImageName;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Draw this item
 * \param graphics Graphics device to draw on
 */
void CAngler::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mFishImage->GetWidth();
    double hit = mFishImage->GetHeight();
    graphics->DrawImage(mFishImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mFishImage->GetWidth(), (float)mFishImage->GetHeight());
}
/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CAngler::HitTest(int x, int y)
{
    double wid = mFishImage->GetWidth();
    double hit = mFishImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mFishImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mFishImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

/**
* This function checks if fish can catch other fish
* \return true
*/
bool CAngler::CanCatch()
{
    return true;
}

/**
* This function lets the angler catch another fish if close enough
* \param item a fish to check
*/
bool CAngler::CatchFish(weak_ptr<CItem> item)
{
    // Distance in the X and Y directions
    double dx = GetX() - item.lock() ->GetX();
    double dy = GetY() - item.lock() ->GetY();

    double distance = sqrt(dx * dx + dy * dy);
    if (distance < 150 && mCaughtFish.lock() != item.lock())
    {
        mCaughtFish = item;
        return true;
    }
    return false;
}

/**
* This function sends movement details to caught fish
* \param changeX The change in the x direction
* \param changeY The change in the y direction
*/
void CAngler::PreMoved(double changeX, double changeY)
{
    CItem::PreMoved(changeX, changeY);
    auto caught = mCaughtFish.lock();
    if (caught != nullptr)
    {
        caught->Follow(changeX, changeY);
    }
}
