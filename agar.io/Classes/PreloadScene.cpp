#include "PreloadScene.h"
using namespace CocosDenshion;
USING_NS_CC;
Scene* PreLoad::createScene() {
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ� 
	auto scene = Scene::create();
	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
		auto layer = PreLoad::create();
	// �� PreLoad����Ϊ�ӽڵ���ӵ�����
		scene->addChild(layer);
	// ���س�������
		return scene;
}
bool PreLoad::init() {
	// ���ø����init���� 
	if (!Layer::init()) {
		return false;
	}
	// ����豸�ɼ���ͼ��С 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ����һ�������� 
	auto barSprite = Sprite::create("progressbar.png"); 
	// ��ʼ��һ��ProgressTimer���������� 
	_progress = ProgressTimer::create(barSprite); 
	// setPercentage:0.0f,��ʾ��δ�����κ���Դ����������Ļ�Ͼ���ʲôҲ������ 
	_progress->setPercentage(0); 
	// ����ͼƬ��С��ϵ���� scale���ó�0.5,����Сһ�� 
	_progress->setScale(0.5f); 
	// ���ý�������������ʼλ�ã�Ĭ����ͼƬ���е� 
	// �����Ҫ��ʾ�����ҵ�һ������Ч��������ĳɣ�0,y) 
	_progress->setMidpoint(Vec2(0, 0.5f)); 
	// barChangeRate��ʾ�Ƿ�ı�ˮƽ���ߴ�ֱ����ı��������ó�1��ʾ�ı䣬0��ʾ���ı� 
	_progress->setBarChangeRate(Vec2(1, 0.f)); 
	// kCCProgressTimerTypeBar ��ʾΪ���ν����� 
	_progress->setType(ProgressTimer::Type::BAR); 
	// ���ý�����λ������Ļ���� 
	_progress->setPosition(visibleSize.width/2,visibleSize.height/2); 
	// �����������Ϊ��ǰ����ӽڵ� 
	this->addChild(_progress);
	return true;
}
void PreLoad::onEnterTransitionDidFinish() { 
	// ���ø���� onEnterTransitionDidFinish ���� 
	Layer::onEnterTransitionDidFinish(); 
	/* ע�⣺cocos2d-x 3.0֮��Array�� Dictionary���������ˣ�ʹ��Vector�� map��� 
	cocos2d-x 3.0������������Value,���Դ洢���ֻ����������� 
	ValueVector ���Ǳ��� Value �� Vector ���ϣ�typedef std::vector<Value> ValueVector; 
	ValueMap ���Ǳ��� Value �� Map ���ϣ�typedef std : : unordered_map<std ::string, Value> ValueMap;
	*/
	// ����preloadResources.plist�����ļ�����ȡ�ļ��е���Ϸ��Դ�����б�����һ��ValueMap���� 
	ValueMap map = FileUtils::getInstance()->getValueMapFromFile("preloadResources.plist");
	// ͨ��keyֵȡ��ÿ�ֲ�ͬ������Դ��ValueVector���� 
	ValueVector spriteSheets = map.at("SpriteSheets").asValueVector();
	ValueVector effects = map.at("Sounds").asValueVector(); 
	ValueVector musics = map.at("Musics").asValueVector(); 
	// ���ValueVector�����size��ӵõ���Ҫ���Ե���Դ������
	_sourceCount = spriteSheets.size() + effects.size() + musics.size();
	// ���ý��������´��� = 100 / ��Ҫ���Ե���Դ����
	_progressInterval = 100 / _sourceCount;
	// ���μ�����Դ
	loadMusic(musics);
	loadEffect(effects);
	loadSpriteSheets(spriteSheets);
	
// ���ر�������
void loadMusic(ValueVector musicFiles) {
	for (unsigned int i = 0; i != musicFiles.size(); ++i) {
		Value v = musicFiles.at(i);
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(v.asString().c_str());
		progressUpdate();		
	}
}

// ��������
void loadEffect(ValueVector effectFiles) {
	for (unsigned int i = 0; i != effectFiles.size();++i) { 
		Value v = effectFiles.at(i); 
		SimpleAudioEngine::getInstance()->preloadEffect(v.asString().c_str()); 
		progressUpdate (); 
	} 
}

// ���ؾ���� 
void loadSpriteSheets(ValueVector spriteSheets) {
	/*�ú����������plist�ļ�������ͬ����׺Ϊ.png������ͼƬ�� 
	�Ѹ�plist������spriteFrame��Ϣ��ȡ��������֮��Ĵ����п���ͨ�� 
	Sprite : : createWithSpriteFrameName(const std : : strings spriteFrameName)������ȡ��Ӧ�� ����ٱ����� airfightSheet.plist ��Ӧ airfightSheet.png 
	*/ 
	for (unsigned int i = 0; i != spriteSheets.size(); ++i) {
		Value v = spriteSheets.at(i);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(v.asString().c_str());
		progressUpdate();
	}
}

// ���������º��� 
void PreLoad::progressUpdate(){
	// ÿ�ε��øú���˵������һ����Դ���Լ�������Դ����
	if (--_sourceCount) {
		// ���ý������ٷֱ�
		_progress->setPercentage(100 - (_progressInterval * _sourceCount));
	}
	else {
		// ProgressFromTo�����Խ����ķ�ʽ��ʾͼƬ 
		// ��һ��������ʾ����0.5�룬�ڶ���������ʾ�������ٷֱȿ�ʼ��������������ʾһֱ��100 
		auto pft = ProgressFromTo::create(0.5f, _progress->getPercentage(), 100);
		//������һ��CallFunc���� 
		auto callFunc = CallFunc::create([=] {
			// ��������Դ��ɣ��ӳ�2 ����ת����Ϸ������ 
			auto delay = DelayTime::create(2);
			auto callFunc = CallFunc::create([] {
				Director::getInstance()->replaceScene(Game::createScene());
			})��
				auto action = Sequence:icreate(delay, callFunc, NULL);
			this->runAction(action);
		});
		auto action = Sequence::create(pft, callFunc, NULL);
		// ������ִ�ж���
		_progress->runAction(action);
	}
}
