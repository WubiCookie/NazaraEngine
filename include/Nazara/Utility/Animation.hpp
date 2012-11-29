// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_ANIMATION_HPP
#define NAZARA_ANIMATION_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/Resource.hpp>
#include <Nazara/Core/ResourceLoader.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Utility/Enums.hpp>
#include <Nazara/Utility/Sequence.hpp>

struct NAZARA_API NzAnimationParams
{
	unsigned int endFrame = static_cast<unsigned int>(-1);
	unsigned int startFrame = 0;

	bool IsValid() const;
};

class NzAnimation;
class NzSkeleton;

using NzAnimationLoader = NzResourceLoader<NzAnimation, NzAnimationParams>;

struct NzAnimationImpl;

class NAZARA_API NzAnimation : public NzResource
{
	friend NzAnimationLoader;

	public:
		NzAnimation() = default;
		~NzAnimation();

		bool AddSequence(const NzSequence& sequence);
		void AnimateSkeleton(NzSkeleton* targetSkeleton, unsigned int frameA, unsigned int frameB, float interpolation) const;

		bool CreateKeyframe(unsigned int frameCount);
		bool CreateSkeletal(unsigned int frameCount, unsigned int jointCount);
		void Destroy();

		unsigned int GetFrameCount() const;
		unsigned int GetJointCount() const;
		NzSequence* GetSequence(const NzString& sequenceName);
		NzSequence* GetSequence(unsigned int index);
		const NzSequence* GetSequence(const NzString& sequenceName) const;
		const NzSequence* GetSequence(unsigned int index) const;
		unsigned int GetSequenceCount() const;
		int GetSequenceIndex(const NzString& sequenceName) const;
		NzSequenceJoint* GetSequenceJoints(unsigned int frameIndex = 0);
		const NzSequenceJoint* GetSequenceJoints(unsigned int frameIndex = 0) const;
		nzAnimationType GetType() const;

		bool HasSequence(const NzString& sequenceName) const;
		bool HasSequence(unsigned int index = 0) const;

		bool IsValid() const;

		bool LoadFromFile(const NzString& filePath, const NzAnimationParams& params = NzAnimationParams());
		bool LoadFromMemory(const void* data, std::size_t size, const NzAnimationParams& params = NzAnimationParams());
		bool LoadFromStream(NzInputStream& stream, const NzAnimationParams& params = NzAnimationParams());

		void RemoveSequence(const NzString& sequenceName);
		void RemoveSequence(unsigned int index);

	private:
		NzAnimationImpl* m_impl = nullptr;

		static NzAnimationLoader::LoaderList s_loaders;
};

#endif // NAZARA_ANIMATION_HPP
