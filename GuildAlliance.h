#pragma once

const int MAX_SUB_MASTERS = 4;
const int MAX_GUILD_ALLIANCE = 2;
const int ALLIANCE_COST = 1000000;
const int BUILD_ALLIANCE_LEVEL = 40; // CSD-030806
class AllianceMGR
{
public:
    AllianceMGR();
    virtual ~AllianceMGR();
    bool LoadGuildMGRTable();
    static void CheckLevelUp(int cn);


    int GetMaxAllianceExp() { ga_max_exp; };
    static void SetAllianceExp(int exp) { ga_max_exp = exp; };


    int GetMaxNextAllianceExp() { return ga_next_exp; };
    void SetNextAllianceExp(int Nextexp) { ga_next_exp = Nextexp; };

    static int GetExpRate() { ga_exp_rate; };
    static void SetExpRate(int SetRate) { ga_exp_rate = SetRate; };

    static int GetExpBonusRate() { ga_exp_bonus_rate; };
    static void SetExpBonusRate(int bonus) { ga_exp_bonus_rate = bonus; };

protected:
    int Alliancelv;//max 10
    static int ga_max_exp;//if exp for alliance is 1000 to next level
    int ga_next_exp;//if exp_next reached 1001
    static int ga_exp_rate;//how fast you gain exp for alliance
    static int ga_exp_bonus_rate;//how fast you gain exp for alliance



};
class GuildAlliance: public  AllianceMGR
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
        char AllianceName[100];
    }t_del_Alliance;

    typedef struct CreateAlliance {
        
        int guildcode;
        char AllianceName[100];

    }t_Create_Alliance;

    typedef struct AllianceChat {
        char AllianceChat[100];
        char guildname[40];
        int type;

    }t_Alliance_chat;

    typedef struct OfficerChat {
        char AllianceChat[100];
        char guildname[40];
        int type;

    }t_Alliance_chat;
    void MakeOfficers(CHARLIST* Player);

    GuildAlliance();
   // virtual ~GuildAlliance();
    //maybe todo sepecial shop for alliance and maybe stalls for differnt alliance controlled by them??
    static bool LoadAllianceTable();

    bool AllianceLevelUp() { return ga_AllianceLevelup; };//check if alliance leveled up yet
   int  Alliancexp() { return ga_AllianceExp; };//curr exp
    void setAllianceExp(int exp) { ga_AllianceExp = exp; };// we set what exp the alliance gets reece
    void CheckLevelUp(int cn);

   void SetAllianceCode(int code) { ga_alliancecode = code; };
   int GetAllianceCode() { return ga_alliancecode; };

    void setAllianceRank(int rank) { ga_AllianceRank = rank; };
    int GetAllianceRank() { return ga_AllianceRank; };

    void checkforDuplication();
    int getAllianceCode();
    int CreateAllianceCode();

    int getAllianceLevel() { return AllianceLevel;};
    void setAllianceLevel(int level) { AllianceLevel = level; };

   
    
    string AllianceLevelBBS(int cn,string& s);
    void MakeSubMasters(CHARLIST* Player);
    //functions for the packets mapserver to client and viceversa
    void AllianceChat(packet* p);
    void AllianceOfficerChat(packet* p);
    void SendAllianceChat(t_Alliance_chat*p);
    void SendOfficerChat(t_Alliance_chat* p);

public:
    int AllianceLevel;
    bool ga_AllianceLevelup;
protected:
    int ga_AllianceExp;
    

    int ga_guildcode;
    int ga_alliancecode;
    int ga_AllianceRank;
   
  
};

//extern int GetMaxNextAllianceExp();

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
    //todo alliance shop maybe?
    //send back to the client when all is done reece
    void SendDeleteAlliance(packet* p);
    void SendCreateAlliance(packet* p);
protected:
    int ga_npcNo;
    int ga_npcx;
    int ga_npcy;
    char ga_MapName[30];
    int price;
    int nation[3];
};


