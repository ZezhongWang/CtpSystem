/*
 * @Author: w2w 
 * @Date: 2018-02-28 10:58:13 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-02-28 10:58:13 
 */

#ifndef WZ_CONSTANT_H
#define WZ_CONSTANT_H

// Index for Sources
const short SOURCE_CTP = 1;

// Exchange Names

// Exchange ids
const short EXCHANGE_ID_SSE = 1; //上海证券交易所


//char * const  EXCHANGE_SSE = "SSE"; //上海证券交易所
const char EXCHANGE_SSE[] = "SSE"; //上海证券交易所
//const char* EXCHANGE_SSE = "SSE"; //上海证券交易所
//char * a = "aaaa"
//char a[] = "aaa";


///////////////////////////////////
// WZActionFlagType: 报单操作标志
///////////////////////////////////
//删除
#define WZ_CHAR_Delete          '0'
//挂起
#define WZ_CHAR_Suspend         '1'
//激活
#define WZ_CHAR_Active          '2'
//修改
#define WZ_CHAR_Modify          '3'

typedef char WZActionFlagType;

///////////////////////////////////
// WZContingentConditionType: 触发条件
///////////////////////////////////
//立即
#define WZ_CHAR_Immediately     '1'
//止损
#define WZ_CHAR_Touch           '2'
//止赢
#define WZ_CHAR_TouchProfit     '3'
//预埋单
#define WZ_CHAR_ParkedOrder     '4'
//最新价大于条件价
#define WZ_CHAR_LastPriceGreaterThanStopPrice '5'
//最新价大于等于条件价
#define WZ_CHAR_LastPriceGreaterEqualStopPrice '6'
//最新价小于条件价
#define WZ_CHAR_LastPriceLesserThanStopPrice '7'
//最新价小于等于条件价
#define WZ_CHAR_LastPriceLesserEqualStopPrice '8'
//卖一价大于条件价
#define WZ_CHAR_AskPriceGreaterThanStopPrice '9'
//卖一价大于等于条件价
#define WZ_CHAR_AskPriceGreaterEqualStopPrice 'A'
//卖一价小于条件价
#define WZ_CHAR_AskPriceLesserThanStopPrice 'B'
//卖一价小于等于条件价
#define WZ_CHAR_AskPriceLesserEqualStopPrice 'C'
//买一价大于条件价
#define WZ_CHAR_BidPriceGreaterThanStopPrice 'D'
//买一价大于等于条件价
#define WZ_CHAR_BidPriceGreaterEqualStopPrice 'E'
//买一价小于条件价
#define WZ_CHAR_BidPriceLesserThanStopPrice 'F'
//买一价小于等于条件价
#define WZ_CHAR_BidPriceLesserEqualStopPrice 'H'

typedef char WZContingentConditionType;

///////////////////////////////////
// WZDirectionType: 买卖方向
///////////////////////////////////
//买
#define WZ_CHAR_Buy             '0'
//卖
#define WZ_CHAR_Sell            '1'

typedef char WZDirectionType;

///////////////////////////////////
// WZForceCloseReasonType: 强平原因
///////////////////////////////////
//非强平
#define WZ_CHAR_NotForceClose   '0'
//资金不足
#define WZ_CHAR_LackDeposit     '1'
//客户超仓
#define WZ_CHAR_ClientOverPositionLimit '2'
//会员超仓
#define WZ_CHAR_MemberOverPositionLimit '3'
//持仓非整数倍
#define WZ_CHAR_NotMultiple     '4'
//违规
#define WZ_CHAR_Violation       '5'
//其它
#define WZ_CHAR_Other           '6'
//自然人临近交割
#define WZ_CHAR_PersonDeliv     '7'

typedef char WZForceCloseReasonType;

///////////////////////////////////
// WZHedgeFlagType: 投机套保标志
///////////////////////////////////
//投机
#define WZ_CHAR_Speculation     '1'
//套利
#define WZ_CHAR_Argitrage       '2'
//套保
#define WZ_CHAR_Hedge           '3'
//做市商(femas)
#define WZ_CHAR_MarketMaker     '4'
//匹配所有的值(femas)
#define WZ_CHAR_AllValue        '9'

typedef char WZHedgeFlagType;

///////////////////////////////////
// WZOffsetFlagType: 开平标志
///////////////////////////////////
//开仓
#define WZ_CHAR_Open            '0'
//平仓
#define WZ_CHAR_Close           '1'
//强平
#define WZ_CHAR_ForceClose      '2'
//平今
#define WZ_CHAR_CloseToday      '3'
//平昨
#define WZ_CHAR_CloseYesterday  '4'
//强减
#define WZ_CHAR_ForceOff        '5'
//本地强平
#define WZ_CHAR_LocaWZorceClose '6'
//不分开平
#define WZ_CHAR_Non             'N'

typedef char WZOffsetFlagType;

///////////////////////////////////
// WZOrderPriceTypeType: 报单价格条件
///////////////////////////////////
//任意价
#define WZ_CHAR_AnyPrice        '1'
//限价
#define WZ_CHAR_LimitPrice      '2'
//最优价
#define WZ_CHAR_BestPrice       '3'

typedef char WZOrderPriceTypeType;

