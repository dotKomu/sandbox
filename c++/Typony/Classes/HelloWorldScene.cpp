#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

using namespace std;
USING_NS_CC;

namespace {
    const float correction = 0.01f;
} // namespace

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    showDebugMenu();
    
    _popUpParam.first.duration = 0.05f;
    _popUpParam.first.size = 1.5f;
    _popUpParam.second.duration = 0.1f;
    _popUpParam.second.size = 0.7f;
    _popUpParam.thread.duration = 0.05f;
    _popUpParam.thread.size = 1.2f;
    
    return true;
}

Sequence* HelloWorld::createPopUpSequence()
{
    auto startProc = CallFunc::create([this]() {
        if (_popUpParam.startCallback != nullptr) {
            _popUpParam.startCallback();
        }
    });
    auto finishProc = CallFunc::create([this]() {
        if (_popUpParam.finishCallback != nullptr) {
            _popUpParam.finishCallback();
        }
    });
    return Sequence::create(startProc,
                            ScaleBy::create(_popUpParam.first.duration, _popUpParam.first.size),
                            ScaleBy::create(_popUpParam.second.duration, _popUpParam.second.size),
                            ScaleBy::create(_popUpParam.second.duration, _popUpParam.thread.size),
                            finishProc,
                            DelayTime::create(0.2f),
                            RemoveSelf::create(),
                            nullptr);
}

Label* HelloWorld::createPopUpLabel()
{
    auto label = Label::createWithTTF("hello world", "fonts/arial.ttf", 48);
    label->setPosition(getCenterPos());
    label->enableOutline(Color4B::BLUE, 3.0f);
    return label;
}

void HelloWorld::showDebugMenu()
{
#if COCOS2D_DEBUG
    
    auto debugView = ui::ListView::create();
    debugView->setContentSize(Size(150, 200));
    debugView->setPosition(Vec2(debugView->getContentSize().width / 2,
                                (debugView->getContentSize().height / 2) - 100));
    debugView->setDirection(ui::ScrollView::Direction::VERTICAL);
    debugView->setBounceEnabled(true);
    debugView->setTouchEnabled(true);
    this->addChild(debugView);
    
    auto item = ui::Text::create("Refresh", "fonts/arial.ttf", 16);
    item->setTouchEnabled(true);
    item->addClickEventListener([this](Ref*) {
        auto label = createPopUpLabel();
        _popUpParam.finishCallback = [label]() {
            CCLOG("animation end");
        };
        label->runAction(createPopUpSequence());
        this->addChild(label);
    });
    item->setColor(Color3B::RED);
    item->setPosition(Vec2(64, (getCenterPos().y * 2) - 32));
    this->addChild(item);
    
    auto createItem = [this](const string& description, std::function<void(Ref*)> proc) {
        auto item = ui::Text::create(description, "fonts/arial.ttf", 16);
        item->setTouchEnabled(true);
        item->addClickEventListener(proc);
        return item;
    };
    
#define ADD_DEBUG_MENU(__STR__, __PROC__) \
debugView->pushBackCustomItem(createItem(__STR__, __PROC__));
    
    {
        ADD_DEBUG_MENU("first:duration +", [this](Ref*) { _popUpParam.first.duration += correction; });
        ADD_DEBUG_MENU("first:duration -", [this](Ref*) { _popUpParam.first.duration -= correction; });
        ADD_DEBUG_MENU("first:size +", [this](Ref*) { _popUpParam.first.size += correction; });
        ADD_DEBUG_MENU("first:size -", [this](Ref*) { _popUpParam.first.size -= correction; });
        ADD_DEBUG_MENU("-------------------------", [this](Ref*) { });
    }
    {
        ADD_DEBUG_MENU("second:duration +", [this](Ref*){ _popUpParam.second.duration += correction; });
        ADD_DEBUG_MENU("second:duration -", [this](Ref*){ _popUpParam.second.duration -= correction; });
        ADD_DEBUG_MENU("second:size +", [this](Ref*) { _popUpParam.second.size += correction; });
        ADD_DEBUG_MENU("second:size -", [this](Ref*) { _popUpParam.second.size -= correction; });
        ADD_DEBUG_MENU("-------------------------", [this](Ref*) { });
    }
    {
        ADD_DEBUG_MENU("thread:duration +", [this](Ref*){ _popUpParam.thread.duration += correction; });
        ADD_DEBUG_MENU("thread:duration -", [this](Ref*){ _popUpParam.thread.duration -= correction; });
        ADD_DEBUG_MENU("thread:size +", [this](Ref*) { _popUpParam.thread.size += correction; });
        ADD_DEBUG_MENU("thread:size -", [this](Ref*) { _popUpParam.thread.size -= correction; });
    }
#else
    CCLOG("invalid COCOS2D_DEBUG.");
#endif
}

Vec2 HelloWorld::getCenterPos()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    return Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
}
