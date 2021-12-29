/**
 * \file Aquarium.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms aquarium
 */

#pragma once
#include<memory>
#include<vector>
#include "Item.h"

/**
* Class that forms aquarium
*/
class CAquarium
{
public:
	/// constructor
	CAquarium();
	void Add(std::shared_ptr<CItem> item);
	std::shared_ptr<CItem> HitTest(int x, int y);
	/// draw the aquarium
	void OnDraw(Gdiplus::Graphics* graphics); 
	/// move clicked items to end of vector
	void MoveToEnd(std::shared_ptr<CItem> item);
	/// iterate through items and see if can be caught
	void CheckForCatch(CItem* item);
private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use
	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
};

