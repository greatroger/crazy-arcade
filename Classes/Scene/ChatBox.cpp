#include "ChatBox.h"
#include "ui/UIText.h"
#include"Network/Msg.h"
#include"Global/Player.h"


USING_NS_CC;


ChatBox::ChatBox()
{
}


ChatBox::~ChatBox()
{
}

bool ChatBox::init()
{
	createChatBox();
	scheduleUpdate();
	return true;
}

void ChatBox::update(float det)
{
	updataMessage();
}

void ChatBox::createChatBox()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();

	USING_NS_CC_EXT;

	msgInput = EditBox::create(Size(300, 30), Scale9Sprite::create("Scene/Login/inputbox.png"));
	msgInput->setPlaceHolder("chat here:");
	msgInput->setColor(Color3B::WHITE);
	msgInput->setMaxLength(20);
	msgInput->setPosition(Vec2(visiblesize.width*0.15, visiblesize.height*0.05));
	msgInput->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);

	this->addChild(msgInput, 1);

	auto send = MenuItemLabel::create(
		Label::createWithTTF("Send", "fonts/Quicksand-Bold.ttf", 25),
		CC_CALLBACK_1(ChatBox::menuSendCallback, this));
	send->setPosition(Vec2(visiblesize.width*0.35, visiblesize.height*0.05));

	auto menu = Menu::create();
	menu->addChild(send, 0);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			menuSendCallback(this);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	boxHistory = cocos2d::ui::ListView::create();
	boxHistory->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	boxHistory->setContentSize(Size(400, 200));
	boxHistory->setBackGroundColor(Color3B(238, 238, 238));
	boxHistory->setBackGroundColorOpacity(225 * 0.8f);
	boxHistory->setPosition(Vec2(0, visiblesize.height*0.1));
	this->addChild(boxHistory, -1);
}


void ChatBox::menuSendCallback(cocos2d::Ref * pSender)
{
	Sleep(50);
	std::string msg = msgInput->getText();
	if (msg.empty() || msg == " ")
	{
		msgInput->touchDownAction(msgInput, cocos2d::ui::Widget::TouchEventType::ENDED);
		return;
	}
	msgInput->setText("");
	SendMsg_Chat(msg);
}


constexpr int MAX_MSG_NUM = 10;

void ChatBox::updataMessage()
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto name = it->first;
		auto player = it->second;
		std::string txt = player->msg_chat;
		if (txt.empty()) continue;

		auto text = cocos2d::ui::Text::create(name + ": " + txt, "fonts/È«ÐÂÓ²±Ê¿¬Êé¼ò.ttf", 20);
		text->ignoreContentAdaptWithSize(false);
		if (name == Player::local_Username)
			text->setColor(cocos2d::Color3B::BLUE);
		else
			text->setColor(cocos2d::Color3B::GREEN);

		auto width = text->getContentSize().width;
		text->setContentSize(Size(400, 26 * (1 + (width + 60) / 400)));
		boxHistory->addChild(text, 0);
		if (boxHistory->getChildrenCount() > MAX_MSG_NUM)
			boxHistory->removeItem(0);

		boxHistory->forceDoLayout();
		boxHistory->jumpToBottom();

		player->msg_chat.clear();
	}
}

