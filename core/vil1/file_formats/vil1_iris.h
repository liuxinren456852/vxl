//-*- c++ -*-------------------------------------------------------------------
#ifndef vil_iris_file_format_h_
#define vil_iris_file_format_h_
#ifdef __GNUC__
#pragma interface
#endif
// Author: joris.schouteden@esat.kuleuven.ac.be
// Created: 17 Feb 2000

#include <vil/vil_file_format.h>
#include <vil/vil_generic_image.h>

//: Loader for RGB files (sgi iris)
class vil_iris_file_format : public vil_file_format {
public:
  virtual char const* tag() const;
  virtual vil_generic_image* make_input_image(vil_stream* vs);
  virtual vil_generic_image* make_output_image(vil_stream* vs, vil_generic_image const* prototype);
};

//: Generic image implementation for RGB files
class vil_iris_generic_image : public vil_generic_image {
  unsigned long *starttab_;
  unsigned long *lengthtab_;
  
  bool read_header();
  bool write_header();

  friend class vil_iris_file_format;
public:

  vil_iris_generic_image(vil_stream* is);
  vil_iris_generic_image(vil_stream* is, vil_generic_image const* prototype);

  //: Dimensions.  Planes x W x H x Components
  virtual int planes() const { return planes_; }
  virtual int width() const { return width_; }
  virtual int height() const { return height_; }
  virtual int components() const { return components_; }

  virtual int bits_per_component() const { return (bytes_per_component_ * 8); }
  virtual int bytes_per_pixel() const { return bytes_per_component_ * planes_; };

  virtual enum vil_component_format component_format() const { return VIL_COMPONENT_FORMAT_UNSIGNED_INT; }
  
  virtual vil_generic_image* get_plane(int) const;
  
  //: Copy plane PLANE of this to BUF, 
  virtual bool do_get_section(void* buf, int x0, int y0, int, int) const;
  virtual bool do_put_section(void const* buf, int x0, int y0, int width, int height);
  
  //: Return the image interpreted as rgb bytes.
  //virtual bool get_section_rgb_byte(void* buf, int plane, int x0, int y0, int width, int height) const;
  //virtual bool get_section_float(void* buf, int plane, int x0, int y0, int width, int height) const;
  //virtual bool get_section_byte(void* buf, int plane, int x0, int y0, int width, int height) const;

  char const* file_format() const;
  
//protected:
  vil_stream* is_;

  int magic_;

  int width_;
  int height_;
  int planes_;
  
  int pixmin_;
  int pixmax_;
  int storage_;
  int dimension_;
  int colormap_;
  char* imagename_;
  int start_of_data_;
  int components_;
  int bits_per_component_;
  int bytes_per_component_;

  bool read_offset_tables();

  // Read a Run-Length encoded section
  bool get_section_rle(void* ib, int x0, int y0, int xs, int ys) const;

  // Read a plain section
  bool get_section_verbatim(void* ib, int x0, int y0, int xs, int ys) const;

};

#endif   // DO NOT ADD CODE AFTER THIS LINE! END OF DEFINITION FOR CLASS vil_iris_file_format.
