#pragma once

namespace drawing
{
	struct rect_t
	{
		rect_t() = default;
		rect_t( long l, long t, long r, long b ) : left( l ), top( t ), right( r ), bottom( b ){};
		rect_t( const RECT r ) : left( r.left ), top( r.top ), right( r.right ), bottom( r.bottom ){};

		long left, top, right, bottom;
	};

	struct paint_t
	{
		paint_t() = default;
		paint_t( void_t h, rect_t s, bool e, bool r, bool u ) : hdc( static_cast< HDC >( h ) ), 
			size( s ), erase( e ), restore( r ), update( u ){};
		paint_t( PAINTSTRUCT* paint ) : hdc( paint->hdc ), size( paint->rcPaint ), erase( paint->fErase ),
			restore( paint->fRestore ), update( paint->fIncUpdate ){};

		void_t hdc;
		rect_t size;
		int erase, restore, update;
	};

	void initialize( void_t window, paint_t& paint, uint_t size[ 2 ] );
}