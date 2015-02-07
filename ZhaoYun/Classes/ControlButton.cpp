#include "ControlButton.h"
MyControlButton::MyControlButton():controlBtn(NULL),isTouch(false)
{
}
MyControlButton::~MyControlButton()
{

}
void MyControlButton::CreateButton(const char* name_png,const char* button_title,unsigned int num)
{
	//得到按钮图片的大小 
    Scale9Sprite* btn = Scale9Sprite::create(name_png);

    int  png_height=static_cast<int>(btn->getContentSize().height);
    int  png_width=static_cast<int>( btn->getContentSize().width);
//  btn->autorelease();

    //要显示的图片大小
    CCRect rect = CCRectMake(0,0,png_width,png_height);   //图片的大小
    CCRect rectInsets = CCRectMake(1,1,1,1); //left，right，width，height

    //按钮标题,Marker Felt为字体类型，png_height为字体高度
    CCLabelTTF *title = CCLabelTTF::create(button_title, "Marker Felt",png_height-10);
    title->setOpacity(num);//设置可见度

    //正常状态下的按钮图片
    Scale9Sprite *btnNormal = Scale9Sprite::create(name_png,rect,rectInsets);
	
    //创建按钮
    controlBtn = ControlButton::create(title, btnNormal);
    this->addChild(controlBtn);
    //绑定事件
    BindButtonEven();
	
	
}
void MyControlButton::BindButtonEven()
{
	if(!controlBtn)
		return;
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDownAction),Control::EventType::TOUCH_DOWN);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragEnter),Control::EventType::DRAG_ENTER);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragExit),Control::EventType::DRAG_EXIT);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragInside),Control::EventType::DRAG_INSIDE);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchDragOutside),Control::EventType::DRAG_OUTSIDE);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchUpInside),Control::EventType::TOUCH_UP_INSIDE);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchUpOutside),Control::EventType::TOUCH_UP_OUTSIDE);
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MyControlButton::touchCancel),Control::EventType::TOUCH_CANCEL);
}
/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */  
void MyControlButton::touchDownAction(Ref* pSender, Control::EventType event)
{
	isTouch=true;

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */  
void MyControlButton::touchDragEnter(Ref* pSender, Control::EventType event)
{
	
}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */  
void MyControlButton::touchDragExit(Ref* pSender, Control::EventType event)
{
	
}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */  
void MyControlButton::touchDragInside(Ref* pSender, Control::EventType event)
{

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */  
void MyControlButton::touchDragOutside(Ref* pSender, Control::EventType event)
{

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */  
void MyControlButton::touchUpInside(Ref* pSender, Control::EventType event)
{
	isTouch=false;

}

/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */  
void MyControlButton::touchUpOutside(Ref* pSender, Control::EventType event)
{
	

}
/* 暂时没有发现能用鼠标触发这个事件的操作，看了注释，应该是由其它事件中断按钮事件而触发的 */ 
void MyControlButton::touchCancel(Ref* pSender, Control::EventType event)
{

}
