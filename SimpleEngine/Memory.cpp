#include "Memory.h"
#include "Log.h"
#include <Windows.h>
//#include <string.h>

struct memory_stats
{
	size_t total_allocated;
	size_t tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
	"UNKNOWN    ",
	"ARRAY      ",
	"DARRAY     ",
	"DICT       ",
	"RING_QUEUE ",
	"BST        ",
	"STRING     ",
	"ENGINE     ",
	"JOB        ",
	"TEXTURE    ",
	"MAT_INST   ",
	"RENDERER   ",
	"GAME       ",
	"TRANSFORM  ",
	"ACTOR      ",
	"COMPONENT  ",};


static struct memory_stats stats;

void initialize_memory()
{
	memset(&stats, 0, sizeof(stats));
}

void shutdonwn_memory()
{
}

void* memory_alloc(size_t size, memory_tag tag)
{
	if (tag == MEMORY_TAG_UNKNOWN) {
		Log::info("memory_alloc called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.total_allocated += size;
	stats.tagged_allocations[tag] += size;

	// platform_allocate
	//void* block = (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	void* block = malloc(size);
	// platform_zero_memory
	memset(block, 0, size);

	return block;
}

void memory_free(void* block, size_t size, memory_tag tag)
{
	if (tag == MEMORY_TAG_UNKNOWN) {
		Log::info("memory_free called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.total_allocated -= size;
	stats.tagged_allocations[tag] -= size;

	// platform_free
	//HeapFree(GetProcessHeap(), 0, block);
	free(block);
}

void* zero_memory(void* block, size_t size)
{
	return memset(block, 0, size);
}

void* copy_memory(void* dest, const void* source, size_t size)
{
	return memcpy(dest, source, size);
}

void* set_memory(void* dest, int value, size_t size)
{
	return memset(dest, value, size);
}

char* get_memory_usage_str()
{
	const size_t gib = 1024 * 1024 * 1024;
	const size_t mib = 1024 * 1024;
	const size_t kib = 1024;

	char buffer[8000] = "System memory use (tagged):\n";
	size_t offset = strlen(buffer);

	for (size_t i = 0; i < MEMORY_TAG_MAX_TAGS; ++i) {
		char unit[4] = "XiB";
		float amount = 1.0f;
		if (stats.tagged_allocations[i] >= gib) {
			unit[0] = 'G';
			amount = stats.tagged_allocations[i] / (float)gib;
		}
		else if (stats.tagged_allocations[i] >= mib) {
			unit[0] = 'M';
			amount = stats.tagged_allocations[i] / (float)mib;
		}
		else if (stats.tagged_allocations[i] >= kib) {
			unit[0] = 'K';
			amount = stats.tagged_allocations[i] / (float)kib;
		}
		else {
			unit[0] = 'B';
			unit[1] = 0;
			amount = (float)stats.tagged_allocations[i];
		}

		int length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
		offset += length;
	}
	char* out_string = _strdup(buffer);
	return out_string;
}
