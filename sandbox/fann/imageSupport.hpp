/*
 *  imageSupport.h
 *  fannTest
 *
 *  Created by David Love on 1/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_SUPPORT_H
#define IMAGE_SUPPORT_H

#include <vector>

// only new boost API's
#define BOOST_FILESYSTEM_NO_DEPRECATED
// boost filesystem libs
#include <boost/filesystem.hpp>
// because I'm lazy
#define bf boost::filesystem

// for imageArray definition
#include "imageNetwork.hpp"

// simple class to keep track of a set of images in a single directory
class imageDirectory {
private:
	const bf::path m_directory;
	imageArray m_images;
	imageArray m_imagesReversed;
public:
	imageDirectory (const bf::path& directory);
	inline const bf::path& path() { return m_directory; }
	inline const unsigned int size() { return m_images.size(); }
	inline const std::vector<fann_type>& getImage (unsigned int index) { return m_images[index]; }
	inline const imageArray& getImages (bool reversed = false) {
		if (reversed) {
			return m_imagesReversed;
		} else {
			return m_images;
		}
	}
};
	
#endif // IMAGE_SUPPORT_H
