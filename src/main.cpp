#include <Geode/modify/InfoLayer.hpp>

#include <Geode/ui/Button.hpp>

using namespace geode::prelude;

class $modify(InfoLayer) {

    struct Fields {
        Button* button = nullptr;
    };

    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2)) {
            return false;
        }

        auto menu = m_mainLayer->getChildByID("refresh-menu");

        if (!menu) {
            return true;
        }

        auto btn = Button::createWithSprite("button.png"_spr, [this](Button*) {
            if (m_itemCount > 0) {
                this->loadPage(
                    (m_itemCount - 1) / (GameManager::get()->getGameVariable("0088") ? 20 : 10),
                    false
                );
            }
        });
        btn->setScaleMultiplier(1.05f);
        btn->setScale(0.9f);
        btn->setID("button"_spr);

        if (m_itemCount <= 0) {
            btn->setVisible(false);
        }
        
        menu->addChild(btn);
        menu->updateLayout();

        m_fields->button = btn;
        
        return true;
    }

    void loadCommentsFinished(CCArray* p0, const char* p1) {
        InfoLayer::loadCommentsFinished(p0, p1);

        if (auto btn = m_fields->button) {
            btn->setVisible(p0 && p0->count() > 0);
            btn->getParent()->updateLayout();
        }
    }
    
};