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

#ifndef ROBOT_HASH_H
#define ROBOT_HASH_H

#include "Common.h"
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <copying> Atomic </copying>

class ROBOT_EXPORT Hash
{
public:
	// Constructors
	explicit Hash				(const uint8* data,
								 uint32 dataLength);
	explicit Hash				(const char* file = NULL);

public:
	// Functions
	void		Append			(const uint8* data,
								 uint32 dataLength);
	bool		Append			(const char* file);

public:
	// Operators
	bool		operator ==		(const Hash& hash) const;
	bool		operator !=		(const Hash& hash) const;

public:
	// Properties
	uint32		Result;			// Rolling checksum value
};

} // namespace Robot
#endif // ROBOT_HASH_H
