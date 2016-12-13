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

#include "XTLock.h"

XTMutex::XTMutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
}

XTMutex::~XTMutex()
{
    pthread_mutex_destroy(&mutex);
}

void XTMutex::lock()
{
    pthread_mutex_lock(&mutex);
}

void XTMutex::unlock()
{
    pthread_mutex_unlock(&mutex);
}

XTLock::XTLock(XTMutex& mutex):mutex(mutex)
{
    mutex.lock();
}

XTLock::~XTLock()
{
    mutex.unlock();
}
