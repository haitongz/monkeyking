#include "S_TimeIntv.H"
#include <string>
#include <iostream>

#define loops 1000

void InitialDataArea(double* pdArray,
const int nBound,
const int nInitBlock,
const double dIniValue);

void InitialDataArea2(double* pdArray,
const int nBound,
const double dIniValue);

int main(int argc, void* argv[])
{
   const int nBound = 512*512;
   const int nInitBlock = 512;
   const double dIniValue = 0.01;
   double* pdArray = (double*)malloc(nBound * sizeof(double));

   std::cout << "memcpy version..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i)
         InitialDataArea(pdArray, nBound, nInitBlock, dIniValue);
   }

   std::cout << "assignment version..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i)
         InitialDataArea2(pdArray, nBound, dIniValue);
   }

   free(pdArray);
}

void InitialDataArea(double* pdArray, const int nBound, const int nInitBlock, const double dIniValue)
{
   //assert mod nBound by nInitBlock = 0
   double* pdArrayT = pdArray;
   unsigned nIdx = 0;
   for(nIdx = 0; nIdx < nInitBlock; ++nIdx, ++pdArrayT) {
      (*pdArrayT) = dIniValue;
   }

   const int nCpySize = nInitBlock * sizeof(double);
   for(nIdx = nInitBlock; nIdx < nBound; nIdx += nInitBlock, pdArrayT += nInitBlock) {
      memcpy(pdArrayT, pdArray, nCpySize);
   }
}

void InitialDataArea2(double* pdArray, const int nBound, const double dIniValue)
{
   for(int nIdx = 0; nIdx < nBound; ++nIdx) {
      *pdArray++ = dIniValue;
   }
}
