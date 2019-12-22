#pragma once

namespace window
{
	struct window_t
	{
		window_t() = default;
		window_t( uint_t s, int c, int w, void_t i, void_t o, void_t u, void_t b, void_t p, char_t m, char_t n )
			: style( s ), colors( c ), windows( w ), instance( i ), icon( o ), cursor( u ), background( b ), 
			process( p ), menu( m ), name( n ){};
		window_t( WNDCLASSW* window ) : style( window->style ), colors( window->cbClsExtra ), windows( window->cbWndExtra ),
			instance( window->hInstance ), icon( window->hIcon ), cursor( window->hCursor ), background( window->hbrBackground ), 
			process( window->lpfnWndProc ), menu( window->lpszMenuName ), name( window->lpszClassName ){};

		uint_t style;
		int colors, windows;
		void_t instance, icon, cursor, background, process;
		char_t menu, name;
	};

	struct point_t
	{
		point_t() = default;
		point_t( long x, long y )
			: x( x ), y( y ){};

		long x, y;
	};

	struct msg_t
	{
		msg_t() = default;
		msg_t( void_t i, point_t p, uint_t m, ulong_t t, uint_t w, ulong_t l )
			: window( i ), point( p ), message( m ), time ( t ), w( w ), l( l ){};

		void_t window;
		point_t point;
		uint_t message, w;
		ulong_t time, l;
	};

	void initialize( std::wstring name, void_t instance, uint_t x, uint_t y );
}