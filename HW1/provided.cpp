#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <cstring>

// ======================================================================================

// Helper function to read the provided font from a file.  The format
// of the font file is described in comments below.  The width,
// height, and bitmap_letters variables are set by this function.
void ReadFont(const std::string &font_file, 
	      int &width,
	      int &height,
	      std::vector<std::vector<std::string> > &bitmap_letters) {

  // open the font file for reading
  std::ifstream istr(font_file.c_str());
  if (!istr) { 
    std::cerr << "ERROR: cannot open font file " << font_file << std::endl; 
    exit(0);
  }

  // read in the width & height for every character in the file
  istr >> width >> height;
  assert (width >= 1);
  assert (height >= 1);

  // Create a vector to store all 256 ASCII characters of the
  // characters.  Each character is represented as a vector of
  // <height> strings that are each <width> wide.  Initially the
  // characters are unknown (represented with the '?' character).
  bitmap_letters = std::vector<std::vector<std::string> > 
    ( 256, std::vector<std::string> ( height, std::string(width, '?')));

  // read in all the characters
  // first is the ascii integer representation of the character
  int ascii;
  while (istr >> ascii) {
    assert (ascii >= 0 && ascii < 256);
    // next the character is printed in single quotes
    char c;
    istr >> c;
    assert (c == '\'');
    // use std::noskipws to make sure we can read the space character correctly
    istr >> std::noskipws >> c;
    // verify that the ascii code matches the character
    assert (c == (char)ascii);
    // switch back to std::skipws mode
    istr >> std::skipws >> c;
    assert (c == '\'');
    // read in the letter
    std::vector<std::string> bitmap;
    std::string tmp;
    for (int i = 0; i < height; i++) {
      istr >> tmp;
      assert ((int)tmp.size() == width);
      // make sure the letter uses only '#' and '.' characters
      for (unsigned int j = 0; j < tmp.size(); j++) { 
        assert (tmp[j] == '.' || tmp[j] == '#'); 
      }
      bitmap.push_back(tmp);
    }
    // overwrite the initially unknown letter in the vector
    bitmap_letters[ascii] = bitmap;
  }
}

std::string replacechar(std::string input, std::string f, std::string bg)
{
	std::string out="";
  for(int i=0; i<input.length(); i++)
  {
    if(input[i] == '#')
      out = out+f;
    else
     	out = out+bg;
  }
  return out;
}

int main(int argc, char* argv[])
{
  if(argc != 4 && argc != 6)
  {
    std::cerr << "Incorrect number of inputs" << std::endl;
    return 1;
  }
  
  //std::cout << "YES " << argv[1] << std::endl;
  std::vector<std::vector<std::string> >temp;
	int w=0, h=0;
	ReadFont(argv[2],w,h,temp);
	
	//display
  if(std::strcmp(argv[1], "display") == 0)
  {
		std::vector<int>output;
		std::string input = argv[3];
		
		for(int i=0; i<input.length(); i++)
		  output.push_back(int(input[i]));
	
		for(int i=0; i<h; i++)
		{
		  for(int k=0; k<output.size(); k++)
			{
				std::cout << replacechar(temp[output[k]][i], argv[4], argv[5]) << ".";
			}
	   std::cout << std::endl;
	  }
	}
	//read
	if(std::strcmp(argv[1], "read") == 0)
	{
		std::ifstream file;
		file.open(argv[3]);
		std::vector<std::string>filestuff;
		std::string s;
		std::vector<std::string>check;
		
		while(file >> s)
			filestuff.push_back(s);
		
		//within each word
		for(int j=0; j<filestuff[0]/w; j++)
		{
			//each word
			for(int i=0; i<filestuff.size(); i++)
			{
				//each char
				for(int k=0; k<w; k++)
				{
					//grab the part of the string that in the char
					std::string t = filestuff[i].substr(j*w, j*w+w);
					//create the vector that is the char
					check.push_back(t);
				}
			}
		}
		
	}
	
	
}

// ======================================================================================
