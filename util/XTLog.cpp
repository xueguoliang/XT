/*
 * Copyright 2016 xueguoliang(xueguoliang@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "XTLog.h"

XTLog::XTLog()
{
    _level = XTLogV;
}

XTLog *XTLog::instance()
{
    static XTLog* theOne = new XTLog;
    return theOne;
}

void XTLog::print(int level, const char *fmt, va_list ap)
{
    if(level > this->_level)
        return;
    vprintf(fmt, ap);
}
