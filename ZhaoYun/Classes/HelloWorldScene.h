#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HRocker.h"
#include "Hero.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//每帧更新时调用的事件
	virtual void update(float delta);
private:
	HRocker* rocker;//摇杆
	Hero*    hero;///精灵

    Size visibleSize;
    Vec2 origin;
};

#endif // __HELLOWORLD_SCENE_H__
