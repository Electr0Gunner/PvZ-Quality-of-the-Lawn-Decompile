// ***************************************************************
//  Profile   version:  2.0   ·  date: 01/02/2008
//  -------------------------------------------------------------
//  Version 2.0 of the Profile class!  Allows you to retrieve
//	any of the four basic types {String, Int, Float, Boolean}
//	without explicitly defining the variable (with support for
//	returning a default value).
//
//	For example, let's say that later in development, a new variable
//	is added.  The variable can be accessed from the map with an
//	default parameter, such that if it hasn't been written yet, the
//	default will be returned.  No explicit variable definition or
//	subsequent updating/validation of previous save files.
//
//	User Profiles are always valid across all versions of the program!
//  -------------------------------------------------------------
//  Copyright (C) James Poag 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "Profile.h"
#include "XMLWriter.h"		// Write
#include "XMLParser.h"		// Read
#include "SexyAppBase.h"

#include "Common.h"			// Sexy Functions like FileExists()

using namespace Sexy;

//************************************
// Method:      Profile
// FullName:    Sexy::Profile::Profile
// Access:      protected 
//************************************
Profile::Profile()
{
}

//************************************
// Method:    GetProfile
// FullName:  Sexy::Profile::GetProfile
// Access:    public 
// Returns:   Profile*
// Description: Singleton Access!  Only one user loaded at a time, this is so we
//				can access the Profile variables anywhere in code, quickly!
//************************************
Profile* Sexy::Profile::GetProfile()
{
	static Profile aProfile;
	return &aProfile;
}

//************************************
// Method:    GetStateFileName
// FullName:  Sexy::Profile::GetStateFileName
// Access:    public 
// Returns:   std::string
// Description: returns the file name of the save state named 'theStateName'
//				This is very useful for saving mid-game progress.  Let's say
//				that a user quits out 1/2 way through a level.  Well, you're
//				going to want to save the state of the game.  This provides
//				a mechanism so that all users will have their own, individual
//				game state.  So mom and can can both pick up where they left off!
// Parameter: SexyString theStateName
//************************************
std::string Sexy::Profile::GetStateFileName( SexyString theStateName, SexyString theUserName /*= ""*/ )
{
	std::string aStateName = SexyStringToStringFast(theStateName);
	std::string aUserName =  (theUserName == _S("")) ? SexyStringToStringFast(mUserName) : SexyStringToStringFast(theUserName);

	return StrFormat("%susers\\%s\\%s.sav", GetAppDataFolder().c_str(), aUserName.c_str(), aStateName.c_str());
}

//************************************
// Method:    GetUserFileName
// FullName:  Sexy::Profile::GetUserFileName
// Access:    virtual public 
// Returns:   std::string
// Description: Used internally to locate the XML Profile settings for the User.
//				This is a separate method (like the one above) in order to change
//				the location for the entire class.  This way you don't have to 
//				Edit the save and load methods separately.  This GetStateFileName()
//				method is along the same idea, only it's used externally by you!
// Parameter: SexyString theUserName
//************************************
std::string Sexy::Profile::GetUserFileName( SexyString theUserName /*= ""*/ )
{
	std::string aUserName = (theUserName == _S("")) ? SexyStringToStringFast(mUserName) : SexyStringToStringFast(theUserName);

	return StrFormat("%susers/%s.xml", GetAppDataFolder().c_str(), aUserName.c_str());
}

//************************************
// Method:    SetIntegerValue
// FullName:  Sexy::Profile::SetIntegerValue
// Access:    public 
// Returns:   void
// Description: Lets you add values to the Profile based on a text key!
//				No more hard coding a value every time you want to expand the 
//				Profile!
// Parameter: SexyString theValueName
// Parameter: int theValue
//************************************
void Sexy::Profile::SetIntegerValue( SexyString theValueName, int theValue )
{
	if (mIntegerMap.find(theValueName) != mIntegerMap.end())
		mIntegerMap[theValueName] = theValue;
	else
		mIntegerMap.insert(std::pair<SexyString,int>(theValueName,theValue));
}

//************************************
// Method:    GetIntegerValue
// FullName:  Sexy::Profile::GetIntegerValue
// Access:    public 
// Returns:   int
// Description: Gets the value of the integer associated with the Key or returns
//				'theDefault' value if not loaded!
// Parameter: SexyString theValueName
// Parameter: int theDefault
//************************************
int Sexy::Profile::GetIntegerValue( SexyString theValueName, int theDefault )
{
	// We will not create a value that doesn't exist.  This means that you can
	// have things like secret values that won't be created in the profile.xml
	// unless you have garnered that prize! (and called SetIntegerValue())
	if (mIntegerMap.find(theValueName) != mIntegerMap.end())
		return mIntegerMap[theValueName];

	return theDefault;
}

