#include "Scene/LoginScene.h"
#include"Network/Client.h"
#include"Scene/RoomScene.h"
#include"Scene/GameScene.h"
#include"Global/Player.h"

USING_NS_CC;


LoginScene::LoginScene()
{
}


LoginScene::~LoginScene()
{
}

bool LoginScene::init()
{
	addInputBox();
	addLoginButton();

	
	return true;
}
void LoginScene::addBackground()
{

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
		/*Player::local_Username = "55";
		if (StartClient("55", "127.0.0.01") > 0)
		{
			Sleep(500);
			auto roomScene = GameScene::create();
			Director::getInstance()->replaceScene(TransitionFade::create(0.1, roomScene));
			
		}
		return;*/

		if (type != ui::Widget::TouchEventType::ENDED) return;
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
				Sleep(500);
				auto roomScene = RoomScene::create();
				Director::getInstance()->pushScene(TransitionFade::create(1,roomScene));
			}
			else
			{
				MessageBox("can't connect to server", "Alert");
			}
		}
	});

	this->addChild(loginButton);
}