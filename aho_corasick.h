/*************************************************
 *
 * Author: liushu1231
 * Create time: 2016 1ÔÂ 12 19Ê±07·Ö50Ãë
 * E-Mail:liushu.fly@gmail.com
 * version 1.0
 *
*************************************************/

#ifndef _AHO_CORASICK_H_
#define _AHO_CORASICK_H_

#include<string>
#include<map>
#include<vector>
#include<stdint.h>

struct ResultNode
{
	size_t pos;
	size_t tag_index;

	ResultNode():pos(0),tag_index(0)
	{
	}
	ResultNode(size_t p,size_t l):
		pos(p),tag_index(l)
	{
	}
};

class CAhoCorasick
{
public:
	CAhoCorasick();
	~CAhoCorasick();

	int32_t BuildAC(
			const std::vector<std::string>& patterns,
			const std::vector<std::string>& tags
			);
	int32_t Search(
			const std::string& query,
			std::vector<ResultNode>& result_vec
			);

private:
	typedef unsigned char uchar;
	struct TrieNode
	{
		bool is_end;
		size_t tag_index;
		std::map<uchar,size_t> next_nodes;
		int64_t fail_node;
		int64_t index;//position in nodes vector
		TrieNode(int64_t in):is_end(false),fail_node(0),index(in)
		{
		}
	};
private:
	int32_t Insert2Trie(
			const std::string& pattern,
			const size_t tag_index
			);
	int32_t BuildFailNodes();
	
private:
	std::vector<TrieNode> m_nodes;
};

#endif
