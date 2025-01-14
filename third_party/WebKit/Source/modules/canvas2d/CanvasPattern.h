/*
 * Copyright (C) 2006, 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CanvasPattern_h
#define CanvasPattern_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "core/svg/SVGMatrixTearOff.h"
#include "platform/graphics/Pattern.h"
#include "wtf/Forward.h"

namespace blink {

class ExceptionState;
class Image;

class CanvasPattern final : public GarbageCollectedFinalized<CanvasPattern>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static Pattern::RepeatMode parseRepetitionType(const String&, ExceptionState&);

    static CanvasPattern* create(PassRefPtr<Image> image, Pattern::RepeatMode repeat, bool originClean)
    {
        return new CanvasPattern(std::move(image), repeat, originClean);
    }

    Pattern* getPattern() const { return m_pattern.get(); }
    const AffineTransform& getTransform() const { return m_patternTransform; }

    bool originClean() const { return m_originClean; }

    DEFINE_INLINE_TRACE() { }

    void setTransform(SVGMatrixTearOff*);

private:
    CanvasPattern(PassRefPtr<Image>, Pattern::RepeatMode, bool originClean);

    RefPtr<Pattern> m_pattern;
    AffineTransform m_patternTransform;
    bool m_originClean;
};

} // namespace blink

#endif // CanvasPattern_h
