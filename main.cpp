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

void cbk(XTTimer* timer)
{
    XTI("expire is %llu\n", timer->expire);
}

int main(int argc, char* argv[])
{
 //   XTTimer::addTimer(10000, cbk);
 //   XTTimer::addTimer(1000, cbk);
  //  XTTimer::addTimer(2000, cbk);
    vector<string> ids;
    ids.push_back("ag1612");
    XTCore::instance()->subscribe(ids);
    XTCore::instance()->run();
    return 0;
}
