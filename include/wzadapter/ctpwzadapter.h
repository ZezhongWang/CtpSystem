/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:41:24 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-28 12:03:10
 */
#ifndef CTP_WZ_ADAPTER_H
#define CTP_WZ_ADAPTER_H

#include <wzadapter/wzdatastruct.h>
#include <string.h>

#include <api/ctp/ThostFtdcUserApiStruct.h>

inline struct WZMarketDataField parseFrom(const struct CThostFtdcDepthMarketDataField &ori)
{
	struct WZMarketDataField res = {};
	memcpy(res.TradingDay, ori.TradingDay, 9);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.ExchangeInstID, ori.ExchangeInstID, 64);
	res.LastPrice = ori.LastPrice;
	res.PreSettlementPrice = ori.PreSettlementPrice;
	res.PreClosePrice = ori.PreClosePrice;
	res.PreOpenInterest = ori.PreOpenInterest;
	res.OpenPrice = ori.OpenPrice;
	res.HighestPrice = ori.HighestPrice;
	res.LowestPrice = ori.LowestPrice;
	res.Volume = ori.Volume;
	res.Turnover = ori.Turnover;
	res.OpenInterest = ori.OpenInterest;
	res.ClosePrice = ori.ClosePrice;
	res.SettlementPrice = ori.SettlementPrice;
	res.UpperLimitPrice = ori.UpperLimitPrice;
	res.LowerLimitPrice = ori.LowerLimitPrice;
	res.PreDelta = ori.PreDelta;
	res.CurrDelta = ori.CurrDelta;
	memcpy(res.UpdateTime, ori.UpdateTime, 9);
	res.UpdateMillisec = ori.UpdateMillisec;
	res.BidPrice1 = ori.BidPrice1;
	res.BidVolume1 = ori.BidVolume1;
	res.AskPrice1 = ori.AskPrice1;
	res.AskVolume1 = ori.AskVolume1;
	res.BidPrice2 = ori.BidPrice2;
	res.BidVolume2 = ori.BidVolume2;
	res.AskPrice2 = ori.AskPrice2;
	res.AskVolume2 = ori.AskVolume2;
	res.BidPrice3 = ori.BidPrice3;
	res.BidVolume3 = ori.BidVolume3;
	res.AskPrice3 = ori.AskPrice3;
	res.AskVolume3 = ori.AskVolume3;
	res.BidPrice4 = ori.BidPrice4;
	res.BidVolume4 = ori.BidVolume4;
	res.AskPrice4 = ori.AskPrice4;
	res.AskVolume4 = ori.AskVolume4;
	res.BidPrice5 = ori.BidPrice5;
	res.BidVolume5 = ori.BidVolume5;
	res.AskPrice5 = ori.AskPrice5;
	res.AskVolume5 = ori.AskVolume5;
	return res;
}

inline struct WZQryPositionField parseFrom(const struct CThostFtdcQryInvestorPositionField& ori)
{
	struct WZQryPositionField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	return res;
}

inline struct CThostFtdcQryInvestorPositionField parseTo(const struct WZQryPositionField& lf)
{
	struct CThostFtdcQryInvestorPositionField res = {};
	memcpy(res.BrokerID, lf.BrokerID, 11);
	memcpy(res.InvestorID, lf.InvestorID, 13);
	memcpy(res.InstrumentID, lf.InstrumentID, 31);
	return res;
}

inline struct WZRspPositionField parseFrom(const struct CThostFtdcInvestorPositionField& ori)
{
	struct WZRspPositionField res = {};
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	res.YdPosition = (int)(ori.Position - ori.TodayPosition);
	res.Position = ori.Position;
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	res.PositionCost = ori.PositionCost;
	res.HedgeFlag = ori.HedgeFlag;
	res.PosiDirection = ori.PosiDirection;
	return res;
}

inline struct WZInputOrderField parseFrom(const struct CThostFtdcInputOrderField& ori)
{
	struct WZInputOrderField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	res.LimitPrice = ori.LimitPrice;
	res.Volume = ori.VolumeTotalOriginal;
	res.MinVolume = ori.MinVolume;
	res.TimeCondition = ori.TimeCondition;
	res.VolumeCondition = ori.VolumeCondition;
	res.OrderPriceType = ori.OrderPriceType;
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.CombOffsetFlag[0];
	res.HedgeFlag = ori.CombHedgeFlag[0];
	res.ForceCloseReason = ori.ForceCloseReason;
	res.StopPrice = ori.StopPrice;
	res.IsAutoSuspend = ori.IsAutoSuspend;
	res.ContingentCondition = ori.ContingentCondition;
	return res;
}

inline struct CThostFtdcInputOrderField parseTo(const struct WZInputOrderField& WZ)
{
	struct CThostFtdcInputOrderField res = {};
	memcpy(res.BrokerID, WZ.BrokerID, 11);
	memcpy(res.UserID, WZ.UserID, 16);
	memcpy(res.InvestorID, WZ.InvestorID, 13);
	memcpy(res.BusinessUnit, WZ.BusinessUnit, 21);
	memcpy(res.ExchangeID, WZ.ExchangeID, 9);
	memcpy(res.InstrumentID, WZ.InstrumentID, 31);
	memcpy(res.OrderRef, WZ.OrderRef, 13);
	res.LimitPrice = WZ.LimitPrice;
	res.VolumeTotalOriginal = WZ.Volume;
	res.MinVolume = WZ.MinVolume;
	res.TimeCondition = WZ.TimeCondition;
	res.VolumeCondition = WZ.VolumeCondition;
	res.OrderPriceType = WZ.OrderPriceType;
	res.Direction = WZ.Direction;
	res.CombOffsetFlag[0] = WZ.OffsetFlag;
	res.CombHedgeFlag[0] = WZ.HedgeFlag;
	res.ForceCloseReason = WZ.ForceCloseReason;
	res.StopPrice = WZ.StopPrice;
	res.IsAutoSuspend = WZ.IsAutoSuspend;
	res.ContingentCondition = WZ.ContingentCondition;
	// 自己加的
	strcpy(res.GTDDate, "");
	return res;
}

