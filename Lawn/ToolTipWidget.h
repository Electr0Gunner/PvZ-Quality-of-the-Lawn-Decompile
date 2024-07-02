#ifndef __TOOLTIPWIDGET_H__ 
#define __TOOLTIPWIDGET_H__

#include "../SexyAppFramework/Common.h"
namespace Sexy
{
    class Graphics;
}

class ToolTipWidget
{
public:
    SexyString			mTitle;                 
    SexyString			mLabel;                 
    SexyString			mWarningText;           
    int                 mX;                     
    int                 mY;                     
    int                 mWidth;                 
    int                 mHeight;                
    bool                mVisible;               
    bool                mCenter;                
    int                 mMinLeft;               
    int                 mMaxBottom;             
    int                 mGetsLinesWidth;        
    int                 mWarningFlashCounter;   

public:
    ToolTipWidget();

    void                Draw(Sexy::Graphics* g);
    void                SetLabel(const SexyString& theLabel);
    void                SetTitle(const SexyString& theTitle);
    void                SetWarningText(const SexyString& theWarningText);
    void                CalculateSize();
    void                GetLines(std::vector<SexyString>& theLines);
    inline void         FlashWarning() { mWarningFlashCounter = 70; }
    inline void         Update() { if (mWarningFlashCounter > 0) mWarningFlashCounter--; }
    inline void         SetPosition(int theX, int theY) { mX = theX; mY = theY; }
};

#endif