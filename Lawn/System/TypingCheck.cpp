#include "TypingCheck.h"
using namespace Sexy;

TypingCheck::TypingCheck(const std::string& thePhrase)
{
	SetPhrase(thePhrase);
}

void TypingCheck::SetPhrase(const std::string& thePhrase)
{
	for (int i = 0; i < thePhrase.size(); i++)
		AddChar(thePhrase[i]);
}

void TypingCheck::AddKeyCode(Sexy::KeyCode theKeyCode)
{
	mPhrase.append(1, (char)theKeyCode);
}

void TypingCheck::AddChar(char theChar)
{
	theChar = (char)tolower(theChar);
	std::string aCharString(&theChar);
	AddKeyCode(GetKeyCodeFromName(aCharString));
}

bool TypingCheck::Check()
{
	if (mRecentTyping.compare(mPhrase) == 0)
	{
		mRecentTyping.clear();
		return true;
	}
	return false;
}

bool TypingCheck::Check(Sexy::KeyCode theKeyCode)
{
	mRecentTyping.append(1, (char)theKeyCode);
	int aLength = mPhrase.size();
	if (aLength == 0)
		return false;

	if (mRecentTyping.size() > aLength)
		mRecentTyping = mRecentTyping.substr(1, aLength);
	
	return Check();
}
