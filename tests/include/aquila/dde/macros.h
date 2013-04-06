/**
 * ============================================================================
 * 2011/07/19
 * $Id: macros.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * Вспомогательные макросы и функции.
 * ============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace aquila {
	namespace dde {

MATCHER_P2(IsString, /*HSZ*/ hsz, /*int*/codePage, "") { \
	if ( hsz == NULL ) { return arg == NULL; } \
	return arg->getHandle() == hsz && arg->getCodePage() == codePage; \
}

MATCHER_P(IsConversation, /*HCONV*/ hConv, "") { \
	if ( hConv == NULL ) { return arg == NULL; } \
	return arg->getHandle() == hConv; \
}

MATCHER_P(IsData, /*HDDEDATA*/ hData, "") { \
	if ( hData == NULL ) { return arg == NULL; } \
	return arg->getHandle() == hData; \
}

MATCHER_P2(IsBinaryEq, ptr, length, "") { \
	return memcmp(ptr, arg, length) == 0; \
}


	} // end namespace dde
} // end namespace aquila