#include "stdafx.h"
#include "GomerSimpson.h"

Shopping CGomerSimpson::ReadFromFile(const std::string & inputFileName)
{
	Shopping gomerData;
	std::ifstream inpFile(inputFileName);
	unsigned price;
	inpFile >> gomerData.balance;
	for (size_t i = 0; i < 3; ++i)
	{
		inpFile >> price;
		gomerData.discPrices.push_back(price);
	}
	std::sort(gomerData.discPrices.begin(), gomerData.discPrices.end());
	return gomerData;
}

bool CGomerSimpson::CheckBuyerData(const Shopping & GomerBuyer)
{
	if (!CheckBalanceInRange(GomerBuyer.balance))
	{
		return false;
	}
	if (GomerBuyer.discPrices.size() != NUMBER_PRICES)
	{
		return false;
	}
	for (auto &i : GomerBuyer.discPrices)
	{
		if (!CheckBalanceInRange(i))
		{
			return false;
		}
	}
	return true;
}


Shopping CGomerSimpson::Purchase(const Shopping & GomerBuyer)
{
	if (!CheckBuyerData(GomerBuyer))
	{
		return GomerBuyer;
	}
	Shopping result = GomerBuyer;
	unsigned balance = result.balance;
	unsigned minPrice = result.discPrices.front();
	if (balance % minPrice == 0)
	{
		result.numberDiscs[minPrice] = balance / minPrice;
	}
	for (auto i = balance / minPrice; i > 0; --i)
	{
		unsigned countSecondPrice = 0;
		while (balance - minPrice * i >= countSecondPrice * result.discPrices[1])
		{
			unsigned countThirdPrice = 0;
			int localSecond = balance - minPrice * i - countSecondPrice * result.discPrices[1];
			if (localSecond >= 0 && localSecond < (int)result.balance)
			{
				result.balance = localSecond;
				result.numberDiscs[result.discPrices[0]] = i;
				result.numberDiscs[result.discPrices[1]] = countSecondPrice;
				result.numberDiscs[result.discPrices[2]] = countThirdPrice;
			}
			while (localSecond >= (int)(countThirdPrice * result.discPrices[2]))
			{
				int localThird = balance - minPrice * i - countSecondPrice * result.discPrices[1] - countThirdPrice * result.discPrices[2];
				if (localThird >= 0 && localThird < (int)result.balance)
				{
					result.balance = localThird;
					result.numberDiscs[result.discPrices[0]] = i;
					result.numberDiscs[result.discPrices[1]] = countSecondPrice;
					result.numberDiscs[result.discPrices[2]] = countThirdPrice;
				}
				++countThirdPrice;
				if (result.balance == 0)
				{
					return result;
				}
			}
			++countSecondPrice;
			if (result.balance == 0)
			{
				return result;
			}
		}
		if (result.balance == 0)
		{
			return result;
		}
	}
	return result;
}

void CGomerSimpson::recordInFile(const std::string & outFileName, const Shopping & result)
{
	std::ofstream outFile(outFileName);
	outFile << result.balance << std::endl;
	for (auto &i : result.numberDiscs)
	{
		outFile << i.first << "-" << i.second << " ";
	}
}

bool CGomerSimpson::CheckBalanceInRange(unsigned balance) const
{
	return (balance >= 1 && balance <= MAX_PRICE);
}
