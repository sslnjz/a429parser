#pragma once

#include <stdint.h>

int bit_one_count(uint32_t n)
{
    unsigned int c = 0 ;
    for (c =0; n; ++c)
        n &= (n -1) ;
    return c ;
}

static uint8_t reverse_8bit(uint8_t src)
{
   src = (src & 0xF0) >> 4 | (src & 0x0F) << 4;
   src = (src & 0xCC) >> 2 | (src & 0x33) << 2;
   src = (src & 0xAA) >> 1 | (src & 0x55) << 1;
   return src;
}

static bool calculate_parity(uint32_t value, bool even = true)
{
   uint32_t count = bit_one_count(value);
   return even ? (count % 2) != 0 : count % 2 == 0;
}

static uint32_t bcd2bnr(uint32_t bcd)
{
   uint32_t bnr = 0, step = 0;
   while (bcd)
   {
      bnr += (bcd & 0x0F) * std::pow(10, step);
      bcd = bcd >> 4;
      ++step;
   }
   return bnr;
}

static uint32_t bnr2bcd(uint32_t value)
{
   uint32_t bcd = 0, step = 0;
   while (value)
   {
      bcd |= (value % 10) << (step * 4);
      value /= 10;
      ++step;
   }
   return bcd;
}

static bool get_selected_bits(
   const uint32_t& word,
   const uint32_t startBit,
   const uint32_t numBits,
   uint32_t& selected)
{
   const uint32_t& base = (startBit + numBits - 1);
   // error if specified bit field is invalid
   if (startBit < 1 || numBits < 1 || base > 32)
      return false;

   const uint64_t& one = 1;
   // mask: numBits bits starting at startBit are set
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startBit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   // Mask all bits outside of bit field and move bit field to start
   // at bit 1
   selected = (word & mask) >> (startBit - 1);

   return true;
}

static bool get_bits_2c_helper(
   const uint32_t& word,
   const uint32_t startBit,
   const uint32_t numBits,
   int32_t& value)
{
   const uint32_t& base = (startBit + numBits - 1);
   // error if specified bit field is invalid
   if (startBit < 1 || numBits < 1 || base > 32)
      return false;

   const uint64_t& one = 1;
   // mask: numBits bits starting at startBit are set
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startBit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   // Mask all bits outside of bit field and move bit field to start
   // at bit 1
   value = (word & mask) >> (startBit - 1);

   // If value represents a negative value, convert all bits before the
   // most significant bit to 1
   const uint32_t& c = static_cast<uint32_t>(one << (numBits - 1));

   if (static_cast<uint32_t>(value) >= c)
   {
      const uint32_t& d = static_cast<uint32_t>(one << numBits);
      value |= (0xffffffff - d + 1);
   }

   return true;
}

static bool get_bits_2c(
   const uint32_t& word,
   const uint32_t startBit,
   const uint32_t numBits,
   const int32_t valueLSB,
   uint32_t& value)
{
   int32_t val = 0;
   if (get_bits_2c_helper(word, startBit, numBits, val))
   {
      value = valueLSB * val;
      return true;
   }
   return false;
}

static bool get_bits_2c(
   const uint32_t& word,
   const uint32_t startBit,
   const uint32_t numBits,
   const double valueLSB,
   double& value)
{
   int32_t val = 0;
   if (get_bits_2c_helper(word, startBit, numBits, val))
   {
      value = valueLSB * static_cast<double>(val);
      return true;
   }
   return false;
}



static bool set_bits2c_helper(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const int64_t& value,
   uint32_t& word)
{
   const int32_t& base = (startbit + numbits - 1);
   if (startbit < 1 || numbits < 1 || base > 32)
      return false;

   const uint64_t& one = 1;
   const uint64_t& a = (one << (numbits - 1));

   // error if scaled value cannot fit in bits
   if ((value < (-1 * static_cast<int64_t>(a)))
      || (value > (static_cast<int64_t>(a) - 1))) {
      return false;
   }

   const uint64_t& b = (one << base);
   const uint64_t& c = (one << (startbit - 1));
   const uint32_t& mask = static_cast<uint32_t>(b - c);

   // clear specified bits in word
   word &= ~mask;
   word |= static_cast<uint32_t>((value << (startbit - 1)) & mask);

   return true;
}

static bool set_bits2c(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& scaled,
   const int32_t& value,
   uint32_t& word)
{
   return set_bits2c_helper(startbit, numbits,
      static_cast<int64_t>(value) / static_cast<int64_t>(scaled), word);
}

static bool set_bits2c(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const double& scaled,
   const double& value,
   uint32_t& word)
{
   return set_bits2c_helper(startbit, numbits,
      static_cast<int64_t>(std::round(value / scaled)), word);
}

