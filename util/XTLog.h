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

#ifndef XTLOG_H
#define XTLOG_H

#include <stdio.h>
#include <stdarg.h>

#define XTLogV 0x7f
#define XTLogI 0x3f
#define XTLogW 0x2f
#define XTLogE 0x1f

// All or None
#define XTLogN 0
#define XTLogA 0x7fffffff

class XTLog
{
public:
    XTLog();
    static XTLog* instance();
    void print(int level, const char* fmt, va_list ap);

    int _level;
};

static inline void __XTLog(int level, const char* file, int line, const char* fmt, ...)
{
    // thread safe
    thread_local static char newfmt[4096];
    sprintf(newfmt, "%s %d: %s", file, line, fmt);
    va_list ap;
    va_start(ap, fmt);
    XTLog::instance()->print(level, newfmt, ap);
    va_end(ap);
}

#define XTPrint(level, fmt, ...) __XTLog(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define XTE(fmt, ...) XTPrint(XTLogE, fmt, ##__VA_ARGS__)
#define XTW(fmt, ...) XTPrint(XTLogW, fmt, ##__VA_ARGS__)
#define XTI(fmt, ...) XTPrint(XTLogI, fmt, ##__VA_ARGS__)
#define XTV(fmt, ...) XTPrint(XTLogV, fmt, ##__VA_ARGS__)

#endif // XTLOG_H
