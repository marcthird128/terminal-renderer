// renderer.c: renders the actual image data

#include "terminal-renderer/renderer.h"

int ImageBuffer_init(ImageBuffer* self, int width, int height, int bytesPerPixel) {
	// fill in fields
	self->width = width;
	self->height = height;
	self->bytesPerPixel = bytesPerPixel;

	// allocate buffer
	size_t size = width * height * bytesPerPixel;
	self->size = size;
	self->buffer = malloc(size);
	if (self->buffer == NULL) {
		return 1;
	}
	return 0;
}

int ImageBuffer_free(ImageBuffer* self) {
	// if already freed do nothing
	if (self->buffer == NULL) {
		return 0;
	}

	// free buffer
	free(self->buffer);
	self->buffer = NULL;

	// no possible way for this to fail
	return 0;
}

int ImageBuffer_render(ImageBuffer* self, RenderString* str, ColorGeneratorFn colorFn) {
	// buffer for generated colors
	char colorBuffer[COLOR_BUFFER_SIZE];
	int colorSize;

	// calculate image size
	size_t imageSize = self->width * self->height * self->bytesPerPixel;

	// iterate through pixels
	for (size_t offset = 0; offset < imageSize; offset += self->bytesPerPixel) {
		// generate the color
		colorSize = colorFn(self->buffer + offset, colorBuffer, COLOR_BUFFER_SIZE);

		// append to str
		if (RenderString_append(str, colorBuffer, colorSize)) {
			return 1;
		}
	}

	// null terminate
	RenderString_append(str, "\0", 1);

	// success
	return 0;
}

int RenderString_init(RenderString* self, size_t sizeHint) {
	// calculate size
	size_t size = 16; // 16 is a good default
	
	// make sure its a power of 2
	while (size < sizeHint) size <<= 1;

	// fill in fields
	self->length = 0;
	self->size = size;

	// allocate
	self->buffer = malloc(size);
	if (self->buffer == NULL) {
		return 1;
	}
	return 0;
}

int RenderString_free(RenderString* self) {
	free(self->buffer);
	self->buffer = NULL;
}

int RenderString_append(RenderString* self, const char* str, int size) {
	// append string size
	self->length += size;

	// if it needs to be resized
	if (self->length > self->size) {
		while (self->length > self->size) self->size <<= 1;
		
		self->buffer = realloc(self->buffer, self->size);
		if (self->buffer == NULL) {
			return 1;
		}
	}

	// append the actual string
	for (int i=0; i<size; i++) {
		*(self->buffer + i) = str[i];
	}

	// worked
	return 0;
}
