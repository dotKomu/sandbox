#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
private:
    struct ScaleParam {
        float duration = 0;
        float size = 0;
    };
    struct PopUpParam {
        std::function<void()> startCallback = nullptr;
        std::function<void()> finishCallback = nullptr;
        ScaleParam first;
        ScaleParam second;
        ScaleParam thread;
    };

public:
    CREATE_FUNC(HelloWorld);
    static cocos2d::Scene* createScene();

    bool init() override;

private:
    cocos2d::Vec2 getCenterPos();
    void showDebugMenu();
    cocos2d::Sequence* createPopUpSequence();
    cocos2d::Label* createPopUpLabel();
    
private:
    PopUpParam _popUpParam;
};

#endif // __HELLOWORLD_SCENE_H__
