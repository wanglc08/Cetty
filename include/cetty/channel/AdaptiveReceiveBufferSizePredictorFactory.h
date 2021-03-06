#if !defined(CETTY_CHANNEL_ADAPTIVERECEIVEBUFFERSIZEPREDICTORFACTORY_H)
#define CETTY_CHANNEL_ADAPTIVERECEIVEBUFFERSIZEPREDICTORFACTORY_H

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

#include "cetty/channel/ReceiveBufferSizePredictorFactory.h"
#include "cetty/channel/AdaptiveReceiveBufferSizePredictor.h"
#include "cetty/util/Exception.h"

namespace cetty { namespace channel {

using namespace cetty::util;

/**
 * The {@link ReceiveBufferSizePredictorFactory} that creates a new
 * {@link AdaptiveReceiveBufferSizePredictor}.
 *
 * 
 * @author <a href="http://gleamynode.net/">Trustin Lee</a>
 * @author <a href="mailto:frankee.zhou@gmail.com">Frankee Zhou</a>
 */

class AdaptiveReceiveBufferSizePredictorFactory : public ReceiveBufferSizePredictorFactory {
public:
    /**
     * Creates a new factory with the default parameters.  With the default
     * parameters, the expected buffer size starts from <tt>1024</tt>, does not
     * go down below <tt>64</tt>, and does not go up above <tt>65536</tt>.
     */
    AdaptiveReceiveBufferSizePredictorFactory()
        : minimum(AdaptiveReceiveBufferSizePredictor::DEFAULT_MINIMUM),
          initial(AdaptiveReceiveBufferSizePredictor::DEFAULT_INITIAL),
          maximum(AdaptiveReceiveBufferSizePredictor::DEFAULT_MAXIMUM) {
    }

    /**
     * Creates a new factory with the specified parameters.
     *
     * @param minimum  the inclusive lower bound of the expected buffer size
     * @param initial  the initial buffer size when no feed back was received
     * @param maximum  the inclusive upper bound of the expected buffer size
     */
    AdaptiveReceiveBufferSizePredictorFactory(int minimum, int initial, int maximum)
        : minimum(minimum), initial(initial), maximum(maximum) {
        if (minimum <= 0) {
            throw InvalidArgumentException("minimum is less than zero.");
        }
        if (initial < minimum) {
            throw InvalidArgumentException("initial is less than zero.");
        }
        if (maximum < initial) {
            throw InvalidArgumentException("maximum is less than zero.");
        }
    }

    virtual ~AdaptiveReceiveBufferSizePredictorFactory() {}

    virtual ReceiveBufferSizePredictor* getPredictor() {
        return new AdaptiveReceiveBufferSizePredictor(minimum, initial, maximum);
    }

private:
    int minimum;
    int initial;
    int maximum;
};
}}

#endif //#if !defined(CETTY_CHANNEL_ADAPTIVERECEIVEBUFFERSIZEPREDICTORFACTORY_H)
