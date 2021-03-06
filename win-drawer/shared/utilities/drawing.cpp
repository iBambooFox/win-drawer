#include "../shared.hpp"

namespace drawing
{
	uint_t size[ 2 ];

	void style( void_t window, paint_t paint )
	{
		const auto context = static_cast< HDC >( paint.hdc );
		
		RECT rect;
		RECT text;

		rect.left = 5;
		rect.top = 5;
		
		rect.right = drawing::size[ 0 ] - 5;
		rect.bottom = drawing::size[ 1 ] - 5;

		text.left = 25;
		text.top = 25;

		auto screen_color = RGB( 30, 30, 30 );
		auto text_color = RGB( 100, 100, 100 );

		::FillRect( context, &rect, CreateSolidBrush( screen_color ) );

		::SetTextColor( context, COLORREF( text_color ) );
		::SetBkMode( context, TRANSPARENT );

		::DrawTextW( context, L">> ANIWARE <<", -1, &rect, DT_CENTER );
	}

	void content( void_t window, paint_t paint )
	{
		const auto context = static_cast< HDC >( paint.hdc );
		const auto margin = 1;

		RECT label;
		RECT indent;

		label.left = 50;
		label.top = 50;
		label.right = 150;
		label.bottom = 70;

		indent.left = label.left + margin;
		indent.top = label.top + margin;
		indent.right = label.right - margin;
		indent.bottom = label.bottom - margin;

		auto label_color = RGB( 60, 60, 60 );
		auto indent_color = RGB( 45, 45, 45 );
		auto text_color = RGB( 80, 80, 80 );

		::FillRect( context, &label, CreateSolidBrush( label_color ) );
		::FillRect( context, &indent, CreateSolidBrush( indent_color ) );

		::SetTextColor( context, COLORREF( text_color ) );
		::SetBkMode( context, TRANSPARENT );

		::DrawTextW( context, L"button", -1, &indent, DT_CENTER );
	}

	void initialize( void_t window, paint_t& paint, uint_t size[ 2 ] )
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

		drawing::size[ 0 ] = size[ 0 ];
		drawing::size[ 1 ] = size[ 1 ];

		if ( paint.hdc = static_cast< void_t >( ::BeginPaint( static_cast< HWND >( window ), &translate( &paint ) ) ) )
		{
			style( window, paint );
			content( window, paint );
		}

		::EndPaint( static_cast< HWND >( window ), &translate( &paint ) );
	}
}