#pragma once

int MAX_SUB_MASTERS = 4;
int MAX_GUILD_ALLIANCE = 2;
class GuildAlliance 
{
public:
    enum AllianceRank
    {
        ALLIANCEMASTER = 0,
        ALLIANCEOFFICER = 1,
        NOOB  =3

    };

    enum ALLIANCELOG_TYPE
    {
        CREATEALLIANCE=1,
        DISBANDALLIANCE=2,
        ERROR_CREATING=3,
        ALLIANCECHAT=4,
        RANKUP=5
    };
    //function
    //struct

    typedef struct DelAlliance{
        int AllianceCode;
        int AlliancerRank;
    }t_del_Alliance;

    typedef struct CreateAlliance {
        
        int guildcode;

    }t_Create_Alliance;

    typedef struct AllianceChat {
        char AllianceChat[100];
        char guildname[40];

    }t_Alliance_chat;

    void MakeOfficers(CHARLIST* Player);

    GuildAlliance();
    virtual ~GuildAlliance();
    //maybe todo sepecial shop for alliance and maybe stalls for differnt alliance controlled by them??
    static bool LoadAllianceTable();

    bool AllianceLevelUp() { return AllianceLevelup; };//check if alliance leveled up yet

   static int  Alliancexp() { return AllianceExp; };//curr exp
   static  int setAllianceExp(int exp) { AllianceExp = exp; };// we set what exp the alliance gets reece

    int SetAllianceCode();
  

    int setAllianceRank(int rank) { AllianceRank = rank; };
    int GetAllianceRank() { return AllianceRank; };

    void checkforDuplication();
    int getAllianceCode();
    int CreateAllianceCode();

    int getAllianceLevel() { return AllianceLevel;};
    int setAllianceLevel(int level) { AllianceLevel = level; };

   
    
    string AllianceLevelBBS(int cn,string& s);
    void MakeSubMasters(CHARLIST* Player);
    //functions for the packets mapserver to client and viceversa
    void AllianceChat();
    void AllianceOfficerChat();
protected:
    int AllianceLevel;
    int ga_guildcode;
    int ga_alliancecode;
    int AllianceRank;
    bool AllianceLevelup;
   static  int AllianceExp;
};
class AllianceMGR
{
public:
    AllianceMGR();
   virtual ~AllianceMGR();
   bool LoadGuildMGRTable();
protected:
    int Alliancelv;//max 10
    int max_exp;//if exp for alliance is 1000 to next level
    int next_exp;//if exp_next reached 1001
    int exp_rate;//how fast you gain exp for alliance
};


class GANPC
{
public:
	GANPC();
	~GANPC();
  static  bool LoadAllianceTable();

    //func to createdisband the alliance
    void CreateAlliance(CHARLIST* Player,int guildcode);
    void DisbandAlliance(CHARLIST* Player, int AllianceCode);

    //receive from client reece
    void RecvCreateAlliance(packet* p);
    void RecvDeleteAlliance(packet* p);

    //send back to the client when all is done reece
    void SendDeleteAlliance(packet* p);
    void SendCreateAlliance(packet* p);
protected:
    int g_npcNo;
    int ga_npcx;
    int ga_npcy;
    char ga_MapName[30];
};


