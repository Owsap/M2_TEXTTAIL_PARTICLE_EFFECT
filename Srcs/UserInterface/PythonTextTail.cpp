/// 1.
// Search @ void CPythonTextTail::UpdateTextTail
	if (pTextTail->fDistanceFromPlayer < 1300.0f)
	{
		pTextTail->z = 0.0f;
	}
	else
	{
		pTextTail->z = pTextTail->z * CPythonGraphic::Instance().GetOrthoDepth() * -1.0f;
		pTextTail->z += 10.0f;
	}

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	__UpdateParticleEffect(pTextTail);
#endif

/// 2.
// Search
void CPythonTextTail::ArrangeTextTail()

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
void CPythonTextTail::__UpdateParticleEffect(TTextTail* pTextTail)
{
	if (!pTextTail->QueueParticleFrames.empty())
	{
		const std::string& stFileName = pTextTail->QueueParticleFrames.front();
		CResource* pResource = CResourceManager::Instance().GetResourcePointer(stFileName.c_str());
		if (pResource->IsType(CGraphicImage::Type()))
		{
			CGraphicExpandedImageInstance* pImageInstance = CGraphicExpandedImageInstance::New();
			pImageInstance->SetImagePointer(static_cast<CGraphicImage*>(pResource));
			if (pImageInstance->IsEmpty())
			{
				CGraphicExpandedImageInstance::Delete(pImageInstance);
			}
			else
			{
				pImageInstance->SetScale(TEXTTAIL_PARTICLE_FRAME_SCALE, TEXTTAIL_PARTICLE_FRAME_SCALE);
				pTextTail->ParticleInstanceVector.push_back(pImageInstance);
			}
		}
		pTextTail->QueueParticleFrames.pop();
	}

	++pTextTail->bParticleFrameDelay;
	if (pTextTail->bParticleFrameDelay < TEXTTAIL_PARTICLE_FRAME_DELAY)
		return;

	pTextTail->bParticleFrameDelay = 0;

	++pTextTail->bParticleFrame;
	if (pTextTail->bParticleFrame >= pTextTail->ParticleInstanceVector.size())
		pTextTail->bParticleFrame = 0;
}
#endif

/// 3.
// Search @ void CPythonTextTail::ArrangeTextTail
			// Level À§Ä¡ ¾÷µ¥ÀÌÆ®
			CGraphicTextInstance* pLevel = pTextTail->pLevelTextInstance;

// Add above inside the `if (pTitle)`
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
			for (CGraphicExpandedImageInstance* pImage : pTextTail->ParticleInstanceVector)
			{
				int x = pTextTail->x - (iNameWidth / 2) - (iTitleWidth / 2) - 18.0f;
				if (GetDefaultCodePage() == CP_ARABIC)
					x = pTextTail->x - (iNameWidth / 2) - iTitleWidth - 4.0f;
				int y = pTextTail->y - iTitleHeight - 8.5f;

				pImage->SetPosition(x, y);
			}
#endif

// Example:
		// Title À§Ä¡ ¾÷µ¥ÀÌÆ®
		CGraphicTextInstance* pTitle = pTextTail->pTitleTextInstance;
		if (pTitle)
		{
			[ . . . ]

#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
			for (CGraphicExpandedImageInstance* pImage : pTextTail->ParticleInstanceVector)
			{
				int x = pTextTail->x - (iNameWidth / 2) - (iTitleWidth / 2) - 18.0f;
				if (GetDefaultCodePage() == CP_ARABIC)
					x = pTextTail->x - (iNameWidth / 2) - iTitleWidth - 4.0f;
				int y = pTextTail->y - iTitleHeight - 8.5f;

				pImage->SetPosition(x, y);
			}
#endif

			[ . . . ]
		}
		else
		{
			fxAdd = 4.0f;

			// Level À§Ä¡ ¾÷µ¥ÀÌÆ®
			CGraphicTextInstance* pLevel = pTextTail->pLevelTextInstance;
			if (pLevel)
			{
				[ . . . ]
			}
		}

/// 4.
// Search @ CPythonTextTail::Render()
		if (pTextTail->pTitleTextInstance)
			pTextTail->pTitleTextInstance->Render();

// Replace with
		if (pTextTail->pTitleTextInstance)
		{
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
			if (pTextTail->bParticleFrame < pTextTail->ParticleInstanceVector.size())
			{
				CGraphicExpandedImageInstance* pImage = pTextTail->ParticleInstanceVector[pTextTail->bParticleFrame];
				pImage->Render();
			}
#endif
			pTextTail->pTitleTextInstance->Render();
		}

/// 5.
// Search @ void CPythonTextTail::RegisterCharacterTextTail
	CGraphicTextInstance* pTextInstance = pTextTail->pTextInstance;
	pTextInstance->SetOutline(true);
	pTextInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	pTextTail->ParticleInstanceVector.clear();
	pTextTail->QueueParticleFrames = {};
	pTextTail->bParticleFrame = 0;
	pTextTail->bParticleFrameDelay = 0;
#endif

/// 6.
// Search @ void CPythonTextTail::RegisterCharacterTextTail
	m_CharacterTextTailMap.insert(TTextTailMap::value_type(dwVirtualID, pTextTail));

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	pTextTail->QueueParticleFrames = {};
	char szFrameFileName[256];
	for (int i = 0; i < TEXTTAIL_PARTICLE_FRAMES - 1; ++i)
	{
		snprintf(szFrameFileName, sizeof(szFrameFileName), "d:/ymir work/ui/texttail/effect/frame_%03d.png", i);
		pTextTail->QueueParticleFrames.emplace(szFrameFileName);
	}
#endif
