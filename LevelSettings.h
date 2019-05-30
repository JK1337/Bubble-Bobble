//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelSettings
//							  Date: 27/7/2009
//******************************************************************************************

#ifndef LEVELSETTINGS_H_INCLUDED
#define LEVELSETTINGS_H_INCLUDED

class LevelData;
#include <vector>

class LevelSettings {
public:
	LevelSettings();
	virtual ~LevelSettings();
	void AddLevelData(LevelData* data);
	const LevelData* GetLevelData(UINT levelindex) const;
	const LevelData* LevelSettings::GetLastMAde() const;
private:
	vector<LevelData*> m_vLevelData;
	LevelSettings(const LevelSettings& t);
	LevelSettings& operator=(const LevelSettings& t);
};

#endif