///////////////////////////////////
// WZOrderStatusType: 报单状态
///////////////////////////////////
//全部成交（最终状态）
#define WZ_CHAR_AllTraded       '0'
//部分成交还在队列中
#define WZ_CHAR_PartTradedQueueing '1'
//部分成交不在队列中（部成部撤， 最终状态）
#define WZ_CHAR_PartTradedNotQueueing '2'
//未成交还在队列中
#define WZ_CHAR_NoTradeQueueing '3'
//未成交不在队列中（被拒绝，最终状态）
#define WZ_CHAR_NoTradeNotQueueing '4'
//撤单
#define WZ_CHAR_Canceled        '5'
//订单已报入交易所未应答
#define WZ_CHAR_AcceptedNoReply '6'
//未知
#define WZ_CHAR_Unknown         'a'
//尚未触发
#define WZ_CHAR_NotTouched      'b'
//已触发
#define WZ_CHAR_Touched         'c'
//废单错误（最终状态）
#define WZ_CHAR_Error           'd'
//订单已写入
#define WZ_CHAR_OrderInserted   'i'
//前置已接受
#define WZ_CHAR_OrderAccepted   'j'

typedef char WZOrderStatusType;

///////////////////////////////////
// WZPosiDirectionType: 持仓多空方向
///////////////////////////////////
//净
#define WZ_CHAR_Net             '1'
//多头
#define WZ_CHAR_Long            '2'
//空头
#define WZ_CHAR_Short           '3'

typedef char WZPosiDirectionType;

///////////////////////////////////
// WZPositionDateType: 持仓日期
///////////////////////////////////
//今日持仓
#define WZ_CHAR_Today           '1'
//历史持仓
#define WZ_CHAR_History         '2'
//两种持仓
#define WZ_CHAR_Both            '3'

typedef char WZPositionDateType;

///////////////////////////////////
// WZTimeConditionType: 有效期类型
///////////////////////////////////
//立即完成，否则撤销
#define WZ_CHAR_IOC             '1'
//本节有效
#define WZ_CHAR_GFS             '2'
//当日有效
#define WZ_CHAR_GFD             '3'
//指定日期前有效
#define WZ_CHAR_GTD             '4'
//撤销前有效
#define WZ_CHAR_GTC             '5'
//集合竞价有效
#define WZ_CHAR_GFA             '6'
//FAK或IOC(yisheng)
#define WZ_CHAR_FAK             'A'
//FOK(yisheng)
#define WZ_CHAR_FOK             'O'

typedef char WZTimeConditionType;

///////////////////////////////////
// WZVolumeConditionType: 成交量类型
///////////////////////////////////
//任何数量
#define WZ_CHAR_AV              '1'
//最小数量
#define WZ_CHAR_MV              '2'
//全部数量
#define WZ_CHAR_CV              '3'

typedef char WZVolumeConditionType;

///////////////////////////////////
// WZYsHedgeFlagType: 易盛投机保值类型
///////////////////////////////////
//保值
#define WZ_CHAR_YsB             'B'
//套利
#define WZ_CHAR_YsL             'L'
//无
#define WZ_CHAR_YsNon           'N'
//投机
#define WZ_CHAR_YsT             'T'

typedef char WZYsHedgeFlagType;

///////////////////////////////////
// WZYsOrderStateType: 易盛委托状态类型
///////////////////////////////////
//终端提交
#define WZ_CHAR_YsSubmit        '0'
//已受理
#define WZ_CHAR_YsAccept        '1'
//策略待触发
#define WZ_CHAR_YsTriggering    '2'
//交易所待触发
#define WZ_CHAR_YsExctriggering '3'
//已排队
#define WZ_CHAR_YsQueued        '4'
//部分成交
#define WZ_CHAR_YsPartFinished  '5'
//完全成交
#define WZ_CHAR_YsFinished      '6'
//待撤消(排队临时状态)
#define WZ_CHAR_YsCanceling     '7'
//待修改(排队临时状态)
#define WZ_CHAR_YsModifying     '8'
//完全撤单
#define WZ_CHAR_YsCanceled      '9'
//已撤余单
#define WZ_CHAR_YsLeftDeleted   'A'
//指令失败
#define WZ_CHAR_YsFail          'B'
//策略删除
#define WZ_CHAR_YsDeleted       'C'
//已挂起
#define WZ_CHAR_YsSuppended     'D'
//到期删除
#define WZ_CHAR_YsDeletedForExpire 'E'
//已生效——询价成功
#define WZ_CHAR_YsEffect        'F'
//已申请——行权、弃权、套利等申请成功
#define WZ_CHAR_YsApply         'G'

typedef char WZYsOrderStateType;

///////////////////////////////////
// WZYsOrderTypeType: 易盛委托类型
///////////////////////////////////
//市价
#define WZ_CHAR_YsMarket        '1'
//限价
#define WZ_CHAR_YsLimit         '2'

typedef char WZYsOrderTypeType;

///////////////////////////////////
// WZYsPositionEffectType: 易盛开平类型
///////////////////////////////////
//平仓
#define WZ_CHAR_YsClose         'C'
//不分开平
#define WZ_CHAR_YsNon           'N'
//开仓
#define WZ_CHAR_YsOpen          'O'
//平当日
#define WZ_CHAR_YsCloseToday    'T'

typedef char WZYsPositionEffectType;

///////////////////////////////////
// WZYsSideTypeType: 易盛买卖类型
///////////////////////////////////
//双边
#define WZ_CHAR_YsAll           'A'
//买入
#define WZ_CHAR_YsBuy           'B'
//无
#define WZ_CHAR_YsNon           'N'
//卖出
#define WZ_CHAR_YsSell          'S'

typedef char WZYsSideTypeType;

///////////////////////////////////
// WZYsTimeConditionType: 易盛委托有效类型
///////////////////////////////////
//当日有效
#define WZ_CHAR_YsGFD           '0'
//撤销前有效
#define WZ_CHAR_YsGTC           '1'
//指定日期前有效
#define WZ_CHAR_YsGTD           '2'
//FAK或IOC
#define WZ_CHAR_YsFAK           '3'
//FOK
#define WZ_CHAR_YsFOK           '4'

typedef char WZYsTimeConditionType;

#endif