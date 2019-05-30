//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: SpriteSheetSetting
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef SPRITESHEETSETTING_H_INCLUDED
#define SPRITESHEETSETTING_H_INCLUDED

class SpriteSheetSetting {
public:
	SpriteSheetSetting();
	virtual ~SpriteSheetSetting();

	float GetHeight() const;
	float GetWidth() const;
	float GetMidX() const;
	float GetMidY() const;
	const tstring& GetType() const;

	void SetRowHeight(float rowheight);
	void SetRowWidth(float rowwidth);
	void SetMidX(float midx);
	void SetMidY(float midy);
	void SetType(tstring type);

private:

	float			m_fRowHeight;
	float			m_fRowWidth;
	float			m_fMidX;
	float			m_fMidY;
	tstring			m_sType;

	SpriteSheetSetting(const SpriteSheetSetting& t);
	SpriteSheetSetting& operator=(const SpriteSheetSetting& t);
	

};

#endif