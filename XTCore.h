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

#ifndef XTCORE_H
#define XTCORE_H

#include "XTDef.h"
#include "XTTimer.h"
#include "util/XTHeap.h"
#include "ctp/XTCtpMd.h"
#include "util/XTLock.h"

/*
1. 保存已经订阅的合约信息
2. 每个合约保存关心它这个合约的线程
3. 线程有处理队列和接收队列，如果这个线程在停止状态，那么将数据发送到它的正在工作队列，然后唤醒它
4. 保存其他线程，比如CTP MD线程，LTS MD线程等等，这些线程是产生合约数据的线程
5. 定时器需要的锁
6. 对象池需要的锁(是否需要对象池？)
*/

class XTCore
{
    friend class XTTimer;
public:
    void run();
    static XTCore* instance();
    void subscribe(vector<string> instrumentIDs);

protected:
    XTCore();
    uint32_t checkTimer();
    XTTimer* addTimer(uint32_t period, void (*cbk)(XTTimer*));
    void initCtpMD();
    XTCtpMd* ctpMD;

    int epollfd;

    XTMutex timerMutex;
    XTHeap<XTTimer> timers;
};

#endif // XTCORE_H
