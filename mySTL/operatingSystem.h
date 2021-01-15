#pragma once
#if (__GNUC__==4 && __GNUC_MINOR__==8 && __GNUC_PATCHLEVEL__==5)
#define SYSTEM 1
#elif (__GNUC__==4 && __GNUC_MINOR__==9 && __GNUC_PATCHLEVEL__==2)
	printf("DevCPP\n");
#define SYSTEM 2
#elif (__GNUC__==5 && __GNUC_MINOR__==1 && __GNUC_PATCHLEVEL__==0)
#define SYSTEM 3
#elif (_MSC_VER)
#define SYSTEM 0
#endif
