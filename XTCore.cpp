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

#include "XTCore.h"

XTCore::XTCore():timers(XTTimer::compare, 32)
{
    epollfd = epoll_create(1024);
    initCtpMD();
}

void XTCore::run()
{
    int count = 8;
    struct epoll_event* ev = new struct epoll_event[count];
    int ret;
    while(1)
    {
        ret = epoll_wait(epollfd, ev, count, checkTimer());

        if(ret > 0)
        {
            for(int i=0; i<ret; ++i)
            {
                XTThread* th = (XTThread*)ev[i].data.ptr;

                if(th->type == XTThread::XTT_CTP_MD)
                {
                    th->mainGetToken();
                    // md has data, take it

                    XTI("1\n");
                    XTV("ctp md has data\n");

                    // let MD thread get more data
                    th->mainSetToken();
                }
            }
        }
    }
}

XTTimer* XTCore::addTimer(uint32_t period, void (*cbk)(XTTimer *))
{
    XTTimer* timer = new XTTimer;
    timer->cbk = cbk;
    timer->expire = XTTimer::getCurrentTime() + period;

    XTLock lock(timerMutex);
    timers.add(timer);
    return timer;
}

XTCore *XTCore::instance()
{
    static XTCore* theOne = new XTCore;
    return theOne;
}

void XTCore::subscribe(vector<string> instrumentIDs)
{
#if 1
    int count = instrumentIDs.size();
    XTI("count is %d\n", count);
    char** ids = new char*[count];
    for(int i=0;i <count; ++i)
    {
        ids[i] = strdup(instrumentIDs[i].c_str());
    }

    this->ctpMD->subscribe(ids, count);
    for(int i=0;i <count; ++i)
    {
        free(ids[i]);
    }
    delete []ids;
#else
    char* ids[1024];
    memset(ids, 0, sizeof(ids));

    int count = instrumentIDs.size();
    for(int i=0; i<count; ++i)
    {
        XTI("1\n");
        ids[i] = strdup(instrumentIDs.at(i).c_str());
    }

    XTI("2\n");
    this->ctpMD->subscribe(ids, count);

    XTI("3\n");
    for(int i=0;i <count; ++i)
    {
        XTI("4\n");
        free(ids[i]);
    }
#endif

}

void XTCore::initCtpMD()
{
    ctpMD = new XTCtpMd("test",
                        "tcp://180.168.146.187:10010",
                        "9999",
                        "13381285235",
                        "123456");
    int fd = ctpMD->start();
    ctpMD->mainGetToken();

    struct epoll_event ev;
    ev.data.ptr = ctpMD;
    ev.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    ctpMD->mainSetToken();
}

uint32_t XTCore::checkTimer()
{
    XTLock lock(timerMutex);
    while(!timers.empty())
    {
        uint64_t now = XTTimer::getCurrentTime();
        XTTimer* timer = timers.at(0);
        if(timer->expire < now)
        {
            timer->handle();
            timers.del();
            delete timer;
        }
        else
        {
            return timer->expire - now;
        }
    }
    return 60000;
}



