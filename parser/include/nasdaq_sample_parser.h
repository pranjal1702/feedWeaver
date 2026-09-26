#pragma once
#include<filesystem>
#include<span>
#include<array>
#include<string_view>
#include<cstdint>
#include<cstddef>
#include<string>
#include<unordered_map>

namespace itch50{
struct Symbol{
    std::array<char,8> data{}; // all filled with 0
    Symbol() = default;
    Symbol(std::string_view s);

    std::string_view view() const;

    bool operator==(const Symbol&) const = default;
};

enum class Side{
    BUY,
    SELL
};
struct AddOrder{
    std::uint64_t exchange_ts_ns;
    std::uint64_t order_id;
    std::int32_t price;
    std::uint32_t size;
    Symbol symbol;
    Side side;
    std::string to_string() const;
};

struct OrderExecuted{
    std::uint64_t exchange_ts_ns;
    std::uint64_t order_id;
    std::uint64_t match_number;
    std::uint32_t size;
    std::string to_string() const;
};

class NasdaqSampleParser{
public:
    NasdaqSampleParser();

    void parse(std::span<const std::byte> frame, std::unordered_map<char,uint64_t>& ct);
private:
    AddOrder _parse_add_order(std::span<const std::byte> frame);
    OrderExecuted _parse_executed_order(std::span<const std::byte> frame);
    std::int32_t _read_32(const std::byte* data) const;
    std::uint32_t _read_u32(const std::byte* data) const;
    std::uint64_t _read_u48(const std::byte* data) const;
    std::uint64_t _read_u64(const std::byte* data) const;

};




} // namespace ends