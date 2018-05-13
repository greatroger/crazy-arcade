#include "WelcomeScene.h"
#include "cocos2d.h"
#include"Client.h"
#include"MyMap.h"
#include"every.h"
#include "extensions\cocos-ext.h"  
#include <process.h>
#include"WaitScene.h"


USING_NS_CC;
WelcomeScene::WelcomeScene()
{
	USING_NS_CC_EXT;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//账号框 设置输入8个字符  
	auto editbox1 = EditBox::create(Size(200, 35), Scale9Sprite::create("button/inputbox.png"));
	editbox1->setAnchorPoint(Point(0, 0));
	editbox1->setPosition(Point(visibleSize.width*0.4, visibleSize.height*0.55));
	editbox1->setPlaceHolder("name:");//占位字符  
	editbox1->setMaxLength(8);
	editbox1->setFontColor(Color3B::WHITE);//设置输入字体的颜色  
	editbox1->setTag(1);
	this->addChild(editbox1, 2);
	//密码框 password  
	auto editbox2 = EditBox::create(Size(200, 35), Scale9Sprite::create("button/inputbox.png"));
	editbox2->setAnchorPoint(Point(0, 0));
	editbox2->setPosition(Point(visibleSize.width*0.4, visibleSize.height*0.4));
	editbox2->setPlaceHolder("IP:");
	editbox2->setPlaceholderFontColor(Color3B::WHITE);//设置占位字体的颜色  
	editbox2->setFontColor(Color3B::WHITE);
	editbox2->setInputMode(EditBox::InputMode::NUMERIC);//设置输入类型 数字及特殊符号输入  
	//editbox2->setInputFlag(EditBox::InputFlag::PASSWORD);//设置输入标志 密码输入标志（显示为*）  
	editbox2->setMaxLength(20);
	editbox2->setTag(2);
	this->addChild(editbox2, 2);

	m_name = editbox1;
	m_IP = editbox2;
	auto itemNor = Sprite::create("button/enter_2.png");
	auto closeItem = MenuItemSprite::create(itemNor, nullptr, nullptr, [this](Ref* sender)
	{
		WelcomeScene* scene = (WelcomeScene *)this;
		if (*(scene->m_name->getText()) == '\0' || *(scene->m_IP->getText()) == '\0')
		{

		}
		else
		{
			printf("%s\n", scene->m_IP->getText());
			g_name = scene->m_name->getText();

			if (StartClient(scene->m_name->getText(), scene->m_IP->getText()) == 1)
			{	
				//加钱再优化
				Sleep(300); 

				//连接成功，加载大厅
				auto myScene = WaitScene::create();
				Director::getInstance()->replaceScene(myScene);
			}
			else
				printf("连接服务器失败，请输入正确的IP地址\n");
		}
	});
	closeItem->setPosition(Vec2(visibleSize.width/2, -100));
	closeItem->setScale(0.5f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setScale(0.5f);
	this->addChild(menu, 2);
}
