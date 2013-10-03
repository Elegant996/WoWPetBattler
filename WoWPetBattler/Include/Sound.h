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

#ifndef ROBOT_SOUND_H
#define ROBOT_SOUND_H

#include "Common.h"
#include <memory>
#include <string>
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Sound
{
public:
	// Constructors
	Sound							(void);

public:
	// Functions
	std::string		GetName			(void) const;
	uintptr			GetHandle		(void) const;

	real32			GetVolume		(void) const;
	void			SetVolume		(real32 vol);

	real32			GetLevel		(void) const;

	bool			 IsMuted		(void) const;
	void			SetMuted		(bool muted);

	static uint32	Enumerate		(Sound* results,
									 uint32 length);

	static Sound	GetDefault		(void);

	static bool		Initialize		(void);
	static void		Shutdown		(void);

private:
	// Fields
	class Data;
	std::shared_ptr<Data> mData;	// Shared sound data
};

} // namespace Robot
#endif // ROBOT_SOUND_H
