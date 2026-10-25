#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

namespace {
    struct Feature {
        char const* key;
        char const* label;
    };

    static constexpr Feature FEATURES[] = {
        {"cbf", "CBF"},
        {"hack-cbf", "Hack CBF"},
        {"show-fps", "FPS Display"},
        {"practice-music", "Practice Music Sync"},
        {"auto-retry", "Auto Retry"},
        {"fast-transitions", "Fast Transitions"},
        {"hitbox-view", "Hitbox View"},
        {"rainbow-icons", "Rainbow Icons"},
        {"trail-toggle", "Trail Toggle"},
        {"wave-trail", "Wave Trail"},
        {"screen-shake", "Screen Shake"},
        {"low-detail", "Low Detail Mode"},
        {"hide-particles", "Hide Particles"},
        {"hide-death-effects", "Hide Death Effects"},
        {"attempt-counter", "Attempt Counter"},
        {"speed-control", "Speed Control"},
        {"pause-focus-loss", "Pause on Focus Loss"},
        {"quick-exit", "Quick Exit"},
        {"accent-color", "Custom Accent Color"},
        {"compact-gui", "Compact GUI"}
    };

    class CodePopup final : public Popup, public TextInputDelegate {
    protected:
        CCTextInputNode* m_input = nullptr;

        bool init() {
            if (!Popup::init(250.f, 145.f)) return false;
            this->setTitle("Hack CBF access 💜");

            auto note = CCLabelBMFont::create("Enter the access code to enable Hack CBF", "goldFont.fnt");
            note->setScale(0.38f);
            this->addChild(note);
            note->setPosition({125.f, 91.f});

            m_input = CCTextInputNode::create(190.f, "Access code", "bigFont.fnt", 32, "");
            if (!m_input) return false;
            m_input->setPosition({125.f, 62.f});
            m_input->setDelegate(this);
            this->addChild(m_input);

            auto submit = CCMenuItemSpriteExtra::create(
                ButtonSprite::create("Unlock 💜", 90, true, "goldFont.fnt", "GJ_button_04.png", 25.f, 0.6f),
                this, menu_selector(CodePopup::onSubmit)
            );
            auto menu = CCMenu::create();
            menu->addChild(submit);
            menu->setPosition({125.f, 28.f});
            this->addChild(menu);
            return true;
        }

        void onSubmit(CCObject*) {
            auto entered = m_input ? std::string(m_input->getString()) : std::string();
            if (entered == "rezo1234") {
                Mod::get()->setSettingValue<bool>("hack-cbf", true);
                FLAlertLayer::create("Unlocked 💜", "Hack CBF is toggled on. Note: its actual gameplay logic still needs to be implemented.", "Yay!")->show();
                this->onClose(nullptr);
            } else {
                FLAlertLayer::create("Nope 💜", "That code didn't match. Try again!", "OK")->show();
            }
        }

        void onClose(CCObject*) {
            this->setKeypadEnabled(false);
            this->removeFromParent();
        }

        void textInputClosed(CCTextInputNode*) override {}
        void textChanged(CCTextInputNode*) override {}

    public:
        static CodePopup* create() {
            auto ret = new CodePopup();
            if (ret && ret->init()) {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    };

    class ClydestalesPopup final : public Popup {
    protected:
        bool init() {
            if (!Popup::init(410.f, 315.f)) return false;
            this->setTitle("♡ cClydestales GUI ♡");

            auto subtitle = CCLabelBMFont::create("Clean • Cute • Configurable", "goldFont.fnt");
            subtitle->setScale(0.42f);
            subtitle->setColor({205, 155, 255});
            this->addChild(subtitle);
            subtitle->setPosition({205.f, 267.f});

            auto left = CCLabelBMFont::create("MAIN FEATURES", "goldFont.fnt");
            left->setScale(0.38f);
            left->setColor({185, 130, 255});
            this->addChild(left);
            left->setPosition({110.f, 239.f});

            auto right = CCLabelBMFont::create("MORE OPTIONS", "goldFont.fnt");
            right->setScale(0.38f);
            right->setColor({185, 130, 255});
            this->addChild(right);
            right->setPosition({305.f, 239.f});

            auto menu = CCMenu::create();
            menu->setPosition({0.f, 0.f});
            this->addChild(menu);

            for (int i = 0; i < 20; ++i) {
                auto const& feature = FEATURES[i];
                bool enabled = Mod::get()->getSettingValue<bool>(feature.key);
                auto labelText = fmt::format("{}  {}", enabled ? "♥" : "♡", feature.label);
                auto label = CCLabelBMFont::create(labelText.c_str(), "bigFont.fnt");
                label->setScale(0.36f);
                label->setAnchorPoint({0.f, 0.5f});

                auto item = CCMenuItemSpriteExtra::create(
                    label, this, menu_selector(ClydestalesPopup::onFeature)
                );
                item->setTag(i);
                float x = (i < 10) ? 25.f : 220.f;
                int row = i % 10;
                float y = 215.f - row * 19.5f;
                item->setPosition({x, y});
                menu->addChild(item);
            }

            auto footer = CCLabelBMFont::create("Made with love ♡", "goldFont.fnt");
            footer->setScale(0.42f);
            footer->setColor({255, 155, 230});
            this->addChild(footer);
            footer->setPosition({205.f, 17.f});

            return true;
        }

        void onFeature(CCObject* sender) {
            int index = sender->getTag();
            if (index < 0 || index >= 20) return;
            auto const& feature = FEATURES[index];

            if (std::string(feature.key) == "hack-cbf") {
                if (Mod::get()->getSettingValue<bool>("hack-cbf")) {
                    Mod::get()->setSettingValue<bool>("hack-cbf", false);
                    FLAlertLayer::create("Hack CBF", "Hack CBF has been turned off.", "OK")->show();
                } else {
                    CodePopup::create()->show();
                }
                this->removeFromParent();
                ClydestalesPopup::create()->show();
                return;
            }

            bool oldValue = Mod::get()->getSettingValue<bool>(feature.key);
            Mod::get()->setSettingValue<bool>(feature.key, !oldValue);
            this->removeFromParent();
            ClydestalesPopup::create()->show();
        }

    public:
        static ClydestalesPopup* create() {
            auto ret = new ClydestalesPopup();
            if (ret && ret->init()) {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    };
}

class $modify(ClydestalesMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Use a unique ID to avoid duplicating our icon if another hook re-enters.
        if (this->getChildByID("cClydestales.gui/open-menu")) return true;

        auto icon = CCSprite::create("click-icon.png"_spr);
        if (!icon) {
            icon = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        }
        if (!icon) return true;

        icon->setScale(0.22f);
        auto button = CCMenuItemSpriteExtra::create(
            icon, this, menu_selector(ClydestalesMenuLayer::onOpenClydestales)
        );
        button->setID("cClydestales.gui/open-menu");

        auto menu = CCMenu::create();
        menu->setID("cClydestales.gui/open-menu-container");
        menu->addChild(button);
        menu->setPosition({CCDirector::sharedDirector()->getWinSize().width - 35.f, 35.f});
        this->addChild(menu, 100);
        return true;
    }

    void onOpenClydestales(CCObject*) {
        ClydestalesPopup::create()->show();
    }
};
