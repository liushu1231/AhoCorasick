/*************************************************
 *
 * Author: liushu1231
 * Create time: 2016 1ÔÂ 12 19Ê±07·Ö50Ãë
 * E-Mail:liushu.fly@gmail.com
 * version 1.0
 *
*************************************************/

#include"aho_corasick.h"
#include<assert.h>
#include<queue>

CAhoCorasick::CAhoCorasick()
{
}

CAhoCorasick::~CAhoCorasick()
{
}

int32_t CAhoCorasick::BuildAC(
		const std::vector<std::string>& patterns,
		const std::vector<std::string>& tags
		)
{
	assert(patterns.size() == tags.size());
	//create root node
	m_nodes.push_back(TrieNode(0));
	for(size_t i = 0; i < patterns.size(); ++i)
	{
		Insert2Trie(patterns[i],i);
	}

	BuildFailNodes();

	return 0;
}

int32_t CAhoCorasick::Search(
		const std::string& query,
		std::vector<ResultNode>& result_vec)
{
	result_vec.clear();
	assert(m_nodes.size() > 0);
	TrieNode* root = &m_nodes[0];
	for(size_t i = 0; i < query.size(); ++i)
	{
		auto it_next = root->next_nodes.find((uchar)query[i]);
		while(it_next == root->next_nodes.end() && 
				root->index != 0)
		{//find the mather 
			root = &m_nodes[root->fail_node];
			it_next = root->next_nodes.find((uchar)query[i]);
		}
		if( it_next == root->next_nodes.end() )
		{//fail until root
			root = &m_nodes[0];
		}
		else
		{
			root = &m_nodes[it_next->second];
		}
		TrieNode* temp_node = root;
		while(temp_node->index != 0)
		{
			if(temp_node->is_end == true)
			{
				result_vec.push_back(
						ResultNode(
							i+1,
							temp_node->tag_index
							)
						);
			}
			temp_node = &m_nodes[temp_node->fail_node];
		}
	}//end for
	return 0;
}

int32_t CAhoCorasick::Insert2Trie(
		const std::string& pattern,
		const size_t tag_index
		)
{
	assert(pattern.size() > 0);
	int64_t root_index = 0;
	for(size_t i = 0; i < pattern.size(); ++i)
	{
		auto it = m_nodes[root_index].next_nodes.find(
				(uchar)pattern[i]);
		if( it != m_nodes[root_index].next_nodes.end() )
		{
			root_index = it->second;
		}
		else
		{
			TrieNode node(m_nodes.size());
			m_nodes.push_back( node );
			m_nodes[root_index].next_nodes[(uchar)pattern[i]] =
				m_nodes.size()-1;
			root_index = m_nodes.size()-1;
		}
	}
	m_nodes[root_index].is_end = true;
	m_nodes[root_index].tag_index = tag_index;

	return 0;
}

int32_t CAhoCorasick::BuildFailNodes() 
{
	//set root's fail node
	TrieNode* root = &m_nodes[0];
	root->fail_node = -1;

	//bfs
	std::queue<int64_t> nodes_queue;
	nodes_queue.push(0);
	while(nodes_queue.size() > 0)
	{
		int64_t node_index = nodes_queue.front();
		nodes_queue.pop();
		for(auto it = m_nodes[node_index].next_nodes.begin();
				it != m_nodes[node_index].next_nodes.end();
				it++)
		{
			//set second level's fail node to root
			TrieNode* next_node = &m_nodes[it->second];
			if(node_index == 0)
			{
				next_node->fail_node = 0;
			}
			else
			{
				int64_t fail = m_nodes[node_index].fail_node;
				while( fail != -1 )
				{
					auto it_next = m_nodes[fail].next_nodes.find(
							it->first);
					if(it_next != m_nodes[fail].next_nodes.end() )
					{
						next_node->fail_node = 
							m_nodes[it_next->second].index;
						break;
					}
					fail = m_nodes[fail].fail_node;
				}
				if( fail == -1 )
				{
					next_node->fail_node = 0;
				}
			}
			nodes_queue.push(next_node->index);
		}
	}
	return 0;
}
