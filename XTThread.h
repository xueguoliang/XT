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

#ifndef XTTHREAD_H
#define XTTHREAD_H

#include "XTDef.h"

class XTThread
{
public:

    enum XTThreadType{XTT_CTP_MD, XTT_HANDLE, XTT_NETWORK} type;

    XTThread(XTThreadType type);

    void mainSetToken(char token = 0);
    char mainGetToken();
    void thisSetToken(char token = 0);
    char thisGetToken();

    virtual int start();
    virtual void run();
    void join();

protected:
    static void* threadFunc(void* ptr);
    pthread_t tid;
    int fd[2];
};

#endif // XTTHREAD_H
