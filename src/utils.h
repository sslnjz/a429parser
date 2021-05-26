#pragma once

#include <stdint.h>
#include <string>

class Utils
{
public:
   static uint8_t reverse_8bit(uint8_t src);
   static bool calculate_parity(uint32_t value, bool even = true);
   static bool get_selected_bits(const uint32_t& word, const uint32_t startBit, const uint32_t numBits, uint32_t& selected);
   static bool get_bits2c(const uint32_t& word, const uint32_t startBit, const uint32_t numBits, const int32_t valueLSB, uint32_t& value);
   static bool get_bits2c(const uint32_t& word, const uint32_t startBit, const uint32_t numBits, const double valueLSB, double& value);
   static bool set_bits2c(const uint32_t& startbit, const uint32_t& numbits, const uint32_t& scaled, const int32_t& value, uint32_t& word);
   static bool set_bits2c(const uint32_t& startbit, const uint32_t& numbits, const double& scaled, const double& value, uint32_t& word);
   static bool get_bitsbcd(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, const uint32_t& scaled, uint32_t& value);
   static bool get_bitsbcd(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, const double& scaled, double& value);
   static bool set_bitsbcd(const uint32_t& startbit, const uint32_t& numbits, const double& scaled, const double& value, uint32_t& word);
   static bool set_bitsuint(const uint32_t& startbit, const uint32_t& numbits, const double& valuelsb, const double& value, uint32_t& word);
   static bool get_bitsuint(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, const uint32_t& valuelsb, int32_t& value);
   static bool get_bitsuint(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, const double& valuelsb, double& value);
   static bool set_bitschar(const uint32_t& startbit, const uint32_t& numbits, const std::string& str, uint32_t& word);
   static bool get_bitschar(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, std::string& str);

private:
   static int  bit_one_count(uint32_t n);
   static bool get_bitsuint(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, const uint32_t& valuelsb, uint32_t& value);
   static bool set_bitsuint(const uint32_t& startbit, const uint32_t& numbits, const uint32_t& valuelsb, const uint32_t& value, uint32_t& word);
   static bool get_bitsbcd_helper(const uint32_t& word, const uint32_t& startbit, const uint32_t& numbits, uint32_t& value);
   static bool set_bits2c_helper(const uint32_t& startbit, const uint32_t& numbits, const int64_t& value, uint32_t& word);
   static bool get_bits_2c_helper(const uint32_t& word, const uint32_t startBit, const uint32_t numBits, int32_t& value);
   static bool set_bitsbcd(const uint32_t& startbit, const uint32_t& numbits, const uint32_t& scaled, const uint32_t& value, uint32_t& word);

   static uint32_t bcd2bnr(uint32_t bcd);
   static uint32_t bnr2bcd(uint32_t value);
};

