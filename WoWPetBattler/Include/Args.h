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

#ifndef ROBOT_ARGS_H
#define ROBOT_ARGS_H

#include "Global.h"
#include <memory>
namespace Robot {



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ROBOT_EXPORT Args
{
public:
	// Constructors
	Args							(void);
	Args							(const char*  args);
	Args							(const char** argv);

public:
	// Functions
	bool			Create			(const char*  args);
	bool			Create			(const char** argv);
	void			Destroy			(void);
	
	uint32			GetLength		(void) const;
	uint32			GetHeight		(void) const;
	uint32			GetWidth		(void) const;

	char*			GetArgs			(void) const;
	char**			GetArgv			(void) const;

private:
	// Fields
	class Data;
	std::shared_ptr<Data> mData;	// Shared args data
};

} // namespace Robot
#endif // ROBOT_ARGS_H
