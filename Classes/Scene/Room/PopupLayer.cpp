#include"PopupLayer.h"
PopupLayer::~PopupLayer()
{
	CC_SAFE_RELEASE(m_pMenu);
	CC_SAFE_RELEASE(m_sfBackGround);
	CC_SAFE_RELEASE(m_s9BackGround);
	CC_SAFE_RELEASE(m_ltContentText);
	CC_SAFE_RELEASE(m_ltTitle);
}
bool PopupLayer::init()
{
	//��ʼ��Ĭ��ֵ
	m_pMenu = NULL;
	m_callback = NULL;
	m_sfBackGround = NULL;
	m_s9BackGround = NULL;
	m_ltContentText = NULL;
	m_ltTitle = NULL;
	this->setContentSize(Size::ZERO);
	//��ʼ����Ҫ��Menu,�����ݲ�����Menu�����MenuItemѡ��
	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenuButton(menu);
	//��Ӵ�����Ӧ
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch * t,Event *e)
	{
		printf("touch");
		return true;
	};

	listener->onTouchEnded = [this](Touch *t, Event *e)
	{
		log("touch end");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::create(const char* backgroundImage)
{
	PopupLayer* m1 = PopupLayer::create();
	m1->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	return m1;
}

void PopupLayer::setTitle(const char * title, int fontsize)
{
	LabelTTF *ltfTitle = LabelTTF::create(title, "fonts/Marker Felt.ttf", fontsize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	LabelTTF *ltf = LabelTTF::create(text, "fonts/Marker Felt.ttf", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

bool PopupLayer::addButton(const char*normalImage, const char*selectedImage,
	const char*title, int tag, SEL_MenuHandler selector)
{
	Size winSize = Director::getInstance()->getWinSize();
	//����MenuItem��ť�������ð�ťtag��λ���Լ��ص�����ΪbuttonCallback
	MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, selector);
	menuImage->setTag(tag);
	menuImage->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	menuImage->setScaleX(0.8f);
	//��MenuItem������֣�������ɫ��λ��
	Size imenu = menuImage->getContentSize();
	LabelTTF *ttf = LabelTTF::create(title, "fonts/Marker Felt.ttf",20);
	ttf->setColor(ccc3(0, 0, 0));
	//����������MenuItem�е�λ��
	ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
	ttf->setFontSize(20);
	menuImage->addChild(ttf);
	getMenuButton()->addChild(menuImage);
	return true;
}

void PopupLayer::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}

void PopupLayer::buttonCallBack(CCObject *pSender)
{
	Node * node = dynamic_cast<Node*>(pSender);

	if (m_callback && m_callbackListener)
	{
		//�����setCallbackFunc���������MenuScene�����quitButtonCallback����
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}

void PopupLayer::onEnter()
{
	Layer::onEnter();
	Size winSize = Director::getInstance()->getWinSize();
	//���ݶԻ����С���þŹ��񱳾�ͼƬ
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(getContentSize());
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);
	_contentSize = getContentSize();
	//��Ӱ�ť����������λ��
	this->addChild(getMenuButton());
	float btnWidth = _contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	//��Menu����ȡ���Ӳ˵���
	Vector<Node*>vecArray = getMenuButton()->getChildren();
	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node *node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - _contentSize.width / 2 + btnWidth * (j + 1), winSize.height / 2 -_contentSize.height / 3));
		j++;
	}
	if (getLabelTitle())
	{
		//��ʾ�Ի������
		getLabelTitle()->setPosition(ccpAdd(ccp(winSize.width/2,winSize.height/2), ccp(0, _contentSize.height / 2 - 20)));
		getLabelTitle()->setColor(ccc3(255, 255, 255));
		this->addChild(getLabelTitle());
	}
	//���ݶԻ������ͣ����öԻ�������
	switch (pop_type)
	{
	case QUIT:
		if (getLabelContentText())
		{
			LabelTTF* ltf = getLabelContentText();
			ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(CCSizeMake(_contentSize.width - m_contentPadding * 2, _contentSize.height - m_contentPaddingTop));
			ltf->setColor(ccc3(255, 255, 255));
			this->addChild(ltf);
		}
	}
	//�Ի��򵯳�Ч�����ɴ��С������С���
	Action *popupactions = Sequence::create(ScaleTo::create(0.0, 0.0), ScaleTo::create(0.06, 1.05), ScaleTo::create(0.08, 0.95), ScaleTo::create(0.08, 1.0),NULL);
	this->runAction(popupactions);
}

void PopupLayer::onExit()
{
	Layer::onExit();
}




