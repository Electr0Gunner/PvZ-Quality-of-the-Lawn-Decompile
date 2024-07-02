#include "TodDebug.h"
#include "TodCommon.h"
#include "TodStringFile.h"
#include "../PakLib/PakInterface.h"
#include "../SexyAppFramework/Font.h"

int gTodStringFormatCount;               
TodStringListFormat* gTodStringFormats;  

int gLawnStringFormatCount = 12;
TodStringListFormat gLawnStringFormats[14] = {    
	{ "NORMAL",           nullptr,    Color(40,   50,     90,     255),       0,      0U },
	{ "FLAVOR",           nullptr,    Color(143,  67,     27,     255),       0,      1U },
	{ "KEYWORD",          nullptr,    Color(143,  67,     27,     255),       0,      0U },
	{ "NOCTURNAL",        nullptr,    Color(136,  50,     170,    255),       0,      0U },
	{ "AQUATIC",          nullptr,    Color(11,   161,    219,    255),       0,      0U },
	{ "STAT",             nullptr,    Color(204,  36,     29,     255),       0,      0U },
	{ "METAL",            nullptr,    Color(204,  36,     29,     255),       0,      2U },
	{ "KEYMETAL",         nullptr,    Color(143,  67,     27,     255),       0,      2U },
	{ "SHORTLINE",        nullptr,    Color(0,    0,      0,      0),         -9,     0U },
	{ "EXTRASHORTLINE",   nullptr,    Color(0,    0,      0,      0),         -14,    0U },
	{ "CREDITS1",         nullptr,    Color(0,    0,      0,      0),         3,      0U },
	{ "CREDITS2",         nullptr,    Color(0,    0,      0,      0),         2,      0U },
	{ "NORMAL",           nullptr,    Color(40,   50,     90,     255),       0,      0U },
	{ "KEYWORD",          nullptr,    Color(143,  67,     27,     255),       0,      0U }
};

TodStringListFormat::TodStringListFormat()
{
	mFormatName = "";
	mNewFont = nullptr;
	mLineSpacingOffset = 0;
	mFormatFlags = 0U;
}

TodStringListFormat::TodStringListFormat(const char* theFormatName, Font** theFont, const Color& theColor, int theLineSpacingOffset, unsigned int theFormatFlags) : 
	mFormatName(theFormatName), mNewFont(theFont), mNewColor(theColor), mLineSpacingOffset(theLineSpacingOffset), mFormatFlags(theFormatFlags)
{ 
}

void TodStringListSetColors(TodStringListFormat* theFormats, int theCount)
{
	gTodStringFormats = theFormats;
	gTodStringFormatCount = theCount;
}

bool TodStringListReadName(const char*& thePtr, std::string& theName)
{
	const char* aNameStart = strchr(thePtr, '[');
	if (aNameStart == nullptr)  
	{
		if (strspn(thePtr, " \n\r\t") != strlen(thePtr))  
		{
			TodTrace("Failed to find string name");
			return false;
		}

		theName = "";
		return true;
	}
	else
	{
		const char* aNameEnd = strchr(aNameStart + 1, ']');
		if (aNameEnd == nullptr)  
		{
			TodTrace("Failed to find ']'");
			return false;
		}

		int aCount = aNameEnd - aNameStart - 1;
		theName = Sexy::Trim(string(aNameStart + 1, aCount));  
		if (theName.size() == 0)
		{
			TodTrace("Name Too Short");
			return false;
		}

		thePtr += aCount + 2;  
		return true;
	}
}

void TodStringRemoveReturnChars(std::string& theString)
{
	for (int i = 0; i < theString.size(); )
	{
		if (theString[i] == '\r')
			theString.replace(i, 1, "", 0);  
		else
			i++;
	}
}

bool TodStringListReadValue(const char*& thePtr, std::string& theValue)
{
	const char* aValueEnd = strchr(thePtr, '[');
	int aLen = aValueEnd ? aValueEnd - thePtr : strlen(thePtr);
	theValue = Sexy::Trim(string(thePtr, aLen));  
	TodStringRemoveReturnChars(theValue);  
	thePtr += aLen;  
	return true;
}

