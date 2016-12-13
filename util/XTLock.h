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

#ifndef XTLOCK_H
#define XTLOCK_H

#include <pthread.h>

class XTMutex
{
public:
    XTMutex();
    ~XTMutex();

    void lock();
    void unlock();
private:
    pthread_mutex_t mutex;
};

class XTLock
{
public:
    XTLock(XTMutex& mutex);
    ~XTLock();
private:
    XTMutex& mutex;
};



#endif // XTLOCK_H
