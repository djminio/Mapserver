#include"StdAfx.h"
#include "GuildAlliance.h"
GuildAlliance gc_alliance;
GANPC::GANPC()
{
    ga_npcNo = -1;
    ga_npcx = 0;
    ga_npcy = 0;
    ga_MapName[29]=0;
    price=0;
    nation[2]=0;
}

GANPC::~GANPC()
{
}

GuildAlliance::GuildAlliance()
{
    this->AllianceLevel=0;
    this->ga_guildcode=0;
    this->ga_alliancecode=0;
    this->ga_AllianceRank=0;
    this->ga_AllianceLevelup=0;
    this->ga_AllianceExp=0;
}




AllianceMGR::AllianceMGR()
{
}

AllianceMGR::~AllianceMGR()
{
}


void AllianceMGR::CheckLevelUp(int cn)
{
    if (cn == NULL) return;
    
    int currentexp = gc_alliance.Alliancexp();
    int NextExp = gc_alliance.GetMaxNextAllianceExp();
    //int expbonus= GetExpBonusRate();
    /*int exp= GuildAlliance::Alliancexp();*/

    /*int bonus= currentexp* expbonus;*/
    if (currentexp<NextExp)return;

    //todo need to check Alliance if statement charlist for player
    if (currentexp >= NextExp)
    {
     
        gc_alliance.AllianceLevel++;
       gc_alliance.ga_AllianceLevelup = true;

        //to do updatetodbeamon
        // 
        // //todo send bbs to all members in the alliance when alliance has leveled up
        //add log
        
    }
   gc_alliance.ga_AllianceLevelup = false;
    return;
}
