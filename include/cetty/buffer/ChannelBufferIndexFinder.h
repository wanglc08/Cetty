#if !defined(CETTY_BUFFER_CHANNELBUFFERINDEXFINDER_H)
#define CETTY_BUFFER_CHANNELBUFFERINDEXFINDER_H

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

namespace cetty { namespace buffer {

class ChannelBuffer;

/**
 * Locates an index of data in a {@link ChannelBuffer}.
 * <p>
 * This interface enables the sequential search for the data which meets more
 * complex and dynamic condition than just a simple value matching.  Please
 * refer to {@link ChannelBuffer#indexOf(int, int, ChannelBufferIndexFinder)} and
 * {@link ChannelBuffer#bytesBefore(int, int, ChannelBufferIndexFinder)}
 * for more explanation.
 *
 * 
 * @author <a href="http://gleamynode.net/">Trustin Lee</a>
 *
 * @author <a href="mailto:frankee.zhou@gmail.com">Frankee Zhou</a>
 *
 * @apiviz.uses org.jboss.netty.buffer.ChannelBuffer
 */

class ChannelBufferIndexFinder {
public:
    virtual ~ChannelBufferIndexFinder() {}

    /**
     * Returns <tt>true</tt> if and only if the data is found at the specified
     * <tt>guessedIndex</tt> of the specified <tt>buffer</tt>.
     * <p>
     * The implementation should not perform an operation which raises an
     * exception such as {@link RangeException} nor perform
     * an operation which modifies the content of the buffer.
     */
    virtual bool find(const ChannelBuffer& buffer, int guessedIndex) const = 0;

    /**
     * Index finder which locates a <tt>NUL (0x00)</tt> byte.
     */
    static const ChannelBufferIndexFinder& NUL;

    /**
     * Index finder which locates a non-<tt>NUL (0x00)</tt> byte.
     */
    static const ChannelBufferIndexFinder& NOT_NUL;
    /**
     * Index finder which locates a <tt>CR ('\r')</tt> byte.
     */
    static const ChannelBufferIndexFinder& CR;

    /**
     * Index finder which locates a non-<tt>CR ('\r')</tt> byte.
     */
    static const ChannelBufferIndexFinder& NOT_CR;

    /**
     * Index finder which locates a <tt>LF ('\n')</tt> byte.
     */
    static const ChannelBufferIndexFinder& LF;

    /**
     * Index finder which locates a non-<tt>LF ('\n')</tt> byte.
     */
    static const ChannelBufferIndexFinder& NOT_LF;
    /**
     * Index finder which locates a <tt>CR ('\r')</tt> or <tt>LF ('\n')</tt>.
     */
    static const ChannelBufferIndexFinder& CRLF;

    /**
     * Index finder which locates a byte which is neither a <tt>CR ('\r')</tt>
     * nor a <tt>LF ('\n')</tt>.
     */
    static const ChannelBufferIndexFinder& NOT_CRLF;

    /**
     * Index finder which locates a linear whitespace
     * (<tt>' '</tt> and <tt>'\t'</tt>).
     */
    static const ChannelBufferIndexFinder& LINEAR_WHITESPACE;

    /**
     * Index finder which locates a byte which is not a linear whitespace
     * (neither <tt>' '</tt> nor <tt>'\t'</tt>).
     */
    static const ChannelBufferIndexFinder& NOT_LINEAR_WHITESPACE;
};

}}


#endif //#if !defined(CETTY_BUFFER_CHANNELBUFFERINDEXFINDER_H)
