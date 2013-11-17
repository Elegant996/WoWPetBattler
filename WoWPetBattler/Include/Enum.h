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

#ifndef ROBOT_ENUM_H
#define ROBOT_ENUM_H

#include "Global.h"
#include <map>
#include <cstring>
namespace Robot {



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define ROBOT_ENUM( type ) template<> std::map<const char*, type> \
			Robot::Enum<type>::mMap = std::map<const char*, type>();



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

template <typename Type> class Enum
{
public:
	//----------------------------------------------------------------------------//
	// Constructors                                                               //
	//----------------------------------------------------------------------------//

	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	Enum (void);



public:
	//----------------------------------------------------------------------------//
	// Functions                                                                  //
	//----------------------------------------------------------------------------//

	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	static Type Parse (const char* key)
	{
		// Check if key value is null
		if (key == nullptr) return (Type) -1;

		// Initialize static parser
		if (mMap.empty()) Enum<Type>();

		// Search for matching key
		typename std::map<const char*, Type>::const_iterator i;
		for (i = mMap.begin(); i != mMap.end(); ++i)
			if (strcmp (i->first, key) == 0) return i->second;

		return (Type) -1;
	}

	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	static const char* Parse (Type value)
	{
		// Initialize static parser
		if (mMap.empty()) Enum<Type>();

		// Search for matching value
		typename std::map<const char*, Type>::const_iterator i;
		for (i = mMap.begin(); i != mMap.end(); ++i)
			if (i->second == value) return i->first;

		return nullptr;
	}



private:
	//----------------------------------------------------------------------------//
	// Fields                                                                     //
	//----------------------------------------------------------------------------//

	static std::map<const char*, Type> mMap;
};

} // namespace Robot
#endif // ROBOT_ENUM_H
