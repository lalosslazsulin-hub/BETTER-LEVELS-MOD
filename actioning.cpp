#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRunLevel) {
        // Initialize the base game layer first
        if (!PlayLayer::init(level, useReplay, dontRunLevel)) {
            return false;
        }

        // Target the main batch nodes or screen layout layer
        // Director gives us the visible screen size
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // 1. Create a custom visual anchor (e.g., Vignette Texture overlay)
        // Ensure you add your custom texture file to your mod's resources
        auto overlaySprite = CCSprite::create("vignette_overlay.png");
        if (overlaySprite) {
            overlaySprite->setPosition({winSize.width / 2, winSize.height / 2});
            
            // Adjust scale to completely stretch across the screen
            overlaySprite->setScaleX(winSize.width / overlaySprite->getContentSize().width);
            overlaySprite->setScaleY(winSize.height / overlaySprite->getContentSize().height);
            
            // Set blending options for unique lighting effects (GL_DST_COLOR, GL_ZERO etc.)
            ccBlendFunc blend = { GL_DST_COLOR, GL_SRC_ALPHA };
            overlaySprite->setBlendFunc(blend);
            overlaySprite->setOpacity(150); // Fine-tune look transparency

            // Add the sprite cleanly into the UI layer so it sits above gameplay but below progress bars
            this->addChild(overlaySprite, 10); 
        }

        log::info("Injected unique level visuals successfully.");
        return true;
    }
};
