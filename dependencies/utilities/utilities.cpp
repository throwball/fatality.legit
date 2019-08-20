#include "utilities.hpp"
#include "../common_includes.hpp"
#include <psapi.h>

std::uint8_t* utilities::pattern_scan( void* module, const char* signature ) {
	static auto pattern_to_byte = [ ] ( const char* pattern ) {
		auto bytes = std::vector<int> {};
		auto start = const_cast< char* >( pattern );
		auto end = const_cast< char* >( pattern ) + strlen( pattern );

		for ( auto current = start; current < end; ++current ) {
			if ( *current == '?' ) {
				++current;
				if ( *current == '?' )
					++current;
				bytes.push_back( -1 );
			}
			else {
				bytes.push_back( strtoul( current, &current, 16 ) );
			}
		}
		return bytes;
	};

	auto dos_headers = ( PIMAGE_DOS_HEADER ) module;
	auto nt_headers = ( PIMAGE_NT_HEADERS ) ( ( std::uint8_t* )module + dos_headers->e_lfanew );

	auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte( signature );
	auto scan_bytes = reinterpret_cast< std::uint8_t* >( module );

	auto s = pattern_bytes.size( );
	auto d = pattern_bytes.data( );

	for ( auto i = 0ul; i < size_of_image - s; ++i ) {
		bool found = true;
		for ( auto j = 0ul; j < s; ++j ) {
			if (scan_bytes[ i + j ] != d [ j ] && d [ j ] != -1 ) {
				found = false;
				break;
			}
		}
		if ( found ) {
			return &scan_bytes[ i ];
		}
	}
	return nullptr;
}

void* utilities::game::capture_interface( const char* mod, const char* iface ) {
	using fn_capture_iface_t = void*( *)( const char*, int* );
	auto fn_addr = ( fn_capture_iface_t ) GetProcAddress( GetModuleHandleA( mod ), "CreateInterface" );

	auto iface_addr = fn_addr( iface, nullptr );
	printf( "found %s at 0x%p\n", iface, fn_addr( iface, nullptr ) );

	return iface_addr;
}

void utilities::material_setup() {
	std::ofstream("csgo/materials/fatality_material.vmt") << R"#("VertexLitGeneric" {
            "$basetexture" "vgui/white_additive"
            "$ignorez"      "0"
            "$envmap"       ""
            "$nofog"        "1"
            "$model"        "1"
            "$nocull"       "0"
            "$selfillum"    "1"
            "$halflambert"  "1"
            "$znearer"      "0"
            "$flat"         "0"
			"$phong"		"1"
			"$rimlight"		"1"
        })#";

	std::ofstream("csgo/materials/fatality_reflective.vmt") << R"#("VertexLitGeneric" {
			"$basetexture" "vgui/white_additive"
			"$ignorez" "0"
			"$envmap" "env_cubemap"
			"$normalmapalphaenvmapmask" "1"
			"$envmapcontrast"  "1"
			"$nofog" "1"
			"$model" "1"
			"$nocull" "0"
			"$selfillum" "1"
			"$halflambert" "1"
			"$znearer" "0"
			"$flat" "1"
		})#";
}