bool TodStringListReadItems(const char* theFileText)
{
	const char* aPtr = theFileText;
	std::string aName;
	std::string aValue;

	for (;;)
	{
		if (!TodStringListReadName(aPtr, aName))  
			return false;
		if (aName.size() == 0)  
			return true;
		if (!TodStringListReadValue(aPtr, aValue))  
			return false;

		std::string aNameUpper = Sexy::StringToUpper(aName);
		gSexyAppBase->SetString(aNameUpper, Sexy::StringToWString(aValue));
	}
}

bool TodStringListReadFile(const char* theFileName)
{
	PFILE* pFile = p_fopen(theFileName, "rb");
	if (pFile == nullptr)
	{
		TodTrace("Failed to open '%s'", theFileName);
		return false;
	}

	p_fseek(pFile, 0, SEEK_END);  
	int aSize = p_ftell(pFile);  
	p_fseek(pFile, 0, SEEK_SET);  
	char* aFileText = new char[aSize + 1];
	bool aSuccess = true;
	if (p_fread(aFileText, sizeof(char), aSize, pFile) <= 0)  
	{
		TodTrace("Failed to read '%s'", theFileName);
		aSuccess = false;
	}
	aFileText[aSize] = '\0';
	if (aSuccess)
	{
		aSuccess = TodStringListReadItems(aFileText);
	}
	p_fclose(pFile);  
	delete[] aFileText;

	return aSuccess;
}

void TodStringListLoad(const char* theFileName)
{
	if (!TodStringListReadFile(theFileName))
		TodErrorMessageBox(Sexy::StrFormat("Failed to load string list file '%s'", theFileName).c_str(), "Error");
}

SexyString TodStringListFind(const SexyString& theName)
{
	std::string aNameString = Sexy::SexyStringToString(theName);
	StringWStringMap::iterator anItr = gSexyAppBase->mStringProperties.find(aNameString);
	if (anItr != gSexyAppBase->mStringProperties.end())
	{
		return Sexy::WStringToSexyString(anItr->second);
	}
	else
	{
		return Sexy::StrFormat(_S("<Missing %s>"), theName.c_str());
	}
}

SexyString TodStringTranslate(const SexyString& theString)
{
	if (theString.size() >= 3 && theString[0] == '[')
	{
		SexyString aName = theString.substr(1, theString.size() - 2);  
		return TodStringListFind(aName);
	}
	return theString;
}

SexyString TodStringTranslate(const SexyChar* theString)
{
	if (theString != nullptr)
	{
		int aLen = strlen(theString);
		if (aLen >= 3 && theString[0] == '[')
		{
			SexyString aName(theString, 1, aLen - 2);  
			return TodStringListFind(aName);
		}
		else
			return theString;
	}
	else
		return "";
}

bool TodStringListExists(const SexyString& theString)
{
	if (theString.size() >= 3 && theString[0] == '[')
	{
		SexyString aName = theString.substr(1, theString.size() - 2);  
		return gSexyAppBase->mStringProperties.find(aName) != gSexyAppBase->mStringProperties.end();
	}
	return false;
}

void TodWriteStringSetFormat(const char* theFormat, TodStringListFormat& theCurrentFormat)
{
	for (int i = 0; i < gTodStringFormatCount; i++)
	{
		const TodStringListFormat& aFormat = gTodStringFormats[i];
		if (strncmp(theFormat, aFormat.mFormatName, strlen(aFormat.mFormatName)) == 0)
		{
			if (aFormat.mNewFont != nullptr)
				theCurrentFormat.mNewFont = aFormat.mNewFont;
			if (aFormat.mNewColor != Color(0, 0, 0, 0))
				theCurrentFormat.mNewColor = aFormat.mNewColor;
			theCurrentFormat.mLineSpacingOffset = aFormat.mLineSpacingOffset;
			theCurrentFormat.mFormatFlags = aFormat.mFormatFlags;
			return;
		}
	}
}

bool CharIsSpaceInFormat(char theChar, const TodStringListFormat& theCurrentFormat)
{
	return theChar == ' ' || (TestBit(theCurrentFormat.mFormatFlags, TodStringFormatFlag::TOD_FORMAT_IGNORE_NEWLINES) && theChar == '\n');
}

