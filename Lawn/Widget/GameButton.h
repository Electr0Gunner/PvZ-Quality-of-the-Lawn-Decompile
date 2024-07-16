#ifndef __GAMEBUTTON_H__
#define __GAMEBUTTON_H__

#include "../../SexyAppFramework/SexyVector.h"
#include "../../SexyAppFramework/DialogButton.h"

using namespace std;
using namespace Sexy;

class LawnApp;
class GameButton
{
public:
	enum
	{
		BUTTON_LABEL_LEFT = -1,
		BUTTON_LABEL_CENTER = 0,
		BUTTON_LABEL_RIGHT = 1
	};
	enum
	{
		COLOR_LABEL = 0,
		COLOR_LABEL_HILITE = 1,
		COLOR_DARK_OUTLINE = 2,
		COLOR_LIGHT_OUTLINE = 3,
		COLOR_MEDIUM_OUTLINE = 4,
		COLOR_BKG = 5,
		NUM_COLORS = 6
	};

public:
	LawnApp*				mApp;							
	Widget*					mParentWidget;					
	int						mX;								
	int						mY;								
	int						mWidth;							
	int						mHeight;						
	bool					mIsOver;						
	bool					mIsDown;						
	bool					mDisabled;						
	Color					mColors[6];						
	int						mId;							
	SexyString				mLabel;							
	int						mLabelJustify;					
	Font*					mFont;							
	Image*					mButtonImage;					
	Image*					mOverImage;						
	Image*					mDownImage;						
	Image*					mDisabledImage;					
	Image*					mOverOverlayImage;				
	Rect					mNormalRect;					
	Rect					mOverRect;						
	Rect					mDownRect;						
	Rect					mDisabledRect;					
	bool					mInverted;						
	bool					mBtnNoDraw;						
	bool					mFrameNoDraw;					
	double					mOverAlpha;						
	double					mOverAlphaSpeed;				
	double					mOverAlphaFadeInSpeed;			
	bool					mDrawStoneButton;				
	int						mTextOffsetX;					
	int						mTextOffsetY;					
	int						mButtonOffsetX;					
	int						mButtonOffsetY;					

public:
	GameButton(int theId);
	~GameButton();

	static /*inline*/ bool	HaveButtonImage(Image* theImage, Rect& theRect);
	void					DrawButtonImage(Graphics* g, Image* theImage, Rect& theRect, int theX, int theY);
	/*inline*/ void			SetFont(Font* theFont);
	/*inline*/ bool			IsButtonDown();
	void					Draw(Graphics* g);
	/*inline*/ void			SetDisabled(bool theDisabled);
	/*inline*/ bool			IsMouseOver();
	void					Update();
	/*inline*/ void			Resize(int theX, int theY, int theWidth, int theHeight);
	/*inline*/ void			SetLabel(const SexyString& theLabel);
};

class LawnStoneButton : public DialogButton
{
public:
	LawnStoneButton(Image* theComponentImage, int theId, ButtonListener* theListener) : DialogButton(theComponentImage, theId, theListener) { }

	virtual void			Draw(Graphics* g);
	/*inline*/ void			SetLabel(const SexyString& theLabel);
};

class NewLawnButton : public DialogButton
{
public:
    Font*					mHiliteFont;            
    int						mTextDownOffsetX;       
    int						mTextDownOffsetY;       
	int						mButtonOffsetX;			
	int						mButtonOffsetY;			
	bool					mUsePolygonShape;		
	SexyVector2				mPolygonShape[4];		

public:
    NewLawnButton(Image* theComponentImage, int theId, ButtonListener* theListener);
	virtual ~NewLawnButton();
	
    virtual void			Draw(Graphics* g);
	virtual bool			IsPointVisible(int x, int y);
    void					SetLabel(const SexyString& theLabel);
	void					SetButtonOffset(int theNewX, int theNewY);
};

LawnStoneButton*			MakeButton(int theId, ButtonListener* theListener, const SexyString& theText);
NewLawnButton*				MakeNewButton(int theId, ButtonListener* theListener, const SexyString& theText, Font* theFont, Image* theImageNormal, Image* theImageOver, Image* theImageDown);
void						DrawStoneButton(Graphics* g, int x, int y, int theWidth, int theHeight, bool isDown, bool isHighLighted, const SexyString& theLabel, int theBrightness = 255);

#endif
