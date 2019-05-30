//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Toolbar
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef TOOLBAR_H_INCLUDED
#define TOOLBAR_H_INCLUDED

class GuiSettings;
class ToolComponent;
class LevelEditor;
#include <vector>
#include "BaseEntity.h"
class Toolbar : public BaseEntity{
public:
	Toolbar(GuiSettings* settings, double width, double height,	LevelEditor* editor);
	virtual ~Toolbar();
	virtual void Init();
	virtual bool Update(float dTime);
	virtual bool Draw();
	const string& GetSelectedCategoryName() const;
	void SetSelected(ToolComponent* newselected);
private:
	GuiSettings* m_pGuiSettings;
	Toolbar(const Toolbar& t);
	Toolbar& operator=(const Toolbar& t);
	Vector2D m_vecPos;
	void CreateComponents();

	LevelEditor* m_pLevelEditor;
	std::vector<ToolComponent*> m_vGuiComponents;
	ToolComponent * m_pCurrentSelectedComponent;
};

#endif