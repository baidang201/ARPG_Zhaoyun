#ifndef __ControlButton_H__
#define __ControlButton_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIScale9Sprite.h"


USING_NS_CC;
USING_NS_CC_EXT; 
//用于标识当前按钮的状态
typedef enum{
	touch_begin,
	touch_down,
	touch_up,
}tagForTouch;
class MyControlButton :public CCNode
{
public:
    MyControlButton();
    ~MyControlButton();
    CREATE_FUNC(MyControlButton);
	//创建按钮,其中name_png为按钮的背景图片，button_title为按钮图片上要显示的文字，num为文字的透明度0-100，0为透明
	 void CreateButton(const char* name_png,const char* button_title="0",unsigned int num=0);
	//绑写按钮事件 
	void BindButtonEven();
	/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */ 
    void touchDownAction(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */  
    void touchDragEnter(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */  
    void touchDragExit(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */  
    void touchDragInside(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */ 
    void touchDragOutside(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */
    void touchUpInside(Ref* pSender, Control::EventType event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */  
    void touchUpOutside(Ref* pSender, Control::EventType event);
	/* 暂时没有发现能用鼠标触发这个事件的操作，看了注释，应该是由其它事件中断按钮事件而触发的 */ 
    void touchCancel(Ref* pSender, Control::EventType event);
	//是否按下按钮
	bool isTouch;
private:
	//按钮控件变量
    ControlButton* controlBtn;
};
#endif 
