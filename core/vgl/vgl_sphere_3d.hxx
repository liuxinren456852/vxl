#ifndef vgl_sphere_3d_hxx_
#define vgl_sphere_3d_hxx_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
//:
// \file
// \brief a sphere in 3D nonhomogeneous space
// \author Ian Scott

#include "vgl_sphere_3d.h"
#include <vcl_cmath.h>
#include <vcl_iostream.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_closest_point.h>
#include <vgl/vgl_line_3d_2_points.h>


//: Return true iff the point p is inside (or on) this sphere
template <class T>
bool vgl_sphere_3d<T>::contains(vgl_point_3d<T> const& p) const
{
  return r_ >= 0 && (p-c_).sqr_length() <= r_*r_;
}


//: Calculate the end points of a line clipped by this sphere.
// \return true if any of the line touches the sphere.
template <class T>
bool vgl_sphere_3d<T>::clip(const vgl_line_3d_2_points<T> & line,
                            vgl_point_3d<T> &p1, vgl_point_3d<T> &p2) const
{
  // The empty sphere does not intersect anything:
  if (r_ < 0) return false;

  vgl_point_3d<T> cp = vgl_closest_point(line, c_);

  T cp_sqr_len = (cp - c_).sqr_length();
  if (cp_sqr_len > r_*r_) return false;
  double arg = static_cast<double>(r_*r_ - cp_sqr_len);//for VC10
  T half_chord_len = static_cast<T>(vcl_sqrt(arg));

  vgl_vector_3d<T> linevec = line.direction();
  linevec *= half_chord_len / linevec.length();

  p1 = cp - linevec;
  p2 = cp + linevec;

  return true;
}


//: Writes "<vgl_sphere_3d centre=vgl_point_3d<x,y,z> radius=r)>" to stream
template <class T>
vcl_ostream& vgl_sphere_3d<T>::print(vcl_ostream& os) const
{
  return os << "<vgl_sphere_3d centre=" << c_
            << "radius=" << r_ << '>';
}


//: Read from stream, possibly with formatting.
//  Either just reads 4 blank-separated numbers,
//  or reads 4 comma-separated numbers,
//  or reads 4 numbers in parenthesized form "(123, 321, 567, 890)"
template <class T>
vcl_istream& vgl_sphere_3d<T>::read(vcl_istream& is)
{
  if (! is.good()) return is; // (TODO: should throw an exception)
  bool paren = false;
  T cx, cy, cz, r;
  is >> vcl_ws; // jump over any leading whitespace
  if (is.eof()) return is; // nothing to be set because of EOF (TODO: should throw an exception)
  if (is.peek() == '(') { is.ignore(); paren=true; }
  is >> vcl_ws >> cx >> vcl_ws;
  if (is.eof()) return is;
  if (is.peek() == ',') is.ignore();
  is >> vcl_ws >> cy >> vcl_ws;
  if (is.eof()) return is;
  if (is.peek() == ',') is.ignore();
  is >> vcl_ws >> cz >> vcl_ws;
  if (is.eof()) return is;
  if (is.peek() == ',') is.ignore();
  is >> vcl_ws >> r >> vcl_ws;
  if (paren) {
    if (is.eof()) return is;
    if (is.peek() == ')') is.ignore();
    else                  return is; // closing parenthesis is missing (TODO: throw an exception)
  }
  set_centre(vgl_point_3d<T>(cx,cy,cz));
  set_radius(r);
  return is;
}

template <class Type>
void vgl_sphere_3d<Type>::spherical_to_cartesian(Type elevation_rad, Type azimuth_rad,
                                                 Type& x, Type& y, Type& z) const{

  double el = static_cast<double>(elevation_rad), az = static_cast<double>(azimuth_rad);
  double cx = static_cast<double>(c_.x()),cy =static_cast<double>(c_.y()), cz = static_cast<double>(c_.z());
  double r = static_cast<double>(r_);
  double se = vcl_sin(el), ce = vcl_cos(el);
  double sa = vcl_sin(az), ca = vcl_cos(az);

  x = static_cast<Type>((r*se*ca)+cx);
  y = static_cast<Type>((r*se*sa)+cy);
  z = static_cast<Type>((r*ce)+cz);

}

template <class Type>
void vgl_sphere_3d<Type>::spherical_to_cartesian(Type elevation_rad, Type azimuth_rad, vgl_point_3d<Type>&  pt) const
{

  Type x, y, z;
  spherical_to_cartesian(elevation_rad, azimuth_rad, x, y, z);
  pt.set(x, y, z);

}
template <class Type>
void vgl_sphere_3d<Type>::cartesian_to_spherical(Type x, Type y, Type z, Type& elevation_rad, Type& azimuth_rad) const{
  double xd = static_cast<double>(x-c_.x()), yd = static_cast<double>(y-c_.y()), zd = static_cast<double>(z-c_.z());
  double r  = vcl_sqrt(xd*xd + yd*yd +zd*zd);
  elevation_rad = static_cast<Type>(vcl_acos(zd/r));
  azimuth_rad = static_cast<Type>(vcl_atan2(yd,xd));
}
template <class Type>
void vgl_sphere_3d<Type>::cartesian_to_spherical(vgl_point_3d<Type> const& pt, Type& elevation_rad, Type& azimuth_rad) const{
  return cartesian_to_spherical(pt.x(), pt.y(), pt.z(),elevation_rad,azimuth_rad);
}

//: Writes "<vgl_sphere_3d centre=vgl_point_3d<x,y,z> radius=r)>" to stream
template <class T>
vcl_ostream& operator<<(vcl_ostream& os, const vgl_sphere_3d<T>& sph)
{
  return sph.print(os);
}


//: Read from stream, possibly with formatting.
//  Either just reads 4 blank-separated numbers,
//  or reads 4 comma-separated numbers,
//  or reads 4 numbers in parenthesized form "(123, 321, 567, 890)"
template <class T>
vcl_istream& operator>>(vcl_istream& is, vgl_sphere_3d<T>& sph)
{
  return sph.read(is);
}


#undef VGL_SPHERE_3D_INSTANTIATE
#define VGL_SPHERE_3D_INSTANTIATE(T) \
template class vgl_sphere_3d<T >; \
template vcl_ostream& operator<<(vcl_ostream&, vgl_sphere_3d<T >const&); \
template vcl_istream& operator>>(vcl_istream&, vgl_sphere_3d<T >&)


#endif // vgl_sphere_3d_hxx_
