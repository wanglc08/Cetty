/*
 * Copyright (c) 2010-2011 frankee zhou (frankee.zhou at gmail dot com)
 *
 * Distributed under under the Apache License, version 2.0 (the "License").
 * you may not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "cetty/channel/AdaptiveReceiveBufferSizePredictor.h"
#include "cetty/util/Exception.h"

namespace cetty { namespace channel {

using namespace cetty::util;

int AdaptiveReceiveBufferSizePredictor::SIZE_TABLE[SIZE_TABLE_CNT] = {0};

AdaptiveReceiveBufferSizePredictor::AdaptiveReceiveBufferSizePredictor() {
    init(DEFAULT_MINIMUM, DEFAULT_INITIAL, DEFAULT_MAXIMUM);
}

AdaptiveReceiveBufferSizePredictor::AdaptiveReceiveBufferSizePredictor(int minimum, int initial, int maximum) {
    if (minimum <= 0) {
        throw InvalidArgumentException("minimum is less than zero.");
    }
    if (initial < minimum) {
        throw InvalidArgumentException("initial is less than zero.");
    }
    if (maximum < initial) {
        throw InvalidArgumentException("maximum is less than zero.");
    }
    init(minimum, initial, maximum);
}

void AdaptiveReceiveBufferSizePredictor::previousReceiveBufferSize(int previousReceiveBufferSize) {
    if (previousReceiveBufferSize <= SIZE_TABLE[std::max(0, index - INDEX_DECREMENT - 1)]) {
        if (decreaseNow) {
            index = std::max(index - INDEX_DECREMENT, minIndex);
            nextReceiveBuffSz = SIZE_TABLE[index];
            decreaseNow = false;
        }
        else {
            decreaseNow = true;
        }
    }
    else if (previousReceiveBufferSize >= nextReceiveBuffSz) {
        index = std::min(index + INDEX_INCREMENT, maxIndex);
        nextReceiveBuffSz = SIZE_TABLE[index];
        decreaseNow = false;
    }
}

void AdaptiveReceiveBufferSizePredictor::init(int minimum, int initial, int maximum) {
    initSizeTable();

    int minIndex = getSizeTableIndex(minimum);
    if (SIZE_TABLE[minIndex] < minimum) {
        this->minIndex = minIndex + 1;
    } else {
        this->minIndex = minIndex;
    }

    int maxIndex = getSizeTableIndex(maximum);
    if (SIZE_TABLE[maxIndex] > maximum) {
        this->maxIndex = maxIndex - 1;
    } else {
        this->maxIndex = maxIndex;
    }

    index = getSizeTableIndex(initial);
    nextReceiveBuffSz = SIZE_TABLE[index];
}

void AdaptiveReceiveBufferSizePredictor::initSizeTable() {
    static bool isInited = false;
    if (isInited) return;

    std::vector<int> sizeTable;
    for (int i = 1; i <= 8; i ++) {
        sizeTable.push_back(i);
    }

    for (int i = 4; i < 32; i ++) {
        long v = 1L << i;
        long inc = v >> 4;
        v -= inc << 3;

        for (int j = 0; j < 8; j ++) {
            v += inc;
            if (v >= 0xefffffff) {
                sizeTable.push_back(0xefffffff);
            }
            else {
                sizeTable.push_back(v);
            }
        }
    }

    for (int i = 0; i < SIZE_TABLE_CNT; ++i) {
        SIZE_TABLE[i] = sizeTable.at(i);
    }

    isInited = true;
}

int AdaptiveReceiveBufferSizePredictor::getSizeTableIndex(int size) {
    if (size <= 16) {
        return size - 1;
    }

    int bits = 0;
    int v = size;
    do {
        //v >>>= 1; //TODO
        v >>= 1;
        bits ++;
    } while (v != 0);

    int baseIdx = bits << 3;
    int startIdx = baseIdx - 18;
    int endIdx = baseIdx - 25;

    for (int i = startIdx; i >= endIdx; --i) {
        if (size >= SIZE_TABLE[i]) {
            return i;
        }
    }

    throw RuntimeException("shouldn't reach here; please file a bug report.");
}


}}