Profile::~Profile()
{
}

bool Profile::Save(SexyString theFileName)
{
	XMLWriter aWriter;

	if(aWriter.OpenFile(theFileName) && !aWriter.HasFailed())
	{
		// The XML Writer Class works like a Stack.  
		// http://en.wikipedia.org/wiki/Stack_%28data_structure%29

		// You Start a Node and Set it's Attributes.  Any Nodes you start
		// afterwards are child Nodes of the currently open node.

		// Stop Node removes the node from the stack and closes all child nodes.

		// Notice the Symmetry of Start/Stop Calls

		aWriter.StartElement(_S("Profile"));

			std::map<SexyString,int>::iterator map_itr = mIntegerMap.begin();
			for ( ; map_itr != mIntegerMap.end(); ++map_itr)
			{
				aWriter.StartElement(_S("Integer"));
				aWriter.WriteAttribute(_S("id"), map_itr->first);
				aWriter.WriteAttribute(_S("value"), map_itr->second);
				aWriter.StopElement(/*_S("Integer")*/);
			}

			std::map<SexyString,double>::iterator float_itr = mFloatMap.begin();
			for ( ; float_itr != mFloatMap.end(); ++float_itr)
			{
				aWriter.StartElement(_S("Float"));
				aWriter.WriteAttribute(_S("id"), float_itr->first);
				aWriter.WriteAttribute(_S("value"), (float)float_itr->second);
				aWriter.StopElement(/*_S("Float")*/);
			}

			std::map<SexyString,SexyString>::iterator str_itr = mStringMap.begin();
			for ( ; str_itr != mStringMap.end(); ++str_itr)
			{
				aWriter.StartElement(_S("String"));
				aWriter.WriteAttribute(_S("id"), str_itr->first);
				aWriter.WriteAttribute(_S("value"), str_itr->second);
				aWriter.StopElement(/*_S("Sting")*/);
			}

			std::map<SexyString,bool>::iterator bool_itr = mBoolMap.begin();
			for ( ; bool_itr != mBoolMap.end(); ++bool_itr)
			{
				aWriter.StartElement(_S("Bool"));
				aWriter.WriteAttribute(_S("id"), bool_itr->first);
				aWriter.WriteAttribute(_S("value"), bool_itr->second);
				aWriter.StopElement(/*_S("Bool")*/);
			}


		aWriter.StopElement(/*Profile*/);

		aWriter.CloseFile();

		return true; // Success
	}

	return false; // FAILURE
}

//************************************
// Method:      Load
// FullName:    Sexy::Profile::Load
// Access:      virtual public 
// Returns:     bool
// Parameter:   SexyString theFileName
// Description: Loads the '%user_name%.xml' from the '%APP_DATA_FOLDER%/users/' dir
//************************************
bool  Profile::Load(SexyString theFileName)
{
	mIntegerMap.clear();
	mBoolMap.clear();
	mFloatMap.clear();
	mStringMap.clear();

	XMLParser aParser;

	if(aParser.OpenFile(SexyStringToStringFast(theFileName)) && !aParser.HasFailed())
	{
		XMLElement aNode;

		ParseXML(&aParser);
		return true;			// SUCCESS
	}

	//FAILURE
	return false;
}

// This can be done inline with the code, but makes it messy
bool Profile::HasAttribute(Sexy::XMLElement *theNode, SexyString theAttrib)
{
	return (theNode && theNode->mAttributes.find(theAttrib) != theNode->mAttributes.end());
}

// I'm only passing the Parser to this class because the Profile is the only thing
// we are storing in this class.  See Notes below.
void Profile::ParseXML(Sexy::XMLParser* theParser)
{
	if(theParser == NULL ) return; //OOPS

	XMLElement aNode;

	while(theParser->NextElement(&aNode)) // The Node gets fill with the next node data
	{
		switch(aNode.mType)
		{
		case XMLElement::TYPE_START: //the open tag.  eg: <Profile>
			{
				if(aNode.mValue == _S("Profile")) //Corresponds with the SAVE()
				{
				}
				else if(aNode.mValue == _S("Bool")) //Corresponds with the SAVE()
				{
					if (HasAttribute(&aNode, _S("id")) && HasAttribute(&aNode, _S("value")))
					{
						SexyString anId = aNode.mAttributes[_S("id")];
						SexyString aValue = aNode.mAttributes[_S("value")];
						bool aBoolean = (aValue == _S("true") || aValue == _S("TRUE") || aValue == _S("1") || aValue == _S("yes") || aValue == _S("YES"));

						mBoolMap.insert(std::pair<SexyString,bool>(anId, aBoolean));
					}
				}
				else if(aNode.mValue == _S("String")) //Corresponds with the SAVE()
				{
					if (HasAttribute(&aNode, _S("id")) && HasAttribute(&aNode, _S("value")))
					{
						SexyString anId = aNode.mAttributes[_S("id")];
						SexyString aValue = aNode.mAttributes[_S("value")];

						mStringMap.insert(std::pair<SexyString,SexyString>(anId, aValue));
					}
				}	
				else if(aNode.mValue == _S("Float")) //Corresponds with the SAVE()
				{
					if (HasAttribute(&aNode, _S("id")) && HasAttribute(&aNode, _S("value")))
					{
						SexyString anId = aNode.mAttributes[_S("id")];
						double aValue = atof(SexyStringToStringFast(aNode.mAttributes[_S("value")]).c_str());

						mFloatMap.insert(std::pair<SexyString,double>(anId, aValue));
					}
				}	
				else if(aNode.mValue == _S("Integer"))
				{
					if (HasAttribute(&aNode, _S("id")) && HasAttribute(&aNode, _S("value")))
					{
						SexyString anId = aNode.mAttributes[_S("id")];
						int aValue = sexyatoi(aNode.mAttributes[_S("value")].c_str());

						mIntegerMap.insert(std::pair<SexyString,int>(anId, aValue));
					}
				}
				break;
			}
		case XMLElement::TYPE_END: // The closing tag. eg: </Profile>
			{
				break;
			}
		}
	}
}

