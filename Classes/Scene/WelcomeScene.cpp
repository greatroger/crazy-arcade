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
	//�˺ſ� ��������8���ַ�  
	auto editbox1 = EditBox::create(Size(200, 35), Scale9Sprite::create("button/inputbox.png"));
	editbox1->setAnchorPoint(Point(0, 0));
	editbox1->setPosition(Point(visibleSize.width*0.4, visibleSize.height*0.55));
	editbox1->setPlaceHolder("name:");//ռλ�ַ�  
	editbox1->setMaxLength(8);
	editbox1->setFontColor(Color3B::WHITE);//���������������ɫ  
	editbox1->setTag(1);
	this->addChild(editbox1, 2);
	//����� password  
	auto editbox2 = EditBox::create(Size(200, 35), Scale9Sprite::create("button/inputbox.png"));
	editbox2->setAnchorPoint(Point(0, 0));
	editbox2->setPosition(Point(visibleSize.width*0.4, visibleSize.height*0.4));
	editbox2->setPlaceHolder("IP:");
	editbox2->setPlaceholderFontColor(Color3B::WHITE);//����ռλ�������ɫ  
	editbox2->setFontColor(Color3B::WHITE);
	editbox2->setInputMode(EditBox::InputMode::NUMERIC);//������������ ���ּ������������  
	//editbox2->setInputFlag(EditBox::InputFlag::PASSWORD);//���������־ ���������־����ʾΪ*��  
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
				//��Ǯ���Ż�
				Sleep(300); 

				//���ӳɹ������ش���
				auto myScene = WaitScene::create();
				Director::getInstance()->replaceScene(myScene);
			}
			else
				printf("���ӷ�����ʧ�ܣ���������ȷ��IP��ַ\n");
		}
	});
	closeItem->setPosition(Vec2(visibleSize.width/2, -100));
	closeItem->setScale(0.5f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setScale(0.5f);
	this->addChild(menu, 2);
}
