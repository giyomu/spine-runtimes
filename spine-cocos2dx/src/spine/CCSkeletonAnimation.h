/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_CCSKELETONANIMATION_H_
#define SPINE_CCSKELETONANIMATION_H_

#include <spine/spine.h>
#include <spine/CCSkeleton.h>
#include "cocos2d.h"

namespace spine {

class CCSkeletonAnimation;
typedef void (cocos2d::CCObject::*SEL_AnimationStateEvent)(spine::CCSkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
#define animationStateEvent_selector(_SELECTOR) (SEL_AnimationStateEvent)(&_SELECTOR)

/** Draws an animated skeleton, providing an AnimationState for applying one or more animations and queuing animations to be
  * played later. */
class CCSkeletonAnimation: public CCSkeleton {
public:
	spAnimationState* state;

	static CCSkeletonAnimation* createWithData (spSkeletonData* skeletonData);
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	CCSkeletonAnimation (spSkeletonData* skeletonData);
	CCSkeletonAnimation (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	CCSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	virtual ~CCSkeletonAnimation ();

	virtual void update (float deltaTime);

	void setAnimationStateData (spAnimationStateData* stateData);
	void setMix (const char* fromAnimation, const char* toAnimation, float duration);

	void setAnimationListener (CCObject* instance, SEL_AnimationStateEvent method);
	spTrackEntry* setAnimation (int trackIndex, const char* name, bool loop);
	spTrackEntry* addAnimation (int trackIndex, const char* name, bool loop, float delay = 0);
	spTrackEntry* getCurrent (int trackIndex = 0);
	void clearTracks ();
	void clearTrack (int trackIndex = 0);

	virtual void onAnimationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);

protected:
	CCSkeletonAnimation ();

private:
	typedef CCSkeleton super;
	CCObject* listenerInstance;
	SEL_AnimationStateEvent listenerMethod;
	bool ownsAnimationStateData;

	void initialize ();
};

}

#endif /* SPINE_CCSKELETONANIMATION_H_ */