//************************************
// Method:    LoadUser
// FullName:  Sexy::Profile::LoadUser
// Access:    public 
// Returns:   bool
// Description: Changes the currently loaded user to theUserName.
//				This is one of the main methods you will be using.
// Parameter: SexyString theUserName
//************************************
bool Profile::LoadUser(SexyString theUserName)
{
	SetUserName(theUserName);
	if(mUserName != _S(""))
	{
		std::string aFileName = GetUserFileName(mUserName);

		if(Sexy::FileExists(aFileName))
		{
			return Load(StringToSexyStringFast(aFileName));
		}
	}

	SetUserName(_S(""));
	return false;
}

//************************************
// Method:    SaveUser
// FullName:  Sexy::Profile::SaveUser
// Access:    public 
// Returns:   bool
// Description: Saves the currently loaded user's profile
//				This is one of the main methods you will be using.
//************************************
bool Profile::SaveUser()
{
	if(mUserName != _S(""))
	{
		std::string aFileName = GetUserFileName(mUserName);
		MkDir(GetFileDir(aFileName));

		return Save(StringToSexyStringFast(aFileName));
	}
	return false;
}

//************************************
// Method:    NewUser
// FullName:  Sexy::Profile::NewUser
// Access:    public 
// Returns:   bool
// Description: Creates a new user from the specified user name
//				This is one of the main methods you will be using.
// Parameter: SexyString theUserName
//************************************
bool Profile::NewUser(SexyString theUserName)
{
	SetUserName(theUserName);
	gSexyAppBase->RegistryWriteString("LastProfileName",SexyStringToStringFast(mUserName));
	ResetProfile();
	return SaveUser();
}

