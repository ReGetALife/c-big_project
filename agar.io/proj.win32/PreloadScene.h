#ifndef __Game__SGPlayMusic__  
#define __Game__SGPlayMusic__  

#include <iostream>  
#include "SimpleAudioEngine.h"  
#include "cocos2d.h"  
using namespace cocos2d;
using namespace CocosDenshion;

class SGPlayMusic
{
private:
	float m_nMusicVolume;
	float m_nEffectVolume;

public:
	SGPlayMusic();
	~SGPlayMusic();
	static SGPlayMusic *sharePlayMusic();

	//��������  
	void playerMusicByType(const char* musicName);
	//ֹͣ����  
	void stopMusic();
	//�ı���������  
	void setVolume(float volume);
	//��ͣ��������  
	void pauseMusic();
	//���²��ű�������  
	void rewindMusic();

	//������Ч  
	void playEffectByType(bool isLoop, const char *effectName);
	//ֹͣ��Ч  
	void stopEffect();
	//�ı���Ч����  
	void setEffectVolume(float volume);
	//ֹͣĳ����Ч  
	void stopEffect(unsigned int effectId);
	//���²�����Ч  
	void rewindEffect(unsigned int effectId);

};
#endif 
