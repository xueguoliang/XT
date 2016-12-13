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

#include "XTThread.h"

XTThread::XTThread(XTThreadType t):type(t)
{
    XTI("type is %d\n", type);
}

void XTThread::mainSetToken(char token)
{
    send(fd[0], &token, 1, 0);
}

char XTThread::mainGetToken()
{
    char token;
    recv(fd[0], &token, 1, 0);
    return token;
}

void XTThread::thisSetToken(char token)
{
    send(fd[1], &token, 1, 0);
}

char XTThread::thisGetToken()
{
    char token;
    recv(fd[1], &token, 1, 0);
    return token;
}

int XTThread::start()
{
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, fd) < 0)
    {
        XTE("error create socketpair\n");
        exit(1);
    }
    pthread_create(&tid, NULL, threadFunc, this);
    return fd[0];
}



void XTThread::run()
{

}

void XTThread::join()
{
    pthread_join(tid, NULL);
}

void *XTThread::threadFunc(void *ptr)
{
    XTThread* This = (XTThread*)ptr;
    This->run();
    return NULL;
}
