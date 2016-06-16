#include "stdafx.h"
#include "../GomerSimpson/GomerSimpson.h"

BOOST_AUTO_TEST_SUITE(gomer_buyer)
BOOST_AUTO_TEST_CASE(task_example)
{
	Shopping gomerData;
	gomerData.balance = 14;
	gomerData.discPrices = { 3, 5, 7 };
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(3), 3);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(5), 1);
}
BOOST_AUTO_TEST_CASE(max_balance)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'000;
	gomerData.discPrices = { 3, 5, 7 };
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(3), 333333331);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(5), 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(7), 1);
}
BOOST_AUTO_TEST_CASE(max_balance_add_1_error)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'001;
	gomerData.discPrices = { 3, 5, 7 };
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 1'000'000'001);
}
BOOST_AUTO_TEST_CASE(big_prices)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'000;
	gomerData.discPrices = { 200'000'000, 300'000'000, 700'000'000};
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(200'000'000), 5);
}
BOOST_AUTO_TEST_CASE(two_prices)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'000;
	gomerData.discPrices = { 20, 30};
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 1'000'000'000);
}
BOOST_AUTO_TEST_CASE(big_balance_min_price)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'000;
	gomerData.discPrices = { 2, 3, 4 };
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(2), 500'000'000);
}

BOOST_AUTO_TEST_CASE(big_balance_big_price)
{
	Shopping gomerData;
	gomerData.balance = 1'000'000'000;
	gomerData.discPrices = { 9'990, 9'991, 9'992 };
	CGomerSimpson gomerBuyer;
	gomerData = gomerBuyer.Purchase(gomerData);
	BOOST_CHECK_EQUAL(gomerData.balance, 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(9990), 333333331);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(9991), 0);
	BOOST_CHECK_EQUAL(gomerData.numberDiscs.at(9992), 1);
}
BOOST_AUTO_TEST_SUITE_END()