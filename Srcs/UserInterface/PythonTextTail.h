/// 1.
// Search @ typedef struct STextTail
		CGraphicTextInstance* pTitleTextInstance;
		CGraphicTextInstance* pLevelTextInstance;

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
		bool bParticleEffect;
		std::vector<CGraphicExpandedImageInstance*> ParticleInstanceVector;
		std::queue<std::string> QueueParticleFrames;
		BYTE bParticleFrameDelay;
		BYTE bParticleFrame;
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
		bool bRandomTitleColor;
#if defined(TEXTTAIL_RANDOM_TITLE_COLOR_BY_ORDER)
		BYTE bRandomTitleColorIndex;
#endif
		BYTE bRandomTitleColorDelay;
		float fRandomTitleColorAlpha;
		bool bRandomTitleColorAlphaReverse;
#endif
#endif

/// 2.
// Search
protected:
	TTextTailMap m_CharacterTextTailMap;

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
private:
	void __UpdateParticleEffect(TTextTail* pTextTail);
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
	void __UpdateRandomTitleColor(TTextTail* pTextTail);
#endif
#endif
