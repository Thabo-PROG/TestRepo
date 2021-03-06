#include "screen.h"

// Screen's constructor
Screen::Screen(string::size_type height, string::size_type width, char bkground):
	height_{height},// initialises height_ with height
	width_{width},  // initialises width_ with width
	_screen(height * width, bkground)	// size of _screen is height * width
										// all positions initialized with
										// character value of bkground
{ /* all the work is done in the member initialization list */ }

void Screen::forward()
{   // advance cursor_ one screen element
	++cursor_;

	// wrap around if the cursor_ is at the end of the screen
	if ( cursor_ == _screen.size()) home();

	return;
}

void Screen::back()
{   // move cursor_ backward one screen element
	// check for top of screen; wrap around
	if ( cursor_ == TOP_LEFT )
		end();
	else
		--cursor_;

	return;
}

void Screen::up()
{
    // move cursor_ up one row of screen
    // Exercise 4.4
	// if cursor at top-left position of the screen , move cursor to bottom-right position of the screen
	if ( cursor_ == 0)
       this->end();

	else if ( row() == 1 ) // at top?
      cursor_ += width_*(height_-1)-1;

	else
		cursor_ -= width_;

	return;
}

void Screen::down()
{
    // move cursor_ down one row of screen

    // Exercise 4.4
	// if cursor at bottom-right position of the screen , move cursor to top-left position of the screen
    if ( cursor_ == (height_-1)*width_ )
         this->home();

	if ( row()  == height_ ) // at bottom?
         cursor_-= width_*(height_-1);

	else
		cursor_ += width_;

	return;
}
void Screen::move( string::size_type row, string::size_type col )
{   // move cursor_ to absolute position
	// valid screen position?
	if ( checkRange( row, col ) )
	{
		// row location
		auto row_loc = (row-1) * width_;
		cursor_ = row_loc + col - 1;
	}

	return;
}

char Screen::get( string::size_type row, string::size_type col )
{
	// position cursor_
	move( row, col );
	// the other get() member function
	return get();
}

void Screen::set( char ch )
{
	if ( ch == '\0' )
		cerr << "Screen::set warning: " << "null character (ignored).\n";
	else _screen[cursor_] = ch;

	return;
}

void Screen::set( const string& s )
{   // write string beginning at current cursor_ position
	auto space = remainingSpace();
	auto len   = s.size();
	if ( space < len ) {
       cerr << "Screen::set - Truncating, "
			<< "space available: " << space
			<< ", string length: " << len
			<< endl;
		len = space;
	}

	_screen.replace( cursor_, len, s );
	cursor_ += len - 1;

	return;
}

void Screen::clear( char bkground )
{
    // reset the cursor and clear the screen
	cursor_ = TOP_LEFT;
	// assign the string
	_screen.assign(
    // with size() characters
    _screen.size(),
    // of value bkground
    bkground
		         );

	return;
}

void Screen::reSize( string::size_type h, string::size_type w, char bkground )
{
    // can only *increase* a screen's size to height h and width w
	// remember the content of the screen
	string local{_screen};
	auto local_pos = TOP_LEFT;

	// replaces the string to which _screen refers
	_screen.assign(      // assign the string
		h * w,           // with h * w characters
		bkground         // of value bkground
		);

	// copy content of old screen into the new one
	for ( string::size_type ix = 0; ix < height_; ++ix )
	{ // for each row
		string::size_type offset = w * ix; // row position
		for ( string::size_type iy = 0; iy < width_; ++iy )
			// for each column, assign the old value
			_screen.at(offset + iy) = local[ local_pos++ ]; // Exercise 4.2
			                                                // The string class member function (at) returns a char of a string
			                                                // by reference and not a duplicate of the char of that specified
			                                                // string position. This means the assignment in line 172 prevents
			                                                // duplication of string the local string leading to unwanted
			                                                // memory allocation.
	}

	height_ = h;
	width_ = w;
	// cursor_ remains unchanged

	return;
}

void Screen::display() const
{
	for ( string::size_type ix = 0; ix < height_; ++ix )
	{ // for each row
		string::size_type offset = width_ * ix; // row position
		for ( string::size_type iy = 0; iy < width_; ++iy )
			// for each column, write element
			cout << _screen[ offset + iy ];
		cout << endl;
	}
	return;
}

bool Screen::checkRange( string::size_type row, string::size_type col ) const
{
    // validate coordinates
	if (row < 1 || row > height_ || col < 1 || col > width_)
	{
		cerr << "Screen coordinates ("<< row << ", " << col << " ) out of bounds.\n";
		return false;
	}
	return true;
}

string::size_type Screen::remainingSpace() const
{
    // includes current position
	auto size = width_ * height_   ;
	return(size - cursor_);
}

string::size_type Screen::row() const
{
    // return current row
	return (cursor_ + width_)/width_;
}

// Exercise 4.3
void Screen::move(Direction dir)
{
   Direction back__     = Direction::BACK;
   Direction Down__     = Direction::DOWN;
   Direction Home__     = Direction::HOME;
   Direction End__      = Direction::END;
   Direction Up__       = Direction::UP;
   Direction Forward__  = Direction::FORWARD;

   if(dir == back__)   { this->back();   }

   if(dir == Down__)   { this->down();   }

   if(dir == Home__)   { this->home();   }

   if(dir == End__)    { this->end();    }

   if(dir == Up__)     { this->up();     }

   if(dir == Forward__){ this->forward();}

}

// Exercise 4.5
void Screen::Empty_Square(string::size_type row,string::size_type col,string::size_type length_Size)
{
    if (true == checkRange(row,col))
    {
        if( true==this->IsHorizontalDimensionValid(row,col,length_Size)&&
          true==this->IsVerticalDimensionValid(row,col,length_Size)  )

        {  this->Print_Square(row,col,length_Size);              }

      else if ( false==this->IsHorizontalDimensionValid(row,col,length_Size)||
         false==this->IsVerticalDimensionValid(row,col,length_Size))

        {  cerr<<" length of square is invalid " ;    cout<<endl;}
    }
}


// Exercise 4.5
bool Screen::IsHorizontalDimensionValid(string::size_type row,string::size_type col,string::size_type length_Size)
{
    if ((row+length_Size)/width_<1)
    {    return true;                       }

    else { return false;  }
}

// Exercise 4.5
bool Screen::IsVerticalDimensionValid(string::size_type row,string::size_type col,string::size_type length_Size)
{
    if ((col+length_Size)/height_ <1)
    {   return true;                        }

    else { return false;  }
}

// Exercise 4.5
void Screen::Print_Square(string::size_type row,string::size_type col,string::size_type length_Size)
{
      move(row,col);
      for(int i = 0 ; i<(length_Size-1) ; i++)
      { set('*');move(Direction::FORWARD);  }

      move(row,col);
      for(int i = 0 ; i<(length_Size-1) ; i++)
      { move(Direction::DOWN); set('*');    }

      move(row+length_Size-1,col);
      for(int i = 0 ; i<(length_Size-1) ; i++)
      { move(Direction::FORWARD); set('*'); }

      move(row,col+length_Size-1);
      for(int i = 0 ; i<(length_Size-1) ; i++)
      { set('*'); move(Direction::DOWN);    }

}

