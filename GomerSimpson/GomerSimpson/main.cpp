#include "stdafx.h"
#include "GomerSimpson.h"



int main()
{
	Shopping gomer;
	gomer.balance = 1'000'000'000;
	gomer.discPrices = { 9'99970, 9'99973, 9'99989 };
	/*gomer.balance = 14;
	gomer.discPrices = { 3, 5, 7 };
	*/CGomerSimpson sad;
	Shopping result = sad.Purchase(gomer);
	std::cout << "Balance " << result.balance << std::endl;
	for (auto i : result.numberDiscs)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
	return 0;
}