#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {};
PriorityQueue::~PriorityQueue() {};

void PriorityQueue::insert(const PathEdge& p1)
{
	m_queue.emplace(p1);
}

PathEdge PriorityQueue::useTop()
{
	if (!m_queue.empty())
	{
		PathEdge ans = m_queue.top();
		m_queue.pop();

		return ans;
	}
	throw "Empty Priority Queue";
}

int PriorityQueue::size()
{
	return m_queue.size();
}

void PriorityQueue::clear()
{
	m_queue = priority_queue<PathEdge, vector<PathEdge>, Comparator>();
	return;
}