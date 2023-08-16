/// 1.
// Search @ typedef struct STextTail
		CGraphicTextInstance* pTitleTextInstance;
		CGraphicTextInstance* pLevelTextInstance;

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
		std::vector<CGraphicExpandedImageInstance*> ParticleInstanceVector;
		std::queue<std::string> QueueParticleFrames;
		BYTE bParticleFrameDelay;
		BYTE bParticleFrame;
#endif

/// 2.
// Search
protected:
	TTextTailMap m_CharacterTextTailMap;

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
private:
	void __UpdateParticleEffect(TTextTail* pTextTail);
#endif
