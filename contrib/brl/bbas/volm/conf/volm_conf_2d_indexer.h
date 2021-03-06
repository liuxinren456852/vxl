//This is brl/bbas/volm/conf/volm_conf_2d_indexer.h
#ifndef volm_conf_2d_indexer_h_
#define volm_conf_2d_indexer_h_
//:
// \file
// \brief  A class to create a 2d configurational index using pre-constructed land map indices
//
// \author Yi Dong
// \data August 25, 2014
// \verbatim
//   Modifications
//    <none yet>
// \endverbatim
//
#include <volm/conf/volm_conf_indexer.h>
#include <volm/conf/volm_conf_object.h>
#include <volm/conf/volm_conf_land_map_indexer.h>
#include <bvgl/algo/bvgl_2d_geo_index.h>
#include <vgl/vgl_box_2d.h>
#include <vpgl/vpgl_lvcs.h>
#include <vpgl/vpgl_lvcs_sptr.h>

class volm_conf_2d_indexer : public volm_conf_indexer
{
public:
  static vcl_string name_;
  // ==================== constructor =======================

  //: default constructor
  volm_conf_2d_indexer() : radius_(0.0), land_map_root_(0) { land_map_leaves_.clear(); }
  //: constructor by giving out_put folder, land map index folder and radius
  volm_conf_2d_indexer(double const& radius, vcl_string const& out_folder, vcl_string const& land_map_folder, unsigned const& tile_id);

  ~volm_conf_2d_indexer() {}

  // ======================= access =========================
  double radius()                                      const { return radius_; }
  double radius_in_degree()                            const { return radius_in_degree_; }
  vcl_string land_map_folder()                         const { return land_map_folder_; }
  bvgl_2d_geo_index_node_sptr land_map_root()          const { return land_map_root_; }
  vcl_vector<bvgl_2d_geo_index_node_sptr>& land_map_leaves() { return land_map_leaves_; }

  // ======================= method =========================

  //: return the name of the indexer
  virtual vcl_string get_index_name() const { return name_; }

  //: generate parameter files for different indexer
  virtual bool write_params_file();

  //: handles any necessary loading during indexing as current indexer switches processing from one location leaf to next leaf
  //: load the contents for land map leaves that intersect location leaf
  virtual bool get_next();

  //: function to create index for a location
  virtual bool extract(double const& lon, double const& lat, double const& elev, vcl_vector<volm_conf_object>& values);

private:
  //: search radius
  double radius_;
  //: radius in degree
  double radius_in_degree_;
  //: square value of radius
  double square_radius_;
  //: land map folder
  vcl_string land_map_folder_;
  //: land map indexer
  bvgl_2d_geo_index_node_sptr land_map_root_;
  vcl_vector<bvgl_2d_geo_index_node_sptr> land_map_leaves_;
  //: function to calculate the minimum distance form a rectangular region to a points
  double min_dist_from_box_to_pt(vpgl_lvcs lvcs, vgl_box_2d<double> const& box, double const& lon, double const& lat);

};

#endif // volm_conf_2d_indexer_h_
