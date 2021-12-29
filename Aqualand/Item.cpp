/**
 * \file Item.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"
#include "Angler.h"
#include <memory>

using namespace std;


/**
* Destructor
*/
CItem::~CItem()
{
}

/**
 * Constructor
 * \param aquarium The aquarium this item is a member of
 */
CItem::CItem(CAquarium* aquarium) : mAquarium(aquarium)
{
}

/**
* This function makes fish follow anglers
* \param changeX The change in the x direction
* \param changeY The change in the y direction
*/
void CItem::Follow(double changeX, double changeY)
{
	double initialX = GetX();
	double initialY = GetY();
	SetLocation(changeX + initialX, changeY + initialY);
}

/**
* This function checks if fish is angler and if so, checks if the fish catches another
* \param changeX The change in the x direction
* \param changeY The change in the y direction
*/
void CItem::PreMoved(double changeX, double changeY)
{
    if (CanCatch())
    {
        mAquarium->CheckForCatch(this);

    }
}