
/**
 * \file Nemo.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Nemo.h"
#include <string>
using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring NemoImageName = L"images/nemo.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CNemo::CNemo(CAquarium* aquarium) : CItem(aquarium)
{
    mFishImage = unique_ptr<Bitmap>(Bitmap::FromFile(NemoImageName.c_str()));
    if (mFishImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += NemoImageName;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Draw this item
 * \param graphics Graphics device to draw on
 */
void CNemo::Draw(Gdiplus::Graphics* graphics)
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
bool CNemo::HitTest(int x, int y)
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
* checks if fish can catch others
* \return false
*/
bool CNemo::CanCatch()
{
    return false;
}