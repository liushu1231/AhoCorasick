/*************************************************
 *
 * Author: liushu1231
 * Create time: 2016 1ÔÂ 12 19Ê±07·Ö50Ãë
 * E-Mail:liushu.fly@gmail.com
 * version 1.0
 *
*************************************************/



#include <iostream>
#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "aho_corasick.h"
using namespace std;

TEST(CAhoCorasick,aho_corasick)
{
	CAhoCorasick matcher;
	std::vector<std::string> patterns;
	std::vector<std::string> tags;

	patterns.push_back("nihao");
	tags.push_back("nihao");
	patterns.push_back("hao");
	tags.push_back("hao");
	patterns.push_back("hs");
	tags.push_back("hs");
	patterns.push_back("hsr");
	tags.push_back("hsr");

	matcher.BuildAC(patterns,tags);
	std::vector<ResultNode> result_vec;

	std::string query = "sdmfhsgnshejfgnihaofhsrnihao";
	matcher.Search(query,result_vec);
	for(size_t i = 0; i < result_vec.size(); ++i)
	{
		std::cerr<<result_vec[i].pos<<"\t"<<result_vec[i].tag_index<<"\t"<<tags[result_vec[i].tag_index]<<std::endl;
	}

}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
