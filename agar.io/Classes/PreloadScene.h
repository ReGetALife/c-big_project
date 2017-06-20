#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//Ԥ�����ࣺ���Ԥ���ر������֡���Ч���������׼������
class PreLoad : public cocos2d::Layer {
public:
	/**
	*��̬����������Scene���� 
	* ע�⣺�� Cocos2d - x��û��Cocos2d - iPhone�� �� ��id�� �� ���鷵����ʵ����ָ�� 
	*/
	static cocos2d::Scene* createScene();
	/**
	* init��������ɳ�ʼ�������� 
	* ע�⣺init������Cocos2d - x�з���boolֵ�������Ƿ���Cocos2d - iPhone�� �� ��id��
	*/
	virtual bool init ();
	// ��Node�ڵ���롰��̨��ʱ���� 
	virtual void onEnterTransitionDidFinish(); 
	// ���ر������� 
	void loadMusic(ValueVector musicFiles);
	// ������Ϸ��Ч
	void loadEffect(ValueVector effectFiles);
	// ���ؾ���� 
	void loadSpriteSheets(ValueVector spriteSheets); 
	// ������Ϸ������ void progressUpdate(); 
	void progressUpdate();
	/** 
	*ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(PreLoad);
protected: 
	// ����������Ϸ��Ҫ���ص���Դ���� 
	int _sourceCount; 
	//������
	ProgressTimer* _progress; 
	// ���������µĴ��� 
	float _progressInterval; 
};