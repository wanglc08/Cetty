#if !defined(CETTY_UTIL_CHARSET_H)
#define CETTY_UTIL_CHARSET_H

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

#include <string>

namespace cetty { namespace util {

class Charset {
public:
    Charset() {};
    ~Charset() {};

    static Charset forName(const std::string& charsetName) {
        return Charset();
    }
    static bool isSupported(const std::string& charsetName) {
        return false;
    }

public:
    bool canEncode() const;
    std::string name() const;
    std::string displayName() const;

    bool equals(const Charset& charset);
    int  compareTo(const Charset& charset);
};

}}

#endif //#if !defined(CETTY_UTIL_CHARSET_H)
