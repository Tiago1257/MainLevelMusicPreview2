#include "Geode/binding/LevelSelectLayer.hpp"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCScene.h"
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/BoomScrollLayer.hpp>

using namespace geode::prelude;

class $modify(CoolerLSLayer, LevelSelectLayer) {
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) return false;
		CoolerLSLayer::playLevelMusic();
		return true;
	}

	void playLevelMusic() {
		FMODAudioEngine::get()->stopAllMusic(true);
		auto page = static_cast<LevelPage*>(this->m_scrollLayer->getPage(this->m_scrollLayer->m_page));
		geode::log::info("{}", page->m_level->m_levelID.value());
		FMODAudioEngine::get()->playMusic(
			LevelTools::getAudioFileName(page->m_level->m_levelID.value()),
			true,
			.5f,
			1
		);
	}
};

class $modify(CoolerBSLayer, BoomScrollLayer) {
	void moveToPage(int page) {
		if (auto lsLayer = CCScene::get()->getChildByType<CoolerLSLayer>(1)) {
			lsLayer->playLevelMusic();
		}
		moveToPage(page);
	}
};