int TodWriteString(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength)
{
	Font* aFont = *theCurrentFormat.mNewFont;
	if (drawString)  
	{
		int aSpareX = theWidth - TodWriteString(g, theString, theX, theY, theCurrentFormat, theWidth, DrawStringJustification::DS_ALIGN_LEFT, false, theOffset, theLength);
		switch (theJustification)  
		{
		case DrawStringJustification::DS_ALIGN_RIGHT:
		case DrawStringJustification::DS_ALIGN_RIGHT_VERTICAL_MIDDLE:
			theX += aSpareX;
			break;
		case DrawStringJustification::DS_ALIGN_CENTER:
		case DrawStringJustification::DS_ALIGN_CENTER_VERTICAL_MIDDLE:
			theX += aSpareX / 2;
			break;
		}
	}

	if (theLength < 0 || theOffset + theLength > theString.size())
		theLength = theString.size();
	else
		theLength = theOffset + theLength;  

	SexyString aString;
	int aXOffset = 0;
	bool aPrevCharWasSpace = false;
	for (int i = theOffset; i < theLength; i++)
	{
		if (theString[i] == '{')
		{
			const char* aFormatStart = theString.c_str() + i;
			const char* aFormatEnd = strchr(aFormatStart + 1, '}');
			if (aFormatEnd != nullptr)  
			{
				i += aFormatEnd - aFormatStart;  
				if (drawString)  
					aFont->DrawString(g, theX + aXOffset, theY, aString, theCurrentFormat.mNewColor, g->mClipRect);  
				
				aXOffset += aFont->StringWidth(aString);  
				aString.assign("");  
				TodWriteStringSetFormat(aFormatStart + 1, theCurrentFormat);  
				Font* aFont = *theCurrentFormat.mNewFont;
			}
		}
		else
		{
			if (TestBit(theCurrentFormat.mFormatFlags, TodStringFormatFlag::TOD_FORMAT_IGNORE_NEWLINES))  
			{
				if (CharIsSpaceInFormat(theString[i], theCurrentFormat))  
				{
					if (!aPrevCharWasSpace)  
						aString.append(1, ' ');  
					continue;
				}
				else
					aPrevCharWasSpace = false;  
			}

			aString.append(1, theString[i]);
		}
	}

	if (drawString)  
		aFont->DrawString(g, theX + aXOffset, theY, aString, theCurrentFormat.mNewColor, g->mClipRect);  
	return aXOffset + aFont->StringWidth(aString);
}

int TodWriteWordWrappedHelper(Graphics* g, const SexyString& theString, int theX, int theY, TodStringListFormat& theCurrentFormat, int theWidth, DrawStringJustification theJustification, bool drawString, int theOffset, int theLength, int theMaxChars)
{
	if (theOffset + theLength > theMaxChars)  
	{
		theLength = theMaxChars - theOffset;  
		if (theLength <= 0)
			return -1;
	}
	return TodWriteString(g, theString, theX, theY, theCurrentFormat, theWidth, theJustification, drawString, theOffset, theLength);
}

