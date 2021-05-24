#pragma once

#include <string>

class EFormat
{ 
public:
   enum {
      DIS,
      BCD,
      BNR,
      CHR,
      COD,
      eRange
   };

   EFormat()
   {
      fmtmap[DIS] = "DIS";
      fmtmap[BCD] = "BCD";
      fmtmap[BNR] = "BNR";
      fmtmap[CHR] = "CHR";
      fmtmap[COD] = "COD";
   }

   std::string name(int index)
   {
      if (fmtmap.find(index) != fmtmap.end())
      {
         return fmtmap[index];
      }

      return "";
   }

   int index(const std::string& name)
   {
      auto iter = fmtmap.begin();
      while (iter != fmtmap.end())
      {
         if (iter->second == name)
            return iter->first;
         ++iter;
      }
      return -1;
   }

private:
   std::map<int, std::string> fmtmap;
};


struct A429Bits
{
   int         lsb;        //least significant bit
   int         sigbits;    //significant bits numbert
   double      lsbres;     //least significant bit resolution
   std::string format;     //significant bits format
   std::string codedesc;   //significant bit encode
};

struct A429BitsValue : public A429Bits
{
   uint8_t label;
   uint8_t SDI;
   uint8_t SSM;
   uint8_t parity;
   uint32_t sig;           //significant bit
   double value;           //significant bits represent value
   std::string code;       //significant bit decode
};