#pragma once
#include "cocos2d.h"
#include <string>
#include <ui\CocosGUI.h>
#include <map>
#include <SimpleAudioEngine.h>

USING_NS_CC;
using namespace CocosDenshion;

class ResourceManager 
{
public:
	ResourceManager ();
	~ResourceManager ();
	static ResourceManager* GetInstance();
	void Init(const std::string path);
	void Load(std::string filename);
	Sprite* GetSpriteById(int id);
	std::string GetSplistById(int id);
	ui::Button* GetButtonById(int id);
	Label* GetLabelById(int id);
	TMXTiledMap* GetTitleMapById(int id);
	SimpleAudioEngine* GetAudioById(int id);
private:
	static ResourceManager* s_instance;
	std::string m_dadaFolderPath;
	std::map <int, Sprite*> m_sprites;
	std::map <int, std::string> m_splist;
	std::map <int, ui::Button*> m_buttons;
	std::map <int, Label*> m_labels;
	std::map <int, TMXTiledMap*> m_title;
	std::map <int, SimpleAudioEngine*> m_audio;
};


