#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Geometry.h>
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>

#include "Rcpp.h"


// [[Rcpp::export(name = ".sfwktbuffer")]]
std::vector<std::string> wktbuffer(std::vector<std::string> wkt, double d) {
	Rcpp::Rcout << "geos cpp sf\n";
	std::vector<std::string> out;
	out.reserve(wkt.size());
	geos::geom::GeometryFactory::Ptr factory = geos::geom::GeometryFactory::create();
	geos::io::WKTReader reader(*factory);
	geos::io::WKTWriter writer;
	writer.setTrim(true); 
	for (size_t i=0; i<wkt.size(); i++) {
		std::unique_ptr<geos::geom::Geometry> geom_inp(reader.read(wkt[i]));
		try {
			std::unique_ptr<geos::geom::Geometry> buf = geom_inp->buffer(d);
			out.push_back(writer.write(buf.get()));
		} catch(...) {
			Rcpp::stop("failed on geom" + i);
		}
	}
	return out;
}
