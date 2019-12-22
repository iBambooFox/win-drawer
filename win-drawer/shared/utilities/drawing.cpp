#include "../shared.hpp"

namespace drawing
{
	void initialize( void_t window, paint_t& paint )
	{
		const auto translate = [&]( const paint_t* paint )
		{
			PAINTSTRUCT ret;

			ret.hdc = static_cast< HDC >( paint->hdc );
			
			ret.fErase = paint->erase;
			ret.fRestore = paint->restore;
			ret.fIncUpdate = paint->update;

			ret.rcPaint = {
				paint->size.left,
				paint->size.top,
				paint->size.right,
				paint->size.bottom,
			};

			return ret;
		};

		paint.hdc = static_cast< void_t >( ::BeginPaint( static_cast< HWND >( window ), &translate( &paint ) ) );

		/*
		
		paint routine
		
		*/
		
		::EndPaint( static_cast< HWND >( window ), &translate( &paint ) );
	}
}