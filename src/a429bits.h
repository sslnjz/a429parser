#pragma once

#include <string>

class eformat
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

   eformat()
   {
      enumMap[DIS] = "DIS";
      enumMap[BCD] = "BCD";
      enumMap[BNR] = "BNR";
      enumMap[CHR] = "CHR";
      enumMap[COD] = "COD";
   }

   std::string name(int index)
   {
      if (enumMap.find(index) != enumMap.end())
      {
         return enumMap[index];
      }

      return "";
   }

   int index(const std::string& name)
   {
      auto iter = enumMap.begin();
      while (iter != enumMap.end())
      {
         if (iter->second == name)
            return iter->first;
         ++iter;
      }
      return -1;
   }

private:
   std::map<int, std::string> enumMap;
};


struct A429Bits
{
   int         lsb;        //least significant bit
   int         sigbit;     //significant bits
   double      lsbres;     //least significant bit resolution
   std::string format;     //significant bits format
   std::string codedesc;
};

struct A429BitsValue : public A429Bits
{
   double value;           //significant bits represent value
};