//************************************
// Method:    RenameUser
// FullName:  Sexy::Profile::RenameUser
// Access:    public 
// Returns:   bool
// Description: Rename the userprofile-file
//				This is one of the main methods you will be using.
//				(caller: maybe remember to rename the scores of the user)
// Parameter: SexyString theNewUserName
//************************************
bool Profile::RenameUser(SexyString theNewUserName)
{
	if (theNewUserName != _S(""))
	{
		SexyString OldUserName = mUserName;  // remember old username

		if (SetUserName(theNewUserName) == true)  // sets mUserName to theNewUserName if successful
		{
			SexyString OldFileName = GetUserFileName(OldUserName);
			SexyString NewFileName = GetUserFileName(mUserName);

			rename(OldFileName.c_str(), NewFileName.c_str()); 

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

//************************************
// Method:    DeleteUser
// FullName:  Sexy::Profile::DeleteUser
// Access:    public 
// Returns:   bool
// Description: Delete the profile-file
//				This is one of the main methods you will be using.
// 				(caller: maybe remember to delete the scores of the user)
// Parameter: SexyString theUserName
//************************************
bool Profile::DeleteUser(SexyString theUserName)
{
	if (theUserName != _S(""))
	{
		SexyString aFileName = GetUserFileName(theUserName);

		remove(aFileName.c_str());

		return true;
	}
	return false;
}

//************************************
// Method:    SetUserName
// FullName:  Sexy::Profile::SetUserName
// Access:    public 
// Returns:   bool
// Description: internally used method to validate the user name
//				this is primarily because Windows has file name 
//				restrictions!
// Parameter: SexyString theUserName
//************************************
bool Profile::SetUserName(SexyString theUserName)
{
	// don´t allow the following chars in a username
	for (unsigned int i = 0; i < theUserName.length(); i++)
	{
		if (theUserName[i] == '\\' || theUserName[i] == '/' || 
		theUserName[i] == ':'  || theUserName[i] == '?' ||
		theUserName[i] == '"'  || theUserName[i] == '<' ||   
		theUserName[i] == '>'  || theUserName[i] == '|')
		{
			// bad User Name
			return false;
		}
	}

	mUserName = theUserName;
	// write registry key if the username was entered in a dialog
	gSexyAppBase->RegistryWriteString("LastProfileName", mUserName);
	return true;
}

//************************************
// Method:    ResetProfile
// FullName:  Sexy::Profile::ResetProfile
// Access:    public 
// Returns:   void
// Description: Use this to reset the user to 0!
//************************************
void Profile::ResetProfile()
{
	mFloatMap.clear();
	mIntegerMap.clear();
	mStringMap.clear();
	mBoolMap.clear();
}

//************************************
// Method:    SetBoolValue
// FullName:  Sexy::Profile::SetBoolValue
// Access:    public 
// Returns:   void
// Description: Sets the specified Variable to the Value
// Parameter: SexyString theValueName
// Parameter: bool theValue
//************************************
void Sexy::Profile::SetBoolValue( SexyString theValueName, bool theValue )
{
	if (mBoolMap.find(theValueName) != mBoolMap.end())
		mBoolMap[theValueName] = theValue;
	else
		mBoolMap.insert(std::pair<SexyString,bool>(theValueName,theValue));
}

//************************************
// Method:    GetBoolValue
// FullName:  Sexy::Profile::GetBoolValue
// Access:    public 
// Returns:   bool
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: SexyString theValueName
// Parameter: bool theDefault
//************************************
bool Sexy::Profile::GetBoolValue( SexyString theValueName, bool theDefault )
{
	if (mBoolMap.find(theValueName) != mBoolMap.end())
		return mBoolMap[theValueName];

	return theDefault;
}

//************************************
// Method:    SetFloatValue
// FullName:  Sexy::Profile::SetFloatValue
// Access:    public 
// Returns:   void
// Description:  Sets the specified Variable to the Value
// Parameter: SexyString theValueName
// Parameter: double theValue
//************************************
void Sexy::Profile::SetFloatValue( SexyString theValueName, double theValue )
{
	if (mFloatMap.find(theValueName) != mFloatMap.end())
		mFloatMap[theValueName] = theValue;
	else
		mFloatMap.insert(std::pair<SexyString,double>(theValueName,theValue));
}

//************************************
// Method:    GetFloatValue
// FullName:  Sexy::Profile::GetFloatValue
// Access:    public 
// Returns:   double
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: SexyString theValueName
// Parameter: double theDefault
//************************************
double Sexy::Profile::GetFloatValue( SexyString theValueName, double theDefault )
{
	if (mFloatMap.find(theValueName) != mFloatMap.end())
		return mFloatMap[theValueName];

	return theDefault;
}

//************************************
// Method:    SetStringValue
// FullName:  Sexy::Profile::SetStringValue
// Access:    public 
// Returns:   void
// Description:  Sets the specified Variable to the Value
// Parameter: SexyString theValueName
// Parameter: SexyString theValue
//************************************
void Sexy::Profile::SetStringValue( SexyString theValueName, SexyString theValue )
{
	if (mStringMap.find(theValueName) != mStringMap.end())
		mStringMap[theValueName] = theValue;
	else
		mStringMap.insert(std::pair<SexyString,SexyString>(theValueName,theValue));
}

//************************************
// Method:    GetStringValue
// FullName:  Sexy::Profile::GetStringValue
// Access:    public 
// Returns:   SexyString
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: SexyString theValueName
// Parameter: SexyString theDefault
//************************************
SexyString Sexy::Profile::GetStringValue( SexyString theValueName, SexyString theDefault )
{
	if (mStringMap.find(theValueName) != mStringMap.end())
		return mStringMap[theValueName];

	return theDefault;
}

//************************************
// Method:      EraseStateSaves
// FullName:    Sexy::Profile::EraseStateSaves
// Access:      virtual public 
// Returns:     void
// Parameter:   SexyString theUserName
// Description: To help manage game states, states are saved in a user
//				sub-folder. To delete all the states, just delete the folder.
//************************************
void Sexy::Profile::EraseStateSaves(SexyString theUserName)
{
	if(theUserName == _S(""))
	{
		std::string aUserName =  SexyStringToStringFast(mUserName);
		std::string aStatePath = StrFormat("%susers\\%s\\", GetAppDataFolder().c_str(), aUserName.c_str());

		Deltree(aStatePath);
	}
	else
	{
		std::string aUserName =  SexyStringToStringFast(theUserName);
		std::string aStatePath = StrFormat("%susers\\%s\\", GetAppDataFolder().c_str(), aUserName.c_str());

		Deltree(aStatePath);
	}
}