//
// (c) Copyright 2017 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 13, 2017
//
#include <pni/nexus/xml/dataset_creation_list_builder.hpp>
#include <pni/nexus/xml/dimension_node_handler.hpp>
#include <pni/parsers.hpp>
#include <pni/error.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <iostream>
#include <vector>

namespace pni {
namespace nexus {
namespace xml {

DatasetCreationListBuilder::DatasetCreationListBuilder(const Node &node):
    node_(node),
    dataspace_builder_(node)
{}

void DatasetCreationListBuilder::set_chunking(hdf5::property::DatasetCreationList &dcpl) const
{
  dcpl.layout(hdf5::property::DatasetLayout::Chunked);

  //set the default chunk layout
  hdf5::Dimensions chunk = dataspace_builder_.build().current_dimensions();
  chunk.front() = 1;

  auto has_chunk_node = node_.get_child_optional("chunk");
  if(has_chunk_node)
  {
    Node chunk_node = has_chunk_node.get();
    chunk = DimensionNodeHandler::dimensions(chunk_node);
  }

  dcpl.chunk(chunk);

}

void DatasetCreationListBuilder::set_compression(hdf5::property::DatasetCreationList &dcpl) const
{
  //setting up filters i required
  auto has_strategy_node = node_.get_child_optional("strategy");
  if(has_strategy_node)
  {
    Node node = has_strategy_node.get();

    bool use_compression = false;
    bool use_shuffle     = false;
    long compression_rate = 0;

    if(node.has_attribute("compression"))
      use_compression = node.attribute("compression").data<hdf5::datatype::EBool>();

    if(node.has_attribute("shuffle"))
      use_shuffle = node.attribute("shuffle").data<hdf5::datatype::EBool>();

    if(node.has_attribute("rate"))
      compression_rate = static_cast<long>(node.attribute("rate").data<size_t>());

    if(use_compression)
    {
      if(use_shuffle)
	{
	  hdf5::filter::Shuffle shuffle;
	  shuffle(dcpl);
	}

      hdf5::filter::Deflate deflate(compression_rate);
      deflate(dcpl);
   }

   IndexFilterParametersMap index_parameters;
   unsigned int maxindex = 0;
   unsigned int index = 0;
   for(auto value: node){
     if(value.first == "filter"){
       if(Node(value.second).has_attribute("index")){
	 index =
	   static_cast<unsigned int>(Node(value.second).attribute("index").data<size_t>());
       }
       else {
	 index = 0;
       }
       if(maxindex < index) {
	 maxindex = index;
       }
       index_parameters[index] = parameters_from_node(value.second);
     }
   }
   
   if(!index_parameters.empty()){
     for(unsigned int ind = 0; ind <= maxindex; ind++){
       if(index_parameters.find(ind) != index_parameters.end()){
	 unsigned int filter_id = 0;
	 std::string name{};
	 std::string str_cd_values{};
	 std::string availability{};

	 std::tie(filter_id, name, str_cd_values, availability) =
	   index_parameters[ind];

	 auto avail = hdf5::filter::Availability::Mandatory;
	 if(availability == "optional")
	   avail = hdf5::filter::Availability::Optional;
	 
	 if(filter_id > 0) {
	   if(hdf5::filter::is_filter_available(filter_id)){

	       std::vector<unsigned int> cd_values;
	       get_cd_values(str_cd_values, cd_values);
	       hdf5::filter::ExternalFilter externalfilter(filter_id,
							   cd_values,
							   name);
	       if(availability.empty()) {
		 externalfilter(dcpl);
	       }
	       else {
		 externalfilter(dcpl, avail);
	       }
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	      std::stringstream ss;
	      ss << "The '" << name << "' ("<< filter_id <<") filter not available";
	      throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					 ss.str());
	   }
	       
	 }
	 else if(name == "shuffle"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_SHUFFLE)){
	       hdf5::filter::Shuffle shuffle;
	       shuffle(dcpl);
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"Shuffle filter not available");
	   }
	 }
	 else if(name == "deflate"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_DEFLATE)){
	       compression_rate = static_cast<long>(std::stoul(str_cd_values));
	       hdf5::filter::Deflate deflate(compression_rate);
	       deflate(dcpl);
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"Deflate filter not available");
	   }
	 }
	 else if(name == "nbit"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_NBIT)){
	       hdf5::filter::NBit nbit;
	       nbit(dcpl);
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"NBit filter not available");
	   }
	 }
	 else if(name == "fletcher32"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_FLETCHER32)){
	       hdf5::filter::Fletcher32 fletcher32;
	       fletcher32(dcpl);
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"Fletcher32 filter not available");
	   }
	 }
	 else if(name == "szip"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_SZIP)){
	       std::vector<unsigned int> cd_values;
	       get_cd_values(str_cd_values, cd_values);

	       hdf5::filter::SZip szip;
	       if(cd_values.size() >= 1) {
		 szip.option_mask(cd_values[0]);
	       }
	       if(cd_values.size() >= 2){
		 szip.pixels_per_block(cd_values[1]);
	       }
	       szip(dcpl);
	   }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"SZip filter not available");
	   }
	 }
	 else if(name == "scaleoffset"){
	   if(hdf5::filter::is_filter_available(H5Z_FILTER_SCALEOFFSET)){
	       std::vector<unsigned int> cd_values;
	       get_cd_values(str_cd_values, cd_values);
	       
	       hdf5::filter::ScaleOffset scaleoffset;
	       if(cd_values.size() >= 1){
		 scaleoffset.scale_type(static_cast<hdf5::filter::ScaleOffset::ScaleType>(cd_values[0]));
	       }
	       if(cd_values.size() >= 2) {
		 scaleoffset.scale_factor(static_cast<int>(cd_values[1]));
	       }
	       scaleoffset(dcpl);
	     }
	   else if(avail == hdf5::filter::Availability::Mandatory){
	     throw filter_not_available(PNINEXUS_EXCEPTION_RECORD,
					"ScaleOffset filter not available");
	   }
	 }
       }
     }
   }
  }
}

hdf5::property::DatasetCreationList DatasetCreationListBuilder::build() const
{
  using hdf5::property::DatasetCreationList;

  DatasetCreationList dcpl;
  set_chunking(dcpl);
  set_compression(dcpl);

  return dcpl;
}

//------------------------------------------------------------------------
void DatasetCreationListBuilder::get_cd_values(const std::string text,
					std::vector<unsigned int> & cd_values) const
{
  std::stringstream ss(text);

  while (ss.good()) {
    std::string sval;
    getline(ss, sval, ',');
    cd_values.push_back(std::stoul(sval));
  }
}

//------------------------------------------------------------------------
FilterParameters DatasetCreationListBuilder::parameters_from_node(const Node &node)
{
  unsigned int filter_id = 0;
  std::string name{};
  std::string  availability{};
  std::string cd_values{};

  if(node.has_attribute("id"))
    filter_id =
      static_cast<unsigned int>(node.attribute("id").data<size_t>());
  if(node.has_attribute("name"))
    name = node.attribute("name").data<std::string>();
  if(node.has_attribute("cd_values"))
    cd_values = node.attribute("cd_values").data<std::string>();
  if(node.has_attribute("availability"))
    availability = node.attribute("availability").data<std::string>();

  return {filter_id, name, cd_values, availability};
}

} // namespace xml
} // namespace nexus
} // namespace pni
