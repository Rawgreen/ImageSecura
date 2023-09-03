#include <lodepng.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define max_buffer 0xFFFFFF

struct size
{
  unsigned width;
  unsigned height;
  unsigned char *raw_image;
};

void encodeOneStep(unsigned char *raw_image_data, char *dest_filename,
                   unsigned width, unsigned height)
{
  unsigned error = lodepng_encode_file(dest_filename, raw_image_data, width,
                                       height, LCT_RGB, 8);
  /*if there's an error, display it*/
  if (error)
  {
    printf("error %u: %s\n", error, lodepng_error_text(error));
    return;
  }
}

struct size encode_file(const char *filename)
{
  FILE *file_to_encode = fopen(filename, "rb");
  unsigned char *generated_image = malloc(max_buffer);
  size_t file_length =
      fread(generated_image + 4, 1, max_buffer, file_to_encode);
  printf("file length: %lu\n", file_length);
  fclose(file_to_encode);
  *((uint32_t *)generated_image) = file_length;
  unsigned useful_data_size = file_length + 4;
  unsigned useful_pixels = ceil((double)useful_data_size / (double)3.0);
  unsigned side = ceil(sqrt((double)useful_pixels));
  struct size result = {side, side, generated_image};
  memset(generated_image + useful_data_size, 255, side * side * 3 - useful_data_size);
  return result;
}

void decode_file(const char *source_png_fn, const char *output_fn)
{
  struct size bin_file;
  lodepng_decode_file(&bin_file.raw_image, &bin_file.width, &bin_file.height, source_png_fn, LCT_RGB, 8);
  uint32_t file_length = *((uint32_t *)bin_file.raw_image);
  FILE *output = fopen(output_fn, "wb");
  fwrite(bin_file.raw_image + 4, 1, file_length, output);
  fclose(output);
}

int main(int argc, char **argv)
{
  if (argv[1][0] == 'd')
  {
    decode_file(argv[2], argv[3]);
  }
  else if (argv[1][0] == 'e')
  {
    struct size binary_content = encode_file(argv[2]);
    printf("image size: %d * %d\n", binary_content.width, binary_content.height);
    encodeOneStep(binary_content.raw_image, argv[3], binary_content.width,
                  binary_content.height);
  }
}