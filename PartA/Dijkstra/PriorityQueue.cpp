#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {};
PriorityQueue::~PriorityQueue() {};

void PriorityQueue::insert(PathNode p1)
{
	m_queue.push(p1);
}

PathNode PriorityQueue::useTop()
{
	if (!m_queue.empty())
	{
		PathNode ans = m_queue.top();
		m_queue.pop();

		return ans;
	}
	throw "Empty Priority Queue";
}

int PriorityQueue::size()
{
	return m_queue.size();
}