//�Ի���

#ifndef __PopupLayer_H__
#define __PopupLayer_H__
#include"cocos2d.h"
#include<iostream>
//#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
//#include"MyUtility.h"
USING_NS_CC_EXT;
USING_NS_CC;

enum POP_TYPE
{
	QUIT,                  //�˳���Ϸ
};

class PopupLayer:public Layer
{
public:
	bool init();
	~PopupLayer();
	CREATE_FUNC(PopupLayer);
	//���öԻ�������
	void setPopType(POP_TYPE type);                   
	//���ݱ���ͼƬ��������
	static PopupLayer *create(const char* backgroundImage);    
	//���öԻ������
	void setTitle(const char* title, int fontsize );                
	//���öԻ����ı�����
	void setContentText(const char*title, int fontsize,int padding,int paddingTop);           
	//��ӶԻ��򰴼�
	bool addButton(const char*normalImage, const char*selectedImage, const char*title, int tag = 0, 
		SEL_MenuHandler selector = menu_selector(PopupLayer::buttonCallBack));
	//�ѵ��ö������������������Ϊ�����ص�
	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);                  
	//����Ի���ʱ����
	virtual void onEnter();                                                     
	//�˳��Ի���ʱ����
	virtual void onExit();      
	//��ť���ʱ���ô˷�����Ȼ����õ�����Ļص�����
	void buttonCallBack(CCObject * pSender);

private:
	POP_TYPE pop_type;                                                               //�Ի������ͱ���
	int m_contentPadding;                                                            //�����������ߵĿհ�������
	int m_contentPaddingTop;
	CCObject * m_callbackListener;                                                   //�ص�����
	SEL_CallFuncN m_callback;                                                        //�ص�
	CC_SYNTHESIZE_RETAIN(Menu*, m_pMenu, MenuButton);                                //����retain���Եı���
	CC_SYNTHESIZE_RETAIN(Sprite*, m_sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltContentText, LabelContentText);
};                	      
#endif // !__PopupLayer_H__

