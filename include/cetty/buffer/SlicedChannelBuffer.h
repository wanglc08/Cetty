#if !defined(CETTY_BUFFER_SLICEDCHANNELBUFFER_H)
#define CETTY_BUFFER_SLICEDCHANNELBUFFER_H

/*
 * Copyright 2009 Red Hat, Inc.
 *
 * Red Hat licenses this file to you under the Apache License, version 2.0
 * (the "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at:
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (c) 2010-2011 frankee zhou (frankee.zhou at gmail dot com)
 * Distributed under under the Apache License, version 2.0 (the "License").
 */

#include "cetty/buffer/AbstractChannelBuffer.h"
#include "cetty/buffer/WrappedChannelBuffer.h"

namespace cetty { namespace buffer {

/**
 * A derived buffer which exposes its parent's sub-region only.  It is
 * recommended to use {@link ChannelBuffer#slice()} and
 * {@link ChannelBuffer#slice(int, int)} instead of calling the constructor
 * explicitly.
 *
 *
 * @author <a href="http://gleamynode.net/">Trustin Lee</a>
 *
 * @author <a href="mailto:frankee.zhou@gmail.com">Frankee Zhou</a>
 *
 */

class SlicedChannelBuffer : public AbstractChannelBuffer, public WrappedChannelBuffer {
public:
    SlicedChannelBuffer(const ChannelBufferPtr& buffer,
                        int index,
                        int length);

    virtual ~SlicedChannelBuffer() {}

    virtual ChannelBufferPtr& unwrap() {
        return buffer;
    }

    virtual ChannelBufferFactory& factory() const {
        return buffer->factory();
    }

    virtual ByteOrder order() const {
        return buffer->order();
    }

    virtual int capacity() const {
        return length;
    }

    virtual void readableBytes(Array& array) {}
    virtual void writableBytes(Array& array) {}

    virtual bool hasArray() const {
        return buffer->hasArray();
    }

    virtual const Array& array() {
        return buffer->array();
    }
    virtual ConstArray array() const {
        return buffer->array();
    }

    virtual int arrayOffset() const {
        return buffer->arrayOffset() + adjustment;
    }

    virtual boost::int8_t  getByte(int index) const;
    virtual boost::int16_t getShort(int index) const;
    virtual boost::int32_t getUnsignedMedium(int index) const;
    virtual boost::int32_t getInt(int index) const;
    virtual boost::int64_t getLong(int index) const;

    virtual ChannelBufferPtr duplicate();
    virtual ChannelBufferPtr copy(int index, int length) const;
    virtual ChannelBufferPtr slice(int index, int length);
    virtual void slice(Array& array) {}

    virtual void getBytes(int index, ChannelBuffer& dst, int dstIndex, int length) const;
    virtual void getBytes(int index, const Array& dst, int dstIndex, int length) const;
    virtual void getBytes(int index, OutputStream& out, int length) const;

    virtual void setByte(int index, int value);
    virtual void setShort(int index, int value);
    virtual void setMedium(int index, int value);
    virtual void setInt(int index, int value);
    virtual void setLong(int index, boost::int64_t value);

    virtual void setBytes(int index, const ConstArray& src, int srcIndex, int length);
    virtual void setBytes(int index, const ChannelBuffer& src, int srcIndex, int length);
    virtual int  setBytes(int index, InputStream& in, int length);

    virtual void readSlice(Array& array){}
    virtual void readSlice(GatheringBuffer& gathering){}

private:
    void checkIndex(int index) const;
    void checkIndex(int startIndex, int length) const;

private:
    ChannelBufferPtr buffer;
    int length;
    int adjustment;
};

}}

#endif //#if !defined(CETTY_BUFFER_SLICEDCHANNELBUFFER_H)
