#include "../shared.hpp"

namespace window
{
	ulong_t procedure( void_t window, uint_t msg, PARAMS )
	{
		drawing::paint_t paint{};

		switch( msg )
		{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		case WM_PAINT:
			drawing::initialize( window, paint );
			break;
		default:
			return ::DefWindowProcW( static_cast< HWND >( window ), msg, w, l );
			break;
		}

		return 1ul;
	}

	ulong_t classes( void_t instance, window_t* window, std::wstring name )
	{
		const auto translate = [&]( const window_t* window )
		{
			WNDCLASSW ret;

			ret.style = window->style;
			ret.cbClsExtra = window->colors;
			ret.cbWndExtra = window->windows;

			ret.hInstance = static_cast< HINSTANCE >( window->instance );
			ret.hIcon = static_cast< HICON >( window->icon );
			ret.hCursor = static_cast< HCURSOR >( window->cursor );
			ret.hbrBackground = static_cast< HBRUSH >( window->background );
			ret.lpfnWndProc = static_cast< WNDPROC >( window->process );

			ret.lpszMenuName = window->menu;
			ret.lpszClassName = window->name;
			
			return ret;
		};

		window->background = CreateSolidBrush( RGB( 25, 25, 25 ) );
		window->cursor = LoadCursorA( nullptr, IDC_ARROW );
		window->instance = instance;
		window->name = name.c_str();
		window->process = procedure;

		return ::RegisterClassW( &translate( window ) );
	}

	void message( msg_t msg )
	{
		const auto translate = [&]( const msg_t* msg )
		{
			MSG ret;

			ret.hwnd = static_cast< HWND >( msg->window );
			ret.pt = POINT{ msg->point.x, msg->point.y };

			ret.message = msg->message;
			ret.time = msg->time;

			ret.wParam = msg->w;
			ret.lParam = msg->l;
			
			return ret;
		};

		auto message = translate( &msg );

		while ( ::GetMessageA( &message, 0, 0, 0 ) )
		{
			::TranslateMessage( &message );
			::DispatchMessageA( &message );
		}
	}
	
	void initialize( std::wstring name, void_t instance, uint_t x, uint_t y )
	{ 
		Gdiplus::GdiplusStartupInput input;

		msg_t message{};
		window_t window{};
	
		ulong_t token;

		if ( !Gdiplus::GdiplusStartup( &token, &input, nullptr ) )
			return;

		if ( window::classes( instance, &window, L"Windrawer" ) )
		{
			if ( ::CreateWindowW( L"Windrawer", name.c_str(), ( WS_OVERLAPPEDWINDOW | WS_VISIBLE ), 0, 0, x, y, 0, 0, 0, 0 ) )
			{
				window::message( message );
			}
		}

		Gdiplus::GdiplusShutdown( token );
	}
}