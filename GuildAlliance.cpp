#include"StdAfx.h"
#include "GuildAlliance.h"

GANPC::GANPC()
{
    g_npcNo = -1;
    ga_npcx = 0;
    ga_npcy = 0;

}

GANPC::~GANPC()
{
}

GuildAlliance::GuildAlliance()
{
     this->AllianceLevel=0;
     this->ga_guildcode=0;
     this->ga_alliancecode=0;
     this->AllianceLevelup=false;
     this->AllianceExp=0;
}


AllianceMGR::AllianceMGR()
{
}

AllianceMGR::~AllianceMGR()
{
}