static bool get_bitsbcd_helper(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   uint32_t& value)
{
   const uint32_t& base = (startbit + numbits - 1);
   // error if specified bit field is invalid
   if (startbit < 1 || numbits < 1 || base > 32)
      return false;

   const uint64_t& one = 1;
   // mask: numBits bits starting at startBit are set
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startbit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   // Mask all bits outside of bit field and move bit field to start
   // at bit 1
   uint32_t bcd = (word & mask) >> (startbit - 1);

   value = bcd2bnr(bcd);

   return true;
}

static bool get_bitsbcd(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& scaled,
   uint32_t& value)
{
   uint32_t tmp = 0;
   if (get_bitsbcd_helper(word, startbit, numbits, tmp))
   {
      value = tmp * scaled;
      return true;
   }
   return false;
}


static bool get_bitsbcd(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   const double& scaled,
   double& value)
{
   uint32_t tmp = 0;
   if (get_bitsbcd_helper(word, startbit, numbits, tmp))
   {
      value = static_cast<double>(tmp) * scaled;
      return true;
   }
   return false;
}

static bool set_bitsbcd(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& scaled,
   const uint32_t& value,
   uint32_t& word)
{
   const int& base = (startbit + numbits - 1);
   // error if specified bit field is invalid
   if (startbit < 1 || numbits < 1 || base > 32 || scaled == 0)
      return false;

   const uint32_t& scaled_value = value / scaled;
   const uint32_t& max = static_cast<uint32_t>(std::pow(10, numbits / 4) * std::exp2(numbits % 4) - 1);
   if (scaled_value > max)
      return false;

   const uint64_t& one = 1;
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startbit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   // Clear specified bits in word
   uint32_t tmp = word;
   tmp &= ~mask;
   tmp |= (bnr2bcd(scaled_value) << (startbit - 1));

   word = tmp;

   return true;
}

static bool set_bitsbcd(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const double& scaled,
   const double& value,
   uint32_t& word)
{
   return set_bitsbcd(startbit, numbits, 1, static_cast<uint32_t>(std::round(value / scaled)), word);
}

static bool set_bitsuint(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& valuelsb,
   const uint32_t& value,
   uint32_t& word)
{
   const int& base = (startbit + numbits - 1);
   // error if specified bit field is invalid
   if (startbit < 1 || numbits < 1 || base > 32 || valuelsb == 0)
      return false;

   uint64_t scaled_value;

   // compute scaled value
   scaled_value = value / valuelsb;

   const uint64_t& one = 1;
   const uint64_t& probe = (one << numbits);
   if (scaled_value >= probe) return false;


   // mask: numBits bits starting at startBit are set
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startbit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   // Clear specified bits in word
   uint32_t tmp = word;
   tmp &= ~mask;

   // move scaled value to start at bit startBit. Then add value to
   // bit field
   // Bits to the left of the bit field in the right-hand side value need not 
   // be set to 0 since the leading bits are already 0 in an UInt32

   uint64_t scaled = scaled_value << (startbit - 1);
   if (scaled > UINT32_MAX)
      return false;
   tmp |= static_cast<uint32_t>(scaled);

   word = tmp;
   return true;
}

static bool set_bitsuint(
   const uint32_t& startbit,
   const uint32_t& numbits,
   const double& valuelsb,
   const double& value,
   uint32_t& word)
{
   return set_bitsuint(startbit, numbits, 1,
      (uint32_t)std::round(value / valuelsb), word);
}

static bool get_bitsuint(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& valuelsb,
   uint32_t& value)
{
   const uint32_t& base = (startbit + numbits - 1);
   /// error if specified bit field is invalid
   if (startbit < 1 || numbits < 1 || base>32) return false;

   const uint64_t& one = 1;
   const uint64_t& a = (one << base);
   const uint64_t& b = (one << (startbit - 1));
   const uint32_t& mask = static_cast<uint32_t>(a - b);

   /// Mask all bits outside of bit field and move bit field to start
   /// at bit 1. Then multiply result by scale factor
   value = ((word & mask) >> (startbit - 1)) * valuelsb;

   return true;
}

static bool get_bitsuint(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   const uint32_t& valuelsb,
   int32_t& value)
{
   return get_bitsuint(word, startbit, numbits, valuelsb, (uint32_t&)value);
}

static bool get_bitsuint(
   const uint32_t& word,
   const uint32_t& startbit,
   const uint32_t& numbits,
   const double& valuelsb,
   double& value)
{
   uint32_t uint_value;

   // Call helper routine to get bit field value. Then multiply value
   // by the scale
   if (get_bitsuint(word, startbit, numbits, 1, uint_value))
   {
      value = static_cast<double>(uint_value) * valuelsb;
      return true;
   }
   else
      return false;
}