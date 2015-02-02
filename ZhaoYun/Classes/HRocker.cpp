#include "HRocker.h"
const double PI=3.1415;
HRocker::HRocker(void)
{
	rocketRun=false;
}

HRocker::~HRocker(void)
{
}

//创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
HRocker* HRocker::createHRocker(const char *rockerImageName,const char *rockerBGImageName,CCPoint position)
{
	HRocker *layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName,rockerBGImageName,position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

//自定义初始化函数
void HRocker::rockerInit(const char* rockerImageName,const char* rockerBGImageName,CCPoint position)
{
	Sprite *spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	addChild(spRockerBG,0,tag_rockerBG);

	Sprite *spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	addChild(spRocker,1,tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRockerBG->getContentSize().width*0.5;//
	rocketDirection=-1;//表示摇杆方向不变
}

//启动摇杆(显示摇杆、监听摇杆触屏事件)
void HRocker::startRocker(bool _isStopOther)
{
	Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	Sprite *rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

    auto listenerTouch = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listenerTouch->setSwallowTouches(true);//设置是否想下传递触摸


    //3.0 后可以直接在touchBegan后添加它的实现代码，而不用特意去写一个touchBegan的函数
    listenerTouch->onTouchBegan = [=](Touch* touch, Event* event){ //[]中间的是传入的参数
        CCPoint point = touch->getLocation();
        Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
        if (rocker->boundingBox().containsPoint(point))
            isCanMove = true;
        return true;
    };

    //拖动精灵移动
    listenerTouch->onTouchMoved = [this](Touch* touch, Event* event){
        if (!isCanMove)
        {
            return;
        }
        CCPoint point = touch->getLocation();
        Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
        //得到摇杆与触屏点所形成的角度
        float angle = getRad(rockerBGPosition,point);
        //判断两个圆的圆心距是否大于摇杆背景的半径
        if (sqrt(pow((rockerBGPosition.x - point.x),2) + pow((rockerBGPosition.y - point.y),2)) >= rockerBGR)
        {
            //保证内部小圆运动的长度限制
            rocker->setPosition(ccpAdd(getAngelePosition(rockerBGR,angle),ccp(rockerBGPosition.x,rockerBGPosition.y)));
        }
        else
        {
            rocker->setPosition(point);
        }

        //判断方向
        if(angle>=-PI/4&&angle<PI/4)
        {
            rocketDirection=rocker_right;
            rocketRun=false;
        }
        else if(angle>=PI/4&&angle<3*PI/4)
        {
            rocketDirection=rocker_up;
        }
        else if((angle>=3*PI/4&&angle<=PI)||(angle>=-PI&&angle<-3*PI/4))
        {
            rocketDirection=rocker_left;
            rocketRun=true;
        }
        else if(angle>=-3*PI/4&&angle<-PI/4)
        {
            rocketDirection=rocker_down;
        }
    };

    listenerTouch->onTouchEnded = [=](Touch* touch, Event* event){ // =在c++11里面代表这个lambda表达式中能使用外面的变量
//        if (!isCanMove)
//        {
//            return;
//        }
        Sprite *rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
        Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
        rocker->stopAllActions();
        rocker->runAction(CCMoveTo::create(0.08f,rockerBG->getPosition()));
        isCanMove = false;
        rocketDirection=rocker_stay;
    };


    auto listenerKey = EventListenerKeyboard::create();//创建一个触摸监听
    listenerKey->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* event)
    {
        //isCanMove = true;
        switch(code)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            rocketDirection=rocker_right;
            rocketRun=false;
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            rocketDirection=rocker_up;
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            rocketDirection=rocker_left;
            rocketRun=true;
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            rocketDirection=rocker_down;
            break;
        default:
            break;
        }
        log("press key");
    };

    listenerKey->onKeyReleased = [this](EventKeyboard::KeyCode code, Event* event)
    {
        Sprite *rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
        Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
        rocker->stopAllActions();
        rocker->runAction(CCMoveTo::create(0.08f,rockerBG->getPosition()));
        //isCanMove = false;
        rocketDirection=rocker_stay;
        log("released key");
    };


    //将触摸监听添加到eventDispacher中去
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch ,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey ,this);
}

//停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
void HRocker::stopRocker()
{
	Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	Sprite * rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

    _eventDispatcher->removeAllEventListeners();
}


//获取当前摇杆与用户触屏点的角度
float HRocker::getRad(CCPoint pos1,CCPoint pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	//得到两点x的距离
	float x = px2 - px1;
	//得到两点y的距离
	float y = py1 - py2;
	//算出斜边长度
	float xie = sqrt(pow(x,2) + pow(y,2));
	//得到这个角度的余弦值(通过三角函数中的店里：角度余弦值=斜边/斜边)
	float cosAngle = x / xie;
	//通过反余弦定理获取到期角度的弧度
	float rad = acos(cosAngle);
	//注意：当触屏的位置Y坐标<摇杆的Y坐标，我们要去反值-0~-180
	if (py2 < py1)
	{
		rad = -rad;
	}
	return rad;
}

CCPoint HRocker::getAngelePosition(float r,float angle)
{
	return ccp(r*cos(angle),r*sin(angle));
}

