#pragma once

//-----------------------------------------------------------------
// Expatpp Defines and Include Files
//-----------------------------------------------------------------

#ifdef _UNICODE
#define XML_UNICODE_WCHAR_T
#endif

#include "expatpp.h"
#include <vector>

class GameSettings;
class GuiSettings;
class ComponentInfo;
class CollisionItemInfo;
class LevelData;
class LevelSettings;
//-----------------------------------------------------------------
// Extra Include Files
//-----------------------------------------------------------------

//#include "GameDefines.h"

/**
* Parses an int from text input.
* @param value a tstring containing an integer.
* @return the parsed integer.
*/
int ParseInt(const tstring& value);
/**
* Parses a float from text input.
* @param value a tstring containing a float.
*/ 
float ParseFloat(const tstring& value);
/**
* Parses a boolean from text input. "true" or "TRUE" or 
* any combination of upper and lower case is considered as true,
* the rest is false.
*/ 
bool ParseBoolean(const tstring& value);

//-----------------------------------------------------------------
// XMLParser Class																
//-----------------------------------------------------------------
class XMLParser : public expatpp {
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	XMLParser(GameSettings* mysettings);

	//---------------------------
	// Inherited Methods to Overload
	//---------------------------
	virtual void startElement(const XML_Char *name, const XML_Char **atts);
	virtual void endElement(const XML_Char* name);
	virtual void charData(const XML_Char *s, int len);
	


private:
	// -------------------------
	// Datamembers
	// -------------------------
	GameSettings* m_pGameSettings;
	


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	XMLParser(const XMLParser& t);
	XMLParser& operator=(const XMLParser& t);
};

class XMLParserGUI : public expatpp {
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	XMLParserGUI(GuiSettings* mysettings);

	//---------------------------
	// Inherited Methods to Overload
	//---------------------------
	virtual void startElement(const XML_Char *name, const XML_Char **atts);
	virtual void endElement(const XML_Char* name);
	virtual void charData(const XML_Char *s, int len);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	GuiSettings* m_pGuiSettings;
	ComponentInfo* m_pCurrentComponent;
	CollisionItemInfo* m_pCurrentCollisionItem;


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	XMLParserGUI(const XMLParserGUI& t);
	XMLParserGUI& operator=(const XMLParserGUI& t);
};

class XMLParserLevel : public expatpp {
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	XMLParserLevel(LevelSettings* mysettings);

	//---------------------------
	// Inherited Methods to Overload
	//---------------------------
	virtual void startElement(const XML_Char *name, const XML_Char **atts);
	virtual void endElement(const XML_Char* name);
	virtual void charData(const XML_Char *s, int len);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	LevelSettings* m_pLevelSettings;
	LevelData* m_pCurrentLevel;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	XMLParserLevel(const XMLParserLevel& t);
	XMLParserLevel& operator=(const XMLParserLevel& t);
};