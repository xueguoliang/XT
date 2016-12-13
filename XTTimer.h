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

#ifndef XTTIMER_H
#define XTTIMER_H

#include "XTDef.h"

class XTTimer
{
    friend class XTCore;
public:
    static uint64_t getCurrentTime();
    static XTTimer* addTimer(uint32_t period, void (*cbk)(XTTimer*));
    static void killTimer(XTTimer* timer);

    uint64_t expire;

private:
    XTTimer();
    ~XTTimer();
    bool killFlag;
    void (*cbk)(XTTimer*);
    static int compare(XTTimer*, XTTimer*);
    void kill();
    void handle();
};

#endif // XTTIMER_H
