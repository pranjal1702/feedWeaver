#include "nasdaq_sample_parser.h"
#include<cstring>
#include<format>
#include<iostream>
namespace itch50{

NasdaqSampleParser::NasdaqSampleParser(){}

void NasdaqSampleParser::parse(std::span<const std::byte> frame, std::unordered_map<char,uint64_t>& ct){
    if(frame.empty()){
        return;
    }
    const char message_type = static_cast<char>(frame[0]);
    switch (message_type)
    {
    case 'A':
    {
        auto order = _parse_add_order(frame);
        // std::cout << order.to_string() << '\n';
        ct['A']++;
        break;
    }
    case 'E':
    {
        auto order = _parse_executed_order(frame);
        // std::cout << order.to_string() << '\n';
        ct['E']++;
        break;
    }
    
    default:
        break;
    }

}

AddOrder NasdaqSampleParser::_parse_add_order(std::span<const std::byte> frame){
    if(frame.size()!=36){
        // we need to do something here
        return AddOrder();
    }
    return AddOrder{
        .exchange_ts_ns = _read_u48(frame.data()+5),
        .order_id = _read_u64(frame.data()+11),
        .price = _read_32(frame.data()+32),
        .size = _read_u32(frame.data()+20),
        .symbol = Symbol{
            std::string_view{
                reinterpret_cast<const char*>(frame.data()+24),8
            }
        },
        .side = (frame[19]==std::byte{'B'}) ? Side::BUY : Side::SELL,
    };
}

OrderExecuted NasdaqSampleParser::_parse_executed_order(std::span<const std::byte> frame){
    if(frame.size()!=31){
        // we need to do something here
        return OrderExecuted();
    }
    return OrderExecuted{
        .exchange_ts_ns = _read_u48(frame.data()+5),
        .order_id = _read_u64(frame.data()+11),
        .match_number = _read_u64(frame.data()+23),
        .size = _read_u32(frame.data()+19)
    };
}

Symbol::Symbol(std::string_view s){
    std::memcpy(data.data(),s.data(),std::min(s.size(),data.size()));
}

std::string_view Symbol::view() const{
    return {data.data(), data.size()};
}

std::string AddOrder::to_string() const
{
    return std::format(
        "AddOrder{{ exchange_ts_ns={}, order_id={}, price={}, size={}, symbol={}, side={} }}",
        exchange_ts_ns,
        order_id,
        price,
        size,
        symbol.view(),
        side == Side::BUY ? "BUY" : "SELL"
    );
}

std::string OrderExecuted::to_string() const
{
    return std::format(
        "ExecutedOrder{{ exchange_ts_ns={}, order_id={}, size={}}}",
        exchange_ts_ns,
        order_id,
        size
    );
}
std::int32_t NasdaqSampleParser::_read_32(const std::byte* data) const{
    std::uint32_t value =
    (static_cast<std::uint32_t>(data[0]) << 24) |
    (static_cast<std::uint32_t>(data[1]) << 16) |
    (static_cast<std::uint32_t>(data[2]) << 8)  |
     static_cast<std::uint32_t>(data[3]);

    return static_cast<std::int32_t>(value);
}

std::uint32_t NasdaqSampleParser::_read_u32(const std::byte* data) const
{
    return
        (static_cast<std::uint32_t>(data[0]) << 24) |
        (static_cast<std::uint32_t>(data[1]) << 16) |
        (static_cast<std::uint32_t>(data[2]) << 8)  |
         static_cast<std::uint32_t>(data[3]);
}

std::uint64_t NasdaqSampleParser::_read_u64(const std::byte* data) const
{
    return
        (static_cast<std::uint64_t>(data[0]) << 56) |
        (static_cast<std::uint64_t>(data[1]) << 48) |
        (static_cast<std::uint64_t>(data[2]) << 40) |
        (static_cast<std::uint64_t>(data[3]) << 32) |
        (static_cast<std::uint64_t>(data[4]) << 24) |
        (static_cast<std::uint64_t>(data[5]) << 16) |
        (static_cast<std::uint64_t>(data[6]) << 8)  |
         static_cast<std::uint64_t>(data[7]);
}

std::uint64_t NasdaqSampleParser::_read_u48(const std::byte* data) const
{
    return
        (static_cast<std::uint64_t>(data[0]) << 40) |
        (static_cast<std::uint64_t>(data[1]) << 32) |
        (static_cast<std::uint64_t>(data[2]) << 24) |
        (static_cast<std::uint64_t>(data[3]) << 16) |
        (static_cast<std::uint64_t>(data[4]) << 8)  |
         static_cast<std::uint64_t>(data[5]);
}
}