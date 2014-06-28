#include "LoadingScene.h"
#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//МгдиДњТы
	auto *pLogin = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("./loading/planned.json"));
	this->addChild(pLogin);

	return true;
}

void LoadingScene::loading()
{

}
