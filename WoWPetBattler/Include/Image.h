////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                        (C) 2010-2013  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef ROBOT_IMAGE_H
#define ROBOT_IMAGE_H

#include "Common.h"
#include <memory>
namespace Robot {

	class Color;
	class Size;
	class Point;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Shared </copying>

class ROBOT_EXPORT Image
{
public:
	// Constructors
	explicit Image					(void);
	explicit Image					(const  Size&  size);
	explicit Image					(uint16 w, uint16 h);

public:
	// Functions
	void			Create			(const  Size&  size);
	void			Create			(uint16 w, uint16 h);
	void			Destroy			(void);

	uint16			GetWidth		(void) const;
	uint16			GetHeight		(void) const;
	uint32*			GetData			(void) const;
	uint32			GetLength		(void) const;

	Color			GetPixel		(const Point& point) const;
	Color			GetPixel		(uint16 x, uint16 y) const;

private:
	// Fields
	class Data;
	std::shared_ptr<Data> mData;	// Shared image data
};

} // namespace Robot
#endif // ROBOT_IMAGE_H
