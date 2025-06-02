// renderer.c: renders the actual image data

#include "renderer.h"

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
	RenderString_append(str, colorBuffer, colorSize);

	// success
	return 0;
}
	
	
