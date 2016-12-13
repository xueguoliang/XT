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

#ifndef XTCTPMD_H
#define XTCTPMD_H

#include "XTThread.h"
#include "XTCTPDef.h"

class XTCtpMd : public XTThread, public CThostFtdcMdSpi
{
public:
    XTCtpMd(string filePath,
            string frontAddr,
            string brokenId,
            string username,
            string password);

    void subscribe(char* instrumentIDs[], int count);

private:
    void run();
    void OnFrontConnected();
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                            CThostFtdcRspInfoField *pRspInfo,
                            int nRequestID,
                            bool bIsLast);
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    CThostFtdcMdApi* api;
    pthread_t tid;

    string filePath;
    string frontAddr;
    string brokenId;
    string username;
    string password;
    int reqId;
};

#endif // XTCTPMD_H
