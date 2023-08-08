#pragma once

#include "NationSys.h"

typedef enum _eGUARD_SPECIES
{
	GS_ULTIMATE_GUARD_STONE	= 0,
	GS_INNER_GUARD_STONE	= 1,
	GS_GATE					= 2,
	GS_OUTER_GUARD_STONE	= 3,
	GS_MAX_GUARD_SPECIES	= 4,
} eGUARD_SPECIES;

typedef class CGuardInfo : public CGuardStone  
{
public:
	void SendCanNotBrokeBBS(int nType);
	bool IsTargetBroken(LPCHARLIST lpTarget, int nType);
	void SendBrokeBBS(int Team,int Type,int No,LPCHARLIST pTarget);
	INT GetGuardCount(INT nType);
	INT GetAliveGuardCount(INT nType);
	BOOL CheckAndUpdateStatus(LPCHARLIST lpChar);
	BOOL IsAllBroken();
	BOOL CheckTypeAllBroke(INT Type);
	CGuardInfo();
	virtual ~CGuardInfo();
} CGuardInfo, *LPGUARDINFO;
