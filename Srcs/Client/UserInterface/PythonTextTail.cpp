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
	if (pTextTail->bParticleEffect)
		__UpdateParticleEffect(pTextTail);

#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
	if (pTextTail->bRandomTitleColor)
		__UpdateRandomTitleColor(pTextTail);
#endif
#endif

/// 2.
// Search
void CPythonTextTail::ArrangeTextTail()

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
void CPythonTextTail::__UpdateParticleEffect(TTextTail* pTextTail)
{
	if (pTextTail == nullptr)
		return;

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

#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
#include <random>
#define rgb(r, g, b) D3DXCOLOR(r, g, b, 1.0f)

void CPythonTextTail::__UpdateRandomTitleColor(TTextTail* pTextTail)
{
	if (pTextTail == nullptr)
		return;

	if (!pTextTail->pTitleTextInstance)
		return;

	++pTextTail->bRandomTitleColorDelay;
	if (pTextTail->bRandomTitleColorDelay < TEXTTAIL_RANDOM_TITLE_COLOR_DELAY)
		return;

	pTextTail->bRandomTitleColorDelay = 0;

	std::vector<D3DXCOLOR> vTitleColor
	{
		/* blue tones */ rgb(100, 149, 237), rgb(137, 207, 240), rgb(135, 206, 235), rgb(125, 249, 255), rgb(0, 255, 255)
	};

#if defined(TEXTTAIL_RANDOM_TITLE_COLOR_BY_ORDER)
	const std::size_t nVecSize = vTitleColor.size() - 1;
	if (pTextTail->bRandomTitleColorIndex >= nVecSize)
		pTextTail->bRandomTitleColorIndex = 0;
	pTextTail->bRandomTitleColorIndex += 1;

	const D3DXCOLOR& kColor = vTitleColor[pTextTail->bRandomTitleColorIndex];
#else
	static std::random_device RandomDevice;
	static std::mt19937 Generate(RandomDevice());
	static std::uniform_real_distribution<> Distribute(0, vTitleColor.size() - 1);

	const D3DXCOLOR& kColor = vTitleColor[Distribute(Generate)];
#endif

	if (pTextTail->bRandomTitleColorAlphaReverse)
	{
		if (pTextTail->fRandomTitleColorAlpha >= 1.0f)
		{
			pTextTail->fRandomTitleColorAlpha = 1.0f;
			pTextTail->bRandomTitleColorAlphaReverse = false;
		}
		pTextTail->fRandomTitleColorAlpha += 0.1f;
	}
	else
	{
		if (pTextTail->fRandomTitleColorAlpha <= 0.3f)
		{
			pTextTail->fRandomTitleColorAlpha = 0.3f;
			pTextTail->bRandomTitleColorAlphaReverse = true;
		}
		pTextTail->fRandomTitleColorAlpha -= 0.1f;
	}

	pTextTail->pTitleTextInstance->SetColor(kColor.r, kColor.g, kColor.b, pTextTail->fRandomTitleColorAlpha);
}
#endif
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
			if (pTextTail->bParticleEffect && pTextTail->bParticleFrame < pTextTail->ParticleInstanceVector.size())
			{
				CGraphicExpandedImageInstance* pImage = pTextTail->ParticleInstanceVector[pTextTail->bParticleFrame];
				pImage->Render();
			}
#endif
			pTextTail->pTitleTextInstance->Render();
		}

/// 5.
// Search @ void CPythonTextTail::ShowCharacterTextTail
	if (pInstance->CanPickInstance())
		m_CharacterTextTailList.push_back(pTextTail);

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	switch (pInstance->GetAlignmentGrade())
	{
		case 0:
		{
			pTextTail->bParticleEffect = true;
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
			pTextTail->bRandomTitleColor = true;
#endif
		}
		break;

		default:
		{
			pTextTail->bParticleEffect = false;
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
			pTextTail->bRandomTitleColor = false;
#endif
		}
		break;
	}
#endif

/// 6.
// Search @ void CPythonTextTail::RegisterCharacterTextTail
	CGraphicTextInstance* pTextInstance = pTextTail->pTextInstance;
	pTextInstance->SetOutline(true);
	pTextInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);

// Add below
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	pTextTail->bParticleEffect = false;
	pTextTail->ParticleInstanceVector.clear();
	pTextTail->QueueParticleFrames = {};
	pTextTail->bParticleFrame = 0;
	pTextTail->bParticleFrameDelay = 0;
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
	pTextTail->bRandomTitleColor = false;
#if defined(TEXTTAIL_RANDOM_TITLE_COLOR_BY_ORDER)
	pTextTail->bRandomTitleColorIndex = 0;
#endif
	pTextTail->bRandomTitleColorDelay = 0;
	pTextTail->fRandomTitleColorAlpha = 1.0f;
	pTextTail->bRandomTitleColorAlphaReverse = false;
#endif
#endif

/// 6.
// Search @ void CPythonTextTail::RegisterCharacterTextTail
	m_CharacterTextTailMap.insert(TTextTailMap::value_type(dwVirtualID, pTextTail));

// Add above
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
	char szFrameFileName[256];
	for (int i = 0; i < TEXTTAIL_PARTICLE_FRAMES - 1; ++i)
	{
		snprintf(szFrameFileName, sizeof(szFrameFileName), "d:/ymir work/ui/texttail/effect/frame_%03d.png", i);
		pTextTail->QueueParticleFrames.emplace(szFrameFileName);
	}
#endif
