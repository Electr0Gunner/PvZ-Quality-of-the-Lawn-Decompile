#pragma once

#ifndef PROFILE_HEADER_FILE
#define PROFILE_HEADER_FILE

#include "Common.h"
#include <map>

namespace Sexy
{
	class XMLParser;			// Forward Class declaration to avoid Include files
	class XMLElement;

	class Profile
	{
		// 'Protected' Section allows only classes derived from Profile
		// To access it's class members. We will Access these variables
		// through Get/Set functions (which will validate)
	protected:
		SexyString							mUserName;

		std::map<SexyString, int>			mIntegerMap;
		std::map<SexyString, bool>			mBoolMap;
		std::map<SexyString, SexyString>	mStringMap;
		std::map<SexyString, double>		mFloatMap;


		Profile();

	public:
		static Profile*				GetProfile();
		virtual ~Profile();

		// Serialization Functions
	public:
		virtual bool				Save(SexyString theFileName);			// Returns 'true' if success
		virtual bool				Load(SexyString theFileName);			// Returns 'true' if success
		virtual void				ParseXML(Sexy::XMLParser* theParser);
		virtual bool				HasAttribute(Sexy::XMLElement* theNode, SexyString theAttrib);

		//Even More Abstract Serialization functions
	public:
		virtual bool				LoadUser(SexyString theUserName);		// Load the User from the users dir
		virtual bool				SaveUser();								// Called to Save this User
		virtual bool				NewUser(SexyString theUserName);		// Called to start a New User
		virtual bool				RenameUser(SexyString theNewUserName);	// Called to Rename User
		virtual bool				DeleteUser(SexyString theUserName);		// Called to Delete User

		// Member Variable Get/Set Methods
	public:
		virtual SexyString			GetUserName(){return mUserName;};		// returns the User Name
		virtual bool				SetUserName(SexyString theUserName);	// Returns 'true' if success

		virtual void				ResetProfile();

		// A new Feature!  Allows for Multiple State Types!  Story mode, Casual Mode, Mini Game Mode
		virtual std::string			GetStateFileName(SexyString theStateName, SexyString theUserName = _S(""));
		virtual void				EraseStateSaves(SexyString theUserName = _S(""));
		virtual std::string			GetUserFileName(SexyString theUserName = _S(""));

		// Another Cool Feature!  Read and Write integers with String Values!
		virtual void				SetIntegerValue(SexyString theValueName, int theValue);
		virtual int					GetIntegerValue(SexyString theValueName, int theDefault);

		virtual void				SetBoolValue(SexyString theValueName, bool theValue);
		virtual bool				GetBoolValue(SexyString theValueName, bool theDefault);

		virtual void				SetFloatValue(SexyString theValueName, double theValue);
		virtual double				GetFloatValue(SexyString theValueName, double theDefault);

		virtual void				SetStringValue(SexyString theValueName, SexyString theValue);
		virtual SexyString			GetStringValue(SexyString theValueName, SexyString theDefault);
	};
};

#define GETPROFILEINT(a,b) Sexy::Profile::GetProfile()->GetIntegerValue(a,b)
#define GETPROFILEFLOAT(a,b) Sexy::Profile::GetProfile()->GetFloat(a,b)
#define GETPROFILEBOOL(a,b) Sexy::Profile::GetProfile()->GetBooleanValue(a,b)
#define GETPROFILESTRING(a,b) Sexy::Profile::GetProfile()->GetStringValue(a,b)

#define SETPROFILEINT(a,b) Sexy::Profile::GetProfile()->SetIntegerValue(a,b)
#define SETPROFILEFLOAT(a,b) Sexy::Profile::GetProfile()->SetFloat(a,b)
#define SETPROFILEBOOL(a,b) Sexy::Profile::GetProfile()->SetBooleanValue(a,b)
#define SETPROFILESTRING(a,b) Sexy::Profile::GetProfile()->SetStringValue(a,b)

#endif