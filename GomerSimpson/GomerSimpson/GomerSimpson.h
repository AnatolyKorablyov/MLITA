#pragma once
#include "stdafx.h"

const unsigned MAX_PRICE = 1'000'000'000;
const size_t NUMBER_PRICES = 3;

struct Shopping
{
	unsigned balance = 0;
	std::vector<unsigned> discPrices;
	std::map<unsigned, unsigned> numberDiscs;
};

class CGomerSimpson
{
public:
	Shopping ReadFromFile(const std::string & inputFile);
	bool CheckBuyerData(const Shopping & GomerBuyer);
	Shopping Purchase(const Shopping & GomerBuyer);
	void recordInFile(const std::string & outFileName, const Shopping & result);
private:
	bool CheckBalanceInRange(unsigned balance) const;
};

