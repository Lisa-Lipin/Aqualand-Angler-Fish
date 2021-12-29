/**
 * \file Aquarium.cpp
 *
 * \author Elizabeth Lipin
 */
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "Angler.h"
#include "Item.h"
#include <vector>

using namespace Gdiplus;
using namespace std;

 /**
  * Draw the aquarium
  * \param graphics The GDI+ graphics context to draw on
  */
void CAquarium::OnDraw(Gdiplus::Graphics* graphics)
{
    graphics->DrawImage(mBackground.get(), 0, 0,
        mBackground->GetWidth(), mBackground->GetHeight());
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush green(Color(0, 64, 0));
    graphics->DrawString(L"Under the Sea!", -1,
        &font, PointF(2, 2), &green);
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}
/**
  * move clicked items to end of items vector
  * \param item item to move
  */
void CAquarium::MoveToEnd(std::shared_ptr<CItem> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
        mItems.push_back(item);
    }
}

/**
  * iterate over fish and check for possible catch
  * \param item item to check
  */
void CAquarium::CheckForCatch(CItem* item)
{
    for (auto fish : mItems)
    {
        if (item != fish.get())
        {
            if (((CAngler*)(item))->CatchFish(fish))
            {
                break;
            }
        }
    }
}

/**
 * Aquarium constructor
 */
CAquarium::CAquarium()
{
    mBackground = unique_ptr<Gdiplus::Bitmap>(
        Bitmap::FromFile(L"images/background1.png"));
    if (mBackground->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/background1.png");
    }
}
/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}