inline struct WZRtnOrderField parseFrom(const struct CThostFtdcOrderField& ori)
{
	struct WZRtnOrderField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.ParticipantID, ori.ParticipantID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	res.LimitPrice = ori.LimitPrice;
	res.VolumeTraded = ori.VolumeTraded;
	res.VolumeTotal = ori.VolumeTotal;
	res.VolumeTotalOriginal = ori.VolumeTotalOriginal;
	res.TimeCondition = ori.TimeCondition;
	res.VolumeCondition = ori.VolumeCondition;
	res.OrderPriceType = ori.OrderPriceType;
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.CombOffsetFlag[0];
	res.HedgeFlag = ori.CombHedgeFlag[0];
	res.OrderStatus = ori.OrderStatus;
	res.RequestID = ori.RequestID;
	return res;
}

inline struct WZRtnTradeField parseFrom(const struct CThostFtdcTradeField& ori)
{
	struct WZRtnTradeField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.TradeID, ori.TradeID, 21);
	memcpy(res.OrderSysID, ori.OrderSysID, 21);
	memcpy(res.ParticipantID, ori.ParticipantID, 11);
	memcpy(res.ClientID, ori.ClientID, 11);
	res.Price = ori.Price;
	res.Volume = ori.Volume;
	memcpy(res.TradingDay, ori.TradingDay, 13);
	memcpy(res.TradeTime, ori.TradeTime, 9);
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.OffsetFlag;
	res.HedgeFlag = ori.HedgeFlag;
	return res;
}

inline struct WZOrderActionField parseFrom(const struct CThostFtdcInputOrderActionField& ori)
{
	struct WZOrderActionField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.OrderSysID, ori.OrderSysID, 21);
	res.RequestID = ori.RequestID;
	res.ActionFlag = ori.ActionFlag;
	res.LimitPrice = ori.LimitPrice;
	res.VolumeChange = ori.VolumeChange;
	return res;
}

inline struct CThostFtdcInputOrderActionField parseTo(const struct WZOrderActionField& WZ)
{
	struct CThostFtdcInputOrderActionField res = {};
	memcpy(res.BrokerID, WZ.BrokerID, 11);
	memcpy(res.InvestorID, WZ.InvestorID, 13);
	memcpy(res.InstrumentID, WZ.InstrumentID, 31);
	memcpy(res.ExchangeID, WZ.ExchangeID, 9);
	memcpy(res.UserID, WZ.UserID, 16);
	memcpy(res.OrderRef, WZ.OrderRef, 13);
	memcpy(res.OrderSysID, WZ.OrderSysID, 21);
	res.RequestID = WZ.RequestID;
	res.ActionFlag = WZ.ActionFlag;
	res.LimitPrice = WZ.LimitPrice;
	res.VolumeChange = WZ.VolumeChange;
	return res;
}

inline struct WZQryAccountField parseFrom(const struct CThostFtdcQryTradingAccountField& ori)
{
	struct WZQryAccountField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	return res;
}

inline struct CThostFtdcQryTradingAccountField parseTo(const struct WZQryAccountField& lf)
{
	struct CThostFtdcQryTradingAccountField res = {};
	memcpy(res.BrokerID, lf.BrokerID, 11);
	memcpy(res.InvestorID, lf.InvestorID, 13);
	return res;
}

inline struct WZRspAccountField parseFrom(const struct CThostFtdcTradingAccountField& ori)
{
	struct WZRspAccountField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.AccountID, 13);
	res.PreMortgage = ori.PreMortgage;
	res.PreCredit = ori.PreCredit;
	res.PreDeposit = ori.PreDeposit;
	res.preBalance = ori.PreBalance;
	res.PreMargin = ori.PreMargin;
	res.Deposit = ori.Deposit;
	res.Withdraw = ori.Withdraw;
	res.FrozenMargin = ori.FrozenMargin;
	res.FrozenCash = ori.FrozenCash;
	res.FrozenCommission = ori.FrozenCommission;
	res.CurrMargin = ori.CurrMargin;
	res.CashIn = ori.CashIn;
	res.Commission = ori.Commission;
	res.CloseProfit = ori.CloseProfit;
	res.PositionProfit = ori.PositionProfit;
	res.Balance = ori.Balance;
	res.Available = ori.Available;
	res.WithdrawQuota = ori.WithdrawQuota;
	res.Reserve = ori.Reserve;
	memcpy(res.TradingDay, ori.TradingDay, 9);
	res.Credit = ori.Credit;
	res.Mortgage = ori.Mortgage;
	res.ExchangeMargin = ori.ExchangeMargin;
	res.DeliveryMargin = ori.DeliveryMargin;
	res.ExchangeDeliveryMargin = ori.ExchangeDeliveryMargin;
	res.ReserveBalance = ori.ReserveBalance;
	res.Equity = ori.PreBalance - ori.PreCredit - ori.PreMortgage + ori.Mortgage - ori.Withdraw + ori.Deposit + ori.CloseProfit + ori.PositionProfit + ori.CashIn - ori.Commission ;
	return res;
}



#endif