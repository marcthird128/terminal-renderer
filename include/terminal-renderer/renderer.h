// renderer.h

#ifndef __TERMINAL_RENDERER__RENDERER_H__
#define __TERMINAL_RENDERER__RENDERER_H__

#include <stdint.h>
#include <stdlib.h>

#define COLOR_BUFFER_SIZE 32 // 32 for safety

typedef struct ImageBuffer {
	uint8_t* buffer;
	size_t size; // real size of buffer
	int width;
	int height;
	int bytesPerPixel;
} ImageBuffer;

typedef struct RenderString {
	char* buffer;
	size_t size; // real buffer size
	size_t length; // in-use
} RenderString;

typedef int /* returns size of generated color */ (*ColorGeneratorFn)(uint8_t* /*input*/, char* /*outputBuffer*/, int /*maxSize*/);

int /* returns 1 if failed */ ImageBuffer_render(ImageBuffer* self, RenderString* str, ColorGeneratorFn colorFn);

int /* returns 1 if failed */ RenderString_append(RenderString* self, const char* str, int size);

#endif