int TodDrawStringWrappedHelper(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification, bool drawString)
{
	int theMaxChars = theText.size();
	TodStringListFormat aCurrentFormat;
	aCurrentFormat.mNewFont = &theFont;
	aCurrentFormat.mNewColor = theColor;
	aCurrentFormat.mFormatName = "";
	aCurrentFormat.mLineSpacingOffset = 0;
	aCurrentFormat.mFormatFlags = 0U;

	int aYOffset = theFont->GetAscent() - theFont->GetAscentPadding();
	int aLineSpacing = theFont->GetLineSpacing() + aCurrentFormat.mLineSpacingOffset;
	SexyString aCurString;
	int aLineFeedPos = 0;
	int aCurPos = 0;
	int aCurWidth = 0;
	SexyChar aCurChar = '\0';
	SexyChar aPrevChar = '\0';
	int aSpacePos = -1;
	int aMaxWidth = 0;
	while (aCurPos < theText.size())
	{
		aCurChar = theText[aCurPos];
		if (aCurChar == '{')  
		{
			const char* aFmtStart = theText.c_str() + aCurPos;
			const char* aFormat = aFmtStart + 1;
			const char* aFmtEnd = strchr(aFormat, '}');
			if (aFmtEnd != nullptr)  
			{
				aCurPos += aFmtEnd - aFmtStart + 1;  
				int aOldAscentOffset = theFont->GetAscent() - theFont->GetAscentPadding();
				TodWriteStringSetFormat(aFormat, aCurrentFormat);  
				int aNewAscentOffset = (*aCurrentFormat.mNewFont)->GetAscent() - (*aCurrentFormat.mNewFont)->GetAscentPadding();
				aLineSpacing = (*aCurrentFormat.mNewFont)->GetLineSpacing() + aCurrentFormat.mLineSpacingOffset;
				aYOffset += aNewAscentOffset - aOldAscentOffset;
				continue;
			}
		}
		else if (CharIsSpaceInFormat(aCurChar, aCurrentFormat))
		{
			aSpacePos = aCurPos;
			aCurChar = ' ';
		}
		else if (aCurChar == '\n')
		{
			aSpacePos = aCurPos;
			aCurWidth = theRect.mWidth + 1;
			aCurPos++;
		}

		aCurWidth += (*aCurrentFormat.mNewFont)->CharWidthKern(aCurChar, aPrevChar);  
		aPrevChar = aCurChar;
		if (aCurWidth > theRect.mWidth)  
		{
			int aLineWidth;
			if (aSpacePos != -1)  
			{
				int aCurY = (int)g->mTransY + theRect.mY + aYOffset;
				if (aCurY >= g->mClipRect.mY && aCurY <= g->mClipRect.mY + g->mClipRect.mHeight + aLineSpacing)  
				{
					TodWriteWordWrappedHelper(
						g, 
						theText, 
						theRect.mX, 
						theRect.mY + aYOffset,
						aCurrentFormat, 
						theRect.mWidth, 
						theJustification, 
						drawString, 
						aLineFeedPos, 
						aSpacePos - aLineFeedPos, 
						theMaxChars
					);  
				}

				aLineWidth = aCurWidth;
				if (aLineWidth < 0)  
					break;

				aCurPos = aSpacePos + 1;  
				if (aCurChar != '\n')
					while (aCurPos < theText.size() && CharIsSpaceInFormat(theText[aCurPos], aCurrentFormat))
						aCurPos++;  
			}
			else
			{
				if (aCurPos < aLineFeedPos + 1)
					aCurPos++;  

				aLineWidth = TodWriteWordWrappedHelper(
					g,
					theText,
					theRect.mX,
					theRect.mY + aYOffset,
					aCurrentFormat, 
					theRect.mWidth, 
					theJustification, 
					drawString, 
					aLineFeedPos, 
					aCurPos - aLineFeedPos, 
					theMaxChars
				);  
				if (aLineWidth < 0)  
					break;
			}

			if (aLineWidth > aMaxWidth)
				aMaxWidth = aLineWidth;  
			aYOffset += aLineSpacing;
			aLineFeedPos = aCurPos;  
			aSpacePos = -1;
			aCurWidth = 0;
			aPrevChar = '\0';
		}
		else  
		{
			aCurPos++;  
		}
	}

	if (aLineFeedPos < theText.size())
	{
		int aLastLineLength = TodWriteWordWrappedHelper(
			g,
			theText,
			theRect.mX,
			theRect.mY + aYOffset,
			aCurrentFormat,
			theRect.mWidth,
			theJustification,
			drawString,
			aLineFeedPos, 
			theText.size() - aLineFeedPos, 
			theMaxChars
		);  
		if (aLastLineLength >= 0)
			aYOffset += aLineSpacing;
	}
	else
		aYOffset += aLineSpacing;

	return (*aCurrentFormat.mNewFont)->GetDescent() + aYOffset - aLineSpacing;
}

void TodDrawStringWrapped(Graphics* g, const SexyString& theText, const Rect& theRect, Font* theFont, const Color& theColor, DrawStringJustification theJustification)
{
	SexyString aTextFinal = TodStringTranslate(theText);
	Rect aRectTodUse = theRect;
	if (theJustification == DrawStringJustification::DS_ALIGN_LEFT_VERTICAL_MIDDLE ||
		theJustification == DrawStringJustification::DS_ALIGN_RIGHT_VERTICAL_MIDDLE ||
		theJustification == DrawStringJustification::DS_ALIGN_CENTER_VERTICAL_MIDDLE)  
	{
		aRectTodUse.mY += (aRectTodUse.mHeight - TodDrawStringWrappedHelper(g, aTextFinal, aRectTodUse, theFont, theColor, theJustification, false)) / 2;
	}
	TodDrawStringWrappedHelper(g, aTextFinal, aRectTodUse, theFont, theColor, theJustification, true);
}
