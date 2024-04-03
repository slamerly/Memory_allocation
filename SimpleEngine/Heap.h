#pragma once
#include <corecrt_malloc.h>
#include <cassert>

struct AllocHeader {
	int nSignature;
	int nSize;
	Heap* pHeap;
};

class Heap
{
public:
	Heap(const char* name);
	const char* GetName() const {
		return m_name;
	}

	void* operator new (size_t size, Heap* pHeap)
	{
		size_t nRequestBytes = size + sizeof(AllocHeader) + sizeof(int);
		char* pMem = (char*)malloc(nRequestBytes);
		AllocHeader* pHeader = (AllocHeader*)pMem;
		pHeader->nSignature = MEMSYSTEM_SIGNATURE;
		pHeader->pHeap = pHeap;
		pHeader->nSize = size;

		void* pStartMemBlock = pMem + sizeof(AllocHeader);
		int* pEndMarker = (int*)(pStartMemBlock + size);
		*pEndMarker = MEMSYSTEM_ENDMARKER;

		pHeap->AddAllocation(size);

		
		return pStartMemBlock;
	}

	void operator delete (void* pMemBlock)
	{
		AllocHeader* pHeader = (AllocHeader*)((char*)pMemBlock - sizeof(AllocHeader));
		assert(pHeader->nSignature == MEMSYSTEM_SIGNATURE);
		int* pEndMarker = (int*)(pMemBlock + size);
		assert(*pEndMarker == MEMSYSTEM_ENDMARKER);

		pHeader->pHeap->RemoveAllocation(pHeader->nSize);
		free(pHeader);
	}

	void* operator new (size_t size) {
		return operator new (size, HeapFactory::GetDefaultHeap());
	}

private:
	char m_name[];
};

