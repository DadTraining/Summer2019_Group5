#include "ResourceManager.h"
#include <fstream>

ResourceManager *ResourceManager::s_instance = nullptr;
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ResourceManager();
	}
	return s_instance;
}

void ResourceManager::Init(const std::string path)
{
	this->m_dadaFolderPath = "res";
	std::string filename = m_dadaFolderPath + "/_";
	this->Load(filename);
}

void ResourceManager::Load(std::string filename)
{
	int id, lenght;
	std::string igone, path_normal, path_pressed;

	if (FileUtils::getInstance()->isFileExist(filename))
	{
		auto data = FileUtils::getInstance()->getStringFromFile(filename);
		std::istringstream infile(data.c_str());

		//load Sprite
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			Sprite* sprite = Sprite::create(path_normal);
			sprite->retain();
			m_sprites.insert(std::pair<int ,Sprite*>(id, sprite));
		}

		//load Splist
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			std::string splist = path_normal;
			//splist->retain();
			m_splist.insert(std::pair<int, std::string>(id, splist));
		}

		//load button
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			path_pressed.replace(0, 2, this->m_dadaFolderPath);
			ui::Button* button = ui::Button::create(path_normal, path_pressed);
			button->retain();
			m_buttons.insert(std::pair<int, ui::Button*>(id, button));
		}

		//load label
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			Label* label = Label::createWithTTF("", path_normal, 20);
			label->retain();
			m_labels.insert(std::pair<int, Label*>(id, label));
		}

		//load titleMap
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			TMXTiledMap* title = TMXTiledMap::create(path_normal);
			title->retain();
			m_title.insert(std::pair<int, TMXTiledMap*>(id, title));
		}

		//load Audio
		infile >> igone;
		infile >> lenght;

		for (int i = 0; i < lenght; i++)
		{
			infile >> igone;
			infile >> id;
			infile >> igone;
			infile >> path_normal;

			path_normal.replace(0, 2, this->m_dadaFolderPath);
			/*char *str = new char[path_normal.length + 1];
			for (int i0; i < path_normal.length; i++)
			{
				str[i] = (char)(LPCTSTR)path_normal[i];
			}
			str[path_normal.length] = '/0';*/
			//const  char* str_pattern = path_normal.c_str;
			//char* str = new char[strlen(str_pattern) + 1];
			//strcpy(str, str_pattern);
			char *c = new char[path_normal.size() + 1];
			std::copy(path_normal.begin(), path_normal.end(), c);
			c[path_normal.size()] = '\0';
			SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
			audio->preloadBackgroundMusic(c);

			m_audio.insert(std::pair<int, SimpleAudioEngine*>(id, audio));
		}
	}
}

Sprite* ResourceManager::GetSpriteById(int id)
{
	std::map<int, Sprite*>::iterator it = this->m_sprites.find(id);
	return it->second;
}

std::string ResourceManager::GetSplistById(int id)
{
	std::map<int, std::string>::iterator it = this->m_splist.find(id);
	return it->second;
}

ui::Button* ResourceManager::GetButtonById(int id)
{
	std::map<int, ui::Button*>::iterator it = this->m_buttons.find(id);
	return it->second;
}

Label* ResourceManager::GetLabelById(int id)
{
	std::map<int, Label*>::iterator it = this->m_labels.find(id);
	return it->second;
}

SimpleAudioEngine* ResourceManager::GetAudioById(int id)
{
	std::map<int, SimpleAudioEngine*>::iterator it = this->m_audio.find(id);
	return it->second;
}

TMXTiledMap* ResourceManager::GetTitleMapById(int id)
{
	std::map<int, TMXTiledMap*>::iterator it = this->m_title.find(id);
	return it->second;
}