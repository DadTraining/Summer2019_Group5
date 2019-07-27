#pragma once
#ifndef _MY_BODY_PARSER_H_
#define _MY_BODY_PARSER_H_
#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"

class MyBodyParser {
	MyBodyParser(){}
	rapidjson::Document doc;
public:
	static MyBodyParser* getInstance();
	bool parseJsonFile(const std::string& pFile);
	bool parse(unsigned char* buffer, long length);
	void clearCache();
	PhysicsBody* bodyFormJson(Node* pNode, const std::string& name, PhysicsMaterial material);
};

#endif //_MY_BODY_PARSER_H_