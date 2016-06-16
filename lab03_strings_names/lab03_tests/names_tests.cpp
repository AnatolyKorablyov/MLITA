#include "stdafx.h"
#include "../lab03_strings_names/FindCommonElements.h"

BOOST_AUTO_TEST_SUITE(find_common_letters_in_names)
	BOOST_AUTO_TEST_CASE(find_son_name_with_two_common_elements)
	{
		FamilyNames family;
		family.motherName = "mama";
		family.fatherName = "papa";
		BOOST_CHECK(CommonElements(family));
		BOOST_CHECK_EQUAL(family.sonName, "aa");
	}
	BOOST_AUTO_TEST_CASE(father_name_is_empty)
	{
		FamilyNames family;
		family.motherName = "mamka";
		BOOST_CHECK(!CommonElements(family));
	}
	BOOST_AUTO_TEST_CASE(mother_name_is_empty)
	{
		FamilyNames family;
		family.fatherName = "papka";
		BOOST_CHECK(!CommonElements(family));
	}
	BOOST_AUTO_TEST_CASE(no_common_letters_in_names_in_family)
	{
		FamilyNames family;
		family.motherName = "mama";
		family.fatherName = "sosed";
		BOOST_CHECK(!CommonElements(family));
	}
	BOOST_AUTO_TEST_CASE(example_test_first)
	{
		FamilyNames family;
		family.motherName = "abcabca";
		family.fatherName = "abcda";
		BOOST_CHECK(CommonElements(family));
		BOOST_CHECK_EQUAL(family.sonName, "ca");
	}
	BOOST_AUTO_TEST_CASE(example_test_second)
	{
		FamilyNames family;
		family.motherName = "ccba";
		family.fatherName = "accbbaa";
		BOOST_CHECK(CommonElements(family));
		BOOST_CHECK_EQUAL(family.sonName, "ccba");
	}
	BOOST_AUTO_TEST_CASE(max_size_100000)
	{
		FamilyNames family = ReadFromFile("maxSize.txt");
		BOOST_CHECK(!CommonElements(family));
	}
	BOOST_AUTO_TEST_CASE(max_size_99999)
	{
		FamilyNames family = ReadFromFile("maxSize_99999.txt");
		CommonElements(family);
		BOOST_CHECK_EQUAL(family.sonName, "a");
	}
BOOST_AUTO_TEST_SUITE_END()