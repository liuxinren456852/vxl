/*
 *
 *  Copyright (C) 1996-2002, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmimgle
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose: DicomMonochrome2Image (Header)
 *
 */


#ifndef __DIMO2IMG_H
#define __DIMO2IMG_H

#include "osconfig.h"
#include "dctypes.h"

#include "dimoimg.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for MONOCHROME2 images
 */
class DiMono2Image
  : public DiMonoImage
{
 public:

    /** constructor
     *
     ** @param  docu    pointer to dataset (encapsulated)
     *  @param  status  current image status
     */
    DiMono2Image(const DiDocument *docu,
                 const EI_Status status);

    /** constructor, modality (linear)
     *
     ** @param  docu       pointer to dataset (encapsulated)
     *  @param  status     current image status
     *  @param  slope      rescale slope
     *  @param  intercept  rescale intercept
     */
    DiMono2Image(const DiDocument *docu,
                 const EI_Status status,
                 const double slope,
                 const double intercept);

    /** constructor, modality (LUT)
     *
     ** @param  docu         pointer to dataset (encapsulated)
     *  @param  status       current image status
     *  @param  data         element containing the modality LUT data
     *  @param  descriptor   element containing the modality LUT descriptor
     *  @param  explanation  element containing the modality LUT explanation (optional)
     */
    DiMono2Image(const DiDocument *docu,
                 const EI_Status status,
                 const DcmUnsignedShort &data,
                 const DcmUnsignedShort &descriptor,
                 const DcmLongString *explanation);

    /** constructor, convert color images to monochrome
     *
     ** @param  image  pointer to reference image
     *  @param  red    coefficient by which the red component is weighted
     *  @param  green  coefficient by which the green component is weighted
     *  @param  blue   coefficient by which the blue component is weighted
     */
    DiMono2Image(const DiColorImage *image,
                 const double red,
                 const double green,
                 const double blue);

    /** constructor, createMonoOutput
     *
     ** @param  image   pointer to reference image
     *  @param  pixel   pointer to output pixel data used for the new image
     *  @param  frame   number of frame stored in the new image object
     *  @param  stored  number of bits stored
     *  @param  alloc   number of bits allocated
     */
    DiMono2Image(const DiMonoImage *image,
                 const DiMonoOutputPixel *pixel,
                 const unsigned long frame,
                 const int stored,
                 const int alloc);

    /** destructor
     */
    virtual ~DiMono2Image();

    /** get color model of internal pixel representation.
     *  @return always returns EPI_Monochrome2
     */
    virtual EP_Interpretation getInternalColorModel() const
    {
        return EPI_Monochrome2;
    }

    /** get pixel data with specified format.
     *  (memory is handled internally)
     *
     ** @param  frame   number of frame to be rendered
     *  @param  bits    number of bits for the output pixel data (depth)
     *  @param  planar  flags, whether the output data (for multi-planar images) should be planar or not
     *
     ** @return untyped pointer to the pixel data if successful, NULL otherwise
     */
    virtual void *getOutputData(const unsigned long frame,
                                const int bits,
                                const int planar = 0);

    /** get pixel data with specified format.
     *  (memory is handled externally)
     *
     ** @param  buffer  untyped pointer to the externally allocated memory buffer
     *  @param  size    size of the memory buffer in bytes (will be checked)
     *  @param  frame   number of frame to be rendered
     *  @param  bits    number of bits for the output pixel data (depth)
     *  @param  planar  flags, whether the output data (for multi-planar images) should be planar or not
     *
     ** @return status, true if successful, false otherwise
     */
    virtual int getOutputData(void *buffer,
                              const unsigned long size,
                              const unsigned long frame,
                              const int bits,
                              const int planar = 0);

    /** create copy of current image object
     *
     ** @param  fstart  first frame to be processed
     *  @param  fcount  number of frames
     *
     ** @return pointer to new DicomImage object (NULL if an error occurred)
     */
    DiImage *createImage(const unsigned long fstart,
                         const unsigned long fcount) const;

    /** create scaled copy of specified (clipping) area of the current image object.
     *
     ** @param  left_pos      x coordinate of top left corner of area to be scaled
     *                        (referring to image origin, negative values create a border around the image)
     *  @param  top_pos       y coordinate of top left corner of area to be scaled
     *  @param  clip_width    width of area to be scaled
     *  @param  clip_height   height of area to be scaled
     *  @param  scale_width   width of scaled image (in pixels)
     *  @param  scale_height  height of scaled image (in pixels)
     *  @param  interpolate   specifies whether scaling algorithm should use interpolation (if necessary)
     *                        default: no interpolation (0), 1 = pbmplus algorithm, 2 = c't algorithm
     *  @param  aspect        specifies whether pixel aspect ratio should be taken into consideration
     *                        (if true, width OR height should be 0, i.e. this component will be calculated
     *                         automatically)
     *  @param  pvalue        P-value used for the border outside the image (0..65535)
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    DiImage *createScale(const signed long left_pos,
                         const signed long top_pos,
                         const unsigned long clip_width,
                         const unsigned long clip_height,
                         const unsigned long scale_width,
                         const unsigned long scale_height,
                         const int interpolate,
                         const int aspect,
                         const Uint16 pvalue) const;

    /** create a flipped copy of the current image
     *
     ** @param  horz  flip horizontally if true
     *  @param  vert  flip vertically if true
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    DiImage *createFlip(const int horz,
                        const int vert) const;

    /** create a rotated copy of the current image.
     *
     ** @param  degree  angle by which the image shall be rotated
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    DiImage *createRotate(const int degree) const;

    /** create monochrome copy of the current image.
     *  Since the image is already monochrome the effect is the same as with createImage().
     *
     ** @param  dummy  not used
     *  @param  dummy  not used
     *  @param  dummy  not used
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    DiImage *createMono(const double,
                        const double,
                        const double) const;


 protected:

    /** constructor
     *
     ** @param  image   pointer to dataset (encapsulated)
     *  @param  status  current image status
     *  @param  dummy   (necessary to be different from another constructor)
     */
    DiMono2Image(const DiDocument *docu,
                 const EI_Status status,
                 const char dummy);

    /** constructor, copy
     *
     ** @param  image   pointer to reference image
     *  @param  fstart  first frame to be processed
     *  @param  fcount  number of frames
     */
    DiMono2Image(const DiMonoImage *image,
                 const unsigned long fstart,
                 const unsigned long fcount);

    /** constructor, scale/clip
     *
     ** @param  image         pointer to reference image
     *  @param  left_pos      x coordinate of top left corner of area to be scaled
     *                        (referring to image origin, negative values create a border around the image)
     *  @param  top_pos       y coordinate of top left corner of area to be scaled
     *  @param  src_cols      width of area to be scaled
     *  @param  src_rows      height of area to be scaled
     *  @param  dest_cols     width of scaled image (in pixels)
     *  @param  dest_rows     height of scaled image (in pixels)
     *  @param  interpolate   specifies whether scaling algorithm should use interpolation (if necessary)
     *                        default: no interpolation (0), 1 = pbmplus algorithm, 2 = c't algorithm
     *  @param  aspect        specifies whether pixel aspect ratio should be taken into consideration
     *                        (if true, width OR height should be 0, i.e. this component will be calculated
     *                         automatically)
     *  @param  pvalue        P-value used for the border outside the image (0..65535)
     */
    DiMono2Image(const DiMonoImage *image,
                 const signed long left_pos,
                 const signed long top_pos,
                 const Uint16 src_cols,
                 const Uint16 src_rows,
                 const Uint16 dest_cols,
                 const Uint16 dest_rows,
                 const int interpolate = 0,
                 const int aspect = 0,
                 const Uint16 pvalue = 0);

    /** constructor, flip
     *
     ** @param  image  pointer to reference image
     ** @param  horz   flip horizontally if true
     *  @param  vert   flip vertically if true
     */
    DiMono2Image(const DiMonoImage *image,
                 const int horz,
                 const int vert);

    /** constructor, rotate
     *
     ** @param  image   pointer to reference image
     *  @param  degree  angle by which the image shall be rotated
     */
    DiMono2Image(const DiMonoImage *image,
                 const int degree);
};


#endif
