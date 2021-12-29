/**
 * \file Item.h
 *
 * \author Elizabeth Lipin
 *
 * Base class for item in aquarium
 */

#pragma once

class CAquarium;

/**
* Base class for item in aquarium.
*/
class CItem
{
public:
	/// Destructor
	virtual ~CItem();
    
    /** The X location of the item
     * \returns X location in pixels */
    double GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    double GetY() const { return mY; }

    /// Set the item location
    /// \param x X location
    /// \param y Y location
    void SetLocation(double x, double y) { mX = x; mY = y; }
    
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;
    /// Draw this item
    /// \param graphics Graphics device to draw on
    virtual void Draw(Gdiplus::Graphics* graphics) = 0;
    /** Test this item to see if it has been clicked on
     * \param x X location on the aquarium to test
     * \param y Y location on the aquarium to test
     * \return true if clicked on */
    virtual bool HitTest(int x, int y) = 0;
    /**
    * This function checks if fish can catch other fish
    * \return true
    */
    virtual bool CanCatch() { return false; };
    /**
    * This function checks if fish is angler and if so, checks if the fish catches another
    * \param changeX The change in the x direction
    * \param changeY The change in the y direction
    */
    virtual void PreMoved(double changeX, double changeY);
    /**
    * This function makes fish follow anglers
    * \param changeX The change in the x direction
    * \param changeY The change in the y direction
    */
    void Follow(double changeX, double changeY);
private:
    /// The aquarium this item is contained in
    CAquarium* mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
protected:
    CItem(CAquarium* aquarium);
};

