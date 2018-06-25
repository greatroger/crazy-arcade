#include "Scene/LoginScene.h"
#include"Network/Client.h"
#include"Scene/RoomScene.h"
#include"Scene/GameScene.h"
#include"Global/Player.h"
#include"Network/Msg.h"
#include"Scene/Room/PopupLayer.h"
#include"Scene/StartScene.h"

USING_NS_CC;


LoginScene::LoginScene()
{
}
 

LoginScene::~LoginScene()
{
}

bool LoginScene::init()
{
	addBackground();
	addInputBox();
	addLoginButton();
	createBackButton();
	scheduleUpdate();
	return true;
}

void LoginScene::addBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Scene/Login/background.jpg");
	assert(background != nullptr);
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	background->setScale(2.1f);
	addChild(background, -1);
}

void LoginScene::createBackButton()
{
	auto back = MenuItemLabel::create(
		Label::createWithTTF("Back", "fonts/Quicksand-Bold.ttf", 50),
		CC_CALLBACK_1(LoginScene::menuBackCallback, this));
	back->setPosition(90, 680);
	back->setColor(ccc3(255, 245, 247));
	auto menu = Menu::create();
	menu->addChild(back, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}

void LoginScene::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.6, StartScene::create()));
}

void LoginScene::update(float det)
{
	checkLogin();
}

void LoginScene::checkLogin()
{
	int type = Msg::Login.loginFeedbackType;
	Msg::Login.loginFeedbackType = -1;
	if (type == -1) return;

	isConnecting = false;

	auto  TipsLayer = PopupLayer::create("Scene/Room/c8.png");
	TipsLayer->setContentSize(CCSizeMake(500, 300));
	TipsLayer->setTitle("Tip", 25);
	TipsLayer->addButton("Scene/Room/button_normal.png", "Scene/Room/button_selected.png", "OK");
	switch (type)
	{
	default:
		break;
	case 0:   {
		auto roomScene = RoomScene::create();
	    Director::getInstance()->pushScene(TransitionFade::create(1, roomScene));
	    break; 
	    }
	case 1:
		TipsLayer->setContentText("The name has been used, you can try another name", 30, 30, 200);
		this->addChild(TipsLayer, 5);
		break;
	case 2:
		TipsLayer->setContentText("The room is full, you can try again later", 30, 30, 200);
		this->addChild(TipsLayer, 5);
		break;
	case 3:
		TipsLayer->setContentText("There has something worong with the server, you can try another IP address", 30, 30, 200);
		this->addChild(TipsLayer, 5);
		break;
	case 4:
		TipsLayer->setContentText("The game has started, you can try again later", 30, 30, 200);
		this->addChild(TipsLayer, 5);
		break;
	}
}

void LoginScene::addInputBox()
{
	 auto visiblesize = Director::getInstance()->getVisibleSize();

	 USING_NS_CC_EXT;

	 usernameInput = EditBox::create(Size(300, 50), Scale9Sprite::create("Scene/Login/inputbox.png"));
	 usernameInput->setPlaceHolder("name:");
	 usernameInput->setColor(Color3B::WHITE);
	 usernameInput->setMaxLength(7);
	 usernameInput->setPosition(Vec2(visiblesize.width/2,visiblesize.height*0.7));
	 usernameInput->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	 this->addChild(usernameInput,1);

	 IPAddressInput = EditBox::create(Size(300, 50), Scale9Sprite::create("Scene/Login/inputbox.png"));
	 IPAddressInput->setPlaceHolder("IP:");
	 IPAddressInput->setColor(Color3B::WHITE);
	 IPAddressInput->setMaxLength(15);
	 IPAddressInput->setPosition(Vec2(visiblesize.width / 2, visiblesize.height*0.5));
	 IPAddressInput->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	 this->addChild(IPAddressInput, 1);
}

void LoginScene:: addLoginButton()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();

	auto loginButton = ui::Button::create("Scene/Start/button_normal.png", "Scene/Start/button_selected.png");
	loginButton->setTitleText("Login");
	loginButton->setTitleFontName("fonts/Marker Felt.ttf");
	loginButton->setTitleFontSize(40);
	loginButton->setPosition(Vec2(visiblesize.width / 2, visiblesize.height *0.2));

	loginButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (isConnecting) return;

		auto username = usernameInput->getText();
		auto IPAddress = IPAddressInput->getText();
		if (username[0]==0 ||IPAddress[0]==0 )
		{
			MessageBox("name or IP can't be empty", "Alert");
		}
		else
		{
			Player::local_Username = username;
			if (StartClient(username, IPAddress) > 0)
			{
				isConnecting = true;
			}
			else
			{
				MessageBox("can't connect to server", "Alert");
			}
		}
	});

	this->addChild(loginButton);
}