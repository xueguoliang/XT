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

#include "XTCtpMd.h"

XTCtpMd::XTCtpMd(string filePath,
                 string frontAddr,
                 string brokenId,
                 string username,
                 string password):
    XTThread(XTT_CTP_MD),
    filePath(filePath),
    frontAddr(frontAddr),
    brokenId(brokenId),
    username(username),
    password(password),
    reqId(0)
{

}

void XTCtpMd::subscribe(char *instrumentIDs[], int count)
{
    XTI("4\n");
    api->SubscribeMarketData(instrumentIDs, count);
    XTI("5\n");
}

void XTCtpMd::run()
{
    XTV("run ....\n");
    api = CThostFtdcMdApi::CreateFtdcMdApi(filePath.c_str());

    api->RegisterSpi(this);
    // a little memory leak
    api->RegisterFront(strdup(frontAddr.data()));
    api->Init();
    api->Join(); // wait for
}

void XTCtpMd::OnFrontConnected()
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, brokenId.c_str());
    strcpy(req.UserID, username.c_str());
    strcpy(req.Password, password.c_str());
    int ret = api->ReqUserLogin(&req, ++reqId);
    if(ret < 0)
    {
        XTI("login ret=%d\n", ret);
    }
    else
    {
        XTI("%s", "login ok\n");
    }

    thisSetToken();
}

void XTCtpMd::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                 CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID, bool bIsLast)
{
    XTI("OnRspSubMarketData: %s, %d\n", pRspInfo->ErrorMsg, nRequestID);
}

#if 0
struct CThostFtdcDepthMarketDataField
{
    ///������
    TThostFtdcDateType	TradingDay;
    ///��Լ����
    TThostFtdcInstrumentIDType	InstrumentID;
    ///����������
    TThostFtdcExchangeIDType	ExchangeID;
    ///��Լ�ڽ������Ĵ���
    TThostFtdcExchangeInstIDType	ExchangeInstID;
    ///���¼�
    TThostFtdcPriceType	LastPrice;
    ///�ϴν�����
    TThostFtdcPriceType	PreSettlementPrice;
    ///������
    TThostFtdcPriceType	PreClosePrice;
    ///���ֲ���
    TThostFtdcLargeVolumeType	PreOpenInterest;
    ///������
    TThostFtdcPriceType	OpenPrice;
    ///���߼�
    TThostFtdcPriceType	HighestPrice;
    ///���ͼ�
    TThostFtdcPriceType	LowestPrice;
    ///����
    TThostFtdcVolumeType	Volume;
    ///�ɽ�����
    TThostFtdcMoneyType	Turnover;
    ///�ֲ���
    TThostFtdcLargeVolumeType	OpenInterest;
    ///������
    TThostFtdcPriceType	ClosePrice;
    ///���ν�����
    TThostFtdcPriceType	SettlementPrice;
    ///��ͣ����
    TThostFtdcPriceType	UpperLimitPrice;
    ///��ͣ����
    TThostFtdcPriceType	LowerLimitPrice;
    ///����ʵ��
    TThostFtdcRatioType	PreDelta;
    ///����ʵ��
    TThostFtdcRatioType	CurrDelta;
    ///�����޸�ʱ��
    TThostFtdcTimeType	UpdateTime;
    ///�����޸ĺ���
    TThostFtdcMillisecType	UpdateMillisec;
    ///������һ
    TThostFtdcPriceType	BidPrice1;
    ///������һ
    TThostFtdcVolumeType	BidVolume1;
    ///������һ
    TThostFtdcPriceType	AskPrice1;
    ///������һ
    TThostFtdcVolumeType	AskVolume1;
    ///�����۶�
    TThostFtdcPriceType	BidPrice2;
    ///��������
    TThostFtdcVolumeType	BidVolume2;
    ///�����۶�
    TThostFtdcPriceType	AskPrice2;
    ///��������
    TThostFtdcVolumeType	AskVolume2;
    ///��������
    TThostFtdcPriceType	BidPrice3;
    ///��������
    TThostFtdcVolumeType	BidVolume3;
    ///��������
    TThostFtdcPriceType	AskPrice3;
    ///��������
    TThostFtdcVolumeType	AskVolume3;
    ///��������
    TThostFtdcPriceType	BidPrice4;
    ///��������
    TThostFtdcVolumeType	BidVolume4;
    ///��������
    TThostFtdcPriceType	AskPrice4;
    ///��������
    TThostFtdcVolumeType	AskVolume4;
    ///��������
    TThostFtdcPriceType	BidPrice5;
    ///��������
    TThostFtdcVolumeType	BidVolume5;
    ///��������
    TThostFtdcPriceType	AskPrice5;
    ///��������
    TThostFtdcVolumeType	AskVolume5;
    ///���վ���
    TThostFtdcPriceType	AveragePrice;
    ///ҵ������
    TThostFtdcDateType	ActionDay;
};
#endif

void XTCtpMd::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    thisGetToken();

    XTI("%s: %g\n", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

    thisSetToken();
}

