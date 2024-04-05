#pragma once

enum memory_tag {
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_ENGINE,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ACTOR,
    MEMORY_TAG_COMPONENT,

    MEMORY_TAG_MAX_TAGS
};


void initialize_memory();
void shutdonwn_memory();

void* memory_alloc(size_t size, memory_tag tag);

void memory_free(void* block, size_t size, memory_tag tag);

void* zero_memory(void* block, size_t size);

void* copy_memory(void* dest, const void* source, size_t size);

void* set_memory(void* dest, int value, size_t size);

char* get_memory_usage_str();